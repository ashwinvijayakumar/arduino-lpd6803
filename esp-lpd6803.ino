/******************************************************************************
* Copyright (c) 2017 Ashwin V Kumar
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*******************************************************************************/
/**
 * @file        esp-lpd6803.ino
 *
 * @brief       LPD6308 LED Strip test code for ESP8266
 *
 * @date        Jan 12, 2017, 10:28:04 PM
 *
 * @details     Does a color wipe on a 6308 based serially addressable LED strip
 */

#include "lpd6803.h"

#define LED               2
#define LED_STRIP_LENGTH  50

uint16_t ledStripBuf[LED_STRIP_LENGTH] = {};
Lpd6803 ledStrip( LED_STRIP_LENGTH, ledStripBuf );

void setup() 
{
  pinMode( LED, OUTPUT );
  Serial.begin( 115200 );
}

void loop() 
{
  digitalWrite( LED, HIGH );
  Serial.println( "Wiping white..." );
  for( int i = 0; i < LED_STRIP_LENGTH; i++ )
      ledStrip.setPixelColor( i, 255, 255, 255 );
  ledStrip.show( 50 );
  
  digitalWrite( LED, LOW );
  Serial.println( "Wiping red..." );
  for( int i = 0; i < LED_STRIP_LENGTH; i++ )
      ledStrip.setPixelColor( i, 255, 0, 0 );
  ledStrip.show( 50 );
  
  digitalWrite( LED, HIGH );
  Serial.println( "Wiping green..." );
  for( int i = 0; i < LED_STRIP_LENGTH; i++ )
      ledStrip.setPixelColor( i, 0, 255, 0 );
  ledStrip.show( 50 );
  
  digitalWrite( LED, LOW );
  Serial.println( "Wiping blue..." );
  for( int i = 0; i < LED_STRIP_LENGTH; i++ )
      ledStrip.setPixelColor( i, 0, 0, 255 );
  ledStrip.show( 50 );
}

