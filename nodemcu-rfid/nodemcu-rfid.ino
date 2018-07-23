#include <GDBStub.h>

//=================================================
//
//  To program NodeMCU you must select board "NodeMCU 1.0(ESP-Module)"
//  If you don have install it on board manager  
//
//=================================================

//  Wifi config
#define WIFI_NAME "name"
#define WIFI_PASS "password"

//  Send RFID to this url
#define LINK "http://example.com/test.php"

//=================================================
//                 Pins Connection
//
//    NodeMCU                         RFID-RC522
//
//       D2                             SDA(SS)
//       D5                             SCK
//       D7                             MOSI
//       D6                             MISO
//       -                              IRQ
//       GND                            GND
//       D1                             RST
//       3V3                            3.V3
//
//=================================================

//  RFID libs
#include <SPI.h>
#include <MFRC522.h>

//  Define SDA(SS) and RST pins
#define SS_PIN D2
#define RST_PIN D1

//  NodeMCU libs
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

//  Init RFID
MFRC522 rfid(SS_PIN, RST_PIN);

String data;

//  Init WiFiServer
WiFiServer server(80);

//  Init HttpClient
HTTPClient http;

void setup() {

  //  Begin serial with 115200 (Required!)
  Serial.begin(115200);

  //  Begin RFID
  SPI.begin();
  rfid.PCD_Init();

  //  Log wifi info
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //  Start wifi
  WiFi.begin(WIFI_NAME, WIFI_PASS);

  //  Waiting for connection
  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  server.begin();
  delay(100);

  digitalWrite(LED_BUILTIN, HIGH);

  //  Configure http
  http.begin(LINK);
  http.addHeader("Content-Type", "text/plain");

}

void loop() {

  //  Check connection
  if (WiFi.status() == WL_CONNECTED) {

    digitalWrite(LED_BUILTIN, HIGH);

    //  Get rfid else return
    if ( ! rfid.PICC_IsNewCardPresent())
      return;
    if ( ! rfid.PICC_ReadCardSerial())
      return;

    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
        piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
      return;
    }

    for (byte i = 0; i < 4; i++) {
      data += (String)rfid.uid.uidByte[i];
    }
    
    //    RFID in data
    Serial.println(data);

    //  Send data to url
    int httpCode = http.POST(data);
    if (httpCode == -2) {
      httpCode = http.POST(data);
    }

//  Blink if OK (not required)
    if (httpCode == 200) {
      blinkL();
    }

    data = "";

    //  Reset RFID to next read
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

  } else {

    digitalWrite(LED_BUILTIN, LOW);

  }

}

//  Blink function
void blinkL() {

  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);

}

