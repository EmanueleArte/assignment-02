#include "Lcd.h"

void Lcd::init() {
  lcd = LiquidCrystal_I2C(0x27, 20, 4);
  lcd.init();
}

void Lcd::print(String text, int line) {
  lines[line] = text;
  lcd.setCursor(0, line);
  clear(line);
  lcd.print(text);
}

void Lcd::clear(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < lines[line].length(); i++) {
    lcd.print(" ");
  }
}

void Lcd::clearAll() {
  lcd.clear();
}

void Lcd::turnOn() {
  lcd.backlight();
}

void Lcd::turnOff() {
  lcd.noBacklight();
}