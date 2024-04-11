//Instructions
//433Mhz Transmitter Pin: Arduino GPIO 12

//Library
#include <VirtualWire.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

void setup()
{
  Serial.begin(9600);	  // Debugging only
  Serial.println("setup");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(2000);	            // Bits per sec
}

const int ANGLE_THRESHOLD = 3;

void loop()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  int ANGLE_X = a.acceleration.x;
  int ANGLE_Y = a.acceleration.y;

  char *msg = "0";

  Serial.print("X: ");
  Serial.print(ANGLE_X);
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(ANGLE_Y);

  if(ANGLE_X > (ANGLE_THRESHOLD)){
    msg = "1";
  } else if(ANGLE_X < (ANGLE_THRESHOLD * -1)){
    msg = "2";
  } else if(ANGLE_Y > (ANGLE_THRESHOLD)){
    msg = "3";
  } else if(ANGLE_Y < (ANGLE_THRESHOLD * -1)){
    msg = "4";
  }

  Serial.print("\t");
  Serial.println(msg);
  
  digitalWrite(13, true); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, false);
  delay(100);
}
