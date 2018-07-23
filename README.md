# RFID-RC522 + Arduino Mega / NodeMCU

Working with rfid

#### Required:
- Board:
  - NodeMCU (NodeMCU cp2102 recommended)
  - Arduino Mega 2560
- RFID-RC522
- RFID card / chip

#### ArduinoIDE libs:
- RFID-RC522:
  - SPI.h
  - MFRC522.h
- NodeMCU:
  - ESP8266WiFi.h
  - WiFiClient.h
  - ESP8266HTTPClient.h

#### Connection:
| RFID-RC522 | NodeMCU | Arduino Mega 2560 |
| ---------- | ------- | ----------------- |
| SDA(SS) | D2 | 53 |
| SCK | D5 | 52 |
| MOSI | D7 | 51 |
| MISO | D6 | 50 |
| IRQ | - | - |
| GND | GND | GND |
| RST | D1 | 5 |
| 3.V3 | 3V3 | 3V3 |

#### Functions:
Send RFID using POST:
```sh
$ http.POST(data):
```

Get RFID on site using php:
```sh
$ $rfid = file_get_contents('php://input');
```
