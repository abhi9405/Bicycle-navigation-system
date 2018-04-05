#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define NEOPIN 11
int i = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, NEOPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  
  strip.begin();
  strip.setBrightness(10);
  //strip.setPixelColor(1,strip.Color(100,100,0));
  //strip.show();
  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  halfRingRightBlink(strip.Color(0,255,0),100);
  //halfRingLeftBlinkBold(strip.Color(0,255,0),strip.Color(0,255,0),100);
  //halfRingLeftBlinkBoldContinue(strip.Color(0,255,0),strip.Color(0,255,0),100);    
  
}

uint32_t blink(int num,int duration,uint32_t color)
{
  strip.setPixelColor(num,color);
  
  strip.show();
  delay(duration);
  strip.setPixelColor(num,strip.Color(0,0,0,0));
  strip.show();
  delay(duration);
  return(color);
}

void halfRingLeft(uint32_t color)
{
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,color);  
  strip.show();
}

void halfRingRight(uint32_t color)
{
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,color);  
  strip.show();
}

void halfRingRightBlink(uint32_t color,int duration)
{  
  
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.show();
  strip.setPixelColor(6,color);  
  strip.setPixelColor(11,color);  
  strip.show();
  delay(duration);
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(7,color);  
  strip.setPixelColor(10,color);  
  strip.show();
  delay(duration);
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(8,color);  
  strip.setPixelColor(9,color);  
  strip.show();
  delay(duration);  
}

void halfRingLeftBlink(uint32_t color,int duration)
{  
  
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.show();
  strip.setPixelColor(0,color);  
  strip.setPixelColor(5,color);  
  strip.show();
  delay(duration);
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(1,color);  
  strip.setPixelColor(4,color);  
  strip.show();
  delay(duration);
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(2,color);  
  strip.setPixelColor(3,color);  
  strip.show();
  delay(duration);  
}

void halfRingLeftBlinkBold(uint32_t colorOn,uint32_t colorOff,int duration)
{ 
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,colorOff);  
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.show();
  strip.setPixelColor(0,colorOn);  
  strip.setPixelColor(5,colorOn);  
  strip.show();
  delay(duration);
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(1,colorOn);  
  strip.setPixelColor(4,colorOn);  
  strip.show();
  delay(duration);
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(2,colorOn);  
  strip.setPixelColor(3,colorOn);  
  strip.show();
  delay(duration);  
}

void halfRingRightBlinkBold(uint32_t colorOn,uint32_t colorOff,int duration)
{  
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,colorOff);  
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.show();
  strip.setPixelColor(6, colorOn);  
  strip.setPixelColor(11, colorOn);  
  strip.show();
  delay(duration);
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(7, colorOn);  
  strip.setPixelColor(10, colorOn);  
  strip.show();
  delay(duration);
  for(int i = 6;i <12;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.setPixelColor(8, colorOn);  
  strip.setPixelColor(9, colorOn);  
  strip.show();
  delay(duration);  
}

void halfRingRightBlinkBoldContinue(uint32_t colorOn,uint32_t colorOff,int duration)
{  
  for(int i = 0;i < 6;i++)
    strip.setPixelColor(i,colorOff);  
  for(int i = 6;i < 12;i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));  
  strip.show();
  delay(duration);
  strip.setPixelColor(6, colorOn);  
  strip.setPixelColor(11, colorOn);  
  strip.show();
  delay(duration);
  strip.setPixelColor(7, colorOn);  
  strip.setPixelColor(10, colorOn);  
  strip.show();
  delay(duration);
  strip.setPixelColor(8, colorOn);  
  strip.setPixelColor(9, colorOn);  
  strip.show();
  delay(duration);  
}



