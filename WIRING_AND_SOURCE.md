# Connections — verify before wiring

Photos 6 and 7 are one GPS data-display project, as confirmed by the owner. Wire colors and nearby header labels do not establish complete connections. No original GPIO table is asserted.

| Signal path | Required confirmation | Reference configuration |
| --- | --- | --- |
| Receiver supply | Breakout model, input range, regulation, current and polarity | Hardware-specific supply; no assumed 5V tolerance |
| Receiver TX → controller RX | Receiver output logic level, serial format/baud and actual GPIO | `GPS_RX_PIN`, `GPS_BAUD`; receive-only adapter |
| Ground reference | Actual grounding between receiver and controller | Trace and document before enabling |
| Receiver RX | Whether needed for original firmware | Not used by the new receive-only reference |
| Antenna → receiver | Exact antenna/connector, active/passive type and supply requirements | No RF specifications inferred from appearance |
| TFT power and logic | Controller IC, module voltage/logic limits, backlight requirements | ST7735 is optional reference only |
| TFT SPI and control/reset | Actual clock/data/control pins, boot behavior and pin conflicts | Enter verified `TFT_CS`, `TFT_DC`, `TFT_RST`; confirm target SPI defaults |

## Commissioning sequence

1. Record receiver, board and panel markings before power changes. Keep the original source photographs alongside the connection record.
2. Confirm every supply and logic level from the exact module/board documentation. GPIO configuration is not a level converter. Do not assume a breakout's regulated power input establishes signal tolerance.
3. With a suitable interface and a supervised setup, capture the receiver's real serial output. Confirm rate/format, valid sentence checksums and whether data arrive at all. Do not publish private coordinates or personal routes.
4. Establish the actual receiver TX-to-controller RX connection and ground reference. Enter the confirmed GPIO and baud only after tracing the wires. Avoid flash, boot and shared display-pin conflicts.
5. Test parsing and status reporting without the TFT first. Distinguish USB replay from physical receiver data in recordings.
6. Identify the display driver and confirmed SPI/control connections, then enable the reference display separately. Do not infer ST7735 compatibility solely from the 128×160 label.
7. Record real startup, fresh position, stopped serial data and recovery. Compare a position against a suitable reference before claiming accuracy or time-to-first-fix. Do not use this unvalidated build for navigation or safety decisions.

The searched Arduino/Desktop/firmware folders contain TinyGPS libraries and examples but no matching original sketch. The new reference code does not recover the original wiring or demonstrate that the photographed system acquired a fix.
