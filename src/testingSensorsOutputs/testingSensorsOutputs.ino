#include "Arduino_SensorKit.h"

#define Environment Environment_I2C

#define MOSTURE_SENSOR_PIN A0

#define LED_WET 13

#define LED_DRY 12

#define DRYLEVEL 520
#define WETLEVEL 215

#define DAMPINTERVAL 50

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

  Serial.println("Begining");
}

void loop() {
  // put your main code here, to run repeatedly:
  int moistureLevel = analogRead(MOSTURE_SENSOR_PIN);
  Serial.println(moistureLevel);

  Serial.print("Humidity = ");
  Serial.println(Environment.readHumidity());

  Serial.print("Temperature = ");
  Serial.println(Environment.readTemperature());

  checkWetDry(moistureLevel);

  delay(500);
}
