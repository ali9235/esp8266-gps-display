// New reference implementation; not recovered firmware from the photographs.
#include <Arduino.h>
#include <math.h>
#include <TinyGPS++.h>
#include "config.h"
#include "status.h"

#if ENABLE_GPS_INPUT
#include <SoftwareSerial.h>
SoftwareSerial receiver(GPS_RX_PIN, -1); // Receive only; no commands to the module.
#endif
#if ENABLE_TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
Adafruit_ST7735 screen(TFT_CS, TFT_DC, TFT_RST);
#endif

TinyGPSPlus gps;
bool seenBytes = false;
uint32_t lastByteAt = 0;
uint32_t lastRenderAt = 0;
uint32_t lastReportAt = 0;

bool recent(bool valid, uint32_t age) { return valid && age <= 5000; }

atlas::State currentState(uint32_t now) {
    const bool coordinates = gps.location.isValid()
        && isfinite(gps.location.lat()) && isfinite(gps.location.lng())
        && fabs(gps.location.lat()) <= 90 && fabs(gps.location.lng()) <= 180;
    return atlas::classify(seenBytes, now - lastByteAt, coordinates, gps.location.age());
}

void render(atlas::State state) {
#if ENABLE_TFT
    // This optional 128x160 black-tab profile is a reference, not a photo ID.
    screen.fillScreen(ST77XX_BLACK);
    screen.setCursor(0, 0);
    screen.setTextColor(ST77XX_GREEN);
    screen.println("VOLTRA ATLAS");
    screen.setTextColor(ST77XX_WHITE);
    screen.println(ENABLE_GPS_INPUT ? "RECEIVER INPUT" : "USB REPLAY MODE");
    screen.println(atlas::label(state));
    if (state == atlas::State::RecentPosition) {
        screen.print("Lat: "); screen.println(gps.location.lat(), 6);
        screen.print("Lon: "); screen.println(gps.location.lng(), 6);
        if (recent(gps.altitude.isValid(), gps.altitude.age())) {
            screen.print("Alt m: "); screen.println(gps.altitude.meters(), 1);
        }
        if (recent(gps.speed.isValid(), gps.speed.age())) {
            screen.print("km/h: "); screen.println(gps.speed.kmph(), 1);
        }
    } // Stale coordinates are deliberately not displayed as current.
    if (state != atlas::State::NoData && state != atlas::State::Stale) {
        if (recent(gps.satellites.isValid(), gps.satellites.age())) {
            screen.print("Sats: "); screen.println(gps.satellites.value());
        }
        if (recent(gps.time.isValid(), gps.time.age())) {
            screen.print("UTC: ");
            if (gps.time.hour() < 10) screen.print('0');
            screen.print(gps.time.hour()); screen.print(':');
            if (gps.time.minute() < 10) screen.print('0');
            screen.print(gps.time.minute()); screen.print(':');
            if (gps.time.second() < 10) screen.print('0');
            screen.println(gps.time.second());
        }
    }
#else
    (void)state;
#endif
}

void setup() {
    Serial.begin(115200);
    Serial.println("VOLTRA ATLAS - new reference software");
    Serial.println(ENABLE_GPS_INPUT ? "Receiver RX enabled; confirm wiring." : "USB NMEA REPLAY; physical receiver disabled.");
#if ENABLE_GPS_INPUT
    receiver.begin(GPS_BAUD);
#endif
#if ENABLE_TFT
    screen.initR(INITR_BLACKTAB);
    screen.setTextSize(1);
    screen.setTextWrap(true);
#endif
    render(atlas::State::NoData);
}

void loop() {
#if ENABLE_GPS_INPUT
    Stream& input = receiver;
#else
    Stream& input = Serial; // Feed NMEA text manually; no built-in fake position.
#endif
    for (uint8_t count = 0; count < 96 && input.available() > 0; ++count) {
        const int byte = input.read();
        if (byte < 0) break;
        seenBytes = true;
        lastByteAt = millis();
        gps.encode(static_cast<char>(byte));
    }
    const uint32_t now = millis();
    const atlas::State state = currentState(now);
    if (atlas::due(now, lastRenderAt, 200)) {
        lastRenderAt = now;
        render(state);
    }
    if (atlas::due(now, lastReportAt, 1000)) {
        lastReportAt = now;
        Serial.print(ENABLE_GPS_INPUT ? "RECEIVER: " : "REPLAY: ");
        Serial.print(atlas::label(state));
        Serial.print(" | checksum failures: "); Serial.println(gps.failedChecksum());
    }
    yield();
}
