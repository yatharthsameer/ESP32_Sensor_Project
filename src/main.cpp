#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"

// Pin Definitions
#define LDRPIN 2 // LM393 sensor
#define IRPIN 34 // IR sensor pin

// MPU6050 object
MPU6050 mpu;

// CSI Callback Function
void csi_callback(void *ctx, wifi_csi_info_t *data)
{
  // Get the current timestamp
  unsigned long timestamp = millis();

  // Prepare a buffer for the CSI data
  char csi_buffer[1024];
  int offset = 0;

  // Add timestamp and sensor type
  offset += sprintf(csi_buffer + offset, "%lu,CSI,", timestamp);

  // Add MAC address
  for (int i = 0; i < 6; i++)
  {
    offset += sprintf(csi_buffer + offset, "%02X", data->mac[i]);
    if (i < 5)
      offset += sprintf(csi_buffer + offset, ":");
  }
  offset += sprintf(csi_buffer + offset, ",");

  // Add RSSI
  offset += sprintf(csi_buffer + offset, "%d,", data->rx_ctrl.rssi);

  // Add CSI data length
  offset += sprintf(csi_buffer + offset, "%d,", data->len);

  // Add CSI data
  for (int i = 0; i < data->len; i++)
  {
    offset += sprintf(csi_buffer + offset, "%d", data->buf[i]);
    if (i < data->len - 1)
      offset += sprintf(csi_buffer + offset, ",");
  }

  // Print the CSI data
  Serial.println(csi_buffer);
}

void setup()
{
  // Initialize Serial
  Serial.begin(115200);

  // Initialize MPU6050
  Wire.begin();
  mpu.initialize();

  // Check MPU connection
  if (mpu.testConnection())
  {
    Serial.println("MPU6050 connected successfully.");
  }
  else
  {
    Serial.println("Failed to connect MPU6050.");
    while (1)
      ; // Stop the program if MPU6050 fails to connect
  }

  // Sensor pin modes
  pinMode(LDRPIN, INPUT); // LM393 sensor input
  pinMode(IRPIN, INPUT);  // IR sensor input

  // Initialize WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Set WiFi channel (adjust according to your environment)
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  // Configure CSI
  wifi_csi_config_t csi_config = {
      .lltf_en = true,
      .htltf_en = true,
      .stbc_htltf2_en = true,
      .ltf_merge_en = true,
      .channel_filter_en = true,
      .manu_scale = false,
      .shift = false,
  };

  // Register the CSI callback function
  esp_wifi_set_csi_rx_cb(&csi_callback, NULL);
  esp_wifi_set_csi_config(&csi_config);

  // Enable CSI data collection
  esp_wifi_set_csi(true);

  // Print CSV Header
  Serial.println("Timestamp,Sensor_Type,Data");
}

void loop()
{
  // Get the current timestamp
  unsigned long timestamp = millis();

  // LM393 sensor reading
  int lm393Val = digitalRead(LDRPIN);
  Serial.print(timestamp);
  Serial.print(",LM393,");
  Serial.println(lm393Val);

  // IR sensor reading
  int irVal = analogRead(IRPIN);
  Serial.print(timestamp);
  Serial.print(",IR Sensor,");
  Serial.println(irVal);

  // MPU6050 sensor reading
  int16_t accelX, accelY, accelZ;
  mpu.getAcceleration(&accelX, &accelY, &accelZ);
  Serial.print(timestamp);
  Serial.print(",MPU6050,");
  Serial.print(accelX);
  Serial.print(",");
  Serial.print(accelY);
  Serial.print(",");
  Serial.println(accelZ);

  // Wait for 2 seconds before reading the next set of data
  delay(2000);
}
