# NodeMCU + RFID-RC522

Sending rfid using post request to url.

#### Required:
- NodeMCU (NodeMCUcp2102 recommended)
- RFID-RC522
- RFID card / chip

#### ArduinoIDE libs:
- SPI.h
- MFRC522.h
- ESP8266WiFi.h
- WiFiClient.h
- ESP8266HTTPClient.h

#### Connection:
| RFID-RC522 | NodeMCU |
| ------- | ---------- |
| SDA(SS) | D2 | 
| SCK | D5 |
| MOSI | D7 |
| MISO | D6 |
| IRQ | - |
| GND | GND |
| RST | D1 |
| 3.V3 | 3V3 |

#### Functions:
Send RFID using POST:
```sh
$ http.POST(data):
```

Get RFID on site using php:
```sh
$ $rfid = file_get_contents('php://input');
```
