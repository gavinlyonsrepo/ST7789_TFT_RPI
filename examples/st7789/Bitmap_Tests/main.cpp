/*!
	@file examples/st7789/Bitmap_Tests/main.cpp
	@brief Library test file, bitmaps
	@author Gavin Lyons.
	@note See USER OPTIONS 1-3 in SETUP function
	@test
	-# Test 301 "clock demo" , icons, small bitmap
	-# Test 302 bi-color image 128x128
	-# Test 303 24 bit color image bitmap 220x240 from the file system
	-# Test 304 16 bit color image bitmaps 128x128 from the file system
	-# Test 305 16 bit color image bitmap 240x320 from the file system
*/

// Section ::  libraries
#include <bcm2835.h> // for SPI GPIO and delays.
#include <ctime> // for test301
#include "Bi_Color_Bitmap_Data.hpp" // Data for test 301-302
#include "ST7789_TFT_LCD_RVL.hpp"

// Section :: Defines
//  Test timing related defines
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000
#define CLOCK_DISPLAY_TIME 350

// Display size in pixels
#define myTFTWidth 240
#define myTFTHeight 320

// Section :: Globals
ST7789_TFT myTFT;

//  Section ::  Function Headers
uint8_t Setup(void); // setup + user options
void Test301(void); // "clock demo" icons, small bi-color bitmaps
void Test302(void); // 2 color bitmap 128x128
void Test303(void); // 24 color bitmap 220x240
void Test304(void); // 16 color bitmap 128 X128 (3 off)
void Test305(void); // 16 color bitmap 240 x 320 4 byte burger 
std::string UTC_string(void); // for clock demo
void EndTests(void);

//  Section ::  MAIN loop

int main(void)
{

	if(Setup() != 0)return -1;
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_90); // Rotate display
	Test301();
	Test302();
	Test303();
	Test304();
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_0); // Rotate display
	Test305();
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_90); // Rotate display
	EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space

uint8_t Setup(void)
{
	std::cout << "TFT Start" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error 1201 Problem with init bcm2835 library" << std::endl;
		return 2;
	}

// ** USER OPTION 1 GPIO/SPI TYPE HW SPI **
	int8_t RST_TFT  = 25;
	int8_t DC_TFT   = 24;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT);
//*********************************************

// ** USER OPTION 2 Screen Setup **
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = myTFTWidth;// Screen width in pixels
	uint16_t TFT_HEIGHT = myTFTHeight; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ***********************************

// ** USER OPTION 3 SPI baud rate + SPI_CE_PIN**
	uint32_t SCLK_FREQ =  8000000 ; //  freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // which HW SPI chip enable pin to use,  0 or 1
	if(myTFT.TFTInitSPI(SCLK_FREQ, SPI_CE_PIN) != rvlDisplay_Success)
	{
		bcm2835_close(); //Close lib & /dev/mem, deallocating mem
		return 3;
	}
//*****************************
	std::cout << "ST7789 library version : " << GetRVLibVersionNum()<< std::endl;
	std::cout <<"bcm2835 library version :" << bcm2835_version() << std::endl;
	delayMilliSecRVL(50);
	return 0;
}

void Test301(void)
{
	std::cout << "Test 301: clock demo , icons, small bitmap" << std::endl;
	uint16_t count=CLOCK_DISPLAY_TIME;
	if (count > 999) count = 999;
	char teststr1[] = "G Lyons";
	myTFT.fillScreen(RVLC_BLACK);
	
	// Draw top bar of clock
	myTFT.drawIcon(40, 20, 16, RVLC_BLACK, RVLC_WHITE, pSignalIcon);
	myTFT.drawIcon(60, 20, 16, RVLC_BLACK, RVLC_WHITE, pMsgIcon);
	myTFT.drawIcon(80, 20, 8, RVLC_BLACK, RVLC_WHITE, pAlarmIcon);
	myTFT.drawIcon(210, 20, 16, RVLC_BLACK, RVLC_WHITE, pBatIcon);

	myTFT.drawIcon(35, 45, 12, RVLC_GREEN , RVLC_BLACK, pPowerIcon);
	myTFT.drawIcon(55, 45, 12, RVLC_RED, RVLC_YELLOW, pSpeedIcon);
	myTFT.setFont(font_arialBold);
	myTFT.setCursor(80,45);
	myTFT.print(GetRVLibVersionNum());
	if (myTFT.drawBitmap(180, 45, 40 , 16, RVLC_CYAN , RVLC_BLACK, pSunText) != rvlDisplay_Success)
	{
		std::cout << "Warning an Error occurred in drawBitmap." << std::endl;
		return ;
	}
	// Lines
	myTFT.drawFastHLine(0,15,280,RVLC_WHITE);
	myTFT.drawFastHLine(0,40,280,RVLC_WHITE);
	myTFT.drawFastHLine(0,90,280,RVLC_WHITE);
	myTFT.drawFastHLine(0,135,280,RVLC_WHITE);
	myTFT.drawFastHLine(0,180,280,RVLC_WHITE);
	myTFT.drawFastHLine(0,230,280,RVLC_WHITE);
	// draw clock
	while(count > 99)
	{
		std::string TimeString = UTC_string();
		std::cout<< TimeString << "\r" << std::flush;
		auto DateInfo = TimeString.substr(0, 10);
		auto TimeInfo = TimeString.substr(11,8);
		
		myTFT.setFont(font_groTesk);
		//print time
		myTFT.setTextColor(RVLC_RED, RVLC_BLACK);
		myTFT.setCursor(50,100);
		myTFT.print(TimeInfo);
		myTFT.setFont(font_groTesk);
		//print date
		myTFT.setTextColor(RVLC_GREEN, RVLC_BLACK);
		myTFT.setCursor(50,140);
		myTFT.print(DateInfo);
		
		myTFT.setFont(font_retro);
		// print count
		myTFT.setTextColor(RVLC_YELLOW, RVLC_BLACK);
		myTFT.setCursor(160,210);
		myTFT.print(count);
		count--;
		//print name
		myTFT.setCursor(40,210);
		myTFT.setTextColor(RVLC_CYAN, RVLC_BLACK);
		myTFT.print(teststr1);
	}
	delayMilliSecRVL(TEST_DELAY2);
	myTFT.fillScreen(RVLC_BLACK);
	
}

