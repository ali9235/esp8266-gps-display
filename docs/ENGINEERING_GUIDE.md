# Atlas: explain the receiver-to-screen path

The actual photographs show a powered screen waiting for a fix. The original matching sketch was not located. This walkthrough follows the **new reference firmware** and does not claim satellite acquisition or measured accuracy.

## Identify the hardware, not assumptions

| Visible element | Typical role | Still to establish |
| --- | --- | --- |
| Receiver breakout | Provide navigation data from satellite reception | Exact model, serial format, ratings and actual fix |
| Cabled antenna | Supply the receiver's RF input | Antenna type, compatibility and placement |
| LoLin ESP8266 board | Parse incoming data and control presentation | Exact revision and traced pin map |
| 1.8-inch / 128×160-labelled TFT | Display status/data | Controller IC, profile and wiring |
| USB, breadboard and jumpers | USB link and prototype connections | Full power/signal arrangement |

The reference uses a receive-only serial adapter and an optional SPI display adapter. That is a **software design**, not a recovered wiring diagram. No Wi-Fi transmission is implemented. The owner has not documented the original component-selection reasoning; do not invent it.

## Follow the actual functions

| Source | Names | Meaning |
| --- | --- | --- |
| [config.h](../firmware/gps_display/config.h) | `ENABLE_GPS_INPUT`, `ENABLE_TFT`, GPIO guards | Both peripherals remain disabled/unset until identified |
| [gps_display.ino](../firmware/gps_display/gps_display.ino) | `loop`, `gps.encode` | Up to 96 input bytes per loop are sent to TinyGPSPlus |
| [gps_display.ino](../firmware/gps_display/gps_display.ino) | `currentState` | Location validity, finite values and coordinate bounds |
| [status.h](../firmware/gps_display/status.h) | `classify`, `due` | Freshness policy and unsigned timer checks |
| [gps_display.ino](../firmware/gps_display/gps_display.ino) | `render`, `recent` | Suppress stale location and independently check other fields |

## Four states, with exact boundaries

- **NO DATA:** no bytes have arrived.
- **WAITING FOR POSITION:** bytes are recent but location is invalid. Arbitrary input is not a position.
- **RECENT POSITION:** location is valid and at most 5000 ms old; the most recent byte is at most 2000 ms old.
- **DATA / POSITION STALE:** the byte gap exceeds 2000 ms, or a valid position is older than 5000 ms.

The byte-age test precedes the position-validity test. Rendering is requested every 200 ms, while serial reports are requested every 1000 ms. Those intervals are code policies, not measured throughput. Six displayed decimal places do not prove six-decimal accuracy.

## Compile without contacting a receiver

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 firmware/gps_display
```

Use the dependency versions in [FIRMWARE.md](../FIRMWARE.md). On 16 October 2026 both default and private adapter-only builds passed again. Native state tests were **not rerun** because of the recorded Windows Device Guard execution restriction; the earlier 17-check pass remains historical evidence. No bypass, flash, RF test or physical replay was performed.

Default input is **USB NMEA replay**, not a desktop simulator and not live GPS. If intentionally run later on a verified board, label replay data visibly and use non-sensitive synthetic or sanitized data. Never publish home coordinates, private routes or raw personal receiver logs.

## Exercises before a presentation

- Explain why a recent serial byte is weaker evidence than a checksum-valid location field.
- Trace the tests at 2000/2001 ms and 5000/5001 ms. Predict a state before reading the assertion.
- In a software-only branch, test a changed freshness policy or add boundary cases. Do not enable peripherals or bypass OS execution policy.
- Explain why `SoftwareSerial receiver(GPS_RX_PIN, -1)` is receive-only and does not configure the module.

| Observation | Investigate first |
| --- | --- |
| NO DATA | Input path, source mode, verified serial settings and wiring |
| Bytes but no position | Parser/checksum failures, invalid/no-fix receiver messages; data flow alone is insufficient |
| Repeated stale state | Byte gaps and location age, not assumed RF accuracy |
| Blank TFT | Actual driver/profile, electrical compatibility and traced connections |
| Fresh coordinates in replay | Software parsing only; not satellite reception or an accuracy measurement |

See the [real demonstration plan](DEMO_TEST_PLAN.md). Describe your own assembly work and distinguish new assisted reference code from original physical operation.
