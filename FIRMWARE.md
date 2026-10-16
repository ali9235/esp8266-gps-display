# Atlas reference firmware

This is newly written reference code, not the original photographed program. Nothing has been flashed or tested with the physical receiver/display. The default builds without configuring any GPIO or enabling either peripheral.

## Build on Windows

1. Install Arduino IDE/CLI and the ESP8266 board core. The software reference target is **NodeMCU 1.0 / `esp8266:esp8266:nodemcuv2`**, not a verified identification of the exact LoLin board revision.
2. Install **TinyGPSPlus by Mikal Hart**. The local verification uses version 1.0.3; similarly named ESP32 forks and example sketches are not this project's original code.
3. To compile the optional TFT path, install Adafruit GFX Library, Adafruit ST7735 and ST7789 Library, and Adafruit BusIO. The black-tab ST7735 profile is a new reference choice; the photographed panel's controller must be identified first.
4. Open `firmware/gps_display/gps_display.ino`, select the reference target and **verify/compile**. Compilation does not upload code or demonstrate hardware operation.

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 firmware/gps_display
```

## Default: local NMEA replay, no receiver pins

Both adapters are disabled. The sketch parses text received over USB serial at 115200 baud, identifies itself as **USB NMEA REPLAY**, and reports status once per second. It does not manufacture a location, transmit coordinates over a network, or configure a physical receiver. A default build is not a desktop simulator and still needs a compatible board to run; host-only state tests can run without it.

If using a USB-connected test board later, send complete checksum-bearing NMEA sentences with their line endings. Use synthetic data for a public demo; replay is never evidence of satellite reception. No upload or replay on a physical board was performed during this implementation.

## Data integrity policy

TinyGPSPlus parses NMEA fields. Status is `NO DATA` before bytes arrive, `WAITING FOR POSITION` without a valid location, `RECENT POSITION` for a valid location no older than 5 seconds while bytes are recent, or `DATA / POSITION STALE` after a 2-second input gap or an older location. These are configurable reference freshness policies—not accuracy specifications or proof of a continuously valid fix. Arbitrary received bytes alone are not a valid GPS position.

The optional screen suppresses stale coordinates and independently checks time, satellite count, altitude and speed freshness. Six decimal places are display formatting, not a precision claim. Byte processing is limited to 96 per loop and rendering is requested every 200 ms; actual timing/throughput and TFT performance need hardware measurement.

## Enable real peripherals only after identification

Complete [the connection checklist](WIRING_AND_SOURCE.md). Set the actual `GPS_RX_PIN`, `GPS_BAUD` and `GPS_INTERFACE_VERIFIED`, then enable `ENABLE_GPS_INPUT`. This is a receive-only SoftwareSerial adapter; it does not send receiver configuration commands. Confirm serial format and data rate before using the reference path.

For the TFT, establish the controller/profile, actual SPI and control/reset connections, voltage and boot-pin constraints; set `TFT_CS`, `TFT_DC`, `TFT_RST`, `TFT_MODEL_VERIFIED` and `ENABLE_TFT`. Compiler guards reject unset pins and specific conflicts but do not prove electrical correctness. No compiler fixture is a wiring recommendation.

## Host state checks

With an MSVC Developer Command Prompt:

```bat
cl /nologo /EHsc /std:c++17 /W4 /WX tests\test_core.cpp /Fe:atlas-tests.exe
atlas-tests.exe
```

The tests cover classification, freshness boundaries, missing location, stream loss and unsigned timer rollover. They do not test RF reception, NMEA parser internals, UART wiring, power, antenna, display hardware or GPS accuracy. See [actual build status](BUILD_STATUS.md).

Dependencies: [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus), [ESP8266 Arduino core](https://github.com/esp8266/Arduino), [Adafruit ST7735 library](https://github.com/adafruit/Adafruit-ST7735-Library). Their own licenses apply; no dependency code is copied into this repository. No project-wide license has been selected.
