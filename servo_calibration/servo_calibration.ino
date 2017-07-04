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

  Serial.println("Servo Calibration을 진행합니다.\n핀 번호를 세팅해주세요(예: p 3)");
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
      break;
    }
  }
}

void printCommandList() {
  Serial.println("h:도움말\ni:현재 핀 번호 및 변경된 값\np:디지털 핀 세팅\n+:서보모터에 +값 주기\n-:서보모터에 -값 주기");
}

void printInfo() {
  Serial.println("================");
  Serial.print("디지털 핀: ");
  Serial.println(d_pin);
  Serial.print("수정된 값: ");
  Serial.println(cali_count );
  Serial.println("================");
}

void setDigitalPin() {
  Serial.print("디지털 핀 세팅(2~13): ");
  int temp_pin = Serial.parseInt();
  if ( temp_pin >= 2 && temp_pin <= 13) {
    d_pin = temp_pin;
    servo.attach(d_pin);
    Serial.print("디지털 핀이 수정되었습니다: ");
    Serial.println(d_pin);
    cali_count = 0;
  } else {
    Serial.println("핀 번호 범위를 확인해주세요");
  }
}

void calibration(char op) {
  if (d_pin >= 2 && d_pin <= 13) {
    switch(op) {
      case '+':
        if (90+cali_count < 180)
          cali_count++;
      break;
      case '-':
        if (90+cali_count > 0)
           cali_count--;
      break;
    }
  }
}

