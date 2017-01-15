/******************************************************************************
* Copyright (c) 2016 Ashwin V Kumar
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
 * @file        lpd6803.cpp
 *
 * @brief       LPD6803 library for Arduino
 *
 * @date        Dec 31, 2016, 10:23:06 AM
 *
 * @details     
 */

/* =============================================================================
 * EDIT HISTORY FOR MODULE
 *
 * When     Who         What, where, why
 * -------- -------    ---------------------------------------------------------
 *
 * ========================================================================== */

/* ---- System headers ------------------------------------------------------ */
/* ---- Local headers ------------------------------------------------------- */
#include "lpd6803.h"

/* Initialize the driver */
Lpd6803::Lpd6803( uint16_t n, uint16_t* buffer ):
    numLEDs( n ), pixelBuffer( buffer )
{
    /* Initialize SPI */
    SPI.begin();

    /* SCLK = 1MHz */
    SPI.setFrequency( 1 * 1000 * 1000 );

    /* Clear the strip on initialization */
    clear();
    show( 0 );
}


/* Clear the strip (switch off all LEDs) */
void Lpd6803::clear( void )
{
    for( int i = 0; i < numLEDs; i++ )
        pixelBuffer[i] = LPD6803_STARTBIT_MASK;
}


/* Write to the strip */
void Lpd6803::show( float del )
{
   /* Write Start frame (4 0x00 bytes) */
    SPI.transfer16( 0x0000 );
    SPI.transfer16( 0x0000 );

    /* Write the actual data */
    for( int i = 0; i < numLEDs; i++ )
    {
        SPI.transfer16( pixelBuffer[i] );
        if( del > 0 )
            delay( del );
    }
}


/* Update number of LEDs in the strip */
void Lpd6803::setNumLEDs( uint16_t n )
{
    numLEDs = n;
}


/* Set 'n'th pixel to RGB color value */
void Lpd6803::setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b )
{
    r = map( r, (uint8_t)0, (uint8_t)255, (uint8_t)0, (uint8_t)31 );
    g = map( g, (uint8_t)0, (uint8_t)255, (uint8_t)0, (uint8_t)31 );
    b = map( b, (uint8_t)0, (uint8_t)255, (uint8_t)0, (uint8_t)31 );

    pixelBuffer[n] = LPD6803_STARTBIT_MASK | 
                        ( g << LPD6803_SHIFT_GREEN ) | 
                        ( r << LPD6803_SHIFT_RED ) | 
                        ( b << LPD6803_SHIFT_BLUE );
}


/* Set 'n'th pixel to 16-bit color value */
void Lpd6803::setPixelColor( uint16_t n, uint16_t c )
{
    pixelBuffer[n] = LPD6803_STARTBIT_MASK | c;
}


/* Get pixel color */
uint16_t Lpd6803::getPixelColor( uint16_t n )
{
    return( pixelBuffer[n] & 0x7FFF );
}


/* Set brightness of 'n'th pixel */
void Lpd6803::setBrightness( uint16_t n, float value )
{
    uint8_t g = ( ( pixelBuffer[n] >> LPD6803_SHIFT_GREEN ) && 0x1F ) * value;
    uint8_t r = ( ( pixelBuffer[n] >> LPD6803_SHIFT_RED ) && 0x1F ) * value;
    uint8_t b = ( ( pixelBuffer[n] >> LPD6803_SHIFT_BLUE ) && 0x1F ) * value;

    pixelBuffer[n] = 0x0000 |
                        ( g << LPD6803_SHIFT_GREEN ) |
                        ( r << LPD6803_SHIFT_RED ) |
                        ( b << LPD6803_SHIFT_BLUE );
}


/* Set brightness of the entire strip */
void Lpd6803::setBrightness( float value )
{
    uint8_t r, g, b;

    for( int i = 0; i < numLEDs; i++ )
    {
        g = ( ( pixelBuffer[i] >> LPD6803_SHIFT_GREEN ) && 0x1F ) * value;
        r = ( ( pixelBuffer[i] >> LPD6803_SHIFT_RED ) && 0x1F ) * value;
        b = ( ( pixelBuffer[i] >> LPD6803_SHIFT_BLUE ) && 0x1F ) * value;

        pixelBuffer[i] = 0x0000 |
                            ( g << LPD6803_SHIFT_GREEN ) |
                            ( r << LPD6803_SHIFT_RED ) |
                            ( b << LPD6803_SHIFT_BLUE );
    }
}

/* ---- End of file --------------------------------------------------------- */
