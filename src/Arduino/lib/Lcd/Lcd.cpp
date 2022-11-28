#include "Lcd.h"

Lcd::Lcd() {
  lcd = new LiquidCrystal_I2C(0x27, 20, 4);
}

void Lcd::init() {
  lcd->init();
}

// Prints the given string at the given line
void Lcd::print(char* text, int line) {
    clear(line);
    strcpy(lines[line], text);
    lcd->setCursor(0, line);
    lcd->print(text);
}

// Prints the given string at the given line and column
void Lcd::print(char* text, int line, int col) {
  clear(line, col);
  strcpy(lines[line], text);
  lcd->setCursor(col, line);
  lcd->print(text);
}

// Clears the given line
void Lcd::clear(int line) {
  lcd->setCursor(0, line);
  for (unsigned int i = 0; i < LCD_LINE_LENGTH; i++) {
    lcd->print(" ");
  }
}

// Clears the given line starting from the given column
void Lcd::clear(int line, int col) {
  lcd->setCursor(col, line);
  for (unsigned int i = 0; i < LCD_NUM_LENGTH; i++) {
    lcd->print(" ");
  }
}

void Lcd::clearAll() {
  lcd->clear();
}

void Lcd::turnOn() {
  lcd->display();
  lcd->backlight();
}

void Lcd::turnOff() {
  lcd->noBacklight();
  lcd->noDisplay();
}