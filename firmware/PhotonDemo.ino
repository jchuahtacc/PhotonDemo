#include "Adafruit_Sensor.h"
#include "Adafruit_MMA8451.h"

#define   INTERRUPT1  2

Adafruit_MMA8451 mma = Adafruit_MMA8451();

sensors_event_t event;


void setup() {
  Serial.begin(9600); // Enable serial on USB port
  Serial.println("Hello, friend.");
  Serial.println("Starting MMA8451");
  if (!mma.begin(MMA8451_DEFAULT_ADDRESS)) {
    Serial.println("MMA8451 could not initialize!");
    while(1);       // infinite loop to "halt" the device if accelerometer fails to init
  }
  Serial.println("MMA8451 initialized");

}

void loop() {
  mma.getEvent(&event);
  Serial.print("X ");
  Serial.print(event.acceleration.x);
  Serial.print("\t");
  Serial.print("Y ");
  Serial.print(event.acceleration.y);
  Serial.print("\t");
  Serial.print("Z ");
  Serial.print(event.acceleration.z);
  Serial.print("\t");
  delay(1000);
}
