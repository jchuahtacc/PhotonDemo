#include "Adafruit_Sensor.h"
#include "Adafruit_MMA8451.h"

#define   INTERRUPT1  2

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup() {
  mma.begin(MMA8451_DEFAULT_ADDRESS);

}

void loop() {


}
