# Verification status

| Check | Current status |
| --- | --- |
| Actual photos | Two real views supplied; powered TFT reads waiting for fix |
| Original matching firmware | Not found in the searched folders |
| New state/freshness tests | 17 checks passed on the first run with MSVC C++17, /W4 /WX; repeat execution later blocked by Windows Device Guard |
| Default ESP8266 compile | Passed, including the final GPIO guard revision; physical adapters disabled |
| Optional receiver + TFT adapter compile | Passed using private compiler-only fixtures; not a proposed pin map |
| Reference target and parser | NodeMCU v2, ESP8266 core 3.1.2, TinyGPSPlus 1.0.3 |
| NMEA parser integration at runtime | Not exercised in a host or physical replay test; compile/link only |
| Illustrated video / GIF | 144 MP4 frames decoded at 960×600, 12 fps, 12 seconds; GIF 72 frames / 12 seconds |
| Real GPS acquisition, accuracy, antenna or serial test | Not performed |
| Physical TFT display test | Not performed |
| Board flashing | Not performed |

Compiler fixtures, host logic checks and illustrated animations are not hardware test results. No successful satellite fix is established by the photographs.

The first successful native run is retained separately from the later blocked repeat. The pure state/test source did not change between those runs. No policy bypass was attempted; subsequent verification was compiler-only. No receiver, antenna, GPIO, TFT or outdoor acquisition test has been performed. No firmware was uploaded.

The optional-adapter compiler reports high IRAM use (94% including reserved instruction cache) on this reference target. That is a build resource figure, not a runtime reliability result; reassess resources before adding features.
