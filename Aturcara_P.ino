#include "CytronMotorDriver.h"
CytronMD motor1(PWM_PWM, 3, 9);   // PWM 1A = Pin 3, PWM 1B = Pin 9.
CytronMD motor2(PWM_PWM, 10, 11); // PWM 2A = Pin 10, PWM 2B = Pin 11.

#define calibrate   A1
#define pushButton  2
#define buzz        8

//================ PEMBOLEH UBAH KAWALAN P ================
const int sasaran = 500;
const int kelajuanAsas = 100;

float Kp = 0.2;

int line = 0;
int ralat = 0;
int pembetulan = 0;
int motorKiri = 0;
int motorKanan = 0;

void setup() 
{ Serial.begin(9600);
  calibMakerLine();
}

void loop() 
{ if (PB_pressed() == 1)
  { while(1)
    { 
      line = analogRead(A0);

      // Kira ralat dan pembetulan
      ralat = sasaran - line;
      pembetulan = Kp * ralat;

      // Kira arahan kelajuan motor
      motorKiri  = kelajuanAsas + pembetulan;
      motorKanan = kelajuanAsas - pembetulan;

      // Hadkan arahan motor kepada 0 hingga 255
      motorKiri  = constrain(motorKiri, 0, 255);
      motorKanan = constrain(motorKanan, 0, 255);

      move(motorKiri, motorKanan);
    }
  }
}

//====================================== SUBROUTINES ======================================
uint8_t PB_pressed()
{ uint8_t pb;
  pb = digitalRead(pushButton);
  pb =! pb;
  return pb;
}

void calibMakerLine()
{ pinMode(calibrate,OUTPUT);
  pinMode(pushButton,INPUT_PULLUP);

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
