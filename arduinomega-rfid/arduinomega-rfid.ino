//=================================================
//                 Pins Connection
//
//      Mega                         RFID-RC522
//
//       53                             SDA(SS)
//       52                             SCK
//       51                             MOSI
//       50                             MISO
//       -                              IRQ
//       GND                            GND
//       5                              RST
//       3V3                            3.V3
//
//=================================================

//  RFID libs
#include <SPI.h>
#include <MFRC522.h>

//  Define SDA(SS) and RST pins
#define SS_PIN 53
#define RST_PIN 5

//  Init RFID
MFRC522 rfid(SS_PIN, RST_PIN);

String data;

void setup() {

  Serial.begin(9600);

  //  Begin RFID
  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {

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

  //  Blink (not required)
  blinkL();

  //  ===============================================
  //  Here you can do anything with rfid(in var data)

}

//  Blink function
void blinkL() {

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

}


