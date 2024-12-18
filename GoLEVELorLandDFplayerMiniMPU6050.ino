 
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    
#include "Arduino.h" // Include the core Arduino library
#include "DFRobotDFPlayerMini.h" // Include the DFRobot DFPlayer Mini library

#ifdef ESP32
  #define FPSerial Serial1  // For ESP32, use hardware serial port 1
#else
  #include <SoftwareSerial.h> // Include SoftwareSerial library for non-ESP32 boards
//SoftwareSerial FPSerial(2, 3); // Define SoftwareSerial on pins GPIO2 (RX) and GPIO3 (TX)- XIAO ESP32C3
 SoftwareSerial FPSerial(26, 27); // Define SoftwareSerial on pins GPIO2 (RX) and GPIO3 (TX)
#endif

DFRobotDFPlayerMini myDFPlayer; // Create an instance of the DFRobotDFPlayerMini class

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

void setup()
{ 
    #ifdef ESP32
  FPSerial.begin(9600, SERIAL_8N1, 26, 27); // Start serial communication for XIAO ESP32C3 with 9600 baud rate, 8 data bits, no parity, and 1 stop bit
  #else
  FPSerial.begin(9600); // Start serial communication for other boards with 9600 baud rate
  #endif

  Serial.begin(115200); // Start the Serial monitor communication with 115200 baud rate

  Serial.println(F("DFRobot DFPlayer Mini Demo")); // Print a demo start message
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)")); // Print initialization message
  
  if (!myDFPlayer.begin(FPSerial)) { // Initialize the DFPlayer Mini with the defined serial interface
    Serial.println(F("Unable to begin:")); // If initialization fails, print an error message
    Serial.println(F("1.Please recheck the connection!")); // Suggest rechecking the connection
    Serial.println(F("2.Please insert the SD card!")); // Suggest checking for an inserted SD card
    while(true); // Stay in an infinite loop if initialization fails
  }
  Serial.println(F("DFPlayer Mini online.")); // Print a success message if initialization succeeds
  
  myDFPlayer.volume(60);  // Set the DFPlayer Mini volume to 30 (max is 30)
  
  Wire.begin();
  mpu.initialize();
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
  data.Z= map(ay, -17000, 17000, 0, 255);  // Y axis data
  
 
  Serial.print("Axis X = ");
  Serial.print(data.X);

  Serial.print("  ");

  Serial.print("Axis Y = ");
  Serial.print(data.Y);

  Serial.print("  ");

  Serial.print("Axis Z = ");
  Serial.println(data.Z);

  if(data.X<120 && data.Y<100 && data.Z<100 || data.X>200 && data.Y>130 && data.Z>130 ||data.X<70 && data.Y>129 && data.Z>129){
    myDFPlayer.play(1);  // Play the second MP3 track
    
     Serial.println("Go level or land!!!!");
      delay(2300);
  }


}
