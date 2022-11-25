#include "Lcd.h"

Lcd::Lcd() {
  lcd = new LiquidCrystal_I2C(0x27, 20, 4);
}

void Lcd::init() {
  lcd->init();
}

void Lcd::print(String text, int line) {
    clear(line);
    lines[line] = text;
    lcd->setCursor(0, line);
    lcd->print(text);
  
}

void Lcd::clear(int line) {
  lcd->setCursor(0, line);
  for (unsigned int i = 0; i < lines[line].length(); i++) {
    lcd->print(" ");
  }
}

void Lcd::clearAll() {
  lcd->clear();
}

void Lcd::turnOn() {
  lcd->backlight();
}

void Lcd::turnOff() {
  lcd->noBacklight();
}