#include <Keyboard.h>

#define PIN_A 8
#define PIN_B 6
#define PIN_C 4
#define PIN_D 2
#define PIN_1 3
#define PIN_2 5
#define PIN_3 7
#define PIN_4 9
#define PIN_SHIFT 10
#define HRZ A0
#define VRT A1
#define LED_POWER 11
#define LED_DIGITAL 12

#define DEADZONE 64
#define DEADZONE_NEG 512-DEADZONE
#define DEADZONE_POS 512+DEADZONE

const uint8_t buttonPins[] = {PIN_A, PIN_B, PIN_C, PIN_D, PIN_1, PIN_2, PIN_3, PIN_4};
char buttonKeys[] = {'r', 'e', ' ', KEY_LEFT_CTRL, '1', '2', '3', '4'};
bool wasPressed[8];

int lastHrz = 512;
int lastVrt = 512;

bool digitalMode = true;
bool shiftPressed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Axis
  pinMode(HRZ, INPUT);
  pinMode(VRT, INPUT);

  pinMode(PIN_SHIFT, INPUT_PULLUP);

  //RED PUSH BUTTONS
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_1, INPUT_PULLUP);

  //GREEN BUTTONS
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_2, INPUT_PULLUP);

  //BLUE BUTTONS
  pinMode(PIN_C, INPUT_PULLUP);
  pinMode(PIN_3, INPUT_PULLUP);
  
  //YELLOW BUTTONS
  pinMode(PIN_D, INPUT_PULLUP);
  pinMode(PIN_4, INPUT_PULLUP);

  //OUTPUTS
  pinMode(LED_POWER, OUTPUT);
  pinMode(LED_DIGITAL, OUTPUT);

  //XInput.setJoystickRange(0, 1023);  // Set joystick range to the ADC
	//XInput.setAutoSend(false);  // Wait for all controls before sending

	//XInput.begin();

  //Keyboard.begin();

  analogWrite(LED_POWER, 64); // ON LED
}

void handleDigitalAxis(char keyNeg, char keyPos, int val, int lastVal) {
  if (lastVal < DEADZONE_POS && val > DEADZONE_POS)
    Keyboard.press(keyPos);
  else if (lastVal > DEADZONE_POS && val < DEADZONE_POS)
    Keyboard.release(keyPos);

  if (lastVal > DEADZONE_NEG && val < DEADZONE_NEG)
    Keyboard.press(keyNeg);
  else if (lastVal < DEADZONE_NEG && val > DEADZONE_NEG)
    Keyboard.release(keyNeg);
}

void loop() {
  /*
  // analog stick
  int joyX = analogRead(HRZ);
  int joyY = analogRead(VRT);

  XInput.setJoystickX(JOY_LEFT, joyX);
  XInput.setJoystickY(JOY_LEFT, joyY);
  
  XInput.send();
  */

  // digital toggle
  if (digitalMode != digitalRead(PIN_SHIFT) == LOW) {
    digitalMode = digitalRead(PIN_SHIFT) == LOW;
    digitalWrite(LED_DIGITAL, digitalMode ? HIGH : LOW);
  }

  if (digitalMode) {
    for (uint8_t i = 0; i < 8; i++) {
      int val = digitalRead(buttonPins[i]);
      if (!wasPressed[i] && val == LOW) {
        //Keyboard.press(buttonKeys[i]);
      }
      else if (wasPressed[i] && val == HIGH) {
        //Keyboard.release(buttonKeys[i]);
      }
      wasPressed[i] = val == LOW;
    }

    int curHrz = analogRead(HRZ);
    int curVrt = analogRead(VRT);
    handleDigitalAxis('a', 'd', curHrz, lastHrz);
    handleDigitalAxis('w', 's', curVrt, lastVrt);
    lastHrz = curHrz;
    lastVrt = curVrt;
  }
}