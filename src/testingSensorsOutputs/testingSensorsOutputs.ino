#include "Arduino_SensorKit.h"

#include "LiquidCrystal_I2C.h"
#include "Wire.h"

#define Environment Environment_I2C

#define MOSTURE_SENSOR_PIN A0

#define LED_WET 13

#define LED_DRY 12

#define DRYLEVEL 520
#define WETLEVEL 215

#define DAMPINTERVAL 50

LiquidCrystal_I2C lcd(0x27,  16, 2);

void checkWetDry(int moisture) {
  if (moisture > DRYLEVEL - DAMPINTERVAL) {
    Serial.println("dry");
    digitalWrite(LED_DRY, HIGH);
    digitalWrite(LED_WET, LOW);
  }
  else if (moisture < WETLEVEL + DAMPINTERVAL) {
    Serial.println("wet");
    digitalWrite(LED_WET, HIGH);
    digitalWrite(LED_DRY, LOW);
  }
  else {
    Serial.println("damp");
    digitalWrite(LED_WET, HIGH);
    digitalWrite(LED_DRY, HIGH);
  }

  return;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED_WET, OUTPUT);
  pinMode(LED_DRY, OUTPUT);

  digitalWrite(LED_WET, HIGH);
  digitalWrite(LED_DRY, LOW);

  Wire.begin();

  Environment.begin();

  lcd.init();
  lcd.backlight();

  lcd.print("Begining");
}

void loop() {
  // put your main code here, to run repeatedly:
  int moistureLevel = analogRead(MOSTURE_SENSOR_PIN);
  Serial.println(moistureLevel);

  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.print(Environment.readHumidity());

  lcd.setCursor(0,1);
  lcd.print("Temperature:");
  lcd.print(Environment.readTemperature());

  checkWetDry(moistureLevel);

  delay(500);
}
