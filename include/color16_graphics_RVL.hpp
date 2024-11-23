/*!
	@file     color16_graphics_RVL.hpp
	@author   Gavin Lyons
	@brief    Library header file for 16 bit (565) color graphics library.
				This file handles the graphic methods
*/

#pragma once

// Includes
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <cstdbool>
#include <bcm2835.h> // Dependency
#include "print_data_RVL.hpp"
#include "font_data_RVL.hpp"
#include "common_data_RVL.hpp"

// defines 
#define _swap_int16_t_RVL(a, b) { int16_t t; t = a; a = b; b = t;}

// GPIO abstraction 
#define DisplayRVL_DC_SetHigh  bcm2835_gpio_write(_DisplayRVL_DC, HIGH)
#define DisplayRVL_DC_SetLow  bcm2835_gpio_write(_DisplayRVL_DC, LOW)
#define DisplayRVL_RST_SetHigh  bcm2835_gpio_write(_DisplayRVL_RST, HIGH)
#define DisplayRVL_RST_SetLow  bcm2835_gpio_write(_DisplayRVL_RST, LOW)
#define DisplayRVL_CS_SetHigh bcm2835_gpio_write(_DisplayRVL_CS, HIGH)
#define DisplayRVL_CS_SetLow bcm2835_gpio_write(_DisplayRVL_CS, LOW)
#define DisplayRVL_SCLK_SetHigh bcm2835_gpio_write(_DisplayRVL_SCLK, HIGH)
#define DisplayRVL_SCLK_SetLow  bcm2835_gpio_write(_DisplayRVL_SCLK, LOW)
#define DisplayRVL_SDATA_SetHigh bcm2835_gpio_write(_DisplayRVL_SDATA, HIGH)
#define DisplayRVL_SDATA_SetLow  bcm2835_gpio_write(_DisplayRVL_SDATA,LOW)
#define DisplayRVL_MISO_Read bcm2835_gpio_lev(_DisplayRVL_MISO)

#define DisplayRVL_DC_SetDigitalOutput bcm2835_gpio_fsel(_DisplayRVL_DC, BCM2835_GPIO_FSEL_OUTP)
#define DisplayRVL_RST_SetDigitalOutput bcm2835_gpio_fsel(_DisplayRVL_RST, BCM2835_GPIO_FSEL_OUTP)
#define DisplayRVL_SCLK_SetDigitalOutput bcm2835_gpio_fsel(_DisplayRVL_SCLK, BCM2835_GPIO_FSEL_OUTP)
#define DisplayRVL_SDATA_SetDigitalOutput bcm2835_gpio_fsel(_DisplayRVL_SDATA, BCM2835_GPIO_FSEL_OUTP)
#define DisplayRVL_CS_SetDigitalOutput bcm2835_gpio_fsel(_DisplayRVL_CS, BCM2835_GPIO_FSEL_OUTP)
#define DisplayRVL_MISO_SetDigitalInput bcm2835_gpio_fsel(_DisplayRVL_MISO, BCM2835_GPIO_FSEL_INPT)

// Color definitions 16-Bit Color Values R5G6B5
#define RVLC_BLACK   0x0000
#define RVLC_BLUE    0x001F
#define RVLC_RED     0xF800
#define RVLC_GREEN   0x07E0
#define RVLC_CYAN    0x07FF
#define RVLC_MAGENTA 0xF81F
#define RVLC_YELLOW  0xFFE0
#define RVLC_WHITE   0xFFFF
#define RVLC_TAN     0xED01
#define RVLC_GREY    0x9CD1
#define RVLC_BROWN   0x6201
#define RVLC_DGREEN  0x01C0
#define RVLC_ORANGE  0xFC00
#define RVLC_NAVY    0x000F
#define RVLC_DCYAN   0x03EF
#define RVLC_MAROON  0x7800
#define RVLC_PURPLE  0x780F
#define RVLC_OLIVE   0x7BE0
#define RVLC_LGREY   0xC618
#define RVLC_DGREY   0x7BEF
#define RVLC_GYELLOW 0xAFE5
#define RVLC_PINK    0xFC18

