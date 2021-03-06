#include "Adafruit_Sensor.h"
#include "Adafruit_MMA8451.h"

#define   INT2  D3

Adafruit_MMA8451 mma = Adafruit_MMA8451();

sensors_event_t event;

String firebase_patch = "firebase_patch";
String firebase_delete = "firebase_delete";

volatile bool clicked = false;

void setup() {
  Serial.begin(9600); // Enable serial on USB port
  Serial.println("Hello, friend.");
  Serial.println("Starting MMA8451");
  if (!mma.begin(MMA8451_DEFAULT_ADDRESS)) {
    Serial.println("MMA8451 could not initialize!");
    while(1);       // infinite loop to "halt" the device if accelerometer fails to init
  }
  Serial.println("MMA8451 initialized");
  pinMode(INT2, INPUT);
  attachInterrupt(INT2, ISR, RISING);
  Serial.println("Waiting for first click");
  while (!clicked) delay(500);
  Serial.println("Received first click");
}

void ISR() {
  Serial.println("interrupt!");
  // clear interrupt source
  uint8_t interrupts = mma.getInterruptSource();
  clicked = !clicked;
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
  Particle.publish(firebase_patch, json);
}

void publishToDashboard() {
  Particle.variable("x", String(event.acceleration.x));
  Particle.variable("y", String(event.acceleration.y));
  Particle.variable("z", String(event.acceleration.z));
}

void loop() {
  if (clicked) {
    Serial.println("publishing");
    mma.getEvent(&event);
    publishAccelerometer();
  //  publishToDashboard();
  } else {
    Serial.println("quiet");
  }
  delay(2000);
}
