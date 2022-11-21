#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
#include "MsgService.h"

Ultrasonic us(12, 13);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

void setup() {
  Serial.begin(9600);
  //lcd.init();
  //lcd.backlight();
  MsgService.init();
}

void loop() {
  /*int distance = us.read();
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print(distance);
  Serial.println(distance);
  delay(200);*/

  MsgService.sendMsg("pong");
  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();    
    if (msg->getContent() == "ping"){
       delay(500);
       MsgService.sendMsg("pong");
    }
    /* NOT TO FORGET: message deallocation */
    delete msg;
  }
}