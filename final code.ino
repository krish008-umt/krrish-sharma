#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Correct LCD initialization with the most common I2C address (0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define HIGH_LIGHT 70  // Adjusted threshold for percentage scale

// Pin Definitions
const int ldrPin1 = A0;
const int ldrPin2 = A1;
const int ENA1 = 5;  // PWM for Motor 1
const int ENA2 = 6;  // PWM for Motor 2
const int IN1 = 10;
const int IN2 = 9;
const int IN3 = 11;
const int IN4 = 12;

void setup() {
    Wire.begin();  // Start I2C communication
    lcd.begin(16,2);   // Initialize LCD
    lcd.backlight();

    pinMode(ldrPin1, INPUT);
    pinMode(ldrPin2, INPUT);
    pinMode(ENA1, OUTPUT);
    pinMode(ENA2, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Stop Motors at Start
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void loop() {
    // Read Light Sensors
    int sensorValue1 = analogRead(ldrPin1);
    int sensorValue2 = analogRead(ldrPin2);

    // Convert LDR values to percentage (0-100)
    int intensity1 = map(sensorValue1, 0, 1023, 0, 100);
    int intensity2 = map(sensorValue2, 0, 1023, 0, 100);
    int avg_intensity = (intensity1 + intensity2) / 2;

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Light Intensity:");
    lcd.setCursor(0, 1);
    lcd.print(avg_intensity);
    lcd.print("%");

    // Motor Control Based on Light Intensity
    if (avg_intensity > HIGH_LIGHT) {
        analogWrite(ENA1, 255);  // Full speed
        analogWrite(ENA2, 255);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    } 
  else {
        analogWrite(ENA1, 30);  // Reduced speed
        analogWrite(ENA2, 0);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }

    delay(1000);  // Wait 1 second before updating again
}

    
 

