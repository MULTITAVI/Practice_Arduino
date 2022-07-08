#include <DynamixelWorkbench.h>

#define DEVICE_NAME "3"
#define BAUDRATE 1000000

DynamixelWorkbench dxl;
uint8_t dxl_id_line = 1;
uint8_t dxl_id_hand_MX_28_lower = 7;
uint8_t dxl_id_hand_MX_106 = 2;
uint8_t dxl_id_hand_MX_64 = 3;
uint8_t dxl_id_hand_MX_28_upper = 4;
uint8_t dxl_id_hand_AX_18A = 5;
uint8_t dxl_id_hand_AX_18A_grip = 6;

int pinX = A0;
int pinY = A1;
int pinX_2 = A3;
int pinY_2 = A4;
int pinZ_3 = A7;

void setup() {
  Serial.begin(57600);
  while(!Serial) {}

  const char* log;
  bool result = false;

  uint16_t model_number = 0;

  result = dxl.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);
  }

  result = dxl.ping(dxl_id_line, &model_number, &log) and dxl.ping(dxl_id_hand_MX_28_lower, &model_number, &log) and \
           dxl.ping(dxl_id_hand_MX_106, &model_number, &log) and dxl.ping(dxl_id_hand_MX_64, &model_number, &log) and \
           dxl.ping(dxl_id_hand_MX_28_upper, &model_number, &log) and dxl.ping(dxl_id_hand_AX_18A, &model_number, &log) and \
           dxl.ping(dxl_id_hand_AX_18A_grip, &model_number, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else {
    Serial.println("Succeeded to ping");
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl.jointMode(dxl_id_hand_MX_106, 0, 0, &log) and dxl.jointMode(dxl_id_hand_MX_64, 0, 0, &log) and \
            dxl.jointMode(dxl_id_hand_MX_28_upper, 0, 0, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else {
    Serial.println("Succeed to change joint mode");
    Serial.println("Dynamixel is ready to move");
    Serial.println("Zero calibration. Please wait");

    dxl.goalVelocity(dxl_id_hand_MX_106, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_MX_106, (int32_t)2048);
    delay(2000);
    dxl.goalVelocity(dxl_id_hand_MX_64, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_MX_64, (int32_t)2000);
    delay(2000);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_MX_28_upper, (int32_t)3000);
  }

  result = dxl.jointMode(dxl_id_hand_MX_28_lower, 0, 0, &log) and dxl.jointMode(dxl_id_hand_MX_106, 0, 0, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else {
    Serial.println("Succeed to change joint mode");
    Serial.println("Dynamixel is ready to wheel");
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, (int32_t)50);
    dxl.goalVelocity(dxl_id_hand_MX_106, (int32_t)50);
  }

  result = dxl.wheelMode(dxl_id_hand_MX_28_lower, 0, &log) and dxl.wheelMode(dxl_id_hand_MX_106, 0, &log) and \
            dxl.wheelMode(dxl_id_hand_MX_64, 0, &log) and dxl.wheelMode(dxl_id_hand_MX_28_upper, 0, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }
  else {
    Serial.println("Succeed to change wheel mode");
    Serial.println("Dynamixel is ready to wheel");
  }

  result = dxl.jointMode(dxl_id_hand_AX_18A_grip, 0, 0, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else {
    Serial.println("Succeed to change joint mode");
    Serial.println("Dynamixel is ready to wheel");
  } 
}

void loop() {
  int32_t X = analogRead(pinX);
  int32_t Y = analogRead(pinY);
  
  int32_t X_2 = analogRead(pinX_2);
  int32_t Y_2 = analogRead(pinY_2);

  int32_t Z_3 = analogRead(pinZ_3);
  
  if (X < 700 and Y < 650) {
    int32_t xAngle = map(X, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, 50);
    int32_t yAngle = map(Y, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_106, 50);
  }
  else if (X > 900 and Y < 650) {
    int32_t xAngle = map(X, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, -50);
    int32_t yAngle = map(Y, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_106, 50);
  }
  else if (X > 700 and X < 950 and Y < 650) {
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, 0);
    int32_t yAngle = map(Y, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_106, 50);
  }
 else if (X < 700 and Y > 650 and Y < 950) {
    int32_t xAngle = map(X, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, 50);
    dxl.goalVelocity(dxl_id_hand_MX_106, 0);
  }
  else if (X > 900 and Y > 650 and Y < 950) {
    int32_t xAngle = map(X, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, -50);
    dxl.goalVelocity(dxl_id_hand_MX_106, 0);
  }
  else if (X > 700 and X < 900 and Y > 650 and Y < 950) {
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, 0);
    dxl.goalVelocity(dxl_id_hand_MX_106, 0);
  }
  else if (X < 700 and Y > 950) {
    int32_t xAngle = map(X, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, 50);
    int32_t yAngle = map(Y, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_106, -50);
  }
  else if (X > 900 and Y > 950) {
    int32_t xAngle = map(X, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, -50);
    int32_t yAngle = map(Y, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_106, -50);
  }
  else if (X > 700 and X < 900 and Y > 950) {
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, 0);
    int32_t yAngle = map(Y, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_106, -50);
  }



  if (X_2 < 700 and Y_2 < 650) {
    int32_t xAngle = map(X_2, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_64, 50);
    int32_t yAngle = map(Y_2, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, 50);
  }
  else if (X_2 > 900 and Y_2 < 650) {
    int32_t xAngle = map(X_2, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_64, -50);
    int32_t yAngle = map(Y_2, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, 50);
  }
  else if (X_2 > 700 and X_2 < 950 and Y_2 < 650) {
    dxl.goalVelocity(dxl_id_hand_MX_64, 0);
    int32_t yAngle = map(Y_2, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, 50);
  }
 else if (X_2 < 700 and Y_2 > 650 and Y_2 < 950) {
    int32_t xAngle = map(X_2, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_64, 50);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, 0);
  }
  else if (X_2 > 900 and Y_2 > 650 and Y_2 < 950) {
    int32_t xAngle = map(X_2, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_64, -50);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, 0);
  }
  else if (X_2 > 700 and X_2 < 900 and Y_2 > 650 and Y_2 < 950) {
    dxl.goalVelocity(dxl_id_hand_MX_64, 0);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, 0);
  }
  else if (X_2 < 700 and Y_2 > 950) {
    int32_t xAngle = map(X_2, 0, 700, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_64, 50);
    int32_t yAngle = map(Y_2, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, -50);
  }
  else if (X_2 > 900 and Y_2 > 950) {
    int32_t xAngle = map(X_2, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_64, -50);
    int32_t yAngle = map(Y_2, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, -50);
  }
  else if (X_2 > 700 and X_2 < 900 and Y_2 > 950) {
    dxl.goalVelocity(dxl_id_hand_MX_64, 0);
    int32_t yAngle = map(Y_2, 900, 1023, 0, 100);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, -50);
  }

  if (X_2 > 700 and X_2 < 900 and Y_2 > 650 and Y_2 < 950 and X > 700 and X < 900 and Y > 650 and Y < 950) {
    if (Z_3) {
      dxl.goalPosition(dxl_id_hand_AX_18A_grip, 450);
    }
    else {
      dxl.goalPosition(dxl_id_hand_AX_18A_grip, 700);
    }
  }
}
