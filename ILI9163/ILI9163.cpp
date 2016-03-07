/*
    ILI9163 Lib


    (c)2016 joaquim.org
*/
//#include "font5x5.c"

#include "ILI9163.h"
#include <SPI.h>    

//#include "glcdfont.c"
#include <pgmspace.h>


void ILI9163::begin( void ) {

    // SPI Config
    SPI.begin();
    //  1000000
    // 79000000
    SPI.setFrequency(79000000);
    //SPI.setClockDivider(SPI_CLOCK_DIV2);    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);

    pinMode(__CS, OUTPUT); 
    pinMode(__DC, OUTPUT); 
    pinMode(__RST, OUTPUT); 

    digitalWrite(__CS, HIGH);
    digitalWrite(__RST, HIGH);

    // Hardware reset the LCD
    reset();

    writeCommand(ILI9163_CMD_EXIT_SLEEP_MODE);
    delay(5); // Wait for the screen to wake up

    writeCommand(ILI9163_CMD_SET_PIXEL_FORMAT);
    writeData(0x05); // 16 bits per pixel
   
    writeCommand(ILI9163_CMD_SET_GAMMA_CURVE);
    writeData(0x04); // Select gamma curve 3
    
    writeCommand(ILI9163_CMD_GAM_R_SEL);
    writeData(0x01); // Gamma adjustment enabled
    
    writeCommand(ILI9163_CMD_POSITIVE_GAMMA_CORRECT);
    writeData(0x3f); // 1st Parameter
    writeData(0x25); // 2nd Parameter
    writeData(0x1c); // 3rd Parameter
    writeData(0x1e); // 4th Parameter
    writeData(0x20); // 5th Parameter
    writeData(0x12); // 6th Parameter
    writeData(0x2a); // 7th Parameter
    writeData(0x90); // 8th Parameter
    writeData(0x24); // 9th Parameter
    writeData(0x11); // 10th Parameter
    writeData(0x00); // 11th Parameter
    writeData(0x00); // 12th Parameter
    writeData(0x00); // 13th Parameter
    writeData(0x00); // 14th Parameter
    writeData(0x00); // 15th Parameter
     
    writeCommand(ILI9163_CMD_NEGATIVE_GAMMA_CORRECT);
    writeData(0x20); // 1st Parameter
    writeData(0x20); // 2nd Parameter
    writeData(0x20); // 3rd Parameter
    writeData(0x20); // 4th Parameter
    writeData(0x05); // 5th Parameter
    writeData(0x00); // 6th Parameter
    writeData(0x15); // 7th Parameter
    writeData(0xa7); // 8th Parameter
    writeData(0x3d); // 9th Parameter
    writeData(0x18); // 10th Parameter
    writeData(0x25); // 11th Parameter
    writeData(0x2a); // 12th Parameter
    writeData(0x2b); // 13th Parameter
    writeData(0x2b); // 14th Parameter
    writeData(0x3a); // 15th Parameter
    
    writeCommand(ILI9163_CMD_FRAME_RATE_CONTROL1);
    writeData(0x08); // DIVA = 8
    writeData(0x08); // VPA = 8
    
    writeCommand(ILI9163_CMD_DISPLAY_INVERSION);
    writeData(0x07); // NLA = 1, NLB = 1, NLC = 1 (all on Frame Inversion)
   
    writeCommand(ILI9163_CMD_POWER_CONTROL1);
    writeData(0x0a); // VRH = 10:  GVDD = 4.30
    writeData(0x02); // VC = 2: VCI1 = 2.65
      
    writeCommand(ILI9163_CMD_POWER_CONTROL2);
    writeData(0x02); // BT = 2: AVDD = 2xVCI1, VCL = -1xVCI1, VGH = 5xVCI1, VGL = -2xVCI1

    writeCommand(ILI9163_CMD_VCOM_CONTROL1);
    writeData(0x50); // VMH = 80: VCOMH voltage = 4.5
    writeData(0x5b); // VML = 91: VCOML voltage = -0.225
    
    writeCommand(ILI9163_CMD_VCOM_OFFSET_CONTROL);
    writeData(0x40); // nVM = 0, VMF = 64: VCOMH output = VMH, VCOML output = VML
    
    writeCommand(ILI9163_CMD_SET_COLUMN_ADDRESS);
    writeData(0x00); // XSH
    writeData(0x00); // XSL
    writeData(0x00); // XEH
    writeData(0x7f); // XEL (128 pixels x)
   
    writeCommand(ILI9163_CMD_SET_PAGE_ADDRESS);
    writeData(0x00);
    writeData(0x00);
    writeData(0x00);
    writeData(0x7f); // 128 pixels y
    
    // Select display orientation
    //writeCommand(ILI9163_CMD_SET_ADDRESS_MODE);
    //writeData(rotation);
    setRotation(ROT270);

    // Set the display to on
    writeCommand(ILI9163_CMD_SET_DISPLAY_ON);
    writeCommand(ILI9163_CMD_WRITE_MEMORY_START);
}


