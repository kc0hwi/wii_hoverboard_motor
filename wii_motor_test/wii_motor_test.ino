
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

//Pin declarations
const int PWM_PIN = 9;   // Motor speed 0-255  2-3, 5-12, 44-46 
const int DIR_PIN = 2;   // Motor Direction
const int BRAKE_PIN = 3; // Hard brake, active low

// Variables
bool dir = 0;
bool brake = 0;

void setup() {
  //Serial.begin(115200); // For debugging
  nunchuck.begin();
  if (nunchuck.type == Unknown) {
    nunchuck.type = NUNCHUCK;
  }
  // Set motor pins to outputs
  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(BRAKE_PIN, OUTPUT);
  // Initialize
  digitalWrite(BRAKE_PIN, false);
  digitalWrite(DIR_PIN, false);
  analogWrite(PWM_PIN, 0);
}

void loop() {
  nunchuck.readData();    // Read inputs and update maps

  // Read y value
  int xVal = nunchuck.getJoyX(); // 127 median
  int yVal = nunchuck.getJoyY(); // 128 median
  // map joystick values to half speed
  int ySpeed = map(yVal, 0, 255, -128, 128);

  if (nunchuck.getButtonZ()) {
    //hit the brake
    digitalWrite(BRAKE_PIN, !brake);
  }
  // If speed is positive, leave dir as is
  else if (ySpeed > 5) {
    digitalWrite(BRAKE_PIN, brake);
    analogWrite(PWM_PIN, ySpeed);
    digitalWrite(DIR_PIN, dir);
  } 
  // If speed is negative, change dir
  else if (ySpeed < -5) {
    digitalWrite(BRAKE_PIN, brake);
    analogWrite(PWM_PIN, -ySpeed);
    digitalWrite(DIR_PIN, !dir);  
  } 
  // If speed is in neutral
  else if (yVal <= 5 || yVal >= -5){
    digitalWrite(BRAKE_PIN, brake);
    analogWrite(PWM_PIN, 0);
  }
  else {
    digitalWrite(BRAKE_PIN, brake);
    analogWrite(PWM_PIN, 0);
  }

//  Serial.print("x: ");
//  Serial.print(nunchuck.getJoyX());
//  Serial.print("y position: ");
//  Serial.print(nunchuck.getJoyY());
//  Serial.print(" y speed: ");
//  Serial.print(ySpeed);
//  Serial.print("Button: "); 
//  if (nunchuck.getButtonZ()) Serial.print(" Z "); 
//  if (nunchuck.getButtonC()) Serial.print(" C "); 

  delay(20);
};


