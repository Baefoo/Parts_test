#include <Servo.h>

Servo servo;
int d_pin;
int cali_count;
char command;

void setup() {
  Serial.begin(9600);
  cali_count = 0;
  command = 0;
  d_pin = 0;

  Serial.println("This program calibrates the servo motor.\nYou must set the pin number(e.g: p 3).");
  Serial.println("How to change data e.g: + 3  or  - 2 etc..");
  printCommandList();
}

void loop() {
  servo.write(90 + cali_count);
  if (Serial.available()) {
    command = Serial.read();
    switch (command) {
      case 'h':
        printCommandList();
      break;
      case 'i':
        printInfo();
      break;
      case 'p':
        setDigitalPin();
      break;
      case '+':
      case '-':
        calibration(command);
        delay(20);
      break;
    }
  }
}

void printCommandList() {
  Serial.println("h:help\ni:current pin number & changed value\np:digital pin setting\n+: input + value\n-: input - value");
}

void printInfo() {
  Serial.println("================");
  Serial.print("Digital pin: ");
  Serial.println(d_pin);
  Serial.print("Changed value: ");
  Serial.println(cali_count );
  Serial.println("================");
}

void setDigitalPin() {
  Serial.print("Digital pin setting(2~13): ");
  int temp_pin = Serial.parseInt();
  if ( temp_pin >= 2 && temp_pin <= 13) {
    d_pin = temp_pin;
    servo.attach(d_pin);
    Serial.print("The digital pin has been modified.");
    Serial.println(d_pin);
    cali_count = 0;
  } else {
    Serial.println("Please check the pin number.");
  }
}

void calibration(char op) {
  if (d_pin >= 2 && d_pin <= 13) {
    int temp_value = Serial.parseInt();
    switch(op) {
      case '+':
      cali_count += temp_value;
        if (90+cali_count < 180)
          cali_count++;
      break;
      case '-':
      cali_count -= temp_value;
        if (90+cali_count > 0)
           cali_count--;
      break;
    }
  }
}
