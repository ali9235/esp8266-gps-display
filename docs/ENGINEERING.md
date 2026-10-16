# Atlas — engineering notes

## Two things this repository keeps separate

The photographs document a real receiver/controller/display assembly and a waiting-for-fix screen. The source documents a **new reference implementation**. Neither is used to claim that the other has already been physically demonstrated. Original firmware, actual GPIO mapping and a measured acquisition result remain missing.

## The reference data path

1. **Input:** a receive-only SoftwareSerial adapter when explicitly enabled; otherwise the USB serial input is labelled replay mode. The program sends no configuration commands to the receiver.
2. **Parsing:** each received byte is passed to TinyGPSPlus. The USB report includes the parser's checksum-failure counter. Traffic is not itself a valid position.
3. **Policy:** coordinates must be parser-valid, finite and inside latitude/longitude bounds. Input age and position age then select the application's status.
4. **Presentation:** coordinates appear only for `RecentPosition`. Altitude, speed, UTC and satellite count have their own validity/freshness checks. Stale coordinates are not shown as current.

Source: [gps_display.ino](../firmware/gps_display/gps_display.ino) · [state classifier](../firmware/gps_display/status.h).

[Compact three-stage overview](../media/overview.svg) · [Full architecture](../media/engineering-map.svg) · [Exact decision branches](../media/state-flow.svg)

## What each state actually means

| State | Conditions, in evaluation order | Meaning |
| --- | --- | --- |
| `NoData` | No byte has been received | No input observed; this is not a satellite verdict |
| `Stale` | Bytes were seen, but the latest byte is older than 2,000 ms | Input has stopped being recent |
| `Waiting` | Bytes are recent, but coordinates fail validity/bounds checks | There is no acceptable position to present |
| `RecentPosition` | Coordinates are valid and no older than 5,000 ms, while bytes are recent | A recently updated position is available |
| `Stale` | Coordinates are valid, but older than 5,000 ms | The cached position must not be presented as current |

The diagram follows these branches, not a mandatory sequence. Input may move directly from no data to a recent position. Recent bytes can be malformed or non-position data; the parser and coordinate checks still matter. `RecentPosition` is deliberately **not** named “continuous live fix”: the application has no independently verified RF-quality or fix-continuity measurement.

## Why freshness is separate from numeric formatting

The optional screen prints coordinates with six decimal places. That controls appearance, not accuracy. A cached coordinate can remain numerically plausible after reception stops; the application uses age and input gaps to prevent that value from silently masquerading as current information. The 2-second / 5-second limits are reference design policies and need tuning against the receiver's real output rate.

## Cooperative work, not a claimed frame rate

The loop consumes at most 96 available bytes before returning to other work and requesting a display refresh every 200 ms. Periodic USB reports are requested every second. `yield()` returns control to the ESP8266 core. These limits make the intended scheduling inspectable; they do not prove serial throughput, display frame rate or absence of data loss at a particular receiver baud.

Timing uses unsigned subtraction. The state tests exercise refresh-boundary behavior and timer rollover. Long parser/driver execution, buffer overflow under load and physical timing still need bench testing.

## Hardware adapters stay explicit

The default configuration disables GPS input and TFT output and leaves pins unset. Guards reject unset settings, selected flash/UART/SPI conflicts and duplicate display-control pins. They do not verify voltages, a board's boot behavior, wiring continuity or panel identity. `GPS_INTERFACE_VERIFIED` and `TFT_MODEL_VERIFIED` are user acknowledgements, not automatic electrical diagnostics.

The optional panel implementation uses a 128×160 ST7735 black-tab profile. That is a reference adapter choice; the actual controller cannot be established merely from the photographed label. See [connections](../WIRING_AND_SOURCE.md) before enabling either path.

## Resource and test boundaries

Both disabled-default and optional-adapter variants compiled for NodeMCU v2 with ESP8266 core 3.1.2 and TinyGPSPlus 1.0.3. The optional compiler fixture reports 94% IRAM usage including reserved instruction cache. That narrow build margin is a reason to recheck resources when extending the program, not proof of instability or runtime reliability.

Seventeen pure state tests passed initially with MSVC C++17 `/W4 /WX`; a later native repeat was blocked by Windows Device Guard. The unchanged tests were not rerun through another executable or by weakening that protection. Firmware compilation after the final guards passed. Parser runtime, physical serial input, antenna reception and TFT behavior remain untested. [Full verification record](../BUILD_STATUS.md).

## What a convincing hardware demonstration should show

- Confirmed receiver, antenna, panel and electrical identities.
- A genuine initial position acquisition, explicitly distinguished from USB replay.
- Stopped input, visible stale status and recovery after reception resumes.
- Reference comparisons before any accuracy or acquisition-time claim.
- Raw measurements retained privately, with precise personal locations removed from public media.

Cloud tracking, navigation, route logging and geofencing are not implemented. A potential future extension should be designed and tested as new work, not retroactively attributed to the existing prototype.
