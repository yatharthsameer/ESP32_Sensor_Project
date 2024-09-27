#include <Wire.h>
#include <MPU6050.h>

// Pin Definitions
#define LDRPIN 2 // LM393 sensor
#define IRPIN 34 // IR sensor pin

// MPU6050 object
MPU6050 mpu;

// Setup function
void setup()
{
  // Initialize Serial
  Serial.begin(115200);

  // Initialize MPU6050
  Wire.begin();

  // Uncomment the following block to enable MPU6050

  mpu.initialize();

  // Check MPU connection
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully.");
  } else {
    Serial.println("Failed to connect MPU6050.");
    while (1);  // Stop the program if MPU6050 fails to connect
  }


  // Print CSV Header
  Serial.println("Timestamp,LM393,IR Sensor,MPU6050_X,MPU6050_Y,MPU6050_Z");

  // Uncomment the following lines to enable LM393 sensor

  pinMode(LDRPIN, INPUT);  // LM393 sensor input


  // Uncomment the following lines to enable IR sensor
  
  pinMode(IRPIN, INPUT);   // IR sensor input
  
}

// Main loop
void loop()
{
  // Get the current timestamp
  unsigned long timestamp = millis();

  Serial.print(timestamp);

  // Uncomment the following block to enable LM393 sensor reading

  int lm393Val = digitalRead(LDRPIN);
  Serial.print(",");
  Serial.print(lm393Val);
  

  // Uncomment the following block to enable IR sensor reading
  
  int irVal = analogRead(IRPIN);
  Serial.print(",");
  Serial.print(irVal);
  

  // Uncomment the following block to enable MPU6050 sensor reading

  int16_t accelX, accelY, accelZ;
  mpu.getAcceleration(&accelX, &accelY, &accelZ);
  Serial.print(",");
  Serial.print(accelX);
  Serial.print(",");
  Serial.print(accelY);
  Serial.print(",");
  Serial.print(accelZ);
  

  Serial.println(); // Print newline for each row

  // Wait for 2 seconds before reading the next set of data
  delay(2000);
}
