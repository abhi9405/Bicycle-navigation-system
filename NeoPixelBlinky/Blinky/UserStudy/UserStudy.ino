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

#define PATTERN_SWITCH1 0
#define PATTERN_SWITCH2 1

// Global Variables here
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, NEOPIN, NEO_GRB + NEO_KHZ800);
int ar[] = {S,SW,E,W,SE};
int i = 0;


void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.setBrightness(10);
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly: 
  //Serial.println(ar[i]);
  if(i >= TRIALS)
  {
    i = 0;
    resetStrip(strip.Color(0,0,0),DURATIONL);    
  }
  else
  {
    resetStrip(strip.Color(0,0,0),DURATIONS);
    setPattern(ar[i],strip.Color(0,255,0),DURATIONS);
    i++;      
  }
  delay(DURATIONL);
}

void resetStrip(uint32_t color, int duration)
{
  for(int j = 0; j < 12; j++)
    strip.setPixelColor(j,color);
  strip.show();
  delay(duration);
}

void setPattern(int head, uint32_t color, int duration)
{
  switch(head)
  {
    case N:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(0,color);
        strip.show();
      }  
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(9,color,!color,duration);        
      }
      delay(duration);
      break;

    case NE:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(1,color);
        strip.setPixelColor(2,color);
        strip.show();
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(10,color,!color,duration);
      }
      delay(duration);
      break;
      
    case E:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(3,color);
        strip.show();
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(0,color,!color,duration);
      }
      delay(duration);
      break;
      
    case SE:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(4,color);
        strip.setPixelColor(5,color); 
        strip.show();       
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(1,color,!color,duration);
      }
      delay(duration);
      break;
    case S:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(6,color);
        strip.show();
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(3,color,!color,duration);
      }
      delay(duration);
      break;
      
    case SW:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(7,color);
        strip.setPixelColor(8,color); 
        strip.show();       
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(4,color,!color,duration);
      }
      delay(duration);
      break;
      
    case W:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(9,color);
        strip.show();
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(6,color,!color,duration);
      }
      delay(duration);
      break;
      
    case NW:
      if(PATTERN_SWITCH1)
      {
        strip.setPixelColor(10,color);
        strip.setPixelColor(11,color);
        strip.show();
      }
      if(PATTERN_SWITCH2)
      {
        // Fill this
        setQuarter(7,color,!color,duration);
      }
      delay(duration);
      break;
   
  }
}
void setQuarter(int start,uint32_t color1,uint32_t color2,int duration)
{
  for(int j = 6;j<12;j++)
    strip.setPixelColor((start+j)%12,color2);
  for(int j = 0;j<6;j++)
    strip.setPixelColor((start+j)%12,strip.Color(0,0,0));
  strip.show();
  delay(duration);
  strip.setPixelColor((start+0)%12,color1);
  strip.setPixelColor((start+5)%12,color1);
  strip.show();
  delay(duration);
  strip.setPixelColor((start+1)%12,color1);
  strip.setPixelColor((start+4)%12,color1);
  strip.show();
  delay(duration);
  strip.setPixelColor((start+2)%12,color1);
  strip.setPixelColor((start+3)%12,color1);
  strip.show();
  delay(duration);   
}


  
