#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define NEOPIN 11
#define DURATIONL 1000
#define DURATIONS 100

#define TRIALS 5

#define N 0
#define NW 1
#define W 2
#define SW 3
#define S 4
#define SE 5
#define E 6
#define NE 7

#define PATTERN_SWITCH1 1
#define PATTERN_SWITCH2 0

// Global Variables here
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, NEOPIN, NEO_GRB + NEO_KHZ800);
int ar[] = {E,N,NW,NE,W};
int i = 0;


void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.setBrightness(10);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  if(i >= TRIALS)
  {
    i = 0;
    resetStrip(strip.Color(10,10,10),DURATIONL);    
  }
  else
  {
    setPattern(ar[i],strip.Color(0,255,0),DURATIONS);
    i++;      
  }
}

void resetStrip(uint32_t color, int duration)
{
  for(int j = 0; j < 12; j++)
    strip.setPixelColor(i,color);
  strip.show();
  delay(duration);
}

void setPattern(int head, uint32_t color, int duration)
{
  switch(head)
  {
    case N:
      if(PATTERN_SWITCH1)
        strip.setPixelColor(0,color);
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;

    case NE:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(1,color);
        strip.setPixelColor(2,color);
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;
      
    case E:
      if(PATTERN_SWITCH1)
        strip.setPixelColor(3,color);
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;
      
    case SE:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(4,color);
        strip.setPixelColor(5,color);        
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;
    case S:
      if(PATTERN_SWITCH1)
        strip.setPixelColor(6,color);
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;
      
    case SW:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(7,color);
        strip.setPixelColor(8,color);        
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;
      
    case W:
      if(PATTERN_SWITCH1)
        strip.setPixelColor(9,color);
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;
      
    case NW:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(10,color);
        strip.setPixelColor(11,color);
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
      }
      delay(duration);
      break;
   
  }
}

  
