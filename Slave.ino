# include <LiquidCrystal.h>
# include <Wire.h>
# include <Keypad.h>
int i = 0;
const int buzzer = A0;
const byte ROWS = 4;
const byte COLS = 3;
char x;
String exam_time = "";
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 3}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int count = 0;
int free_count = 0;
int exam = 0;
int mode = 0;
int previous_exam = 1;
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

void setup() {
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() {
  if (mode == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Exam Time:");
    lcd.setCursor(0, 1);
    while (x != '#') {
      x = keypad.getKey();
      if (x) {
      exam_time += x;
      lcd.print(x);
      }
    }
    lcd.clear();
    int exam_time_int = exam_time.toInt();
    while(exam_time_int > 0){
      lcd.clear();
      lcd.print("Remaining:");
      lcd.print(exam_time_int);
      delay(1000);
      exam_time_int --;
    }
    digitalWrite(buzzer, HIGH);
    delay(5000);
    digitalWrite(buzzer, LOW);
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Free Spaces: ");
    lcd.setCursor(0, 1);
    lcd.print(free_count);
  }
}

void receiveEvent(int count) {
  count = Wire.read();
  exam = Wire.read();
  free_count = count;
  if (exam != previous_exam) {
    lcd.clear();
    exam_time = "";
    mode = exam;
  }
  previous_exam = exam;
}


