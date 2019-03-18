# include <Wire.h>
const int ledPin0 = 2;
const int ledPin1 = 3;
const int ledPin2 = 4;
const int ledPin3 = 5;
const int ledPin4 = 6;
const int ledPin5 = 7;
const int buttonPin0 = 8;
const int buttonPin1 = 9;
const int buttonPin2 = 10;
const int buttonPin3 = 11;
const int buttonPin4 = 12;
const int buttonPin5 = 13;
const int roomLightPin0 = A0;
const int roomLightPin1 = A1;
const int roomLightPin2 = A2;
const int roomLightPin3 = A3;
const int exam_input = 0;
int buttonState0 = 1;
int buttonState1 = 1;
int buttonState2 = 1;
int buttonState3 = 1;
int buttonState4 = 1;
int buttonState5 = 1;
int roomLightState0 = 0;
int roomLightState1 = 0;
int roomLightState2 = 0;
int roomLightState3 = 0;
int exam_mode = 0;
int count = 0;
int exam_input_reading;
int exam_input_previous = HIGH;
long time = 0;
long debounce = 200;


void setup() {
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(buttonPin0, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(exam_input, INPUT_PULLUP);
  pinMode(roomLightPin0, OUTPUT);
  pinMode(roomLightPin1, OUTPUT);
  pinMode(roomLightPin2, OUTPUT);
  pinMode(roomLightPin3, OUTPUT);
  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin5, HIGH);

  digitalWrite(roomLightPin1, LOW);
  digitalWrite(roomLightPin2, LOW);
  digitalWrite(roomLightPin3, LOW);
  Wire.begin();

}

void loop() {


  buttonState0 = digitalRead(buttonPin0);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  roomLightState0 = digitalRead(roomLightPin0);
  roomLightState1 = digitalRead(roomLightPin1);
  roomLightState2 = digitalRead(roomLightPin2);
  roomLightState3 = digitalRead(roomLightPin3);
  exam_input_reading = digitalRead(exam_input);

  if (exam_input_reading == HIGH & exam_input_previous == LOW && millis() - time > debounce) {
    if (exam_mode == 1) {
      exam_mode = 0;
    }
    else {
      exam_mode = 1;
    }
    time = millis();
  }

  if (buttonState0 == HIGH) {
    digitalWrite(ledPin0, HIGH);
  }
  else {
    digitalWrite(ledPin0, LOW);
  }


  if (buttonState1 == HIGH) {
    digitalWrite(ledPin1, HIGH);
  }
  else {
    digitalWrite(ledPin1, LOW);
  }



  if (buttonState2 == HIGH) {
    digitalWrite(ledPin2, HIGH);
  }
  else {
    digitalWrite(ledPin2, LOW);
  }


  if (buttonState3 == HIGH) {
    digitalWrite(ledPin3, HIGH);
  }
  else {
    digitalWrite(ledPin3, LOW);
  }


  if (buttonState4 == HIGH) {
    digitalWrite(ledPin4, HIGH);
  }
  else {
    digitalWrite(ledPin4, LOW);
  }


  if (buttonState5 == HIGH) {
    digitalWrite(ledPin5, HIGH);
  }
  else {
    digitalWrite(ledPin5, LOW);
  }

  if (exam_mode == 0) {

    if ((buttonState0 == LOW) | (buttonState3 == LOW) | (buttonState1 == LOW & roomLightState1 == LOW) | (buttonState4 == LOW & roomLightState1 == LOW)) {
      digitalWrite(roomLightPin0, HIGH);
      roomLightState0 = HIGH;
    }
    else {
      digitalWrite(roomLightPin0, LOW);
      roomLightState0 = LOW;
    }
    if ((buttonState2 == LOW) | (buttonState5 == LOW) | (buttonState1 == LOW & roomLightState0 == LOW) | (buttonState4 == LOW & roomLightState0 == LOW)) {
      digitalWrite(roomLightPin1, HIGH);
      roomLightState1 = HIGH;
    }
    else {
      digitalWrite(roomLightPin1, LOW);
      roomLightState1 = LOW;
    }
    if ((buttonState3 == LOW) | (buttonState4 == LOW & roomLightState3 == LOW)) {
      digitalWrite(roomLightPin2, HIGH);
      roomLightState2 = HIGH;
    }
    else {
      digitalWrite(roomLightPin2, LOW);
      roomLightState2 = LOW;
    }
    if ((buttonState5 == LOW) | (buttonState4 == LOW & roomLightState2 == LOW)) {
      digitalWrite(roomLightPin3, HIGH);
      roomLightState3 = HIGH;
    }
    else {
      digitalWrite(roomLightPin3, LOW);
      roomLightState3 = LOW;
    }
  }
  else
  {
    digitalWrite(roomLightPin0, HIGH);
    digitalWrite(roomLightPin1, HIGH);
    digitalWrite(roomLightPin2, HIGH);
    digitalWrite(roomLightPin3, HIGH);
  }

  count = buttonState0 + buttonState1 + buttonState2 + buttonState3 + buttonState4 + buttonState5;
  exam_input_previous = exam_input_reading;
  Wire.beginTransmission(8);
  Wire.write(count);
  Wire.write(exam_mode);
  Wire.endTransmission();
}