/*!
	@brief Class to handle fonts and graphics of color 16 bit display
*/
class color16_graphics:public display_Fonts, public Print  {

 public:

	color16_graphics(); // Constructor
	~color16_graphics(){};
	
	// Screen related
	// Defined in the display sub class
	virtual void setAddrWindow(uint16_t, uint16_t, uint16_t, uint16_t) = 0;
	void fillScreen(uint16_t color);
	void setCursor(int16_t x, int16_t y);
	
	// Shapes and lines
	void drawPixel(uint16_t, uint16_t, uint16_t);
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	rvlDisplay_Return_Codes_e drawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color);
	rvlDisplay_Return_Codes_e drawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color);

	void drawRectWH(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
	rvlDisplay_Return_Codes_e fillRectangle(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
	void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

	void drawRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
	void fillRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
	
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

	// Text related functions 
	virtual size_t write(uint8_t) override;
	rvlDisplay_Return_Codes_e writeChar( int16_t x, int16_t y, char value );
	rvlDisplay_Return_Codes_e writeCharString( int16_t x, int16_t y, char *text);
	void setTextWrap(bool w);
	void setTextColor(uint16_t c, uint16_t bg);
	void setTextColor(uint16_t c);
	
	// Bitmap & Icon
	rvlDisplay_Return_Codes_e drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t color, uint16_t bgcolor, const unsigned char character[]);
	rvlDisplay_Return_Codes_e drawBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, uint16_t bgcolor, const uint8_t *pBmp);
	rvlDisplay_Return_Codes_e drawBitmap24(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h);
	rvlDisplay_Return_Codes_e drawBitmap16(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h);
	// RGB to 565
	int16_t Color565(int16_t ,int16_t , int16_t );
protected:

	void pushColor(uint16_t color);
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
	
	void writeCommand(uint8_t);
	void writeData(uint8_t);
	void spiWrite(uint8_t);
	void spiWriteSoftware(uint8_t spidata);

	void spiWriteDataBuffer(uint8_t* spidata, uint32_t len);

	bool _hardwareSPI=true; /**< True for Hardware SPI on , false fpr Software SPI on*/
	
	bool _textwrap = true;              /**< wrap text around the screen on overflow*/
	uint16_t _textcolor = 0xFFFF ;      /**< 16 bit ForeGround color for text*/
	uint16_t _textbgcolor =0x0000 ;     /**< 16 bit BackGround color for text*/

	int16_t _cursorX = 0; /**< Current X co-ord cursor position */
	int16_t _cursorY = 0; /**< Current Y co-ord cursor position */
	uint16_t _width;      /**< Display w as modified by current rotation*/
	uint16_t _height;    /**< Display h as modified by current rotation*/
	uint8_t _XStart= 0;     /**< Used to store _colstart changed by current rotation */
	uint8_t _YStart= 0;     /**< Used to store _rowstart changed by current rotation */

	int8_t _DisplayRVL_DC;    /**< GPIO for data or command line */
	int8_t _DisplayRVL_RST;   /**< GPIO for reset line */
	int8_t _DisplayRVL_CS;    /**< GPIO for chip select line,  Software SPI only */
	int8_t _DisplayRVL_SCLK;  /**< GPIO for Clock line,  Software SPI only */
	int8_t _DisplayRVL_SDATA; /**< GPIO for MOSI line,  Software SPI only */
	int8_t _DisplayRVL_MISO;  /**< GPIO for  MISO line,  Software SPI only */

	uint16_t _HighFreqDelay = 0; /**< uS GPIO Communications delay, SW SPI ONLY */
	uint8_t _TFT_SPI_Handle_Chosen = 0; /**< Which SPi interface handle to use 0 or 1(aux) */
private:

};
// ********************** EOF *********************
