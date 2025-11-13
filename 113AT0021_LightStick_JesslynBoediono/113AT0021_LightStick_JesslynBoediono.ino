// Lightstick with 3 modes (Constant, Blink, Breathing)
// Short click = change color
// Long press = change mode
// Color order: Green, Blue, Yellow, Red

int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int buttonPin = 2;

int mode = 0;         // 0: Constant, 1: Blink, 2: Breathing
int colorIndex = 0;   // 0: Green, 1: Blue, 2: Yellow, 3: Red

unsigned long lastPressTime = 0;
bool lastButtonState = HIGH;

int debounceDelay = 50;
int longPressTime = 800;
int fadeValue = 0;
int fadeDirection = 1;

// Updated color order
int colors[4][3] = {
  {0, 255, 0},  
  {0, 0, 255},   
  {255, 255, 0}, 
  {255, 0, 0}   
};

// For blinking and breathing timing
unsigned long prevMillis = 0;
int brightness = 0;
int fadeAmount = 5;
bool ledOn = false;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  handleButton();

  if (mode == 0) {
    // Constant Light
    showColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
  } 
  else if (mode == 1) {
    // Blink Mode (on/off)
    blinkMode();
  } 
  else if (mode == 2) {
    // Breathing Mode (fade in/out)
    breathingMode();
  }
}

void handleButton() {
  bool buttonState = digitalRead(buttonPin);
  unsigned long now = millis();

  if (buttonState != lastButtonState) {
    delay(debounceDelay);
    if (buttonState == LOW) {
      lastPressTime = now;
    } else {
      unsigned long pressDuration = now - lastPressTime;
      if (pressDuration < longPressTime) {
        // Short click: change color
        colorIndex = (colorIndex + 1) % 4; // updated to 4 colors
      } else {
        // Long press: change mode
        mode = (mode + 1) % 3;
        prevMillis = now;
        ledOn = false;
        brightness = 0;
        fadeAmount = 5;
      }
    }
  }
  lastButtonState = buttonState;
}

void showColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void blinkMode() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= 500) { // 0.5s blink
    prevMillis = currentMillis;
    ledOn = !ledOn;
    if (ledOn) {
      showColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    } else {
      showColor(255, 255, 255); // OFF
    }
  }
}

void breathingMode() {

  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= 10) { // breathing speed
    prevMillis = currentMillis;

    fadeValue += fadeDirection * 5;
    if (fadeValue <= 0 || fadeValue >= 255) {
      fadeDirection = -fadeDirection; // reverse at ends
    }

  
    int r = 255 - ((255 - colors[colorIndex][0]) * fadeValue / 255);
    int g = 255 - ((255 - colors[colorIndex][1]) * fadeValue / 255);
    int b = 255 - ((255 - colors[colorIndex][2]) * fadeValue / 255);
    showColor(r, g, b);
    delay(15);
  }
}
