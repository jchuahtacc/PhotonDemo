#include "Adafruit_Sensor.h"
#include "Adafruit_MMA8451.h"

#define   INTERRUPT1  2

Adafruit_MMA8451 mma = Adafruit_MMA8451();

sensors_event_t event;
String firebase_event = "firebase_post";

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

void publishAccelerometer() {
  // Construct json to send
  String json = "";
  json.concat(String("{\"x\" : \""));
  json.concat(String(event.acceleration.x));
  json.concat(String("\", \"y\" : \""));
  json.concat(String(event.acceleration.y));
  json.concat(String("\", \"z\" : \""));
  json.concat(String(event.acceleration.z));
  json.concat(String("\"}"));
  Serial.println(json);
  /*
  Hey, look! Garbage collected String class means no memory leaks!
  */
  /*
  uint32_t freeMem = System.freeMemory();
  Serial.print("Free memory: ");
  Serial.println(freeMem);
  */
  // Call our firebase_post webhook with the json data to POST
  Particle.publish(firebase_event, json);
}

void loop() {
  mma.getEvent(&event);
  publishAccelerometer();
  delay(1000);
}
