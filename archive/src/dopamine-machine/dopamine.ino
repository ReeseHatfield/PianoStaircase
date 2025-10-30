#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  //Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    //Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  //Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

bool isPlaying = false;
void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  // if (isPlaying) {
  //   digitalWrite(4, HIGH);
  // } else {
  //   digitalWrite(4,LOW);
  // }

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    //Serial.print("Distance (mm): "); 
    int distance = measure.RangeMilliMeter;
    
    Serial.println(distance);
    if(distance < 1000 && distance > 30){

      tone(10,261.6+distance*1.25 -30);
      digitalWrite(4,HIGH);
    }
    else {
      noTone(10);
      digitalWrite(4,LOW);
    }
    
    
  } else {
    //Serial.println(" out of range...rip ");
    Serial.println("-1");
    noTone(10);
    digitalWrite(4,LOW);
  }
    
  delay(100);
}