/*
	ILI9163 Lib


	(c)2016 joaquim.org
*/



#ifndef _ILI9163LIB_H_
#define _ILI9163LIB_H_

#include "Arduino.h"
#include "pins_arduino.h"
#include "wiring_private.h"
#include <stdio.h>
#include <stdlib.h>
#include <SPI.h>

#include <eagle_soc.h>

#include "Adafruit_GFX.h"

// define size
#define ILI9163_HEIGHT 						128
#define ILI9163_WIDTH 						128

/*
This display:
http://www.ebay.com/itm/Replace-Nokia-5110-LCD-1-44-Red-Serial-128X128-SPI-Color-TFT-LCD-Display-Module-/271422122271
This particular display has a design error! The controller has 3 pins to configure to constrain
the memory and resolution to a fixed dimension (in that case 128x128) but they leaved those pins
configured for 128x160 so there was several pixel memory addressing problems.
I solved by setup several parameters that dinamically fix the resolution as needed so below
the parameters for this diplay.
*/
#define _GRAMWIDTH      					128
#define _GRAMHEIGH      					160


// ILI9163 LCD Controller Commands
#define ILI9163_CMD_NOP                     0x00
#define ILI9163_CMD_SOFT_RESET              0x01
#define ILI9163_CMD_GET_RED_CHANNEL         0x06
#define ILI9163_CMD_GET_GREEN_CHANNEL       0x07
#define ILI9163_CMD_GET_BLUE_CHANNEL        0x08
#define ILI9163_CMD_GET_PIXEL_FORMAT        0x0C
#define ILI9163_CMD_GET_POWER_MODE          0x0A
#define ILI9163_CMD_GET_ADDRESS_MODE        0x0B
#define ILI9163_CMD_GET_DISPLAY_MODE        0x0D
#define ILI9163_CMD_GET_SIGNAL_MODE         0x0E
#define ILI9163_CMD_GET_DIAGNOSTIC_RESULT   0x0F
#define ILI9163_CMD_ENTER_SLEEP_MODE        0x10
#define ILI9163_CMD_EXIT_SLEEP_MODE         0x11
#define ILI9163_CMD_ENTER_PARTIAL_MODE      0x12
#define ILI9163_CMD_ENTER_NORMAL_MODE       0x13
#define ILI9163_CMD_EXIT_INVERT_MODE        0x20
#define ILI9163_CMD_ENTER_INVERT_MODE       0x21
#define ILI9163_CMD_SET_GAMMA_CURVE         0x26
#define ILI9163_CMD_SET_DISPLAY_OFF         0x28
#define ILI9163_CMD_SET_DISPLAY_ON          0x29
#define ILI9163_CMD_SET_COLUMN_ADDRESS      0x2A
#define ILI9163_CMD_SET_PAGE_ADDRESS        0x2B
#define ILI9163_CMD_WRITE_MEMORY_START      0x2C
#define ILI9163_CMD_WRITE_LUT               0x2D
#define ILI9163_CMD_READ_MEMORY_START       0x2E
#define ILI9163_CMD_SET_PARTIAL_AREA        0x30
#define ILI9163_CMD_SET_SCROLL_AREA         0x33
#define ILI9163_CMD_SET_TEAR_OFF            0x34
#define ILI9163_CMD_SET_TEAR_ON             0x35
#define ILI9163_CMD_SET_ADDRESS_MODE        0x36
#define ILI9163_CMD_SET_SCROLL_START        0X37
#define ILI9163_CMD_EXIT_IDLE_MODE          0x38
#define ILI9163_CMD_ENTER_IDLE_MODE         0x39
#define ILI9163_CMD_SET_PIXEL_FORMAT        0x3A
#define ILI9163_CMD_WRITE_MEMORY_CONTINUE   0x3C
#define ILI9163_CMD_READ_MEMORY_CONTINUE    0x3E
#define ILI9163_CMD_SET_TEAR_SCANLINE       0x44
#define ILI9163_CMD_GET_SCANLINE            0x45
#define ILI9163_CMD_READ_ID1                0xDA
#define ILI9163_CMD_READ_ID2                0xDB
#define ILI9163_CMD_READ_ID3                0xDC
#define ILI9163_CMD_FRAME_RATE_CONTROL1     0xB1
#define ILI9163_CMD_FRAME_RATE_CONTROL2     0xB2
#define ILI9163_CMD_FRAME_RATE_CONTROL3     0xB3
#define ILI9163_CMD_DISPLAY_INVERSION       0xB4
#define ILI9163_CMD_SOURCE_DRIVER_DIRECTION 0xB7
#define ILI9163_CMD_GATE_DRIVER_DIRECTION   0xB8
#define ILI9163_CMD_POWER_CONTROL1          0xC0
#define ILI9163_CMD_POWER_CONTROL2          0xC1
#define ILI9163_CMD_POWER_CONTROL3          0xC2
#define ILI9163_CMD_POWER_CONTROL4          0xC3
#define ILI9163_CMD_POWER_CONTROL5          0xC4
#define ILI9163_CMD_VCOM_CONTROL1           0xC5
#define ILI9163_CMD_VCOM_CONTROL2           0xC6
#define ILI9163_CMD_VCOM_OFFSET_CONTROL     0xC7
#define ILI9163_CMD_WRITE_ID4_VALUE         0xD3
#define ILI9163_CMD_NV_MEMORY_FUNCTION1     0xD7
#define ILI9163_CMD_NV_MEMORY_FUNCTION2     0xDE
#define ILI9163_CMD_POSITIVE_GAMMA_CORRECT  0xE0
#define ILI9163_CMD_NEGATIVE_GAMMA_CORRECT  0xE1
#define ILI9163_CMD_GAM_R_SEL               0xF2

