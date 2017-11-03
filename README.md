# ESPi-Mesh-NFC-Relay-POC

proof of concept
only intended for testing

-----

### required Arduino IDE libs

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
