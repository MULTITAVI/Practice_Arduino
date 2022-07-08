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

  result = dxl.jointMode(dxl_id_line, 0, 0, &log) and dxl.jointMode(dxl_id_hand_MX_106, 0, 0, &log) and \
           dxl.jointMode(dxl_id_hand_MX_64, 0, 0, &log) and dxl.jointMode(dxl_id_hand_MX_28_upper, 0, 0, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else {
    Serial.println("Succeed to change joint mode");
    Serial.println("Dynamixel is ready to move");
    Serial.println("Zero calibration. Please wait");

    
    dxl.goalPosition(dxl_id_line, (int32_t)0);
    delay(5000);
    dxl.goalVelocity(dxl_id_hand_MX_106, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_MX_106, (int32_t)2048);
    delay(5000);
    dxl.goalVelocity(dxl_id_hand_MX_28_upper, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_MX_28_upper, (int32_t)3000);
    delay(5000);
    dxl.goalVelocity(dxl_id_hand_MX_64, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_MX_64, (int32_t)2000);
    delay(5000);
  
    Serial.println("Put the item on the conveyor belt");

    delay(10000);
  }

  result = dxl.jointMode(dxl_id_hand_MX_28_lower, 0, 0, &log) and dxl.jointMode(dxl_id_hand_AX_18A_grip, 0, 0, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else {
    dxl.goalVelocity(dxl_id_hand_MX_28_lower, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_MX_28_lower, (int32_t)3072);
    delay(5000);
    dxl.goalVelocity(dxl_id_hand_AX_18A_grip, (int32_t)50);
    dxl.goalPosition(dxl_id_hand_AX_18A_grip, (int32_t)700);
  }

  result = dxl.wheelMode(dxl_id_line, 0, &log);
  if (result == false) {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }
  else {
    Serial.println("Dynamixel is ready to wheel");
  }
}

void loop() {
  
  dxl.goalVelocity(dxl_id_line, (int32_t)-200);
  delay(10500);
  dxl.goalVelocity(dxl_id_line, (int32_t)0);
  dxl.goalPosition(dxl_id_hand_MX_106, (int32_t)1688);
  delay(1000);
  dxl.goalPosition(dxl_id_hand_MX_64, (int32_t)2600);
  delay(5000);
  dxl.goalPosition(dxl_id_hand_MX_28_upper, (int32_t)1024);
  delay(5000);
  dxl.goalPosition(dxl_id_hand_AX_18A_grip, (int32_t)450);
  delay(5000);
  dxl.goalPosition(dxl_id_hand_MX_28_lower, (int32_t)1024);
  delay(5000);
  dxl.goalPosition(dxl_id_hand_AX_18A_grip, (int32_t)700);
  delay(5000);
  delay(100000);
  delay(5000);
  dxl.goalVelocity(dxl_id_line, (int32_t)200);
  delay(10500);
}
