#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#define button 12
String data, val1, val2, val3, val4;
int a, b, c, d, e, f;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(button, INPUT_PULLUP);
  lcd.clear();
  lcd.print("Receiver Module");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:a2b3c5d5e

  if (Serial.available() > 0) {
    data = Serial.readString();
    // Serial.println(data);
    a = data.indexOf("a");
    b = data.indexOf("b");
    a = a + 1;
    val1 = data.substring(a, b);
    // Serial.println(val1);

    b = data.indexOf("b");
    c = data.indexOf("c");
    b = b + 1;
    val2 = data.substring(b, c);
    // Serial.println(val2);

    c = data.indexOf("c");
    d = data.indexOf("d");
    c = c + 1;
    val3 = data.substring(c, d);
    // Serial.println(val3);
    delay(1000);

    d = data.indexOf("d");
    a = data.indexOf("e");
    d = d + 1;
    val4 = data.substring(d, a);
    // Serial.println(val4);

    lcd.clear();
    lcd.print("Idly:");
    lcd.print(val1);
    lcd.print("   Vada:");
    lcd.print(val2);
    lcd.setCursor(0, 1);
    lcd.print("Poori:");
    lcd.print(val3);
    lcd.print("  Dosa:");
    lcd.print(val4);
    delay(2000);
  }
  if (digitalRead(button) == LOW) {
    Serial.println("Order Received");
    delay(1000);
  }
}