// bitmap 2 colour , 128x128 bi color bitmap
void Test302(void)
{
	std::cout << "Test 302: Bi-color bitmap 128 X 128" << std::endl;
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.setTextColor(RVLC_WHITE, RVLC_BLACK);
	myTFT.setFont(font_orla);
	char teststr1[] = "Bitmap 2";
	myTFT.writeCharString(35, 10, teststr1);
	delayMilliSecRVL(TEST_DELAY2);
	
	if(myTFT.drawBitmap(40, 40, 128 , 128, RVLC_WHITE , RVLC_GREEN, pBackupMenuBitmap) != rvlDisplay_Success)
		return;
	delayMilliSecRVL(TEST_DELAY5);
}

// bitmap 24 colour , All file format = Windows BITMAPINFOHEADER offset 54
// bitmap are 220 by 240 
void Test303(void)
{
	std::cout << "Test 303: 24 bit color image bitmaps from the file system 220 X 240" << std::endl;
	myTFT.fillScreen(RVLC_BLACK);
	char teststr1[] = "Bitmap 24";
	myTFT.setTextColor(RVLC_WHITE, RVLC_BLACK);
	myTFT.writeCharString(35, 10, teststr1);
	delayMilliSecRVL(TEST_DELAY1);

	FILE *pFile ;
	size_t pixelSize = 3; // 24 bit 3 bytes per pixel
	uint8_t FileHeaderOffset = 54;
	uint8_t NumberOfFiles  = 1;
	uint8_t* bmpBuffer = nullptr;
	bmpBuffer = (uint8_t*)malloc((220 * 240) * pixelSize);
	if (bmpBuffer == nullptr)
	{
		std::cout << "Error Test 303 : MALLOC could not assign memory " << std::endl;
		return;
	}
	for (uint8_t i = 0 ; i < NumberOfFiles ; i++)
	{
		switch (i) // select file
		{
			case 0: pFile = fopen("bitmap/bitmap24images/24pic7_220X240.bmp", "r"); break;
		}

		if (pFile == nullptr)  // Check file exists
		{
			std::cout << "Error Test 303: File does not exist" << std::endl;
			free(bmpBuffer);
			return;
		}

		fseek(pFile, FileHeaderOffset, 0); // Put file in Buffer
		fread(bmpBuffer, pixelSize, 220 * 240, pFile);
		fclose(pFile);

		if(myTFT.drawBitmap24(20, 0, bmpBuffer,220,240) != rvlDisplay_Success)
		{// Check for success 0x00
			std::cout << "Warning an Error occurred in drawBitmap24" << std::endl;
			free(bmpBuffer);
			return;
		}
		delayMilliSecRVL(TEST_DELAY5);
	}
	free(bmpBuffer);  // Free Up Buffer
}

