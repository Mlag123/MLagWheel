/*
README
Version firmware 1.0.0
Use library:
Arduino Joystick Library = by MHeironimus. GitHub = https://github.com/MHeironimus/ArduinoJoystickLibrary;
GyverEncoder = by AlexGyver https://github.com/AlexGyver temporarily not used.
Author firmware MLag = GitHub https://github.com/Mlag123
ENG:
This is firmware for wheel supported next Arduino board:
Arduino micro, Arduno Leonardo. It is on chips ATmega32U4
I do not guarantee work on other boards.
RU:
Эта прошивка для руля поддерживает следующие виды ардуино плат:
Arduino micro, Arduno Leonardo. Только на чипах ATmega32U4
Я не гарантирую корректную работу прошивки на других платах или чипах.
Спасибо за понимание.
В будущем хочу сделать поддержку калибровки руля, и сохранение данных в EEPROM, но пока ещё с этим не разобрался.

*/


#include <GyverEncoder.h>

#include <Joystick.h>
Joystick_ Joystick;

#define wheel A1
#define but_1 3
#define debug 0       // Дебаг | debug
#define typeSensor 0  //если энокдер, то выставите 1, если потенцимоетр, то выставите 0 | If an encoder is used, then set 1, if a potentiometer, then 0
#define ENC_A 2
#define ENC_B 4
#define ENC_TYPE 1          //type Encodeer
#define minRangeWheel 0     // минимальное значение руля 0,1023 |  Minimal range wheel 0-1023 
#define maxRangeWheel 1023  // максимальное значение руля 0,1023 | Max range wheel 0-1023
#define clutch A2
#define brake A3
#define throttle A4
#define clutch_on 1    //есть ли педаль сцепления?, если да, то 1  | is there a clutch pedal? Put 1
#define brake_on 1     //есть ли педаль тормоза?, если да, то 1 | is there a brake pedal? Put 1
#define throttle_on 1  //есть ли педаль газа?, если да, то 1 | is there a throttle pedal? Put 1


volatile int encCounter;
volatile boolean state0, lastState, turnFlag;



void setup() {
  // put your setup code here, to run once:
  /* pinMode(but_1, INPUT);
  pinMode(wheel, OUTPUT);

  pinMode(clutch, INPUT);
  pinMode(brake, INPUT);
  pinMode(throttle, INPUT);
  */



  attachInterrupt(0, enc, CHANGE);  //прерывание
  Joystick.begin();
}

int enc() {
  state0 = digitalRead(ENC_A);
  if (state0 != lastState) {
#if (ENC_TYPE == 1)
    turnFlag = !turnFlag;
    if (turnFlag)
      encCounter += (digitalRead(ENC_B) != lastState) ? -1 : 1;
#endif
    lastState = state0;
    return lastState;
  }
}
int clutchAxis() {
  int clutch_change = map(analogRead(clutch), 0, 1023, -127, 128);
  if (clutch_on == 1) {
    Joystick.setZAxis(clutch_change);
  }
  return clutch_change;
}
int brakeAxis() {
  int brake_change = map(analogRead(brake), 0, 1023, -127, 128);
  if (brake_on == 1) {
    Joystick.setYAxis(brake_change);
  }
  return brake_change;
}
int throttleAxis() {
  int throttle_change = map(analogRead(throttle), 0, 1023, -127, 128);
if(throttle_on == 1){
    Joystick.setRxAxis(throttle_change);
}
  return throttle_change;
}
void loop() { 
  Joystick.setXAxisRange(minRangeWheel, maxRangeWheel);


  int wheel_axis;


  if (typeSensor == 0) {
    wheel_axis = map(analogRead(wheel), minRangeWheel, maxRangeWheel, -128, 127);
  } else if (typeSensor == 1) {

    wheel_axis = map(enc(), minRangeWheel, maxRangeWheel, -128, 127);
  }

  if (debug == 1) {

    Serial.println(wheel_axis);
    Serial.println(clutchAxis());
    Serial.println(brakeAxis());
    Serial.println(throttleAxis());
  }


  Joystick.setXAxis(wheel_axis);
  int throttleAxis();
  int brakeAxis();
  int clutchAxis();
  delay(10);



  // put your main code here, to run repeatedly:
}
