# Atlas: prove the source and freshness of a position

**Status: planned, not performed.** The existing photo establishes a powered waiting-for-fix display only.

## Before a hardware test

Complete [WIRING_AND_SOURCE.md](../WIRING_AND_SOURCE.md): exact receiver/antenna, voltage and serial requirements, actual board and TFT controller. Trace connections with power off. Do not copy private compiler fixture GPIOs or send receiver commands through the receive-only reference adapter. No firmware upload is part of this documentation update.

Keep the receiver stationary in a suitable test environment and follow the identified hardware documentation. A consumer GPS receiver is not a surveyed reference. Choose your comparison method and tolerance before claiming positional error.

## A 60–90 second recording that means something

1. Show the receiver, antenna, display and source revision. State **RECEIVER INPUT** or **USB REPLAY** explicitly.
2. Show actual startup/no-data/waiting behavior. If no fix is obtained, report that result; do not substitute replay as proof of reception.
3. If a genuine fix is acquired, demonstrate freshness and a safe data-interruption test. Use a planned power-off reconnection or software-controlled input pause, not ad hoc live rewiring.
4. State what was tested and what was not. Redact actual coordinates and location-bearing metadata before public upload; retain an unedited original privately.

Disclose any cuts or time compression. Never title synthetic replay as a live satellite demonstration.

## Bench cases

| ID | Test | Keep | Acceptance basis |
| --- | --- | --- | --- |
| G1 | No data / startup | Mode, version and actual state | Distinguish absence of input from a fix |
| G2 | Input without valid location | Parser status and sanitized state evidence | Bytes alone do not produce RECENT POSITION |
| G3 | Fresh location and stream interruption | Timestamped state transitions and input mode | Compare against documented freshness boundaries, not claimed RF accuracy |
| G4 | Position comparison, if available | Actual reference method, uncertainty and observed error | Tolerance chosen before test; no accuracy claim without a credible reference |

Use [hardware-observations.csv](../tests/hardware-observations.csv). Leave raw coordinate fields out of public logs. Record units, method, source revision and sanitized evidence filename. All template rows start `not_run`.

## Questions to explain

What is a fix? What does a checksum establish? Can a valid old location be trusted as current? Why do 200 ms renders not prove receiver update rate? Which evidence would justify an accuracy claim? Answer from code and observed data, not a static photo.
