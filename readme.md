Pin Connections:


1)Connections for the MPU6050 (I2C communication):

Place the MPU6050 on the breadboard so that it straddles the middle gap.
Using jumper wires, make the following connections:
VCC → Red power rail (3.3V)
GND → Blue ground rail (GND)
SCL → D22 (Connect SCL pin of MPU6050 to GPIO 22 on the ESP32 using a jumper wire)
SDA → D21 (Connect SDA pin of MPU6050 to GPIO 21 on the ESP32 using a jumper wire)


2) Connections for the IR Obstacle Sensor (Analog Output):
Place the IR sensor on the breadboard.
Using jumper wires, connect:
VCC → Red power rail (3.3V)
GND → Blue ground rail (GND)
OUT → D34 (Connect the OUT pin of the IR sensor to GPIO 34 on the ESP32 for analog reading)


3) Connections for the LM393 Sensor (Digital Output):
Place the LM393 sensor on the breadboard.
Using jumper wires, connect:
VCC → Red power rail (3.3V)
GND → Blue ground rail (GND)
OUT → D2 (Connect the OUT pin of the LM393 sensor to GPIO 2 on the ESP32 for digital reading)
