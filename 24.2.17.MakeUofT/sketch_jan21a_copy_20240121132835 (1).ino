#include <HX711.h>
#include <Servo.h>

#define LOADCELL_DOUT_PIN  10
#define LOADCELL_SCK_PIN  9
const int buttonPin = 12;
Servo myservo;
int buttonState = 0;
int buttonstatus = 0;
int pos = 0;
int weight =0;
HX711 scale;

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;

// 定义数字的引脚（共阳极）
int D1 = 22; // 第一个数字
int D2 = 24; // 第二个数字
int D3 = 26; // 第三个数字
int D4 = 28; // 第四个数字

int DP = 30; // 小数点


float calibration_factor = 7050/45.3592; //-7050 worked for my 440lb max scale setup

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  // 初始化数字的引脚为输出
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  // 初始化小数点的引脚为输出
  pinMode(DP, OUTPUT);
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  myservo.attach(2);
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading;
  pinMode(buttonPin, INPUT);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  weight = abs(int(scale.get_units()));
   Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.println();
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    if (buttonstatus == 0){
      buttonstatus = 1;
    }else if (buttonstatus == 1){
      buttonstatus = 0;
    }
  }
  if (buttonstatus == 1){
      read_and_display(weight*4);
  }else
  read_and_display(weight);

}

void number_display(int nstNumber, int digitNum){
  if(digitNum == 1){
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
  }else if(digitNum == 2){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH); 
  }else if(digitNum == 3){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH); 
  }else{
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH); 
  }

  if(nstNumber == 0){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, LOW);
  }else if(nstNumber == 1){
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
  }else if(nstNumber == 2){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, HIGH);
  }else if(nstNumber == 3){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, HIGH);
  }else if(nstNumber == 4){
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
  }else if(nstNumber == 5){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
  }else if(nstNumber == 6){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
  }else if(nstNumber == 7){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
  }else if(nstNumber == 8){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
  }else if(nstNumber == 9){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
  }
}

void read_and_display(int number){
  if (number > 999.9) {
    number = 999.9;
  }
  int intPart = int(number);
  int decPart = int((number - intPart) * 10);

  int firstNumber = int((intPart %10) - (number - intPart));  //this num is: 1 
  int secondNumber = int(((intPart % 100) - ((intPart % 100 % 10))) / 10); //this num is: 2
  int thirdNumber = int((number - (intPart % 100)) / 100); //this num is: 3
  int fourthNumber = 0; //this num is:
  int time = 500;

  while(time > 0){
    number_display(firstNumber, 1);
    delay(5);
    number_display(secondNumber, 2);
    delay(5);
    number_display(thirdNumber, 3);
    delay(5);
    number_display(fourthNumber, 4);
    delay(5);
    time -= 25;
  }
}