
#include "z80.h"
#include "zx81.h"
#include "FS.h"
#include <ILI9163.h>

//extern ILI9163   lcd;

static unsigned char zx2ascii[128] = {
/*  0- 9 */ ' ', '_', '_', '_', '_', '_', '_', '_', '_', '_', 
/* 10-19 */ '_', '\"','!', '$', ':', '?', '(', ')', '>', '<', 
/* 20-29 */ '=', '+', '-', '*', '/', ';', ',', '.', '0', '1', 
/* 30-39 */ '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 
/* 40-49 */ 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
/* 50-59 */ 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 
/* 60-63 */ 'W', 'X', 'Y', 'Z'
};

ZX81::ZX81() {
    vid_hsync = 0;
    key_sync = 0;
    // Initialize the CPU and the RAM
        
    memset( ram_, 0x00, sizeof(ram_) );
    memset( keyboard, 0xFF, sizeof(keyboard) );
    memset( keyboardbuffer, 0x00, sizeof(keyboardbuffer) );
    memset( screen_, 0x0, sizeof(screen_) );
    
    posbuffer = 0;
    
}


void ZX81::GetASM() {

  Serial.println("");
}

void ZX81::ShowMEM( unsigned int pos ) {

  for( int j = 0; j < 0x10; j++ ) {
    Serial.printf( "%04X ", pos + (j * 0x10) );
    for( int i = 0; i < 0x10; i++ ) {
      Serial.printf( "%02X ", readByte(pos + (i + (j * 0x10))) );
    }

    Serial.printf("    ");
    
    for( int i = 0; i < 0x10; i++ ) {
      if ( (readByte(pos + (i + (j * 0x10))) > 31) && (readByte(pos + (i + (j * 0x10))) < 96) ) {
        Serial.printf("%c", zx2ascii[readByte(pos + (i + (j * 0x10)))] );
      } else {
        Serial.printf(".");
      }
    }
    
    
    Serial.println("");
  }
  
}

void ZX81::debug() {

}

void ZX81::setLCD(ILI9163 *setLCD) {
  lcd = setLCD;
}

void ZX81::updateScreen(void) {
  int px, py;
  unsigned char c, nl = 0;
  unsigned int spos = ( readByte(0x400c) + (readByte(0x400d) << 8) );
  memset( screen_, 0x0, sizeof(screen_) ); 
  
  for (py=0; py < 25; py++) {
    for (px=0; px < 32; px++) {
      c = readByte(spos++);            
      if ( c == 0x76 ) break;      
      screen_[py][px] = c;
    }   
  }

  
}

void ZX81::showScreen(void) {
  int px, py;
  unsigned char c;
  
  lcd->setCursor(0, 0);

  for (py=0; py < 15; py++) {
    for (px=0; px < 21; px++) {
      c = screen_[py][px];
      if( c >= 0x3F ) {
        c = c - 0x80;
        lcd->setTextColor(WHITE, BLACK);
      } else {
        lcd->setTextColor(BLACK, WHITE);
      }     
      lcd->printf("%c", zx2ascii[c]);    
    }    
  }

  lcd->setCursor(0, 120);
  for (px=0; px < 21; px++) {
    c = screen_[24][px];
    if( c >= 0x3F ) {
      c = c - 0x80;
      lcd->setTextColor(WHITE, BLACK);
    } else {
      lcd->setTextColor(BLACK, WHITE);
    }     
    lcd->printf("%c", zx2ascii[c]);    
  }
  
  
}

/*
    For Z80 Environment: read a byte from memory.
*/
unsigned char ZX81::readByte( unsigned int addr ) {
  unsigned char b;
  if ( (addr >= Z80_RAM_BASE) && (addr <= (Z80_RAM_BASE + Z80_RAM_SIZE)) ) {
    return ram_[addr - Z80_RAM_BASE];
  } else if (addr <= Z80_RAM_BASE) {
    if ( addr >= 0x2000 ) {
      return pgm_read_byte(zx81rom + (addr - 0x2000));
    } else {
      return pgm_read_byte(zx81rom + addr);
    }
  /*} else if ( addr >= 0xC000 ) {
    //Serial.printf("Read MEM : %04X\n", addr);
    b = ram_[(addr & 0x7FFF) - Z80_RAM_BASE];
    if (b & 0x40) {        
      return b;
    }
    return 0x00;*/
  } else {
    return 0xFF;  
  }
  
}

/*
    For Z80 Environment: write a byte to memory.
*/
void ZX81::writeByte( unsigned int addr, unsigned char b ) {
  if ( (addr >= Z80_RAM_BASE) && (addr <= (Z80_RAM_BASE + Z80_RAM_SIZE)) ) {
    ram_[addr - Z80_RAM_BASE] = b;
  }
}

