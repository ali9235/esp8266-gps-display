#pragma once

// All physical adapters are deliberately disabled; not the photograph's pin map.
#define ENABLE_GPS_INPUT 0
#define GPS_INTERFACE_VERIFIED 0
#define GPS_RX_PIN -1
#define GPS_BAUD 0

#define ENABLE_TFT 0
#define TFT_MODEL_VERIFIED 0
#define TFT_CS -1
#define TFT_DC -1
#define TFT_RST -1

#if ENABLE_GPS_INPUT && (!GPS_INTERFACE_VERIFIED || GPS_RX_PIN < 0 || GPS_BAUD <= 0)
#error "Identify the GPS output, logic levels, RX GPIO and baud before enabling hardware."
#endif
#if ENABLE_GPS_INPUT && (GPS_RX_PIN > 16 || GPS_RX_PIN == 1 || GPS_RX_PIN == 3 || (GPS_RX_PIN >= 6 && GPS_RX_PIN <= 11))
#error "GPS RX is outside the reference board's usable GPIO range."
#endif
#if ENABLE_TFT && (!TFT_MODEL_VERIFIED || TFT_CS < 0 || TFT_DC < 0 || TFT_RST < 0)
#error "Verify the display controller and all actual control/reset connections first."
#endif
#if ENABLE_TFT && (TFT_CS > 16 || TFT_DC > 16 || TFT_RST > 16 || TFT_CS == TFT_DC || TFT_CS == TFT_RST || TFT_DC == TFT_RST)
#error "Invalid or duplicate TFT control GPIOs."
#endif
#if ENABLE_TFT && ((TFT_CS >= 6 && TFT_CS <= 11) || (TFT_DC >= 6 && TFT_DC <= 11) || (TFT_RST >= 6 && TFT_RST <= 11) || TFT_CS == 1 || TFT_CS == 3 || TFT_DC == 1 || TFT_DC == 3 || TFT_RST == 1 || TFT_RST == 3 || TFT_CS == 13 || TFT_CS == 14 || TFT_DC == 13 || TFT_DC == 14 || TFT_RST == 13 || TFT_RST == 14)
#error "TFT control GPIOs overlap flash, USB serial or reference hardware SPI signals."
#endif
#if ENABLE_GPS_INPUT && ENABLE_TFT && (GPS_RX_PIN == TFT_CS || GPS_RX_PIN == TFT_DC || GPS_RX_PIN == TFT_RST || GPS_RX_PIN == 13 || GPS_RX_PIN == 14)
#error "GPS RX conflicts with the reference TFT control/SPI path."
#endif
