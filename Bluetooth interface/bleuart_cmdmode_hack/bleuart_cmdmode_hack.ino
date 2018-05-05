/*********************************************************************
 This is an example for our nRF51822 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif


// ------------------------------NeoPixel Stuff---------------------------------//

#define NEOPIN 5
#define DURATIONL 100
#define DURATIONS 10

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
int ar[] = {S,SW,E,W,SE};
int i = 0;

// ----------------------------------------------------------------------------------- //
/*=========================================================================
    APPLICATION SETTINGS

    FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
   
                              Enabling this will put your Bluefruit LE module
                              in a 'known good' state and clear any config
                              data set in previous sketches or projects, so
                              running this at least once is a good idea.
   
                              When deploying your project, however, you will
                              want to disable factory reset by setting this
                              value to 0.  If you are making changes to your
                              Bluefruit LE device via AT commands, and those
                              changes aren't persisting across resets, this
                              is the reason why.  Factory reset will erase
                              the non-volatile memory where config data is
                              stored, setting it back to factory default
                              values.
       
                              Some sketches that require you to bond to a
                              central device (HID mouse, keyboard, etc.)
                              won't work at all with this feature enabled
                              since the factory reset will clear all of the
                              bonding data stored on the chip, meaning the
                              central device won't be able to reconnect.
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    MODE_LED_BEHAVIOUR        LED activity, valid options are
                              "DISABLE" or "MODE" or "BLEUART" or
                              "HWUART"  or "SPI"  or "MANUAL"
    -----------------------------------------------------------------------*/
    #define FACTORYRESET_ENABLE         1
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/

// Create the bluefruit object, either software serial...uncomment these lines
/*
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);
*/

/* ...or hardware serial, which does not need the RTS/CTS pins. Uncomment this line */
// Adafruit_BluefruitLE_UART ble(Serial1, BLUEFRUIT_UART_MODE_PIN);

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

/* ...software SPI, using SCK/MOSI/MISO user-defined SPI pins and then user selected CS/IRQ/RST */
//Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_SCK, BLUEFRUIT_SPI_MISO,
//                             BLUEFRUIT_SPI_MOSI, BLUEFRUIT_SPI_CS,
//                             BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void)
{
  //while (!Serial);  // required for Flora & Micro
  //delay(500);

  // -----------------NeoPixel Stuff-----------------------------------//
  strip.begin();
  strip.setBrightness(10);
 resetStrip(strip.Color(0,0,0),DURATIONL);
 // setPattern(1,strip.Color(0,2,245),DURATIONS);
  
  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Command Mode Example"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println(F("Then Enter characters to send to Bluefruit"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
//  while (! ble.isConnected()) {
//      delay(500);
//  }



  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("******************************"));
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
    Serial.println(F("******************************"));
  }
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void)
{
  // Check for user input
 // char inputs[BUFSIZE+1] = {"p"};

  //if ( getUserInput(inputs, BUFSIZE) )
  //{
    // Send characters to Bluefruit
//    Serial.print("[Send] ");
//    Serial.println(inputs);
//
//    ble.print("AT+BLEUARTTX=");
//    ble.println(inputs);
//
//    // check response stastus
//    if (! ble.waitForOK() ) {
//      Serial.println(F("Failed to send?"));
//    }
  //}

  // Check for incoming characters from Bluefruit
 
/*  
  ble.println("AT+BLEUARTRX");
  ble.readline();
  if (strcmp(ble.buffer, "OK") == 0) {
    // no data
    return;
  }
  
  // Some data was found, its in the buffer
  Serial.print(F("[Recv] ")); Serial.println(ble.buffer);
  ble.waitForOK();

  String a;

  a = ble.buffer;
*/
 

int combi, dist, dir;

//combi = a.toInt();


//dist = combi / 10;
//dir = combi % 10;

int i, count = 0;

dist = 800;
dir = 6;

for(i = 0; i < 80; i++)
{

  dist = dist - 10;

Serial.print("dist = "); Serial.println(dist);
Serial.print("dir = "); Serial.println(dir);

int R, G, B;
float Rf, Gf, Bf;

Gf = (255.0/999.0)*(float)dist;
Rf = 255 - (255.0/999.0)*(float)dist;
if(dist < 450)
{
  Bf = (255.0/999.0)*(float)dist;
} else {
  Bf = 255.0 - (255.0/999.0)*(float)dist;
}

R = Rf;
G = Gf;
B = Bf;

Serial.print("R = "); Serial.print(R); Serial.print("  G = "); Serial.println(G); Serial.print("  B = "); Serial.println(B);


// strip.setPixelColor(2, strip.Color(10, 100, 0));
// strip.show();

resetStrip(strip.Color(0,0,0),1);
setPattern(0,strip.Color(255,0,0),1);

delay(500);

count = count + 1;
Serial.println(count);
}

while (1){
  resetStrip(strip.Color(0,0,0),1);
setPattern(0,strip.Color(0,255,0),1);
}

}

/**************************************************************************/
/*!
    @brief  Checks for user input (via the Serial Monitor)
*/
/**************************************************************************/
//bool getUserInput(char buffer[], uint8_t maxSize)
//{
//  // timeout in 100 milliseconds
//  TimeoutTimer timeout(100);
//
//  memset(buffer, 0, maxSize);
//  while( (!Serial.available()) && !timeout.expired() ) { delay(1); }
//
//  if ( timeout.expired() ) return false;
//
//  delay(2);
//  uint8_t count=0;
//  do
//  {
//    count += Serial.readBytes(buffer+count, maxSize);
//    delay(2);
//  } while( (count < maxSize) && (Serial.available()) );
//
//  return true;
//}


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

