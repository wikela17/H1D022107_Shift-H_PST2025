#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Belilah kuota";
const char* password = "pusingkuotaabis123";
int LED1 = D0;
int LED2 = D1;
int LED3 = D4;

ESP8266WebServer Server(80);

String webpage;

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.println();
  Serial.print("Configuring acsess point,,,");

  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);

  Serial.print("Access Point SSID: ");
  Serial.println(WiFi.softAPSSID());

  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());

  webpage+= "<h1> Web Control ESP8266</h1>";
  webpage+= "<h2> Wike Laelatunuji </h2>";
  webpage+= "<p>LED 1 : ";
  webpage+= "<a href=\"LED1ON\"\"><button>ON</button></a><a href=\"LED1OFF\"\"><button>OFF</button></a></p><br>";
  webpage+= "<p>LED 2 : ";
  webpage+= "<a href=\"LED2ON\"\"><button>ON</button></a><a href=\"LED2OFF\"\"><button>OFF</button></a></p><br>";
  webpage+= "<p>LED 3 : ";
  webpage+= "<a href=\"LED3ON\"\"><button>ON</button></a><a href=\"LED3OFF\"\"><button>OFF</button></a></p>";

  Server.on("/", []() {
    Server.send(200, "text/html", webpage);
  });

  Server.on("/LED1ON", []() {
    Server.send(200, "text/html", webpage);
    digitalWrite(LED1, HIGH);
    delay(1000);
  });

  Server.on("/LED2ON", []() {
    Server.send(200, "text/html", webpage);
    digitalWrite(LED2, HIGH);
    delay(1000);
  });

  Server.on("/LED3ON", []() {
    Server.send(200, "text/html", webpage);
    digitalWrite(LED3, HIGH);
    delay(1000);
  });

  Server.on("/LED1OFF", []() {
    Server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
    delay(1000);
  });

  Server.on("/LED2OFF", []() {
    Server.send(200, "text/html", webpage);
    digitalWrite(LED2, LOW);
    delay(1000);
  });

  Server.on("/LED3OFF", []() {
    Server.send(200, "text/html", webpage);
    digitalWrite(LED3, LOW);
    delay(1000);
  });

  Server.begin();
  Serial.println("Webserver dijalankan");

}

void loop() {
  Server.handleClient();
}