/*
    For Z80 Environment: read from a port.

*/
unsigned char ZX81::readPort( unsigned char reg, unsigned int port ) {
  unsigned char b;
  //if(!(port&4)) port=0xfb;
  //if(!(port&1)) port=0xfe;

  //Serial.printf("Read Port : %04X | Reg : %02X\n", port, reg);
  if ( keyboardbuffer[0] != 0x0 ) {
    setKey(keyboardbuffer[0] , keyboardbuffer[1], keyboardbuffer[2]);
    //Serial.printf("Key Down...\n");
  }
  
  if (port == 0xfe) {
    switch (reg) {
      case 0xfe: b = keyboard[0]; key_sync++; break; 
      case 0xfd: b = keyboard[1]; break; 
      case 0xfb: b = keyboard[2]; break; 
      case 0xf7: b = keyboard[3]; break; 
      case 0xef: b = keyboard[4]; break; 
      case 0xdf: b = keyboard[5]; break; 
      case 0xbf: b = keyboard[6]; break; 
      case 0x7f: b = keyboard[7]; break;
      default :
        b = 0xFF;        
    }
    
    return b;
  }

  //Serial.printf("Read Port : %04X | Reg : %02X\n", port, reg);
  return 0x0;
  
}

/*
    For Z80 Environment: write to a port.
*/
void ZX81::writePort( unsigned int addr, unsigned char b ) {
  /*vid_hsync++;
  if ( vid_hsync > 5 ) {
    vid_hsync = 0;        
  }*/

  updateScreen();
  
}


void ZX81::reset() {
  
  z80reset();

}


void ZX81::run( ) {
  execZ80();
}

/*
    __Line____Bit__0____1____2____3____4__
     0  (A8)     SHIFT  Z    X    C    V
     1  (A9)       A    S    D    F    G
     2  (A10)      Q    W    E    R    T
     3  (A11)      1    2    3    4    5
     4  (A12)      0    9    8    7    6
     5  (A13)      P    O    I    U    Y
     6  (A14)    ENTER  L    K    J    H
     7  (A15)     SPC   .    M    N    B
*/


void ZX81::putKeyboard(unsigned char key, unsigned char shift, unsigned char function) {

  keyboardbuffer[0] = key;
  keyboardbuffer[1] = shift;
  keyboardbuffer[2] = function;
}

void ZX81::resetKey(unsigned char c) {
  //
  if ( keyboardbuffer[0] != 0x0 ) {
    setKey(31 , 0, 0);
    /*for(int i = 0; i < 8; i++) {
      keyboard[i] = ~keyboard[i];
    }*/
    //Serial.printf("Key Up...\n");
  } 
  keyboardbuffer[0] = 0x0;
  keyboardbuffer[1] = 0x0;
  keyboardbuffer[2] = 0x0;
  
}
  
void ZX81::setKey(unsigned char key, unsigned char shift, unsigned char function) {
  int b, y;
  //if ( key_sync != 0 ) return;
  //putKeyboard(key);
  //return;
  keyboardbuffer[0] = key;
  for(y=0; y < 8; y++) {    /* 8 half-rows */
    b=0;  /* we set bits in b as appropriate */
    switch(y)  /* below comments given in order b1->b5 */
    {
    /* left-hand side */
    case 0: /* sft,z,x,c,v */
      if(key==31) b|=1;
      if(shift==1) b|=1;
      if(key==32) b|=2;
      if(key==33) b|=4;
      if(key==34) b|=8;
      if(key==35) b|=16;
      break;
    case 1: /* a,s,d,f,g */
      if(key==21) b|=1;
      if(key==22) b|=2;
      if(key==23) b|=4;
      if(key==24) b|=8;
      if(key==25) b|=16;
      break;
    case 2: /* q,w,e,r,t */
      if(key==11) b|=1;
      if(key==12) b|=2;
      if(key==13) b|=4;
      if(key==14) b|=8;
      if(key==15) b|=16;
      break;
    case 3: /* 1,2,3,4,5 */
      if(key==1) b|=1;
      if(key==2) b|=2;
      if(key==3) b|=4;
      if(key==4) b|=8;
      if(key==5) b|=16;
      break;

    /* right-hand side */
    case 4: /* 0,9,8,7,6 */
      if(key==10) b|=1;
      if(key==9) b|=2;
      if(key==8) b|=4;
      if(key==7) b|=8;
      if(key==6) b|=16;
      break;
    case 5: /* p,o,i,u,y */
      if(key==20) b|=1;
      if(key==19) b|=2;
      if(key==18) b|=4;
      if(key==17) b|=8;
      if(key==16) b|=16;
      break;
    case 6: /* ent,l,k,j,h */
      if(key==30) b|=1;
      if(key==29) b|=2;
      if(key==28) b|=4;
      if(key==27) b|=8;
      if(key==26) b|=16;
      break;
    case 7: /* spc,dot,m,n,b */
      if(key==40) b|=1;
      if(key==39) b|=2;
      if(key==38) b|=4;
      if(key==37) b|=8;
      if(key==36) b|=16;
      break;
    }
  keyboard[y]=((b^31)|0xe0);  /* some things need top bits to be 1 */
  //Serial.printf("Set Key : %02X : %02X\n", y, keyboard[y]);
  
  }
}

