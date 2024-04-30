#include "Arduino.h"
#include "SoftwareSerial.h"
#include "NextionX2.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

SoftwareSerial softSerial(10, 11);

NextionComPort nextion;
NextionComponent button_1(nextion, 1, 2);
NextionComponent button_2(nextion, 1, 3);
NextionComponent button_3(nextion, 1, 4);
NextionComponent button_4(nextion, 1, 5);
NextionComponent button_5(nextion, 1, 6);

NextionComponent count_1(nextion, 1, 7);
NextionComponent count_2(nextion, 1, 8);
NextionComponent count_3(nextion, 1, 9);
NextionComponent count_4(nextion, 1, 10);

uint32_t time;
#define TIMER 2000

int button_1_count = 0;
int button_2_count = 0;
int button_3_count = 0;
int button_4_count = 0;

int cost_1 = 0;
int cost_2 = 0;
int cost_3 = 0;
int cost_4 = 0;

int total_cost = 0;
void setup() {
  nextion.begin(softSerial);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(LED_BUILTIN, OUTPUT);
  nextion.picture(320, 100, 0);
  button_1.touch(button_1_pressed);
  button_2.touch(button_2_pressed);
  button_3.touch(button_3_pressed);
  button_4.touch(button_4_pressed);
  button_5.touch(button_5_pressed);
  time = millis();
  lcd.clear();
  lcd.print("Transmitter ");
  lcd.setCursor(0,1);
  lcd.print("Module");
  delay(2000);
}

void loop() {
  nextion.update();
  if (millis() > time + TIMER) {

    time = millis();
    cost_1 = button_1_count * 10;
    cost_2 = button_2_count * 20;
    cost_3 = button_3_count * 30;
    cost_4 = button_4_count * 40;

    total_cost = cost_1 + cost_2 + cost_3 + cost_4;
  }
  if (Serial.available() > 0) {

    lcd.clear();
    lcd.print("Order Received");
    lcd.setCursor(0, 1);
    lcd.print("Total Cost: ");
    lcd.print(total_cost);
    lcd.print(" /-");
    delay(15000);
    lcd.clear();
    lcd.print("Ready for");
    lcd.setCursor(0, 1);
    lcd.print("New order");
    delay(1000);

    //Serial.println(total_cost);
    button_1_count = 0;
    button_2_count = 0;
    button_3_count = 0;
    button_4_count = 0;
  }
}

void button_1_pressed() {
  button_1_count++;
  count_1.value(button_1_count);
}

void button_2_pressed() {
  button_2_count++;
  count_3.value(button_2_count);
}

void button_3_pressed() {
  button_3_count++;
  count_2.value(button_3_count);
}

void button_4_pressed() {
  button_4_count++;
  count_4.value(button_4_count);
}

void button_5_pressed() {
  lcd.clear();
  lcd.print("Sending order");
  delay(1500);
  String str = "a" + String(button_1_count) + "b" + String(button_2_count) + "c" + String(button_3_count) + "d" + String(button_4_count) + "e";
  Serial.println(str);
  delay(2000);
  count_1.value(0);
  count_2.value(0);
  count_3.value(0);
  count_4.value(0);
}