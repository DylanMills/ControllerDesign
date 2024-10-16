#include <Keyboard.h>
#include <Joystick.h>
#include <HID_Buttons.h>

#define PIN_A 2
#define PIN_B 4
#define PIN_C 6
#define PIN_D 8
#define PIN_1 9
#define PIN_2 7
#define PIN_3 5
#define PIN_4 3
#define PIN_SHIFT 10
#define PIN_HRZ A0
#define PIN_VRT A1
#define LED_POWER 12
#define LED_DIGITAL 11

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
	12, 0,                  // Button Count, Hat Switch Count
	true, true, false,      // X, and Y axes, no Z axis
	false, false, false,    // No Rx, Ry, or Rz
	false, false,           // No rudder or throttle
	false, false, false);   // No accelerator, brake, or steering

const uint8_t buttonPins[8] = {PIN_A, PIN_B, PIN_C, PIN_D, PIN_1, PIN_2, PIN_3, PIN_4};
const uint8_t buttonMap[8] = {0, 1, 2, 3, 4, 5, 10, 11};
// A, B, X, Y, LB, RB, LT, RT
char keyMap[8] = {'r', 'e', ' ', KEY_LEFT_CTRL, '1', '2', '3', '4'};

JoystickButton analogButtons[8] = {
  JoystickButton(buttonMap[0]), JoystickButton(buttonMap[1]),
  JoystickButton(buttonMap[2]), JoystickButton(buttonMap[3]),
  JoystickButton(buttonMap[4]), JoystickButton(buttonMap[5]),
  JoystickButton(buttonMap[6]), JoystickButton(buttonMap[7]),
};
KeyboardButton digitalButtons[8] = {
  KeyboardButton(keyMap[0]), KeyboardButton(keyMap[1]),
  KeyboardButton(keyMap[2]), KeyboardButton(keyMap[3]),
  KeyboardButton(keyMap[4]), KeyboardButton(keyMap[5]),
  KeyboardButton(keyMap[6]), KeyboardButton(keyMap[7]),
};

KeyboardButton keyUp('w');
KeyboardButton keyDown('s');
KeyboardButton keyRight('d');
KeyboardButton keyLeft('a');
KeyboardButton keyMod(KEY_LEFT_SHIFT);

const int joyCenter = 512;
const int joyDeadzone = 50;

bool digitalMode = false;
bool shiftPressed = false;

void setup() {
  Serial.begin(9600);

  //CONTROL STICK
  pinMode(PIN_HRZ, INPUT);
  pinMode(PIN_VRT, INPUT);

  //DIGITAL->ANALOG TOGGLE
  pinMode(PIN_SHIFT, INPUT_PULLUP);

  // BUTTONS
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_1, INPUT_PULLUP);

  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_2, INPUT_PULLUP);

  pinMode(PIN_C, INPUT_PULLUP);
  pinMode(PIN_3, INPUT_PULLUP);
  
  pinMode(PIN_D, INPUT_PULLUP);
  pinMode(PIN_4, INPUT_PULLUP);

  //OUTPUTS
  pinMode(LED_POWER, OUTPUT);
  pinMode(LED_DIGITAL, OUTPUT);

  Joystick.begin();
  Keyboard.begin();

  digitalWrite(LED_POWER, HIGH); // ON LED
  analogWrite(LED_DIGITAL, digitalMode ? 32 : LOW);
}

void loop() {
  bool shiftDown = !digitalRead(PIN_SHIFT);
  if (!shiftPressed && shiftDown) {
    digitalMode = !digitalMode;
    analogWrite(LED_DIGITAL, digitalMode ? 32 : LOW);
  }
  shiftPressed = shiftDown;

  if (digitalMode)
    updateDigital();
  else
    updateAnalog();
}

void updateDigital() {
  for (uint8_t i = 0; i < 8; i++) {
    digitalButtons[i].set(!digitalRead(buttonPins[i]));
  }
  int x = analogRead(PIN_HRZ);
  int y = analogRead(PIN_VRT);

  keyUp.set(y > joyCenter + joyDeadzone);
  keyDown.set(y < joyCenter - joyDeadzone);

  keyRight.set(x < joyCenter - joyDeadzone);
  keyLeft.set(x > joyCenter + joyDeadzone);
}

void updateAnalog() {
  for (uint8_t i = 0; i < 8; i++) {
    analogButtons[i].set(!digitalRead(buttonPins[i]));
  }
  Joystick.setXAxis(1023 - analogRead(PIN_HRZ));
  Joystick.setYAxis(analogRead(PIN_VRT));
}