void ILI9163::writeCommand(uint8_t address) {
    digitalWrite(__CS, LOW);
    // set D/C pin for command
    digitalWrite(__DC, LOW);
    // send data by SPI
    SPI.write(address);
    digitalWrite(__CS, HIGH);
}

void ILI9163::writeData(uint8_t data) {
    digitalWrite(__CS, LOW);
    // set D/C pin for data
    digitalWrite(__DC, HIGH);
    // send data by SPI
    SPI.write(data);
    digitalWrite(__CS, HIGH);
}

void ILI9163::writeData16(uint16_t word) {
    digitalWrite(__CS, LOW);
    // set D/C pin for data
    digitalWrite(__DC, HIGH);
    // send data by SPI
    SPI.write16(word);
    digitalWrite(__CS, HIGH);
}

//set coordinate for print or other function
void ILI9163::setAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2) {

    uint16_t offsetX = 0, offsetY = 0;

    switch(_rotation) {
        case ROT0:
        case ROT180:
        case ROT90:
            break;
        case ROT270:
            offsetY = __OFFSET;
            break;
    }

    writeCommand(ILI9163_CMD_SET_COLUMN_ADDRESS);
    writeData16(x1 + offsetX);
    writeData16(x2 + offsetX);

    writeCommand(ILI9163_CMD_SET_PAGE_ADDRESS);
    writeData16(y1 + offsetY);
    writeData16(y2 + offsetY);
    // memory write
    writeCommand(ILI9163_CMD_WRITE_MEMORY_START);
}

// Reset the LCD hardware
void ILI9163::reset(void) {
    // Reset pin is active low (0 = reset, 1 = ready)
    /*digitalWrite(__RST, LOW);
    delay(50);

    digitalWrite(__RST, HIGH);
    delay(120);*/
}


//rotate screen at desired orientation
void ILI9163::setRotation(Rotation rotation) {
    writeCommand(ILI9163_CMD_SET_ADDRESS_MODE);
    writeData(rotation);
    _rotation = rotation;
    switch(_rotation) {
        case ROT0:
        case ROT180:
            _width  = WIDTH;
            _height = HEIGHT;
            break;
        case ROT90:
        case ROT270:
            _width  = HEIGHT;
            _height = WIDTH;
        break;
    }
}

void  ILI9163::RamAdressReset( void ) {
    writeCommand(ILI9163_CMD_SET_COLUMN_ADDRESS);
    writeData(0x00);
    writeData(0x00);
    writeData(0x00);
    writeData(0x7f);
  
    writeCommand(ILI9163_CMD_SET_PAGE_ADDRESS);
    writeData(0x00);
    writeData(0x00);
    writeData(0x00);
    writeData(0x9f);  
    // memory write
    writeCommand(ILI9163_CMD_WRITE_MEMORY_START);        
}


