/*
  traffic_light.ino for Arduino

  Pinout:
  D2 - Pushbutton
  D3 - Green LED
  D4 - Yellow LED
  D5 - Red LED

*/

unsigned long currentTime = 0;
unsigned long targetTime = 0;
byte currentPositionInPattern = -1;
byte colorPosition = 0;
bool currentState[3] = { 0, 0, 0 };

/*
  Pattern is actual blinking pattern
  0 and array end is treated as a switch to next color
  time in ms

  Example: { 100, 100, 100, 0, 100, 0, 100 }
  will result in:
    red 100ms on, red 100ms off, red 100ms on
    yellow 100ms on
    green 100 ms on
*/
int currentPattern[] = { 5000, 0, 200, 200, 200, 200, 200, 200, 0, 5000, 300, 300 };

int currentPatternLength = (sizeof(currentPattern))/(sizeof(currentPattern[0]));
int nextTarget;
byte BUTTON_PIN = 2;
int buttonValue = LOW;
int buttonValueNew = LOW;
int buttonPressed = 0;
int clickCounter = 0;
byte currentTaskId = 0;

byte leds[3] = {3, 4, 5};

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
    Serial.println("led" + String(leds[i]));
  }
  Serial.println("Hello");
  Serial.print("basicPattern length ");
  Serial.println(currentPatternLength);

  delay(350);
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void checkButtonState() {
  buttonValue = digitalRead(BUTTON_PIN);
  if (buttonValue == LOW) {
    buttonPressed = 1;
  } else {
    if (buttonPressed == 1) {
      onButtonPress();
    }
  }
}

void onButtonPress() {
  clickCounter++;
  buttonValueNew = !buttonValueNew;
  buttonPressed = 0;
  // only 0/1 for now
  currentTaskId = !currentTaskId;

  digitalWrite(LED_BUILTIN, clickCounter%2);
  Serial.print("onButtonPress");
  Serial.println(currentTaskId);
}

int setNextTarget() {
  nextTarget = currentPattern[currentPositionInPattern];
  return nextTarget;
}

byte updateCurrentPositionInPattern() {
  currentPositionInPattern++;
  if (currentPositionInPattern >= currentPatternLength) {
    currentPositionInPattern = 0;
  }
  return currentPositionInPattern;
}

void updateColorPosition() {
  currentState[colorPosition] = 0;
  colorPosition++;
  if (colorPosition > 2) {
    colorPosition = 0;
    currentPositionInPattern = 0;
  }
  currentState[colorPosition] = 1;
}

void resetPattern() {
  colorPosition = 0;
  currentPositionInPattern = -1;
  targetTime = 0;

  for (int i = 0; i < 3; i++) {
    currentState[i] = 0;
    digitalWrite(leds[i], 0);
  }
}

void playPattern() {
  currentTime = millis();

  if (currentTime >= targetTime) {
    updateCurrentPositionInPattern();
    setNextTarget();

    if (targetTime == 0) {
      // start
      currentState[colorPosition] = !currentState[colorPosition];
    } else if (nextTarget == 0) {
      updateCurrentPositionInPattern();
      updateColorPosition();
      setNextTarget();
    } else if (currentPositionInPattern == 0) {
      updateColorPosition();
    } else {
      currentState[colorPosition] = !currentState[colorPosition];
    }

    targetTime = currentTime + nextTarget;

    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], currentState[i]);
    }

    Serial.print(currentState[0]);
    Serial.print(currentState[1]);
    Serial.print(currentState[2]);
    Serial.println(" x");
  }
}

void playCurrentTask() {
  if (currentTaskId == 0) {
    playPattern();
  } else {
    resetPattern();
  }
}

void loop() {
  checkButtonState();

  playCurrentTask();
}
