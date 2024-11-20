/*!
	@file common_data_RVL.hpp
	@author Gavin Lyons
	@brief file to hold common data used by all Displays
	Project Name: ST7789_TFT_RPI
*/

#pragma once

#include <cstdint>

uint16_t GetRVLibVersionNum(void);

#define delayMicroSecRVL bcm2835_delayMicroseconds /**< bcm2835 library Micro second delay abstraction */
#define delayMilliSecRVL bcm2835_delay             /**< bcm2835 library Milli second delay abstraction */

/*! Enum to define a standard return code for most functions that return failures*/
enum rvlDisplay_Return_Codes_e : uint8_t
{
	rvlDisplay_Success = 0,                /**< Success, Function ran without defined Error*/
	rvlDisplay_Reserved = 1,               /**< Reserved */
	rvlDisplay_WrongFont = 2,              /**< Wrong Font selected*/
	rvlDisplay_CharScreenBounds = 3,       /**< Text Character is out of Screen bounds, Check x and y*/
	rvlDisplay_CharFontASCIIRange = 4,     /**< Text Character is outside of chosen Fonts ASCII range, Check the selected Fonts ASCII range.*/
	rvlDisplay_CharArrayNullptr = 5,       /**< Text Character Array is an invalid pointer object*/
	rvlDisplay_FontPtrNullptr = 6,         /**< Pointer to the font is an invalid pointer object*/
	rvlDisplay_BitmapNullptr = 7,          /**< The Bitmap data array is an invalid pointer object*/
	rvlDisplay_BitmapScreenBounds = 8,     /**< The Bitmap starting point is outside screen bounds, check x and y*/
	rvlDisplay_BitmapLargerThanScreen = 9, /**< The Bitmap is larger than screen, check  w and h*/
	rvlDisplay_BitmapVerticalSize = 10,    /**< A vertical Bitmap's height must be divisible by 8.*/
	rvlDisplay_BitmapHorizontalSize = 11,  /**< A horizontal Bitmap's width  must be divisible by 8*/
	rvlDisplay_BitmapSize = 12,            /**< Size of the Bitmap is incorrect: BitmapSize(vertical)!=(w*(h/8),BitmapSize(horizontal)!=(w/8)*h*/
	rvlDisplay_CustomCharLen = 13,         /**< CustomChar array must always be 5 bytes long*/
	rvlDisplay_BufferSize = 14,            /**< Size of the Buffer is incorrect: BufferSize(vertical)!=(w*(h/8)*/
	rvlDisplay_BufferNullptr = 15,         /**< The Buffer data array is an invalid pointer object*/
	rvlDisplay_SPIbeginFail = 16,          /**< bcm2835_spi_begin() has failed, running as root?*/
	rvlDisplay_SPICEXPin = 17,             /**< SPICE_PIN value incorrect must be 0 or 1 */
	rvlDisplay_I2CbeginFail = 18,          /**< bcm2835_i2c_begin() has failed, running as root?*/
	rvlDisplay_ShapeScreenBounds = 19,     /**< Shape is outside screen bounds, check x and y */
	rvlDisplay_MallocError = 20,           /**< malloc could not assign memory*/
	rvlDisplay_WrongInputPCBType = 21      /**< Wrong input PCB type chosen */
};


