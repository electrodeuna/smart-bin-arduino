#include <Servo.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Variables globales
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;
Servo myservo; 

void setup() {
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  Serial.begin(9600);
// Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Adjust the Proximity sensor gain
  if ( !apds.setProximityGain(PGAIN_2X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the APDS-9960 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
}

void loop() {

  if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    if(proximity_data >100) {
      myservo.write(90);                 
      delay(3000);  
      myservo.write(0);         
    }
  }

  delay(250);                          
}
