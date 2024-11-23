/*! 
	@file examples/st7789//Frame_rate_test_two/main.cpp
	@brief Frame rate test. FPS text + graphics
	@note See USER OPTIONS 1-3 in SETUP function
	@details 
		16 FPS recorded V 1.0.2 at 8MHz TFT SPI0
		10 FPS recorded V 1.0.2 at 8MHz TFT SPI1
		3 FPS recorded  V 1.0.2 at software SPI
	@test 
		-# Test 603 Frame rate per second (FPS) test text + graphics
*/

// Section ::  libraries 
#include <bcm2835.h> // for SPI GPIO and delays.
#include <ctime> // for test FPS
#include "ST7789_TFT_LCD_RVL.hpp"

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000

// Section :: Globals 
ST7789_TFT myTFT;
uint16_t myTFTWidth = 240;// Screen width in pixels
uint16_t myTFTHeight = 320; // Screen height in pixels

// vars for the test
uint16_t countLimit = 1000;
uint16_t count  = 0;
uint64_t  previousCounter =0;

// =============== Function prototype ================
int8_t SetupHWSPI(void);
void TestFPS(void);
void EndTests(void);
void display(long , int );
static uint64_t counter( void );

// ======================= Main ===================
int main()
{
	if(SetupHWSPI() != 0)return -1;
	TestFPS();
	EndTests();
	return 0;
}
// ======================= End of main  ===================

//  Section ::  Function Space 
// Hardware SPI setup
int8_t SetupHWSPI(void)
{
	std::cout << "TFT Start Test 603 FPS text + graphics" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error 1201 Problem with init bcm2835 library" << std::endl;
		return 2;
	}

// ** USER OPTION 1 GPIO HW SPI **
	int8_t RST_TFT  = 25;
	int8_t DC_TFT   = 24;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT);
//*********************************************

// ** USER OPTION 2 Screen SetupHWSPI **
	uint16_t OFFSET_COL = 0;  // These offsets can be adjusted for any issues->
	uint16_t OFFSET_ROW = 0;  // with manufacture tolerance/defects at edge of display
	uint16_t TFT_WIDTH = myTFTWidth;   // Screen width in pixels
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
	delayMilliSecRVL(100);
	return 0;
}

void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.writeCharString(25, 50, teststr1);
	delayMilliSecRVL(2500);
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}


void TestFPS() {
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_90);
	myTFT.fillScreen(RVLC_BLACK);
	myTFT.setFont(font_orla);
	
	std::cout << "FPS test: text + graphics ends at :: " << countLimit << std::endl;
	while (count < countLimit)
	{
		static long framerate = 0;
		display(framerate, count);
		framerate++;
		count++;
		delayMilliSecRVL(1);
	}

}


// Function to display left hand side
void display(long currentFramerate, int count)
{

	myTFT.setCursor(25, 30);
	myTFT.print("G Lyons");
	myTFT.setCursor(25, 70);
	myTFT.print(count);

	// Values to count frame rate per second
	static long lastFramerate = 0;
	static uint16_t fps;
	uint64_t currentCounter = counter();
	if(currentCounter - previousCounter >= 1000000000)
	{
		//(Rolls over every 1 second)
		fps = currentFramerate - lastFramerate;
		lastFramerate = currentFramerate ;
		previousCounter = currentCounter;
	}

	myTFT.setCursor(25, 110);
	myTFT.print(fps);
	myTFT.print(" fps");
	myTFT.setCursor(25, 150);
	myTFT.print(GetRVLibVersionNum());

	myTFT.drawFastVLine(160, 20, 200, RVLC_BLUE);
	myTFT.fillRect(200, 70, 20, 20, RVLC_RED);
	myTFT.fillCircle(200, 30, 10, RVLC_GREEN);
	myTFT.fillTriangle(180,200, 200, 180 , 220, 200, RVLC_YELLOW);

}

//This returns nano-seconds as a 64-bit unsigned number, monotonically increasing,
//probably since system boot.
//The actual resolution looks like microseconds. returns nanoseconds
static uint64_t counter( void )
{
  struct timespec now;
  clock_gettime( CLOCK_MONOTONIC, &now );
  return  ((uint64_t)now.tv_sec * 1000000000U) + (uint64_t)now.tv_nsec;
}
