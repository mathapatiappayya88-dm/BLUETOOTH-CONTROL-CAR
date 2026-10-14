
#include <SoftwareSerial.h>

// HC-05 Bluetooth: RX, TX
SoftwareSerial bluetooth(10, 11);

// L298N motor driver pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 6
#define ENB 9

int motorSpeed = 180;  // Speed: 0 to 255
char command;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  bluetooth.begin(9600);

  stopCar();

  Serial.println("Bluetooth Car Ready");
}

void loop() {
  if (bluetooth.available()) {
    command = bluetooth.read();
    Serial.print("Command: ");
    Serial.println(command);

    switch (command) {
      case 'F':
        forward();
        break;

      case 'B':
        backward();
        break;

      case 'L':
        turnLeft();
        break;

      case 'R':
        turnRight();
        break;

      case 'S':
        stopCar();
        break;

      case '0':
        motorSpeed = 0;
        setSpeed();
        break;

      case '1':
        motorSpeed = 100;
        setSpeed();
        break;

      case '2':
        motorSpeed = 140;
        setSpeed();
        break;

      case '3':
        motorSpeed = 180;
        setSpeed();
        break;

      case '4':
        motorSpeed = 200;
        setSpeed();
        break;

      case '5':
        motorSpeed = 220;
        setSpeed();
        break;

      case '6':
        motorSpeed = 255;
        setSpeed();
        break;

      default:
        break;
    }
  }
}

void setSpeed() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void forward() {
  setSpeed();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  setSpeed();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  setSpeed();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  setSpeed();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