void ILI9163::displayOff(void) {
    writeCommand(ILI9163_CMD_SET_DISPLAY_OFF); 
}
void ILI9163::displayOn(void) {
    writeCommand(ILI9163_CMD_SET_DISPLAY_ON);
}


#ifdef USE_BUFFER
    void ILI9163::displayUpdate() {
        setAddress(0, 0, ILI9163_WIDTH, ILI9163_HEIGHT);
        for (int16_t i=0; i < (ILI9163_WIDTH * ILI9163_HEIGHT); i++) {        
            writeData16(buffer_[i]);
        }
    }

    void ILI9163::drawPixel(int16_t x, int16_t y, uint16_t color) {
        int16_t pos = 0;

        if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;

        int16_t t;
        switch(rotation) {
         case 1:
          t = x;
          x = WIDTH  - 1 - y;
          y = t;
          break;
         case 2:
          x = WIDTH  - 1 - x;
          y = HEIGHT - 1 - y;
          break;
         case 3:
          t = x;
          x = y;
          y = HEIGHT - 1 - t;
          break;
        }

        buffer_[x + y * WIDTH] = color;
    }

    // clear everything
    void ILI9163::clearDisplay( uint16_t color ) {    
        uint16_t i, pixels = WIDTH * HEIGHT;
        for(i=0; i<pixels; i++) buffer_[i] = color;
    }

#else

// clear everything
void ILI9163::clearDisplay( uint16_t color ) {    
    RamAdressReset();
    for (int16_t i=0; i < (_GRAMWIDTH * _GRAMHEIGH); i++) {        
        writeData16(color);
    }
}

void ILI9163::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
    setAddress(x, y, x + 1, y + 1);
    writeData16(color);
}


void ILI9163::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  // Update in subclasses if desired!
    setAddress(x, y, x, y + h);
    for (int16_t i=0; i < h; i++) {        
      writeData16(color);
    }
}

void ILI9163::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  // Update in subclasses if desired!
    setAddress(x, y, x + w, y);
    for (int16_t i=0; i < w; i++) {        
      writeData16(color);
    }
}

void ILI9163::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    // Update in subclasses if desired!
    setAddress(x, y, (x + w) - 1, (y + h) - 1);
    for (int16_t i=0 ; i < (w * h); i++) {        
        writeData16(color);
    }

}


size_t ILI9163::write(uint8_t c) {
    if(c == '\n') {
      cursor_y += textsize*8;
      cursor_x  = 0;
    } else if(c == '\r') {
      // skip em
    } else {
      if(wrap && ((cursor_x + textsize * 6) >= _width)) { // Heading off edge?
        cursor_x  = 0;            // Reset x to zero
        cursor_y += textsize * 8; // Advance y one line
      }
      drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
      cursor_x += textsize * 6;
    }
    return 1;
}


// Draw a character
void ILI9163::drawChar(int16_t x, int16_t y, unsigned char c,
 uint16_t color, uint16_t bg, uint8_t size) {
    if((x >= _width)            || // Clip right
       (y >= _height)           || // Clip bottom
       ((x + 6 * size - 1) < 0) || // Clip left
       ((y + 8 * size - 1) < 0))   // Clip top
      return;
    
    int16_t charBuf[8][6];

    if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

    for(int8_t i=0; i<6; i++ ) {
      uint8_t line;
      if(i < 5) line = pgm_read_byte(font+(c*5)+i);
      else      line = 0x0;
      for(int8_t j=0; j<8; j++, line >>= 1) {
        if(line & 0x1) {
            charBuf[j][i] = color;
        } else {
            charBuf[j][i] = bg;
        }
      }
    }

    setAddress(x, y, x + 5, y + 7);
    for (int8_t i = 0; i < 8; i++) {
        for (int8_t j = 0; j < 6; j++) {
            writeData16(charBuf[i][j]);
        }
    }
}

#endif