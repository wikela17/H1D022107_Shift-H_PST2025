#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


const int trigPin = D5;  
const int echoPin = D6;  
const int sdaPin  = D2;  
const int sclPin  = D1;  


LiquidCrystal_I2C lcd(0x27, 16, 2);


long bacaJarakCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long durasi = pulseIn(echoPin, HIGH, 25000); // timeout 25ms
  long jarak = durasi * 0.034 / 2;

  return jarak;
}

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  
  Wire.begin(sdaPin, sclPin);

  
  lcd.init();
  lcd.backlight();

 
  lcd.setCursor(0, 0);
  lcd.print("S.H.I.E.L.D SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("Mengaktifkan...");
  delay(2000);
}

void loop() {
  long total = 0;
  const int jumlahPembacaan = 5;

  for (int i = 0; i < jumlahPembacaan; i++) {
    total += bacaJarakCM();
    delay(50); 
  }

  long jarak = total / jumlahPembacaan;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(jarak);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  if (jarak < 100) {
    lcd.print("AREA BERBAHAYA");
  } else {
    lcd.print("AMAN");
  }

  delay(300); 
}