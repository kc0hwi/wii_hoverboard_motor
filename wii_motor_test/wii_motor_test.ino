/*   Control two scooter motors with wii nunchuck
 *   
 *   https://mad-ee.com/controlling-a-hoverboard-motor-with-a-simple-arduino/
 *     
 *   
 *   
 *   Platform:  Arduino MEGA
 */
#include <WiiChuck.h>

Accessory nunchuck;

// some constants
int minSpeed = -128;
int maxSpeed = 128;
int lowerDeadZone = -5;
int upperDeadZone = 5;

// intialize some variables
int leftSpeed = 0;
int rightSpeed = 0;
bool leftDir = 0;
bool leftBrake = 0;
bool rightDir = 0;
bool rightBrake = 0;

//Pin declarations
const int L_PWM_PIN = 9;   // Motor speed 0-255  2-3, 5-12, 44-46 
const int L_DIR_PIN = 2;   // Motor Direction
const int L_BRAKE_PIN = 3; // Hard brake, active low
const int R_PWM_PIN = 10;   
const int R_DIR_PIN = 5;   
const int R_BRAKE_PIN = 6; 

void setup() {
  Serial.begin(115200);
  nunchuck.begin();
  if (nunchuck.type == Unknown) {
    nunchuck.type = NUNCHUCK;
  }
//    // Set motor pins to outputs
//  pinMode(PWM_PIN, OUTPUT);
//  pinMode(DIR_PIN, OUTPUT);
//  pinMode(BRAKE_PIN, OUTPUT);
//  // Initialize
//  digitalWrite(BRAKE_PIN, false);
//  digitalWrite(DIR_PIN, false);
//  analogWrite(PWM_PIN, 0);
}

void loop() {
  nunchuck.readData();    // Read inputs and update maps
  
  // Read x y  values
  int xVal = nunchuck.getJoyX(); // 127 median
  int yVal = nunchuck.getJoyY(); // 128 median
  // map joystick values
  int yMap = map(yVal, 0, 255, -128, 128);
  int xMap = map(xVal, 0, 255, -128, 128);

  if (nunchuck.getButtonZ()) {
    // Engage the brakes
    setBrakes();
  }
  else if (xMap < 0 && yMap > 0) { 
    leftSpeed = yMap + xMap;
    rightSpeed = yMap;
  }
  else if (xMap > 0 && yMap > 0) {
    leftSpeed = yMap;
    rightSpeed = yMap - xMap; 
  }
  else if (xMap < 0 && yMap < 0) { // reverse and swinging left
    leftSpeed =  yMap - xMap;
    rightSpeed = yMap;
  } 
  else if (xMap > 0 && yMap < 0) { // reverse and swinging right
    leftSpeed = yMap; 
    rightSpeed = yMap + xMap; 
  } 
  else if (xMap < 0 && yMap == 0) {
    leftSpeed = yMap;
    rightSpeed = -xMap; // spin left in place
  } 
  else if (xMap > 0 && yMap == 0) {
    leftSpeed = xMap; // spin right in place
    rightSpeed = yMap;
  } 
  else {
    leftSpeed = 0;
    rightSpeed = 0;
  }

  Serial.print("x: ");
  Serial.print(xMap);
  Serial.print(" y: ");
  Serial.print(yMap);
  Serial.print("    ");
  Serial.print("left speed: ");
  Serial.print(leftSpeed);
  Serial.print(" right speed: ");
  Serial.print(rightSpeed);
//  Serial.print("Button: "); 
//  if (nunchuck.getButtonZ()) Serial.print(" Z "); 
//  if (nunchuck.getButtonC()) Serial.print(" C "); 

  Serial.println();
  delay(50);
}

void setLeftMotor(int leftSpeed) {
   Serial.println('left speed debug');
}

void setRightMotor(int rightSpeed) {
   Serial.println('right speed debug');
}

void setBrakes() {
  digitalWrite(L_BRAKE_PIN, !leftBrake);
  digitalWrite(R_BRAKE_PIN, !rightBrake);
}