#define __CS  05
#define __DC  04
#define __RST 16


// This is the offset between image in RAM and TFT. In that case 160 - 128 = 32
#define __OFFSET		32


// RGB24 to RGB16: Translates a 3 byte RGB value into a 2 byte value for the LCD (values should be 0-31)
// Radu Motisan: we need to scale the 8bit values to 5bit (for blue or red) / 6bit (for green)
inline uint16_t rgb24to16(uint8_t r, uint8_t g, uint8_t b) {
	return ((b>>3) << 11) | ((g>>2) << 5) | (r>>3);
}


#define	BLACK   	rgb24to16(  0,   0,   0)
#define WHITE   	rgb24to16(255, 255, 255)
#define BLUE    	rgb24to16(  0,   0, 255)
#define RED     	rgb24to16(255,   0,   0)
#define GREEN   	rgb24to16(  0, 255,   0)
#define CYAN    	rgb24to16(  0, 255, 255)
#define MAGENTA 	rgb24to16(255,   0, 255)
#define YELLOW  	rgb24to16(255, 255,   0)
#define BRIGHT_RED	rgb24to16(249,  56,  34)
#define LIGHT_GREY	rgb24to16(211, 211, 211)
#define DARK_GREY	rgb24to16(169, 169, 169)


// Use ram Buffer
// Nice LCD update but high memory usage :( 
#define USE_BUFFER

class ILI9163  : public Adafruit_GFX {


public:

	enum Rotation {
		ROT0 = 0,	// portrait
		ROT90 = 96,	// landscape
		ROT180 = 160,	// flipped portrait
		ROT270 = 192	// flipped landscape
	};

	ILI9163( void ) : Adafruit_GFX(ILI9163_WIDTH, ILI9163_HEIGHT) { }

	void begin( void );

	void writeCommand(uint8_t address);
	void writeData(uint8_t data);
	void writeData16(uint16_t word);
	void setAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
	void RamAdressReset( void );
	void reset(void);

	void displayOn();
  	void displayOff();
  	void clearDisplay( uint16_t color );
  	void setRotation(Rotation rotation);

	void drawPixel(int16_t x, int16_t y, uint16_t color);	
	
	#ifdef USE_BUFFER
		void displayUpdate();
	#else
		void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
		void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
		void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

		size_t write(uint8_t);
		void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
	#endif

	protected:
		Rotation _rotation;
		#ifdef USE_BUFFER
			uint16_t buffer_[ ILI9163_HEIGHT * ILI9163_WIDTH ];
		#endif

};


#endif
