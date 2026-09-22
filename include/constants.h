#pragma once

// #define DEBUG

#define BOD 9600
#define OLED_CLASS U8G2_SSD1306_128X64_NONAME_1_HW_I2C
#define RESISTOR_PIN A0
#define GREEN_LED_PIN 3
#define TOGGLE_PIN A3
#define BURNER_PIN 4 // (led)
// #define BURNER_DELTA 10
#define DEFAULT_HYSTERESIS 10

// !FIXME bug
#define BUTTON_PIN_PLUS 12
#define BUTTON_PIN_MINUS 11

// led configs
#define RED_LED_PIN 2

#define CHECK_ADDRESS 0

/// MAX_VALUES
#define MAX_PERMITTED_TEMP 110
#define MIN_PERMITTED_TEMP -10

/// periods
#define ERROR_PERIOD 1000 * 5      // 5 sec
#define SETTINGS_CLICK_PERIOD 1000 // 1 sec
#define BUTTON_PERIOD 400          // 0.4 sec
#define DEBUG_PERIOD 500           // ms between debug log lines

/// UI
#define FONT u8g2_font_squeezed_b7_tr

// oled size
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define CENTER_X OLED_WIDTH / 2
#define CENTER_Y OLED_HEIGHT / 2
// columns
#define SECOND_COLUMN 80
#define FIRST_COLUMN 0

// temperature
#define TEMP_Y 10
#define TEMP_X FIRST_COLUMN

// deltaValue
#define HYSTERESIS_Y 10
#define HYSTERESIS_X SECOND_COLUMN

// voltage
#define VOLT_Y 30
#define VOLT_X FIRST_COLUMN

// user temperature
#define USERTEMP_Y 30
#define USERTEMP_X SECOND_COLUMN

// burner
#define BURNER_Y 50
#define BURNER_X 0

/// settings
// delta (burner hysteresis) bounds
#define MIN_DELTA 0
#define MAX_DELTA 50

#define DEFAULT_USER_TEMP 50

