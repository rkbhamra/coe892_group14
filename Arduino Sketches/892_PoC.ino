#include "thingProperties.h"

#define PHOTORESISTOR0_PIN 34 
#define PHOTORESISTOR1_PIN 32  
#define PHOTORESISTOR2_PIN 35 
#define PHOTORESISTOR3_PIN 33  
#define LIGHT_THRESHOLD 2000   

void setup() {
  Serial.begin(9600);
  delay(1500); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
    ArduinoCloud.update();

    // Read light levels
    int light0 = analogRead(PHOTORESISTOR0_PIN);
    int light1 = analogRead(PHOTORESISTOR1_PIN);
    int light2 = analogRead(PHOTORESISTOR2_PIN);
    int light3 = analogRead(PHOTORESISTOR3_PIN);

    // Update boolean variables based on threshold
    photoResistor0 = (light0 > LIGHT_THRESHOLD);
    photoResistor1 = (light1 > LIGHT_THRESHOLD);
    photoResistor2 = (light2 > LIGHT_THRESHOLD);
    photoResistor3 = (light3 > LIGHT_THRESHOLD);

    // Debugging output
    Serial.print("Light Level 0: ");
    Serial.print(light0);
    Serial.print(" -> ");
    Serial.println(photoResistor0 ? "HIGH" : "LOW");

    Serial.print("Light Level 1: ");
    Serial.print(light1);
    Serial.print(" -> ");
    Serial.println(photoResistor1 ? "HIGH" : "LOW");

    Serial.print("Light Level 2: ");
    Serial.print(light2);
    Serial.print(" -> ");
    Serial.println(photoResistor2 ? "HIGH" : "LOW");

    Serial.print("Light Level 3: ");
    Serial.print(light3);
    Serial.print(" -> ");
    Serial.println(photoResistor3 ? "HIGH" : "LOW");
}
