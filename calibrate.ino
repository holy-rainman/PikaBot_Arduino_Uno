#include "CytronMotorDriver.h"
CytronMD motor1(PWM_PWM, 3, 9);   // PWM 1A = Pin 3, PWM 1B = Pin 9.
CytronMD motor2(PWM_PWM, 10, 11); // PWM 2A = Pin 10, PWM 2B = Pin 11.

#define calibrate A1

void setup() 
{ Serial.begin(9600);
  calibMakerLine();
}

void loop() 
{ Serial.println(analogRead(A0));
}

//====================================== SUBROUTINES ======================================
void calibMakerLine()
{ pinMode(calibrate,OUTPUT);

  //long press on push button
  digitalWrite(calibrate,LOW);  delay(3000);  digitalWrite(calibrate,HIGH);

  move(150,-150);  delay(500);
  move(-150,150);  delay(800);
  move(150,-150);  delay(500);
  stop();     

  //short press on push button
  digitalWrite(calibrate,LOW);  delay(500);   digitalWrite(calibrate,HIGH);
}

void move(int16_t motorL, int16_t motorR)
{ motorR = motorR*-1; //inverting to obtain +ve value for forward
  motorL = motorL*-1; 
  
  motor1.setSpeed(motorR);
  motor2.setSpeed(motorL);
}

void stop()
{ motor1.setSpeed(0);
  motor2.setSpeed(0);
}
