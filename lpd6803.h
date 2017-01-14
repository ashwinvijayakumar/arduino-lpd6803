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
 * @file        lpd6803.h
 *
 * @brief       LPD6803 library for ESP8266-Arduino
 *
 * @date        Dec 31, 2016, 10:22:17 AM
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

#ifndef LPD6803_H_
#define LPD6803_H_

//#ifdef    __cplusplus
//extern "C" {
//#endif

/* ---- System headers ------------------------------------------------------ */
/* ---- Local headers ------------------------------------------------------- */
#include <SPI.h>

#define LPD6803_STARTBIT_MASK   0x8000

/* 5bits per color */
#define LPD6803_SHIFT_BLUE      0
#define LPD6803_SHIFT_RED       5
#define LPD6803_SHIFT_GREEN     10

/* Brightness range for each color ( 0 to 2^5 ) */
#define LPD6803_BRIGHTNESS_MIN  0
#define LPD6803_BRIGHTNESS_MAX  (uint16_t)( ( pow(2.0, 5.0) ) - 1 )

/**
 * @defgroup DOXYGEN_GROUP_LPD6803 LPD6803
 * @ingroup DOXYGEN_GROUP_DISPLAY
 * @{
 */

class Lpd6803 {

public:

    /**
     * @brief   Initialize the driver
     * @param   n - Number of LEDs in the strip
     * @param   pixelBuffer - buffer to hold each LED's color
     */
    Lpd6803( uint16_t n, uint16_t* buffer );


    /**
     * Clear the strip (switch off all LEDs)
     */
    void clear( void );


    /**
     * @brief   Write to the strip
     * @detail  Values set by @see clear, @see setPixelColor, @see setBrightness,
     * etc will be physically written to the strip only after @see show is called.
     * @param   del - Delay between updating consecutive LEDs
     */
    void show( float del );


    /**
     * @brief   Update number of LEDs in the strip
     */
    void setNumLEDs( uint16_t n );


    /**
     * @brief   Set 'n'th pixel to RGB color value
     */
    void setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b );


    /**
     * @brief   Set 'n'th pixel to 16-bit color value
     * @detail  Also see @see setPixelColor. Use @see Lpd6803::color to
     * generate 'c' value
     */
    void setPixelColor( uint16_t n, uint16_t c );


    /**
     * @brief   Get pixel color
     * @detail  This a value stored in the local buffer, not actually read
     * from the LED strip. Use @see color to convert the return value to RGB.
     * @return  16bit color value ( X | BBBBB | RRRRR | GGGGG )
     */
    uint16_t getPixelColor( uint16_t n );


    /**
     * @brief   Set brightness of 'n'th pixel
     * @detail  LPD6803 does not provide a discrete functionality to set
     * brightness, so we rewrite the pixel value with the specified brightness.
     */
    void setBrightness( uint16_t n, float value );


    /**
     * @brief   Set brightness of the entire strip
     * @detail  Also see @see setBrightness
     */
    void setBrightness( float value );


    /**
     * @brief   Convert RGB to 16-bit color value
     */
    uint16_t color( uint8_t r, uint8_t g, uint8_t b );


    /**
     * @brief   Convert 16-bit color value to RGB
     */
    void color( uint16_t c, uint8_t* r, uint8_t* g, uint8_t* b );


    /**
     * @brief   Destructor
     */
    ~Lpd6803( ) {}


private:

    /* Number of LEDs in the strip */
    uint16_t numLEDs;

    /* Buffer to store pixel data before it is physically written to the strip */
    uint16_t* pixelBuffer;
};

/**@}*/ /* DOXYGEN_GROUP_LPD6803 */

//#ifdef    __cplusplus
//}
//#endif

#endif /* LPD6803_H_ */

/* ---- End of file --------------------------------------------------------- */
