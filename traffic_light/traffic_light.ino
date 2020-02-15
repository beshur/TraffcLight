// traffic_light.c for Arduino

unsigned long currentTime = 0;
unsigned long targetTime = 0;
byte currentPositionInPattern = -1;
byte colorPosition = 0;
bool currentState[3] = { 0, 0, 0 };
int currentPattern[] = { 1000, 0, 1000, 0, 1000 };
//int currentPattern[] = { 5000, 300, 300, 0, 200, 200, 200, 200, 200, 200, 0, 5000 };

int currentPatternLength = (sizeof(currentPattern))/(sizeof(currentPattern[0]));
int nextTarget;
byte BUTTON_PIN = 2;
int buttonValue = LOW;
int buttonValueNew = LOW;
int buttonPressed = 0;
int clickCounter = 0;

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
  currentState[colorPosition] = true;
  Serial.println("Hello");
  Serial.print("basicPattern length ");
  Serial.println(currentPatternLength);

  delay(1000);
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

  digitalWrite(LED_BUILTIN, clickCounter%2);

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
  }
  currentState[colorPosition] = 1;
}

void loop() {
  checkButtonState();
  
  currentTime = millis();

  if (currentTime >= targetTime) {
    updateCurrentPositionInPattern();
    setNextTarget();

    if (nextTarget == 0) {
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
    Serial.println("-----");
  }
}