// test function for 16 bit color bitmaps made in GIMP (RGB 565 16 bit color)
// 3 files
// File 1 16pic1.bmp BITMAPV5HEADER offset 132
// Color space information written
// File 2&3 16pic2.bmp & 16pic3.bmp
// OS/2 OS22XBITMAPHEADER (BITMAPINFOHEADER2) offset 72
// NO color space information written
// All bitmaps are 128 by 128.
void Test304(void)
{
	std::cout << "Test 304: 16 bit color image bitmaps from the file system 128 X 128" << std::endl;
	myTFT.fillScreen(RVLC_BLACK);
	char teststr1[] = "Bitmap 16";
	myTFT.writeCharString(35, 10, teststr1);
	delayMilliSecRVL(TEST_DELAY2);

	FILE *pFile ;
	size_t pixelSize = 2; // 16 bit 2 bytes per pixel
	uint8_t NumberOfFiles  = 3;
	uint8_t offsetBMPHeader = 0;
	uint8_t offsetNoColSpace = 72;
	uint8_t offsetColSpace = 132;
	uint8_t bitmapWidth = 128;
	uint8_t bitmapHeight = 128;
	uint8_t* bmpBuffer1 = nullptr;
	bmpBuffer1 = (uint8_t*)malloc((bitmapWidth * bitmapHeight) * pixelSize);

	if (bmpBuffer1 == nullptr)
	{
		std::cout << "Error Test 304 : MALLOC could not assign memory " << std::endl;
		return;
	}

	for (uint8_t i = 0 ; i < NumberOfFiles ; i++)
	{
		switch (i) // select file
		{
			case 0:
				pFile = fopen("bitmap/bitmap16images/16pic1.bmp", "r");
				offsetBMPHeader = offsetColSpace ;
			break;
			case 1: pFile = fopen("bitmap/bitmap16images/16pic2.bmp", "r"); 
				offsetBMPHeader = offsetNoColSpace;
			break;
			case 2: pFile = fopen("bitmap/bitmap16images/16pic3.bmp", "r"); 
				offsetBMPHeader = offsetNoColSpace;
			break;
		}
		if (pFile == nullptr)
		{
			std::cout << "Error Test 404 : File does not exist" << std::endl;
			free(bmpBuffer1);
			return;
		}
		fseek(pFile, offsetBMPHeader, 0);
		fread(bmpBuffer1, pixelSize, bitmapWidth * bitmapHeight, pFile);
		fclose(pFile);

		if (myTFT.drawBitmap16(40, 40, bmpBuffer1, bitmapWidth, bitmapHeight) != rvlDisplay_Success)
		{
		// Check for success 0x00
			std::cout << "Warning an Error occurred in drawBitmap16" << std::endl;
			free(bmpBuffer1);
			return;
		}
		delayMilliSecRVL(TEST_DELAY5);
	} // end of for loop

	free(bmpBuffer1); // Free Up Buffer
	myTFT.fillScreen(RVLC_BLACK);
} // end of test 


// bitmap 16 colour full screen
// File 1 fourbyteburger240X320.bmp BITMAPV5HEADER offset 132 , 240x320 pixels
// Color space information written
// bitmap are 240 by 320 
void Test305(void)
{
	std::cout << "Test 305: 16 bit color image bitmaps from the file system 240 X 320" << std::endl;
	myTFT.fillScreen(RVLC_BLACK);
	delayMilliSecRVL(TEST_DELAY1);

	FILE *pFile ;
	size_t pixelSize = 2; // 16 bit 2 bytes per pixel
	uint8_t FileHeaderOffset = 132;
	uint8_t NumberOfFiles  = 1;
	uint8_t* bmpBuffer = nullptr;
	uint16_t bitmapWidth = 240;
	uint16_t bitmapHeight = 320;
	bmpBuffer = (uint8_t*)malloc((bitmapWidth * bitmapHeight) * pixelSize);
	if (bmpBuffer == nullptr)
	{
		std::cout << "Error Test 305 : MALLOC could not assign memory " << std::endl;
		return;
	}
	for (uint8_t i = 0 ; i < NumberOfFiles ; i++)
	{
		switch (i) // select file
		{
			case 0: pFile = fopen("bitmap/bitmap16images/fourbyteburger240X320.bmp", "r"); break;
		}

		if (pFile == nullptr)  // Check file exists
		{
			std::cout << "Error Test 305: File does not exist" << std::endl;
			free(bmpBuffer);
			return;
		}

		fseek(pFile, FileHeaderOffset, 0); // Put file in Buffer
		fread(bmpBuffer, pixelSize, bitmapWidth * bitmapHeight, pFile);
		fclose(pFile);

		if(myTFT.drawBitmap16(0, 0, bmpBuffer,bitmapWidth, bitmapHeight) != rvlDisplay_Success)
		{// Check for success 0x00
			std::cout << "Warning an Error occurred in drawBitmap16" << std::endl;
			free(bmpBuffer);
			return;
		}
		delayMilliSecRVL(TEST_DELAY5);
		delayMilliSecRVL(TEST_DELAY5);
	}
	free(bmpBuffer);  // Free Up Buffer
}

//Return UTC time as a std:.string with format "yyyy-mm-dd hh:mm:ss".
std::string UTC_string() 
{
	std::time_t time = std::time({});
	char timeString[std::size("yyyy-mm-dd hh:mm:ss UTC")];
	std::strftime(std::data(timeString), std::size(timeString), "%F %T UTC", std::gmtime(&time));
	return timeString;
}

void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.setFont(font_orla);
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.writeCharString(35, 50, teststr1);
	delayMilliSecRVL(TEST_DELAY5);
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}


// *************** EOF ****************
