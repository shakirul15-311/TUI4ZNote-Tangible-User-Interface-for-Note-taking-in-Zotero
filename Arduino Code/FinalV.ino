#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String items[] = {"Tangible Interfaces", "Data Sculptures", "Data Physicalization", "Haptic Feedback", "Embodied Cognition"};
int num_items = sizeof(items) / sizeof(items[0]);
int current_item = 0;

const int buttonPin = 6;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long itemChangeDelay = 200; // Half seconds

bool itemChanged = false;
unsigned long itemChangedTime = 0;

const int filenameButtonPin = 7;
int filenameButtonState;
int lastFilenameButtonState = LOW;
unsigned long lastFilenameDebounceTime = 0;
unsigned long filenameDebounceDelay = 50;

bool filenameSelected = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print(items[current_item]);
  pinMode(buttonPin, INPUT_PULLUP); // set the button pin to input with internal pull-up resistor
  pinMode(filenameButtonPin, INPUT_PULLUP); // set the filename button pin to input with internal pull-up resistor
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) { // button is active low, so check for LOW state
        itemChanged = true;
        itemChangedTime = millis();
      }
    }
  }

  lastButtonState = reading;

  // check if the item has changed and if the delay has elapsed
  if (itemChanged && (millis() - itemChangedTime) >= itemChangeDelay) {
    current_item = (current_item + 1) % num_items;
    lcd.clear();
    lcd.print(items[current_item]);

    itemChanged = false;
  }

  // check if filename button has been pressed
  int filenameButtonReading = digitalRead(filenameButtonPin);

  if (filenameButtonReading != lastFilenameButtonState) {
    lastFilenameDebounceTime = millis();
  }

  if ((millis() - lastFilenameDebounceTime) > filenameDebounceDelay) {
    if (filenameButtonReading != filenameButtonState) {
      filenameButtonState = filenameButtonReading;

      if (filenameButtonState == LOW) { // button is active low, so check for LOW state
        filenameSelected = true;
      }
    }
  }

  lastFilenameButtonState = filenameButtonReading;
}
