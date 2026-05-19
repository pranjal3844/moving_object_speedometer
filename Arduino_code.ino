#include <LiquidCrystal.h>
// LCD pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// Pin assignments
const int irSensor1 = 2;
const int irSensor2 = 3;
const int ledPin = 5; // LED moved to D7
const int buzzerPin = 6; // Buzzer remains on D6
// Speed parameters
const float distance = 0.13; // 13 cm = 0.13 meters
const float speedLimit = 2.0; // Speed threshold in m/s
unsigned long time1 = 0;
unsigned long time2 = 0;
float speed = 0;
void setup() {
pinMode(irSensor1, INPUT);
pinMode(irSensor2, INPUT);
pinMode(ledPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
lcd.begin(16, 2);
lcd.print("Speed Detector");
delay(2000);
lcd.clear();
Serial.begin(9600); // For debugging
}
void loop() {
lcd.setCursor(0, 0);
lcd.print("Waiting Object");
// Wait for object at IR sensor 1
while (digitalRead(irSensor1) == HIGH);
time1 = millis();
digitalWrite(ledPin, HIGH);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Object Detected");
// Wait for object at IR sensor 2
while (digitalRead(irSensor2) == HIGH);
time2 = millis();
digitalWrite(ledPin, LOW);
// Calculate speed
float timeTaken = (time2 - time1) / 1000.0;
speed = distance / timeTaken;
// Debug output
Serial.print("Time: ");
Serial.print(timeTaken);
Serial.print(" s | Speed: ");
Serial.print(speed);
Serial.println(" m/s");
// Display on LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Speed: ");
lcd.print(speed, 2);
lcd.print(" m/s");
if (speed > speedLimit) {
Serial.println("Overspeed! Buzzer ON");
digitalWrite(buzzerPin, HIGH); // Buzzer ON
digitalWrite(ledPin, HIGH); // LED ON
lcd.setCursor(0, 1);
lcd.print("Over Speed!");
delay(1200); // Buzzer & LED stay ON for 5s
digitalWrite(buzzerPin, LOW); // Buzzer OFF
digitalWrite(ledPin, LOW); // LED OFF
} else {
lcd.setCursor(0, 1);
lcd.print("Speed Normal");
delay(2000);
}
lcd.clear();
}
