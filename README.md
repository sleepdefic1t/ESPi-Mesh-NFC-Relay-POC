# ESPi-Mesh-NFC-Relay-POC

proof of concept
only intended for testing

-----

### Parts
| module | url |
|:--- |:--- |
| | |
| | |
| 1x **Raspberry Pi Zero W** | https://www.adafruit.com/product/3400 |
| | |
| 1x **Adafruit: HUZZAH ESP8266 Breakout** | https://www.adafruit.com/product/2471 |
| | |
| 2x **Adafruit: Feather Huzzah 8266** | https://www.adafruit.com/product/2821 |
| | |
| 1x **Adafruit: PN532 NFC/RFID Breakout Board** | https://www.adafruit.com/product/364 |
| | |
| 1x **Adafruit: Power Relay FeatherWing** | https://www.adafruit.com/product/3191 |
| | |


### Required Pi Software

| os image | url |
|:--- |:--- |
| | |
| **Ark: IoT Core Image for Raspberry Pi** | https://github.com/Ark-IoT/ark-iot-core-image/releases |
| or | |
| **RASPBIAN STRETCH LITE** | https://www.raspberrypi.org/downloads/raspbian/ |
| | |

#

| linux libraries | url |
|:--- |:--- |
| | |
| **Minicom** * | https://help.ubuntu.com/community/Minicom |
- `ssh` to Pi 
- `sudo minicom -b 115200 -o -D /dev/serial0
 
-----

### Required Arduino IDE libs
Place the following libraries in `~/Documents/Arduino/libraries/`:

| library | repo |
|:--- |:--- |
| | |
| **Dons NDEF Library** | https://github.com/don/NDEF |
| | |
| **SeedStudio: PN532** * | https://github.com/Seeed-Studio/PN532 |
| | |

> \* replace `PN532/emulatetag.h` & `PN532/emulatetag.cpp` with the matching`emulatetag.x` files in this repo.  
      You can backup those files, or overwrite them if necessary. 

-----

### Wiring

#### Pi-Node

|  Pi Wiring  |    8266 Breakout Wiring    |
| :----------: | :---------: |
|<table> <tr><th>Wire</th> <th>Pin</th> <th>Color</th></tr>  <tr><td>3.3V</td> <td>1</td> <td>Red</td></tr> <tr><td>GND</td><td>6</td><td>Black</td> </tr> <tr><td>TX</td> <td>14</td> <td>Blue</td></tr>  <tr><td>RX</td> <td>15</td> <td>Green</td></tr> </table> | <table> <tr><th>Pi Pin</th> <th>Wire</th> <th>Pin</th> <th>Color</th></tr>  <tr><td>1</td> <td>V+</td><td>V+</td> <td>Red</td></tr> <tr><td>6</td> <td>GND</td> <td>GND</td> <td>Black</td> </tr> <tr><td>1</td> <td>V+</td><td>V+</td> <td>Red</td></tr>  <tr><td>14(RX)</td> <td>TX</td> <td>TX</td> <td>Green</td>  <tr><td>15(TX)</td> <td>RX</td> <td>RX</td> <td>Blue</td></tr>  <tr><td>1(3.3V)</td> <td>NFC-Button</td> <td>14</td> <td>Red>Btn>Yellow</td>  <tr><td>1(3.3V)</td> <td>Relay-Test-Button</td> <td>12</td> <td>Red>Btn>White</td>  </table> |

#### NFC-Node

|  Feather Huzzah 8266 Wiring  |    PN532 Breakout Wiring    |
| :----------: | :---------: |
|<table> <tr><th>Wire</th> <th>Pin</th> <th>Color</th></tr>  <tr><td>3.3V</td> <td>--</td> <td>Red</td></tr> <tr><td>GND</td><td>--</td><td>Black</td> </tr> <tr><td>MISO</td> <td>12</td> <td>Blue</td></tr>  <tr><td>MOSI</td> <td>13</td> <td>Green</td> </tr> <tr><td>SCK</td> <td>14</td> <td>Orange</td> <tr><td>SCL</td> <td>5</td> <td>Yellow</td> </tr>  </tr> </table> | <table> <tr><th>8266 Pin</th> <th>Pin</th> <th>Color</th></tr>  <tr><td>3.3V</td> <td>3.3V</td> <td>Red</td></tr> <tr><td>GND</td> <td>GND</td> <td>Black</td></tr> <tr><td>SCL(5)</td> <td>SSEL/SCL/RX</td> <td>Yellow</td> </tr> <tr><td>MOSI(12)</td> <td>MOSI</td> <td>Blue</td>  <tr><td>MISO(13)</td> <td>MISO/SDA/TX</td> <td>Green</td> <tr><td>SCK(14)</td> <td>SCK</td> <td>Orange</td> </table> |

#### Relay-Node

|  Feather Huzzah 8266 Wiring  |    Power Relay Wiring    |
| :----------: | :---------: |
|<table> <tr><th>Wire</th> <th>Pin</th></tr>  <tr><td>3.3V</td> <td>3.3V</td></tr> <tr><td>GND</td> <td>GND</td></tr> <tr><td>Signal</td> <td>15</td> </tr> </table> | <table> <tr><th>Wire</th> <th>Pin</th></tr>  <tr><td>3.3V</td> <td>3.3V</td></tr> <tr><td>GND</td> <td>GND</td></tr> <tr><td>Signal</td> <td>15</td> </tr> </table> |
