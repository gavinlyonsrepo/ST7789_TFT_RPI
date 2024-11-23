/*! 
	@file examples/st7789/Frame_rate_test_bmp/main.cpp
	@brief Frame rate test. FPS Bitmaps, frame rate per second
	@note See USER OPTIONS 1-3 in SETUP function
	@details This test is setup for a 128by128 bitmaps 
		3 files 128by128 pixels are loaded and displayed as many times as possible in 
		10 seconds to calculate FPS.
		Results:
		814 frames, 10 sec, 81.3904 fps  at 8Mhz SPI Baud rate, HW SPI 0
		349 frames, 10 sec, 34.8921 fps  at 8Mhz SPI Baud rate, HW SPI 1 (aux)
		32 frames, 10 sec, 3.17005 fps  at Software SPI 
	@test 
		-# Test 601 Frame rate per second (FPS) test. 24bit bitmaps.
*/

// Section ::  libraries 
#include <bcm2835.h> // for SPI GPIO and delays.
#include <ctime> // for test FPS
#include "ST7789_TFT_LCD_RVL.hpp"

// Section :: Defines   
//  Test related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000

// Test bitmaps related
#define myBMPWidth 128 //size in pixels of bitmap 
#define myBMPHeight 128
uint8_t numberOfFiles = 3;

// Section :: Globals 
ST7789_TFT myTFT;
// Display size in pixels
#define myTFTWidth 240
#define myTFTHeight 320

//  Section ::  Function Headers 

int8_t Setup(void); // setup + user options
void TestFPS(void); // Frames per second 24 color bitmap test,
void EndTests(void);

int64_t getTime(); // Utility for FPS test
uint8_t* loadImage(char* name); // Utility for FPS test

//  Section ::  MAIN loop

int main(void) 
{
	if(Setup() != 0)return -1;
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_90); // Rotate display
	TestFPS();
	EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space 

int8_t Setup(void)
{
	std::cout << "TFT Start" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error 1201 Problem with init bcm2835 library" << std::endl;
		return 2;
	}
	
// ** USER OPTION 1 GPIO/SPI TYPE HW OR SW **
	int8_t RST_TFT  =  25;
	int8_t DC_TFT   =  24;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT);
//*********************************************

// ** USER OPTION 2 Screen Setup **
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW ,myTFTWidth , myTFTHeight);
// ***********************************

// ** USER OPTION 3  SPI baud rate + SPI_CE_PIN**
	uint32_t SCLK_FREQ =  8000000 ; // HW Spi freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // which HW SPI chip enable pin to use,  0 or 1
	if(myTFT.TFTInitSPI( SCLK_FREQ, SPI_CE_PIN) != rvlDisplay_Success)
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


/*!
 *@brief Frames per second test , 24 color bitmap test, 
*/
void TestFPS(void) {

	myTFT.fillScreen(RVLC_RED);
	
	// Load images into buffers
	uint8_t* img[numberOfFiles] = { 
		loadImage((char*)"bitmap/bitmap24images/24pic2.bmp"),
		loadImage((char*)"bitmap/bitmap24images/24pic4.bmp"),
		loadImage((char*)"bitmap/bitmap24images/24pic5.bmp")
	};
	for (uint8_t i=0; i< numberOfFiles ;i++) // Did any loadImage call return nullptr
	{
		if (img[i] == nullptr){ 
			for(uint8_t j=0; j< numberOfFiles; j++) free(img[j]); // Free Up Buffer if set
			delayMilliSecRVL(TEST_DELAY1);
			return;
		}
	}
	int64_t start = getTime(), duration = 0;
	uint32_t frames = 0;
	double fps = 0;

	// Run for ~10sec
	while(duration < 10000000) {
		myTFT.drawBitmap24(35, 50, img[frames % numberOfFiles], myBMPWidth, myBMPHeight);

		duration = getTime() - start;

		if((++frames % 50) == 0) {
			fps = (double)frames / ((double)duration / 1000000);
			std::cout << fps << std::endl;
		}
	}

	// Get final Stats and print
	duration = getTime() - start;
	fps = (double)frames / ((double)duration / 1000000);
	std::cout << frames << " frames, " << duration / 1000000 << " sec, " << fps << " fps" << std::endl;

	// Free Up Buffers
	for(int i=0; i< numberOfFiles; i++) free(img[i]);
}


void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.setFont(font_orla);
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.writeCharString(35, 50, teststr1);
	delayMilliSecRVL(TEST_DELAY5);
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}

int64_t getTime() {
	struct timespec tms;
	if (clock_gettime(CLOCK_REALTIME,&tms)) return -1;
	int64_t micros = tms.tv_sec * 1000000;
	micros += tms.tv_nsec/1000;
	if (tms.tv_nsec % 1000 >= 500) ++micros;
	return micros;
}

uint8_t* loadImage(char* name) {
	FILE *pFile ;
	size_t pixelSize = 3; // 24 bit 3 bytes per pixel
	uint8_t* bmpBuffer1 = nullptr;
	uint8_t FileHeaderOffset = 54;
	pFile = fopen(name, "r");
	if (pFile == nullptr) {
		std::cout << "Error TestFPS : File does not exist" << std::endl;
		return nullptr;
	} else {
		bmpBuffer1 = (uint8_t*)malloc((myBMPWidth * myBMPHeight) * pixelSize);
		if (bmpBuffer1 == nullptr)
		{
			std::cout << "Error TestFPS : MALLOC could not assign memory " << std::endl;
			return nullptr;
		}
		fseek(pFile,  FileHeaderOffset, 0);
		fread(bmpBuffer1, pixelSize, myBMPWidth * myBMPHeight, pFile);
		fclose(pFile);
	}
	
	return bmpBuffer1;
}

// *************** EOF ****************
