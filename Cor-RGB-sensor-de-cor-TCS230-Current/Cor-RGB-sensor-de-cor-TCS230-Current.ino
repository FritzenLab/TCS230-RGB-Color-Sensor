/*     Arduino Color Sensing Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  Modified by Clovis Fritzen http://www.FritzenLab.com.br in May 1st, 2017
 *  
 *  Also using Adafuit NeoPixel code
 *  
 *  - This code reads a color sensor (TCS230) converts it to RGB and shows it
 *  back in an Adafruit NeoPixel. The color is read and then showed back!
 */

#include <Adafruit_NeoPixel.h>  
#ifdef __AVR__  
#include <avr/power.h>  
#endif  
   
 // Which pin on the Arduino is connected to the NeoPixels?  
#define PIN      9  
   
 // How many NeoPixels are attached to the Arduino?  
#define NUMPIXELS   1  
   
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  
   
int delayval = 333; // delay  
 
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequency = 0;
int Red, Green, Blue;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.  
}

void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,72,255,0);
  if (frequency < 0) {
    frequency = 0;
  }
  if (frequency > 255) {
    frequency = 255;
  }
  Red= frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 30,90,255,0);
  if (frequency < 0) {
    frequency = 0;
  }
  if (frequency > 255) {
    frequency = 255;
  }
  Green = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,70,255,0);
  if (frequency < 0) {
    frequency = 0;
  }
  if (frequency > 255) {
    frequency = 255;
  }
  Blue = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  pixels.setPixelColor(0, pixels.Color(Red,Green,Blue)); // Moderately bright green color.
  pixels.setBrightness(64);  
  pixels.show(); // This sends the updated pixel color to the hardware. 
  delay(100);
}
