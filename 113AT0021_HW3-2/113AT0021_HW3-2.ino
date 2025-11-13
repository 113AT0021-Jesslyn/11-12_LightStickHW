const int ledPin = 3;      // RGB LED color leg
const int buttonPin = 2;   // button pin

int mode = 1;              // 1–4
bool lastButtonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // button → GND
}

void loop() {
  // --- handle button click ---
  bool reading = digitalRead(buttonPin);

  if (reading == LOW && lastButtonState == HIGH) {
    mode++;
    if (mode > 4) mode = 1; // loop back
    delay(100); // simple debounce
  }
  lastButtonState = reading;

  // --- LED behavior ---
  if (mode == 1) { // steady ON
    digitalWrite(ledPin, LOW); // LOW = ON
  } else if (mode == 2) { // slow blink
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    delay(1000);
  } else if (mode == 3) { // medium blink
    digitalWrite(ledPin, LOW);
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(500);
  } else if (mode == 4) { // fast blink
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
  }
}
