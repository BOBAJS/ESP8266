/*********************************************************************************************

	z80.c

    z80 cpu emulation code

	2013/10/30  S.Suwa http://www.suwa-koubou.jp

	http://www.suwa-koubou.jp/micom/MZ80Emulator/mz80emu_en.html

*********************************************************************************************/
#include <ESP8266WiFi.h>

/*============================================================================================
                    z80 instruction functions
  ============================================================================================*/

void	fnc_0x00(void); void	fnc_0x01(void);	void	fnc_0x02(void); void	fnc_0x03(void);
void	fnc_0x04(void); void	fnc_0x05(void); void	fnc_0x06(void); void	fnc_0x07(void);
void	fnc_0x08(void); void	fnc_0x09(void);	void	fnc_0x0a(void); void	fnc_0x0b(void);
void	fnc_0x0c(void); void	fnc_0x0d(void); void	fnc_0x0e(void); void	fnc_0x0f(void);
void	fnc_0x10(void); void	fnc_0x11(void);	void	fnc_0x12(void); void	fnc_0x13(void);
void	fnc_0x14(void);	void	fnc_0x15(void); void	fnc_0x16(void); void	fnc_0x17(void);
void	fnc_0x18(void); void	fnc_0x19(void);	void	fnc_0x1a(void); void	fnc_0x1b(void);
void	fnc_0x1c(void); void	fnc_0x1d(void); void	fnc_0x1e(void); void	fnc_0x1f(void);
void	fnc_0x20(void); void	fnc_0x21(void);	void	fnc_0x22(void); void	fnc_0x23(void);
void	fnc_0x24(void); void	fnc_0x25(void); void	fnc_0x26(void); void	fnc_0x27(void);
void	fnc_0x28(void); void	fnc_0x29(void);	void	fnc_0x2a(void); void	fnc_0x2b(void);
void	fnc_0x2c(void); void	fnc_0x2d(void); void	fnc_0x2e(void); void	fnc_0x2f(void);
void	fnc_0x30(void); void	fnc_0x31(void);	void	fnc_0x32(void); void	fnc_0x33(void);
void	fnc_0x34(void); void	fnc_0x35(void); void	fnc_0x36(void); void	fnc_0x37(void);
void	fnc_0x38(void); void	fnc_0x39(void);	void	fnc_0x3a(void); void	fnc_0x3b(void);
void	fnc_0x3c(void); void	fnc_0x3d(void); void	fnc_0x3e(void); void	fnc_0x3f(void);
void	fnc_0x40(void);	void	fnc_0x41(void);	void	fnc_0x42(void);	void	fnc_0x43(void);
void	fnc_0x44(void);	void	fnc_0x45(void);	void	fnc_0x46(void);	void	fnc_0x47(void);
void	fnc_0x48(void);	void	fnc_0x49(void);	void	fnc_0x4a(void);	void	fnc_0x4b(void);
void	fnc_0x4c(void);	void	fnc_0x4d(void);	void	fnc_0x4e(void);	void	fnc_0x4f(void);
void	fnc_0x50(void);	void	fnc_0x51(void);	void	fnc_0x52(void);	void	fnc_0x53(void);
void	fnc_0x54(void);	void	fnc_0x55(void);	void	fnc_0x56(void);	void	fnc_0x57(void);
void	fnc_0x58(void);	void	fnc_0x59(void);	void	fnc_0x5a(void);	void	fnc_0x5b(void);
void	fnc_0x5c(void);	void	fnc_0x5d(void);	void	fnc_0x5e(void);	void	fnc_0x5f(void);
void	fnc_0x60(void);	void	fnc_0x61(void);	void	fnc_0x62(void);	void	fnc_0x63(void);
void	fnc_0x64(void);	void	fnc_0x65(void);	void	fnc_0x66(void);	void	fnc_0x67(void);
void	fnc_0x68(void);	void	fnc_0x69(void);	void	fnc_0x6a(void);	void	fnc_0x6b(void);
void	fnc_0x6c(void);	void	fnc_0x6d(void);	void	fnc_0x6e(void);	void	fnc_0x6f(void);
void	fnc_0x70(void);	void	fnc_0x71(void);	void	fnc_0x72(void);	void	fnc_0x73(void);
void	fnc_0x74(void);	void	fnc_0x75(void);	void	fnc_0x76(void);	void	fnc_0x77(void);
void	fnc_0x78(void);	void	fnc_0x79(void);	void	fnc_0x7a(void);	void	fnc_0x7b(void);
void	fnc_0x7c(void);	void	fnc_0x7d(void);	void	fnc_0x7e(void);	void	fnc_0x7f(void);
void	fnc_0x80(void);	void	fnc_0x81(void);	void	fnc_0x82(void);	void	fnc_0x83(void);
void	fnc_0x84(void);	void	fnc_0x85(void);	void	fnc_0x86(void);	void	fnc_0x87(void);
void	fnc_0x88(void);	void	fnc_0x89(void);	void	fnc_0x8a(void);	void	fnc_0x8b(void);
void	fnc_0x8c(void);	void	fnc_0x8d(void);	void	fnc_0x8e(void);	void	fnc_0x8f(void);
void	fnc_0x90(void);	void	fnc_0x91(void);	void	fnc_0x92(void);	void	fnc_0x93(void);
void	fnc_0x94(void);	void	fnc_0x95(void);	void	fnc_0x96(void);	void	fnc_0x97(void);
void	fnc_0x98(void);	void	fnc_0x99(void);	void	fnc_0x9a(void);	void	fnc_0x9b(void);
void	fnc_0x9c(void);	void	fnc_0x9d(void);	void	fnc_0x9e(void);	void	fnc_0x9f(void);
void	fnc_0xa0(void);	void	fnc_0xa1(void);	void	fnc_0xa2(void);	void	fnc_0xa3(void);
void	fnc_0xa4(void);	void	fnc_0xa5(void);	void	fnc_0xa6(void);	void	fnc_0xa7(void);
void	fnc_0xa8(void);	void	fnc_0xa9(void);	void	fnc_0xaa(void);	void	fnc_0xab(void);
void	fnc_0xac(void);	void	fnc_0xad(void);	void	fnc_0xae(void);	void	fnc_0xaf(void);
void	fnc_0xb0(void);	void	fnc_0xb1(void);	void	fnc_0xb2(void);	void	fnc_0xb3(void);
void	fnc_0xb4(void);	void	fnc_0xb5(void);	void	fnc_0xb6(void);	void	fnc_0xb7(void);
void	fnc_0xb8(void);	void	fnc_0xb9(void);	void	fnc_0xba(void);	void	fnc_0xbb(void);
void	fnc_0xbc(void);	void	fnc_0xbd(void);	void	fnc_0xbe(void);	void	fnc_0xbf(void);
void	fnc_0xc0(void);	void	fnc_0xc1(void);	void	fnc_0xc2(void);	void	fnc_0xc3(void);
void	fnc_0xc4(void);	void	fnc_0xc5(void);	void	fnc_0xc6(void);	void	fnc_0xc7(void);
void	fnc_0xc8(void);	void	fnc_0xc9(void);	void	fnc_0xca(void);	void	fnc_0xcb(void);
void	fnc_0xcc(void);	void	fnc_0xcd(void);	void	fnc_0xce(void);	void	fnc_0xcf(void);
void	fnc_0xd0(void);	void	fnc_0xd1(void);	void	fnc_0xd2(void);	void	fnc_0xd3(void);
void	fnc_0xd4(void);	void	fnc_0xd5(void);	void	fnc_0xd6(void);	void	fnc_0xd7(void);
void	fnc_0xd8(void);	void	fnc_0xd9(void);	void	fnc_0xda(void);	void	fnc_0xdb(void);
void	fnc_0xdc(void);	void	fnc_0xdd(void);	void	fnc_0xde(void);	void	fnc_0xdf(void);
void	fnc_0xe0(void);	void	fnc_0xe1(void);	void	fnc_0xe2(void);	void	fnc_0xe3(void);
void	fnc_0xe4(void);	void	fnc_0xe5(void);	void	fnc_0xe6(void);	void	fnc_0xe7(void);
void	fnc_0xe8(void);	void	fnc_0xe9(void);	void	fnc_0xea(void);	void	fnc_0xeb(void);
void	fnc_0xec(void);	void	fnc_0xed(void);	void	fnc_0xee(void);	void	fnc_0xef(void);
void	fnc_0xf0(void);	void	fnc_0xf1(void);	void	fnc_0xf2(void);	void	fnc_0xf3(void);
void	fnc_0xf4(void);	void	fnc_0xf5(void);	void	fnc_0xf6(void);	void	fnc_0xf7(void);
void	fnc_0xf8(void);	void	fnc_0xf9(void);	void	fnc_0xfa(void);	void	fnc_0xfb(void);
void	fnc_0xfc(void);	void	fnc_0xfd(void);	void	fnc_0xfe(void);	void	fnc_0xff(void);

// instruction code 0xedxx
void	fnc_0xed40(void); void	fnc_0xed41(void); void	fnc_0xed42(void); void	fnc_0xed43(void);
void	fnc_0xed44(void); void	fnc_0xed45(void); void	fnc_0xed46(void); void	fnc_0xed47(void);
void	fnc_0xed48(void); void	fnc_0xed49(void); void	fnc_0xed4a(void); void	fnc_0xed4b(void);
void	fnc_0xed4d(void); void	fnc_0xed4f(void); void	fnc_0xed50(void); void	fnc_0xed51(void);
void	fnc_0xed52(void); void	fnc_0xed53(void); void	fnc_0xed56(void); void	fnc_0xed57(void);
void	fnc_0xed58(void); void	fnc_0xed59(void); void	fnc_0xed5a(void); void	fnc_0xed5b(void);
void	fnc_0xed5e(void); void	fnc_0xed5f(void); void	fnc_0xed60(void); void	fnc_0xed61(void);
void	fnc_0xed62(void); void	fnc_0xed63(void); void	fnc_0xed67(void); void	fnc_0xed68(void);
void	fnc_0xed69(void); void	fnc_0xed6a(void); void	fnc_0xed6b(void); void	fnc_0xed6f(void);
void	fnc_0xed72(void); void	fnc_0xed73(void); void	fnc_0xed78(void); void	fnc_0xed79(void);
void	fnc_0xed7a(void); void	fnc_0xed7b(void); void	fnc_0xeda0(void); void	fnc_0xeda1(void);
void	fnc_0xeda2(void); void	fnc_0xeda3(void); void	fnc_0xeda8(void); void	fnc_0xeda9(void);
void	fnc_0xedaa(void); void	fnc_0xedab(void); void	fnc_0xedb0(void); void	fnc_0xedb1(void);
void	fnc_0xedb2(void); void	fnc_0xedb3(void); void	fnc_0xedb8(void); void	fnc_0xedb9(void);
void	fnc_0xedba(void); void	fnc_0xedbb(void); void	fnc_0xedfc(void); void	fnc_0xedfd(void);
void	fnc_0xedfe(void); void	fnc_0xedff(void); void  fnc_0xedXX(void);


/*============================================================================================
	global variable
  ============================================================================================*/

static void  (*z80ops[])(void) = {
  fnc_0x00, fnc_0x01, fnc_0x02, fnc_0x03, fnc_0x04, fnc_0x05, fnc_0x06, fnc_0x07,
  fnc_0x08, fnc_0x09, fnc_0x0a, fnc_0x0b, fnc_0x0c, fnc_0x0d, fnc_0x0e, fnc_0x0f,
  fnc_0x10, fnc_0x11, fnc_0x12, fnc_0x13, fnc_0x14, fnc_0x15, fnc_0x16, fnc_0x17,
  fnc_0x18, fnc_0x19, fnc_0x1a, fnc_0x1b, fnc_0x1c, fnc_0x1d, fnc_0x1e, fnc_0x1f,
  fnc_0x20, fnc_0x21, fnc_0x22, fnc_0x23, fnc_0x24, fnc_0x25, fnc_0x26, fnc_0x27,
  fnc_0x28, fnc_0x29, fnc_0x2a, fnc_0x2b, fnc_0x2c, fnc_0x2d, fnc_0x2e, fnc_0x2f,
  fnc_0x30, fnc_0x31, fnc_0x32, fnc_0x33, fnc_0x34, fnc_0x35, fnc_0x36, fnc_0x37,
  fnc_0x38, fnc_0x39, fnc_0x3a, fnc_0x3b, fnc_0x3c, fnc_0x3d, fnc_0x3e, fnc_0x3f,
  fnc_0x40, fnc_0x41, fnc_0x42, fnc_0x43, fnc_0x44, fnc_0x45, fnc_0x46, fnc_0x47,
  fnc_0x48, fnc_0x49, fnc_0x4a, fnc_0x4b, fnc_0x4c, fnc_0x4d, fnc_0x4e, fnc_0x4f,
  fnc_0x50, fnc_0x51, fnc_0x52, fnc_0x53, fnc_0x54, fnc_0x55, fnc_0x56, fnc_0x57,
  fnc_0x58, fnc_0x59, fnc_0x5a, fnc_0x5b, fnc_0x5c, fnc_0x5d, fnc_0x5e, fnc_0x5f,
  fnc_0x60, fnc_0x61, fnc_0x62, fnc_0x63, fnc_0x64, fnc_0x65, fnc_0x66, fnc_0x67,
  fnc_0x68, fnc_0x69, fnc_0x6a, fnc_0x6b, fnc_0x6c, fnc_0x6d, fnc_0x6e, fnc_0x6f,
  fnc_0x70, fnc_0x71, fnc_0x72, fnc_0x73, fnc_0x74, fnc_0x75, fnc_0x76, fnc_0x77,
  fnc_0x78, fnc_0x79, fnc_0x7a, fnc_0x7b, fnc_0x7c, fnc_0x7d, fnc_0x7e, fnc_0x7f,
  fnc_0x80, fnc_0x81, fnc_0x82, fnc_0x83, fnc_0x84, fnc_0x85, fnc_0x86, fnc_0x87,
  fnc_0x88, fnc_0x89, fnc_0x8a, fnc_0x8b, fnc_0x8c, fnc_0x8d, fnc_0x8e, fnc_0x8f,
  fnc_0x90, fnc_0x91, fnc_0x92, fnc_0x93, fnc_0x94, fnc_0x95, fnc_0x96, fnc_0x97,
  fnc_0x98, fnc_0x99, fnc_0x9a, fnc_0x9b, fnc_0x9c, fnc_0x9d, fnc_0x9e, fnc_0x9f,
  fnc_0xa0, fnc_0xa1, fnc_0xa2, fnc_0xa3, fnc_0xa4, fnc_0xa5, fnc_0xa6, fnc_0xa7,
  fnc_0xa8, fnc_0xa9, fnc_0xaa, fnc_0xab, fnc_0xac, fnc_0xad, fnc_0xae, fnc_0xaf,
  fnc_0xb0, fnc_0xb1, fnc_0xb2, fnc_0xb3, fnc_0xb4, fnc_0xb5, fnc_0xb6, fnc_0xb7,
  fnc_0xb8, fnc_0xb9, fnc_0xba, fnc_0xbb, fnc_0xbc, fnc_0xbd, fnc_0xbe, fnc_0xbf,
  fnc_0xc0, fnc_0xc1, fnc_0xc2, fnc_0xc3, fnc_0xc4, fnc_0xc5, fnc_0xc6, fnc_0xc7,
  fnc_0xc8, fnc_0xc9, fnc_0xca, fnc_0xcb, fnc_0xcc, fnc_0xcd, fnc_0xce, fnc_0xcf,
  fnc_0xd0, fnc_0xd1, fnc_0xd2, fnc_0xd3, fnc_0xd4, fnc_0xd5, fnc_0xd6, fnc_0xd7,
  fnc_0xd8, fnc_0xd9, fnc_0xda, fnc_0xdb, fnc_0xdc, fnc_0xdd, fnc_0xde, fnc_0xdf,
  fnc_0xe0, fnc_0xe1, fnc_0xe2, fnc_0xe3, fnc_0xe4, fnc_0xe5, fnc_0xe6, fnc_0xe7,
  fnc_0xe8, fnc_0xe9, fnc_0xea, fnc_0xeb, fnc_0xec, fnc_0xed, fnc_0xee, fnc_0xef,
  fnc_0xf0, fnc_0xf1, fnc_0xf2, fnc_0xf3, fnc_0xf4, fnc_0xf5, fnc_0xf6, fnc_0xf7,
  fnc_0xf8, fnc_0xf9, fnc_0xfa, fnc_0xfb, fnc_0xfc, fnc_0xfd, fnc_0xfe, fnc_0xff,
};

static void (*z80edops[])(void) = {
  fnc_0xed40, fnc_0xed41, fnc_0xed42, fnc_0xed43, fnc_0xed44, fnc_0xed45, fnc_0xed46, fnc_0xed47, // 0x40
  fnc_0xed48, fnc_0xed49, fnc_0xed4a, fnc_0xed4b, fnc_0xedXX, fnc_0xedXX, fnc_0xed4d, fnc_0xed4f,
  fnc_0xed50, fnc_0xed51, fnc_0xed52, fnc_0xed53, fnc_0xedXX, fnc_0xedXX, fnc_0xed56, fnc_0xed57, // 0x50
  fnc_0xed58, fnc_0xed59, fnc_0xed5a, fnc_0xed5b, fnc_0xedXX, fnc_0xedXX, fnc_0xed5e, fnc_0xed5f,
  fnc_0xed60, fnc_0xed61, fnc_0xed62, fnc_0xed63, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xed67, // 0x60
  fnc_0xed68, fnc_0xed69, fnc_0xed6a, fnc_0xed6b, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xed6f,
  fnc_0xedXX, fnc_0xedXX, fnc_0xed72, fnc_0xed73, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, // 0x70
  fnc_0xed78, fnc_0xed79, fnc_0xed7a, fnc_0xed7b, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX,
  fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, // 0x80
  fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX,
  fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, // 0x90
  fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX,
  fnc_0xeda0, fnc_0xeda1, fnc_0xeda2, fnc_0xeda3, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, // 0xa0
  fnc_0xeda8, fnc_0xeda9, fnc_0xedaa, fnc_0xedab, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX,
  fnc_0xedb0, fnc_0xedb1, fnc_0xedb2, fnc_0xedb3, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, // 0xb0
  fnc_0xedb8, fnc_0xedb9, fnc_0xedba, fnc_0xedbb, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX, fnc_0xedXX,
};

static void (*z80rstops[])(void) = {
  fnc_0xc7, fnc_0xcf,  // RST 0/RST 8
  fnc_0xd7, fnc_0xdf,  // RST 10/RST 18
  fnc_0xe7, fnc_0xef,  // RST 20/RST 28
  fnc_0xf7, fnc_0xff,  // RST 30/RST 38
};

static const unsigned char paritytable[256] = {
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
  4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4
};


extern unsigned char fetch(unsigned short adr);
extern void        store(unsigned short adr, unsigned char  val);
extern void        store2b(unsigned short adr, unsigned char  vh, unsigned char  vl);
extern unsigned char in(unsigned char dummy, unsigned short adr);
extern unsigned int  out(unsigned char dummy, unsigned char adr, unsigned char val);

int cpu_reset;	// was reseted by functionkey11
int cpu_int;    // normal interrupt appear by functionkey1 - 1
int cpu_intn;   // interrupt RST instruction number 0-7
int cpu_nmi;    // none maskable interrupt appera by keybord functionkey12

static unsigned char   a, f, b, c, d, e, h, l;
static unsigned char   r, a1, f1, b1, c1, d1, e1, h1, l1, i, iff1, iff2, im;
static unsigned short  pc;
static unsigned short  ix, iy, sp;
static unsigned int    radjust;
static unsigned char   ixoriy, new_ixoriy;
static unsigned char   op;
static unsigned int    in_halt;
static unsigned short  tstates;

#define	bc	((b<<8)|c)
#define	de	((d<<8)|e)
#define	hl	((h<<8)|l)
#define	fetch2(x)	((fetch((x)+1)<<8)|fetch(x))
#define	store2(x,y)	store2b(x,(y)>>8,(y)&255)
#define	parity(a)	(paritytable[a])


/*============================================================================================
	cpu reset function
  ============================================================================================*/

void z80reset(void) {
  a = f = b = c = d = e = h = l = a1 = f1 = b1 = c1 = d1 = e1 = h1 = l1 = i = r = iff1 = iff2 = im = 0;
  ix = iy = sp = pc = 0;
  tstates = radjust = 0;
  cpu_reset = cpu_nmi = cpu_int = 0;
  ixoriy = new_ixoriy = 0;
  in_halt = 0;

  // Z80 2.5MHz CPU clock
  //TMR5 = 0;
  //PR5 = 0xffff;
  //T5CON = 0x8050;
}


void debug() {
  
  Serial.println("");
  Serial.println("CPU :");
  
  Serial.printf (" PC : %04X  SP : %04X\n", pc, sp);
  Serial.printf (" AF : %02X%02X  BC : %02X%02X\n", a, f, b, c);
  Serial.printf (" DE : %02X%02X  HL : %02X%02X\n", d, e, h, l);
  Serial.printf ("'AF : %02X%02X 'BC : %02X%02X\n", a1, f1, b1, c1);
  Serial.printf ("'DE : %02X%02X 'HL : %02X%02X\n", d1, e1, h1, l1);
  Serial.printf (" IX : %04X  IY : %04X\n", ix, iy);

}

/*============================================================================================
	z80 cpu instruction emulate loop
  ============================================================================================*/

void execZ80(void) {

  //debug();
  //unsigned short start;

  //while(1){
  //start = TMR5;

  // NMI appear
  //  call 0x0066
  if (cpu_nmi) {
    tstates = 15;
    cpu_nmi = 0;
    iff2 = iff1;
    iff1 = 0; // set DI
    sp -= 2;
    store2(sp, (pc + 2));
    pc = 0x0066;
    return;
  }

  // INT appear, if EI?
  if (cpu_int) {
    cpu_int = 0;
    if (iff1) {
      switch (im) {
        case 0:  // mode 0, execute RST 00-38
          (*z80rstops[cpu_intn])();
          break;
        case 2:  // mode 1, execute RST 38H
          fnc_0xff();
          break;
        case 3:  // mode 2
          tstates = 11;
          sp -= 2;
          store2(sp, (pc + 2));
          pc = (i << 8) + cpu_intn; // ?????
          break;
      } // switch
    } // if
    return;
  }

  
    // was reseted
    if(cpu_reset){
    	Serial.println("Z80: Reset");
    }
  

  // in halt ?
  if (in_halt)	return;

  // fetch and execute next instruction
  tstates = 0;
  op = fetch(pc); pc++;
  (*z80ops[op])();
  // ixoriy: =0 HL, =1 IX, =2 IY
  ixoriy = new_ixoriy;
  new_ixoriy = 0;

  // wait instruction cycle
  //while(TMR5 - start < tstates);
  //}
}


/*============================================================================================
	cpu instruction operation code
  ============================================================================================*/

void	fnc_0x00(void)
{
  // NOP
  tstates += 4;
}

void	fnc_0x01(void)
{
  // LD  BC,nn
  tstates += 10;
  c = fetch(pc), pc++;
  b = fetch(pc), pc++;
}

void	fnc_0x02(void)
{
  // LD (BC),A
  tstates += 7;
  store(bc, a);
}

void	fnc_0x03(void)
{
  // INC BC
  tstates += 6;
  if (!++c)b++;
}

void	fnc_0x04(void)
{
  // INC  B
  tstates += 4;
  b++;
  f = (f & 1) | (b & 0xa8) | ((!(b & 15)) << 4) | ((!b) << 6) | ((b == 128) << 2);
}

void	fnc_0x05(void)
{
  // DEC B
  tstates += 4;
  f = (f & 1) | ((!(b & 15)) << 4) | 2;
  --b;
  f |= (b & 0xa8) | ((b == 127) << 2) | ((!b) << 6);
}

void	fnc_0x06(void)
{
  // LD  B,n
  tstates += 7;
  b = fetch(pc);
  pc++;
}

void	fnc_0x07(void)
{
  // RLCA
  tstates += 4;
  a = (a << 1) | (a >> 7);
  f = (f & 0xc4) | (a & 0x29);
}

void	fnc_0x08(void)
{
  // EX  AF,AF'
  unsigned char t;
  tstates += 4;
  t = a; a = a1; a1 = t;
  t = f; f = f1; f1 = t;
}

void	fnc_0x09(void)
{
  // ADD  HL,BC
  // ADD  IX,BC (0xdd09)
  // ADD  IY,BC (0xfd09)
  tstates += 11;
  if (!ixoriy) {
    unsigned short t;
    l = t = l + (c);
    f = (f & 0xc4) | (((t >>= 8) + (h & 0x0f) + ((b) & 0x0f) > 15) << 4);
    h = t += h + (b);
    f |= (h & 0x28) | (t >> 8);
  } else {
    unsigned long t;
    t = (ixoriy == 1 ? ix : iy);
    f = (f & 0xc4) | (((t & 0xfff) + ((b << 8) | c) > 0xfff) << 4);
    t += (b << 8) | c;
    if (ixoriy == 1)ix = t; else iy = t;
    f |= ((t >> 8) & 0x28) | (t >> 16);
  }
}

void	fnc_0x0a(void)
{
  // LD  A,(BC)
  tstates += 7;
  a = fetch(bc);
}

void	fnc_0x0b(void)
{
  // DEC  BC
  tstates += 6;
  if (!c--)b--;
}

void	fnc_0x0c(void)
{
  // INC  C
  tstates += 4;
  c++;
  f = (f & 1) | (c & 0xa8) | ((!(c & 15)) << 4) | ((!c) << 6) | ((c == 128) << 2);
}

void	fnc_0x0d(void)
{
  // DEC  C
  tstates += 4;
  f = (f & 1) | ((!(c & 15)) << 4) | 2;
  --c;
  f |= (c & 0xa8) | ((c == 127) << 2) | ((!c) << 6);
}

void	fnc_0x0e(void)
{
  // LD  C,n
  tstates += 4;
  c = fetch(pc);
  pc++;
}

void	fnc_0x0f(void)
{
  // RRCA
  tstates += 4;
  f = (f & 0xc4) | (a & 1);
  a = (a >> 1) | (a << 7);
  f |= a & 0x28;
}

void	fnc_0x10(void)
{
  // DJNZ  (PC+e)
  tstates += 8;
  if (!--b) {
    pc++;
  } else {
    int j;
    j = (signed char)fetch(pc);
    pc += j + 1;
    tstates += 5;
  }
}

void	fnc_0x11(void)
{
  // LD  DE,nn
  tstates += 10;
  e = fetch(pc); pc++;
  d = fetch(pc); pc++;
}

void	fnc_0x12(void)
{
  // LD  (DE),A
  tstates += 7;
  store(de, a);
}

void	fnc_0x13(void)
{
  // INC  DE
  tstates += 6;
  if (!++e)d++;
}

void	fnc_0x14(void)
{
  // INC  D
  tstates += 4;
  d++;
  f = (f & 1) | (d & 0xa8) | ((!(d & 15)) << 4) | ((!d) << 6) | ((d == 128) << 2);
}

void	fnc_0x15(void)
{
  // DEC  D
  tstates += 4;
  f = (f & 1) | ((!(d & 15)) << 4) | 2;
  --d;
  f |= (d & 0xa8) | ((d == 127) << 2) | ((!d) << 6);
}

void	fnc_0x16(void)
{
  // LD  D,n
  tstates += 7;
  d = fetch(pc); pc++;
}

void	fnc_0x17(void)
{
  // RLA
  int	t;
  tstates += 4;
  t = a >> 7;
  a = (a << 1) | (f & 1);
  f = (f & 0xc4) | (a & 0x28) | t;
}

void	fnc_0x18(void)
{
  // JR  (PC+e)
  int	j;
  tstates += 7;
  j = (signed char)fetch(pc);
  pc += j + 1;
  tstates += 5;
}

void	fnc_0x19(void)
{
  // ADD  HL,DE
  // ADD  IX,DE (0xdd19)
  // ADD  IY,DE (0xfd19)
  tstates += 11;
  if (!ixoriy) {
    unsigned short t;
    l = t = l + e;
    f = (f & 0xc4) | (((t >>= 8) + (h & 0x0f) + ((d) & 0x0f) > 15) << 4);
    h = t += h + (d);
    f |= (h & 0x28) | (t >> 8);
  } else {
    unsigned long t = (ixoriy == 1 ? ix : iy);
    f = (f & 0xc4) | (((t & 0xfff) + ((d << 8) | e) > 0xfff) << 4);
    t += (d << 8) | e;
    if (ixoriy == 1)ix = t; else iy = t;
    f |= ((t >> 8) & 0x28) | (t >> 16);
  }
}

void	fnc_0x1a(void)
{
  // LD  A,(DE)
  tstates += 7;
  a = fetch(de);
}

void	fnc_0x1b(void)
{
  // DEC  DE
  tstates += 6;
  if (!e--)d--;
}

void	fnc_0x1c(void)
{
  // INC  E
  tstates += 4;
  e++;
  f = (f & 1) | (e & 0xa8) | ((!(e & 15)) << 4) | ((!e) << 6) | ((e == 128) << 2);
}

void	fnc_0x1d(void)
{
  // DEC  E
  tstates += 4;
  f = (f & 1) | ((!(e & 15)) << 4) | 2;
  --e;
  f |= (e & 0xa8) | ((e == 127) << 2) | ((!e) << 6);
}

void	fnc_0x1e(void)
{
  // LD  E,nn
  tstates += 4;
  e = fetch(pc), pc++;
}

void	fnc_0x1f(void)
{
  // RRA
  int	t;
  tstates += 4;
  t = a & 1;
  a = (a >> 1) | (f << 7);
  f = (f & 0xc4) | (a & 0x28) | t;
}

void	fnc_0x20(void)
{
  // JR  NZ,(PC+e)
  tstates += 7;
  if (f & 0x40) {
    pc++;
  } else {
    int j = (signed char)fetch(pc);
    pc += j + 1;
    tstates += 5;
  }
}

void	fnc_0x21(void)
{
  // LD  HL,nn
  // LD  IX,nn (0xdd21)
  // LD  IY,nn (0xfd21)
  tstates += 10;
  if (!ixoriy) {
    l = fetch(pc), pc++;
    h = fetch(pc), pc++;
  } else {
    if (ixoriy == 1) {
      ix = fetch2(pc);
    } else {
      iy = fetch2(pc);
    }
    pc += 2;
  }
}

void	fnc_0x22(void)
{
  // LD  (nn),HL
  // LD  (nn),IX (0xdd22)
  // LD  (nn),IY (0xfd22)
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  if (!ixoriy) {
    store2b(addr, h, l);
  } else if (ixoriy == 1) {
    store2(addr, ix);
  } else {
    store2(addr, iy);
  }
}

void	fnc_0x23(void)
{
  // INC  HL
  // INC  IX (0xdd23)
  // INC  IY (0xfd23)
  tstates += 6;
  if (!ixoriy) {
    if (!++l)h++;
  } else if (ixoriy == 1) {
    ix++;
  } else {
    iy++;
  }
}

void	fnc_0x24(void)
{
  // INC  H
  tstates += 4;
  h++;
  f = (f & 1) | (h & 0xa8) | ((!(h & 15)) << 4) | ((!h) << 6) | ((h == 128) << 2);
}

void	fnc_0x25(void)
{
  // DEC  H
  tstates += 4;
  f = (f & 1) | ((!(h & 15)) << 4) | 2;
  --h;
  f |= (h & 0xa8) | ((h == 127) << 2) | ((!h) << 6);
}

void	fnc_0x26(void)
{
  // LD  H,n
  tstates += 7;
  h = fetch(pc);
  pc++;
}

void	fnc_0x27(void)
{
  // DAA
  unsigned char incr, carry;
  unsigned short y;
  unsigned char z;
  tstates += 4;
  incr = 0, carry = (f & 1);
  if ((f & 0x10) || (a & 0x0f) > 9)incr = 6;
  if ((f & 1) || (a >> 4) > 9)incr |= 0x60;
  if (f & 2) {
    z = (incr);
    y = (a - z - (0)) & 0x1ff;
    f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
    f |= (!(a = y)) << 6;
  } else {
    if (a > 0x90 && (a & 15) > 9)incr |= 0x60;
    z = (incr);
    y = a + z + (0);
    f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
    f |= (!(a = y)) << 6;
  }
  f = ((f | carry) & 0xfb) | parity(a);
}

void	fnc_0x28(void)
{
  // JR  Z,(PC+e)
  tstates += 7;
  if (f & 0x40) {
    int j = (signed char)fetch(pc);
    pc += j + 1;
    tstates += 5;
  } else {
    pc++;
  }
}

void	fnc_0x29(void)
{
  // ADD  HL,HL
  // ADD  IX,IX (0xdd29)
  // ADD  IY,IY (0xfd29)
  tstates += 11;
  if (!ixoriy) {
    unsigned short t;
    l = t = l + (l);
    f = (f & 0xc4) | (((t >>= 8) + (h & 0x0f) + ((h) & 0x0f) > 15) << 4);
    h = t += h + (h);
    f |= (h & 0x28) | (t >> 8);
  } else if (ixoriy == 1) {
    unsigned long t = ix;
    f = (f & 0xc4) | (((t & 0xfff) + (((ix >> 8) << 8) | (ix & 0xff)) > 0xfff) << 4);
    t += ((ix >> 8) << 8) | (ix & 0xff);
    ix = t;
    f |= ((t >> 8) & 0x28) | (t >> 16);
  } else {
    unsigned long t = iy;
    f = (f & 0xc4) | (((t & 0xfff) + (((iy >> 8) << 8) | (iy & 0xff)) > 0xfff) << 4);
    t += ((iy >> 8) << 8) | (iy & 0xff);
    iy = t;
    f |= ((t >> 8) & 0x28) | (t >> 16);
  }
}

void	fnc_0x2a(void)
{
  // LD  HL,(nn)
  // LD  IX,(nn)	(0xdd2a)
  // LD  IY,(nn)  (0xfd2a)
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  if (!ixoriy) {
    l = fetch(addr);
    h = fetch(addr + 1);
  } else if (ixoriy == 1) {
    ix = fetch2(addr);
  } else {
    iy = fetch2(addr);
  }
}

void	fnc_0x2b(void)
{
  // DEC  HL
  // DEC  IX  (0xdd2b)
  // DEC  IY  (0xfd2b)
  tstates += 6;
  if (!ixoriy) {
    if (!l--)h--;
  } else if (ixoriy == 1) {
    ix--;
  } else {
    iy--;
  }
}

void	fnc_0x2c(void)
{
  // INC  L
  unsigned char t;
  tstates += 4;
  l++;
  f = (f & 1) | (l & 0xa8) | ((!(l & 15)) << 4) | ((!l) << 6) | ((l == 128) << 2);
}

void	fnc_0x2d(void)
{
  // DEC  L
  unsigned char t;
  tstates += 4;
  f = (f & 1) | ((!(l & 15)) << 4) | 2;
  --l;
  f |= (l & 0xa8) | ((l == 127) << 2) | ((!l) << 6);
}

void	fnc_0x2e(void)
{
  // LD  L,n
  tstates += 4;
  l = fetch(pc);
  pc++;
}

void	fnc_0x2f(void)
{
  // CPL
  tstates += 4;
  a = ~a;
  f = (f & 0xc5) | (a & 0x28) | 0x12;
}

void	fnc_0x30(void)
{
  // JR  NC,(PC+e)
  tstates += 7;
  if (f & 1) {
    pc++;
  } else {
    int j = (signed char)fetch(pc);
    pc += j + 1;
    tstates += 5;
  }
}

void	fnc_0x31(void)
{
  // LD  SP,nn
  tstates += 10;
  sp = fetch2(pc);
  pc += 2;
}

void	fnc_0x32(void)
{
  // LD  (nn),A
  unsigned short addr;
  tstates += 13;
  addr = fetch2(pc);
  pc += 2;
  store(addr, a);
}

void	fnc_0x33(void)
{
  // INC  SP
  tstates += 6;
  sp++;
}

void	fnc_0x34(void)
{
  // INC  (HL)
  // INC  (IX+e)  (0xdd34)
  // INC  (IY+e)  (0xfd34)
  unsigned short addr;
  unsigned char t;
  tstates += 11;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  t = fetch(addr);
  t++;
  f = (f & 1) | (t & 0xa8) | ((!(t & 15)) << 4) | ((!t) << 6) | ((t == 128) << 2);
  store(addr, t);
}

void	fnc_0x35(void)
{
  // DEC  (HL)
  // DEC  (IX+e) (0xdd35)
  // DEC  (IY+e) (0xfd35)
  unsigned short addr;
  unsigned char t;
  tstates += 11;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  t = fetch(addr);
  f = (f & 1) | ((!(t & 15)) << 4) | 2;
  --t;
  f |= (t & 0xa8) | ((t == 127) << 2) | ((!t) << 6);
  store(addr, t);
}

void	fnc_0x36(void)
{
  // LD  (HL),n
  // LD  (IX+e),n (0xdd36)
  // LD  (IY+e),n (0xfd36)
  unsigned short addr;
  tstates += 10;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 5;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, fetch(pc));
  pc++;
}

void	fnc_0x37(void)
{
  // SCF
  tstates += 4;
  f = (f & 0xc4) | 1 | (a & 0x28);
}

void	fnc_0x38(void)
{
  // JR  C,(PC+e)
  tstates += 7;
  if (f & 1) {
    int j = (signed char)fetch(pc);
    pc += j + 1;
    tstates += 5;
  } else {
    pc++;
  }
}

void	fnc_0x39(void)
{
  // ADD  HL,SP
  // ADD  IX,SP  (0xdd39)
  // ADD  IY,SP  (0xfd39)
  tstates += 11;
  if (!ixoriy) {
    unsigned short t;
    l = t = l + ((sp & 0xff));
    f = (f & 0xc4) | (((t >>= 8) + (h & 0x0f) + (((sp >> 8)) & 0x0f) > 15) << 4);
    h = t += h + ((sp >> 8));
    f |= (h & 0x28) | (t >> 8);
  } else {
    unsigned long t = (ixoriy == 1 ? ix : iy);
    f = (f & 0xc4) | (((t & 0xfff) + (((sp >> 8) << 8) | (sp & 0xff)) > 0xfff) << 4);
    t += ((sp >> 8) << 8) | (sp & 0xff);
    if (ixoriy == 1) {
      ix = t;
    } else {
      iy = t;
    }
    f |= ((t >> 8) & 0x28) | (t >> 16);
  }
}

void	fnc_0x3a(void)
{
  // LD  A,(nn)
  unsigned short addr;
  tstates += 13;
  addr = fetch2(pc);
  pc += 2;
  a = fetch(addr);
}

void	fnc_0x3b(void)
{
  // DEC  SP
  tstates += 6;
  sp--;
}

void	fnc_0x3c(void)
{
  // INC  A
  tstates += 4;
  a++;
  f = (f & 1) | (a & 0xa8) | ((!(a & 15)) << 4) | ((!a) << 6) | ((a == 128) << 2);
}

void	fnc_0x3d(void)
{
  // DEC  A
  tstates += 4;
  f = (f & 1) | ((!(a & 15)) << 4) | 2, --a, f |= (a & 0xa8) | ((a == 127) << 2) | ((!a) << 6);
}

void	fnc_0x3e(void)
{
  // LD  A,n
  tstates += 4;
  a = fetch(pc); pc++;
}

void	fnc_0x3f(void)
{
  // CCF
  tstates += 4;
  f = (f & 0xc4) | ((f & 1) ^ 1) | ((f & 1) << 4) | (a & 0x28);
}

void	fnc_0x40(void)
{
  // LD  B,B
  tstates += 4;
}

void	fnc_0x41(void)
{
  // LD  B,C
  tstates += 4;
  b = c;
}

void	fnc_0x42(void)
{
  // LD  B,D
  tstates += 4;
  b = d;
}

void	fnc_0x43(void)
{
  // LD  B,E
  tstates += 4;
  b = e;
}

void	fnc_0x44(void)
{
  // LD  B,H
  tstates += 4;
  b = h;
}

void	fnc_0x45(void)
{
  // LD  B,L
  tstates += 4;
  b = l;
}

void	fnc_0x46(void)
{
  // LD  B,(HL)
  // LD  B,(IX+e) (0xdd46)
  // LD  B,(IY+e) (0xfd46)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  b = fetch(addr);
}

void	fnc_0x47(void)
{
  // LD  B,A
  tstates += 4;
  b = a;
}

void	fnc_0x48(void)
{
  // LD  C,B
  tstates += 4;
  c = b;
}

void	fnc_0x49(void)
{
  // LD  C,C
  tstates += 4;
}

void	fnc_0x4a(void)
{
  // LD  C,D
  tstates += 4;
  c = d;
}

void	fnc_0x4b(void)
{
  // LD  C,E
  tstates += 4;
  c = e;
}

void	fnc_0x4c(void)
{
  // LD  C,H
  tstates += 4;
  c = h;
}

void	fnc_0x4d(void)
{
  // LD  C,L
  tstates += 4;
  c = l;
}

void	fnc_0x4e(void)
{
  // LD  C,(HL)
  // LD  C,(IX+e) (0xdd4e)
  // LD  C,(IY+e) (0xfd4e)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  c = fetch(addr);
}

void	fnc_0x4f(void)
{
  // LD  C,A
  tstates += 4;
  c = a;
}

void	fnc_0x50(void)
{
  // LD  D,B
  tstates += 4;
  d = b;
}

void	fnc_0x51(void)
{
  // LD  D,C
  tstates += 4;
  d = c;
}

void	fnc_0x52(void)
{
  // LD  D,D
  tstates += 4;
}

void	fnc_0x53(void)
{
  // LD  D,E
  tstates += 4;
  d = e;
}

void	fnc_0x54(void)
{
  // LD  D,H
  tstates += 4;
  d = h;
}

void	fnc_0x55(void)
{
  // LD  D,L
  tstates += 4;
  d = l;
}

void	fnc_0x56(void)
{
  // LD  D,(HL)
  // LD  D,(IX+e) (0xdd56)
  // LD  D,(IY+e) (0xfd56)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  d = fetch(addr);
}

void	fnc_0x57(void)
{
  // LD  D,A
  tstates += 4;
  d = a;
}

void	fnc_0x58(void)
{
  // LD  E,B
  tstates += 4;
  e = b;
}

void	fnc_0x59(void)
{
  // LD  E,C
  tstates += 4;
  e = c;
}

void	fnc_0x5a(void)
{
  // LD  E,D
  tstates += 4;
  e = d;
}

void	fnc_0x5b(void)
{
  // LD  E,E
  tstates += 4;
}

void	fnc_0x5c(void)
{
  // LD  E,H
  tstates += 4;
  e = h;
}

void	fnc_0x5d(void)
{
  // LD  E,L
  tstates += 4;
  e = l;
}

void	fnc_0x5e(void)
{
  // LD  E,(HL)
  // LD  E,(IX+e) (0xdd5e)
  // LD  E,(IY+e) (0xfd5e)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  e = fetch(addr);
}

void	fnc_0x5f(void)
{
  // LD  E,A
  tstates += 4;
  e = a;
}

void	fnc_0x60(void)
{
  // LD  H,B
  tstates += 4;
  h = b;
}

void	fnc_0x61(void)
{
  // LD  H,C
  tstates += 4;
  h = c;
}

void	fnc_0x62(void)
{
  // LD  H,D
  tstates += 4;
  h = d;
}

void	fnc_0x63(void)
{
  // LD  H,E
  tstates += 4;
  h = e;
}

void	fnc_0x64(void)
{
  // LD  H,H
  tstates += 4;
}

void	fnc_0x65(void)
{
  // LD  H,L
  tstates += 4;
  h = l;
}

void	fnc_0x66(void)
{
  //�@LD  H,(HL)
  // LD  H,(IX+e)  (0xdd66)
  // LD  H,(IY+e)  (0xfd66)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  h = fetch(addr);
}

void	fnc_0x67(void)
{
  // LD  H,A
  tstates += 4;
  h = a;
}

void	fnc_0x68(void)
{
  // LD  L,B
  tstates += 4;
  l = b;
}

void	fnc_0x69(void)
{
  // LD  L,C
  tstates += 4;
  l = c;
}

void	fnc_0x6a(void)
{
  // LD  L,D
  tstates += 4;
  l = d;
}

void	fnc_0x6b(void)
{
  // LD  L,E
  tstates += 4;
  l = e;
}

void	fnc_0x6c(void)
{
  // LD  L,H
  tstates += 4;
  l = h;
}

void	fnc_0x6d(void)
{
  // LD  L,L
  tstates += 4;
}

void	fnc_0x6e(void)
{
  // LD  L,(HL)
  // LD  L,(IX+e) (0xdd6e)
  // LD  L,(IY+e) (0xfd6e)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  l = fetch(addr);
}

void	fnc_0x6f(void)
{
  // LD  L,A
  tstates += 4;
  l = a;
}

void	fnc_0x70(void)
{
  // LD  (HL),B
  // LD  (IX+e),B  (0xdd70)
  // LD  (IY+e),B  (0xfd70)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, b);
}

void	fnc_0x71(void)
{
  // LD  (HL),C
  // LD  (IX+e),C  (0xdd71)
  // LD  (IY+e),C  (0xfd71)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, c);
}

void	fnc_0x72(void)
{
  // LD  (HL),D
  // LD  (IX+e),D  (0xdd72)
  // LD  (IY+e),D  (0xfd72)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, d);
}

void	fnc_0x73(void)
{
  // LD  (HL),E
  // LD  (IX+e),E  (0xdd73)
  // LD  (IY+e),E  (0xfd73)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, e);
}

void	fnc_0x74(void)
{
  // LD  (HL),H
  // LD  (IX+e),H  (0xdd74)
  // LD  (IY+e),H  (0xfd74)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, h);
}

void	fnc_0x75(void)
{
  // LD  (HL),L
  // LD  (IX+e),L  (0xdd75)
  // LD  (IY+e),L  (0xfd75)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, l);
}

void	fnc_0x76(void)	/* HALT */
{
  tstates += 4;
  in_halt = 1;
}

void	fnc_0x77(void)
{
  // LD  (HL),A
  // LD  (IX+e),A  (0xdd77)
  // LD  (IY+e),A  (0xfd77)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  store(addr, a);
}

void	fnc_0x78(void)
{
  // LD  A,B
  tstates += 4;
  a = b;
}

void	fnc_0x79(void)
{
  // LD  A,C
  tstates += 4;
  a = c;
}

void	fnc_0x7a(void)
{
  // LD  A,D
  tstates += 4;
  a = d;
}

void	fnc_0x7b(void)
{
  // LD  A,E
  tstates += 4;
  a = e;
}

void	fnc_0x7c(void)
{
  // LD  A,H
  tstates += 4;
  a = h;
}

void	fnc_0x7d(void)
{
  // LD  A,L
  tstates += 4;
  a = l;
}

void	fnc_0x7e(void)
{
  // LD  A,(HL)
  // LD  A,(IX+e)   (0xdd7e)
  // LD  A,(IY+e)   (0xfd7e)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  a = fetch(addr);
}

void	fnc_0x7f(void)
{
  // LD  A,A
  tstates += 4;
}

void	fnc_0x80(void)
{
  // ADD  A,B
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = b;
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x81(void)
{
  // ADD  A,C
  tstates += 4;
  unsigned short y;
  unsigned char z;
  z = c;
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x82(void)
{
  // ADD  A,D
  tstates += 4;
  unsigned short y;
  unsigned char z;
  z = d;
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x83(void)
{
  // ADD  A,E
  tstates += 4;
  unsigned short y;
  unsigned char z;
  z = e;
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x84(void)
{
  // ADD  A,H
  tstates += 4;
  unsigned short y;
  unsigned char z;
  z = h;
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x85(void)
{
  // ADD  A,L
  tstates += 4;
  unsigned short y;
  unsigned char z;
  z = l;
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x86(void)
{
  // ADD  A,(HL)
  // ADD  A,(IX+e)  (0xdd86)
  // ADD  A,(IY+e)  (0xfd86)
  unsigned short addr;
  unsigned short y;
  unsigned char z;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  z = (fetch(addr));
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x87(void)
{
  // ADD  A,A
  unsigned short y;
  unsigned char z = (a);
  tstates += 4;
  z = a;
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x88(void)
{
  // ADC  A,B
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = b;
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x89(void)
{
  // ADC  A,C
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = c;
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x8a(void)
{
  // ADC  A,D
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = d;
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x8b(void)
{
  // ADC  A,E
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = e;
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x8c(void)
{
  // ADC  A,H
  tstates += 4;
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = h;
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x8d(void)
{
  // ADC  A,L
  tstates += 4;
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = l;
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x8e(void)
{
  // ADC  A,(HL)
  // ADC  A,(IX+e)  0xdd8e
  // ADC  A,(IY+e)  0xfd8e
  unsigned short addr;
  unsigned short y;
  unsigned char z;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  z = (fetch(addr));
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x8f(void)
{
  // ADC  A,A
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = a;
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
}

void	fnc_0x90(void)
{
  // SUB  B
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = b;
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x91(void)
{
  // SUB  C
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = c;
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x92(void)
{
  // SUB  D
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = d;
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x93(void)
{
  // SUB  E
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = e;
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x94(void)
{
  // SUB  H
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = h;
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x95(void)
{
  // SUB  L
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = l;
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x96(void)
{
  // SUB  (HL)
  // SUB  (IX+e)  0xdd96
  // SUB  (IY+e)  0xfd96
  unsigned short addr;
  unsigned short y;
  unsigned char z;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  z = (fetch(addr));
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x97(void)
{
  // SUB  A
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = a;
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x98(void)
{
  // SBC  B
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = b;
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x99(void)
{
  // SBC  C
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = c;
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x9a(void)
{
  // SBC  D
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = d;
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x9b(void)
{
  // SBC  E
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = e;
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x9c(void)
{
  // SBC  H
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = h;
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x9d(void)
{
  // SBC  L
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = l;
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x9e(void)
{
  // SBC  (HL)
  // SBC  (IX+e)
  // SBC  (IY+e)
  unsigned short addr;
  unsigned short y;
  unsigned char z;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  z = (fetch(addr));
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0x9f(void)
{
  // SBC  A
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = a;
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
}

void	fnc_0xa0(void)
{
  // AND  B
  tstates += 4;
  a &= b;
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa1(void)
{
  // AND  C
  tstates += 4;
  a &= c;
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa2(void)
{
  // AND  D
  tstates += 4;
  a &= d;
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa3(void)
{
  // AND  E
  tstates += 4;
  a &= e;
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa4(void)
{
  // AND  H
  tstates += 4;
  a &= h;
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa5(void)
{
  // AND  L
  tstates += 4;
  a &= l;
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa6(void)
{
  // AND  (HL)
  // AND  (IX+e)   0xdda6
  // AND  (IY+e)   0xfda6
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  a &= (fetch(addr));
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa7(void)
{
  // AND  A
  tstates += 4;
  a &= a;
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
}

void	fnc_0xa8(void)
{
  // XOR  B
  tstates += 4;
  a ^= b;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xa9(void)
{
  // XOR  C
  tstates += 4;
  a ^= c;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xaa(void)
{
  // XOR  D
  tstates += 4;
  a ^= d;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xab(void)
{
  // XOR  E
  tstates += 4;
  a ^= e;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xac(void)
{
  // XOR  H
  tstates += 4;
  a ^= h;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xad(void)
{
  // XOR  L
  tstates += 4;
  a ^= l;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xae(void)
{
  // XOR  (HL)
  // XOR  (IX+e)  0xddae
  // XOR  (IY+e)  0xfdae
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }

  a ^= (fetch(addr));
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xaf(void)
{
  // XOR  A
  tstates += 4;
  a ^= a;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb0(void)
{
  // OR  B
  tstates += 4;
  a |= b;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb1(void)
{
  // OR  C
  tstates += 4;
  a |= c;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb2(void)
{
  // OR  D
  tstates += 4;
  a |= d;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb3(void)
{
  // OR  E
  tstates += 4;
  a |= e;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb4(void)
{
  // OR  H
  tstates += 4;
  a |= h;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb5(void)
{
  // OR  L
  tstates += 4;
  a |= l;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb6(void)
{
  // OR  (HL)
  // OR  (IX+e)
  // OR  (IY+e)
  unsigned short addr;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  a |= (fetch(addr));
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb7(void)
{
  // OR  A
  tstates += 4;
  a |= a;
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xb8(void)
{
  // CP  B
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = b;
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xb9(void)
{
  // CP  C
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = c;
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xba(void)
{
  // CP  D
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = d;
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xbb(void)
{
  // CP  E
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = e;
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xbc(void)
{
  // CP  H
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = h;
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xbd(void)
{
  // CP  L
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = l;
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xbe(void)
{
  // CP  (HL)
  // CP  (IX+e)  0xddbe
  // CP  (IY+e)  0xfdbe
  unsigned short addr;
  unsigned short y;
  unsigned char z;
  tstates += 7;
  if (ixoriy == 0) {
    addr = hl;
  } else {
    tstates += 8;
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
  }
  z = (fetch(addr));
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xbf(void)
{
  // CP  A
  unsigned short y;
  unsigned char z;
  tstates += 4;
  z = a;
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
}

void	fnc_0xc0(void)
{
  // RET  NZ
  tstates += 5;
  if (!(f & 0x40)) {
    tstates += 6;
    pc = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xc1(void)
{
  // POP  BC
  tstates += 10;
  c = fetch(sp);
  b = fetch(sp + 1);
  sp += 2;
}

void	fnc_0xc2(void)
{
  // JR  NZ,nn
  tstates += 10;
  if (!(f & 0x40)) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xc3(void)
{
  // JP  nn
  tstates += 10;
  pc = fetch2(pc);
}

void	fnc_0xc4(void)
{
  // CALL  NZ,nn
  tstates += 10;
  if (!(f & 0x40)) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xc5(void)
{
  // PUSH  BC
  tstates += 11;
  sp -= 2;
  store2b(sp, b, c);
}

void	fnc_0xc6(void)
{
  // ADD  A,n
  unsigned short y;
  unsigned char z;
  tstates += 7;
  z = (fetch(pc));
  y = a + z + (0);
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + (0) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
  pc++;
}

void	fnc_0xc7(void)
{
  // RST  0
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 0;
}

void	fnc_0xc8(void)
{
  // RET  Z
  tstates += 5;
  if (f & 0x40) {
    tstates += 6;
    pc = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xc9(void)
{
  // RET
  tstates += 10;
  pc = fetch2(sp);
  sp += 2;
}

void	fnc_0xca(void)
{
  // JP  Z,nn
  tstates += 10;
  if (f & 0x40) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xcb(void)
{
  unsigned short addr;
  unsigned char op, reg, val, t;
  tstates += 4;
  if (ixoriy) {
    addr = (ixoriy == 1 ? ix : iy) + (signed char)fetch(pc);
    pc++;
    tstates += 8;
    op = fetch(pc);
    reg = op & 7;
    op = (op & 0xf8) | 6;
  } else {
    op = fetch(pc);
    tstates += 4;
    radjust++;
    addr = hl;
  }
  pc++;
  if (op < 64) {
    switch (op) {
      case  0: b = (b << 1) | (b >> 7); f = (b & 1) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //RLC B
      case  1: c = (c << 1) | (c >> 7); f = (c & 1) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //RLC C
      case  2: d = (d << 1) | (d >> 7); f = (d & 1) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //RLC D
      case  3: e = (e << 1) | (e >> 7); f = (e & 1) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //RLC E
      case  4: h = (h << 1) | (h >> 7); f = (h & 1) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //RLC H
      case  5: l = (l << 1) | (l >> 7); f = (l & 1) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //RLC L
      case  6:                                                              //RLC (HL/IX+e/IY+e)
        tstates += 7; val = fetch(addr);
        val = (val << 1) | (val >> 7); f = (val & 1) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case  7: a = (a << 1) | (a >> 7); f = (a & 1) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //RLCA

      case  8: t = b & 1; b = (b >> 1) | (t << 7); f = (t) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //RRC B
      case  9: t = c & 1; c = (c >> 1) | (t << 7); f = (t) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //RRC C
      case 10: t = d & 1; d = (d >> 1) | (t << 7); f = (t) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //RRC D
      case 11: t = e & 1; e = (e >> 1) | (t << 7); f = (t) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //RRC E
      case 12: t = h & 1; h = (h >> 1) | (t << 7); f = (t) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //RRC H
      case 13: t = l & 1; l = (l >> 1) | (t << 7); f = (t) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //RRC L
      case 14:                                                                  //RRC (HL/IX+e/IY+e)
        tstates += 7; val = fetch(addr);
        t = val & 1; val = (val >> 1) | (t << 7); f = (t) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case 15: t = a & 1; a = (a >> 1) | (t << 7); f = (t) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //RRCA

      case 0x10: t = b >> 7; b = (b << 1) | (f & 1); f = (t) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //RL B
      case 0x11: t = c >> 7; c = (c << 1) | (f & 1); f = (t) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //RL C
      case 0x12: t = d >> 7; d = (d << 1) | (f & 1); f = (t) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //RL D
      case 0x13: t = e >> 7; e = (e << 1) | (f & 1); f = (t) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //RL E
      case 0x14: t = h >> 7; h = (h << 1) | (f & 1); f = (t) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //RL H
      case 0x15: t = l >> 7; l = (l << 1) | (f & 1); f = (t) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //RL L
      case 0x16:                                                                  //RL (HL/IX+e/IY+e)
        tstates += 7; val = fetch(addr);
        t = val >> 7; val = (val << 1) | (f & 1); f = (t) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case 0x17: t = a >> 7; a = (a << 1) | (f & 1); f = (t) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //RLA

      case 0x18: t = b & 1; b = (b >> 1) | (f << 7); f = (t) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //RR B
      case 0x19: t = c & 1; c = (c >> 1) | (f << 7); f = (t) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //RR C
      case 0x1a: t = d & 1; d = (d >> 1) | (f << 7); f = (t) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //RR D
      case 0x1b: t = e & 1; e = (e >> 1) | (f << 7); f = (t) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //RR E
      case 0x1c: t = h & 1; h = (h >> 1) | (f << 7); f = (t) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //RR H
      case 0x1d: t = l & 1; l = (l >> 1) | (f << 7); f = (t) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //RR L
      case 0x1e:                                                                  //RR (HL/IX+e/IY+e)
        tstates += 7; val = fetch(addr);
        t = val & 1; val = (val >> 1) | (f << 7); f = (t) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case 0x1f: t = a & 1; a = (a >> 1) | (f << 7); f = (t) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //RRA

      case 0x20: t = b >> 7; b <<= 1; f = (t) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //SLA B
      case 0x21: t = c >> 7; c <<= 1; f = (t) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //SLA C
      case 0x22: t = d >> 7; d <<= 1; f = (t) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //SLA D
      case 0x23: t = e >> 7; e <<= 1; f = (t) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //SLA E
      case 0x24: t = h >> 7; h <<= 1; f = (t) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //SLA H
      case 0x25: t = l >> 7; l <<= 1; f = (t) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //SLA L
      case 0x26:                                                         //SLA (HL/IX+e/IY+e)
        tstates += 7; val = fetch(addr);
        t = val >> 7; val <<= 1; f = (t) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case 0x27: t = a >> 7; a <<= 1; f = (t) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //SLA A

      case 0x28: t = b & 1; b = ((signed char)b) >> 1; f = (t) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //SRA B
      case 0x29: t = c & 1; c = ((signed char)c) >> 1; f = (t) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //SRA C
      case 0x2a: t = d & 1; d = ((signed char)d) >> 1; f = (t) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //SRA D
      case 0x2b: t = e & 1; e = ((signed char)e) >> 1; f = (t) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //SRA E
      case 0x2c: t = h & 1; h = ((signed char)h) >> 1; f = (t) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //SRA H
      case 0x2d: t = l & 1; l = ((signed char)l) >> 1; f = (t) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //SRA L
      case 0x2e:                                                                        //SRA (HL/IX+e/IY+e)
        tstates += 7; val = fetch(addr);
        t = val & 1; val = ((signed char)val) >> 1; f = (t) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case 0x2f: t = a & 1; a = ((signed char)a) >> 1; f = (t) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //SRA A

      case 0x30: t = b >> 7; b = (b << 1) | 1; f = (t) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //undefine
      case 0x31: t = c >> 7; c = (c << 1) | 1; f = (t) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //undefine
      case 0x32: t = d >> 7; d = (d << 1) | 1; f = (t) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //undefine
      case 0x33: t = e >> 7; e = (e << 1) | 1; f = (t) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //undefine
      case 0x34: t = h >> 7; h = (h << 1) | 1; f = (t) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //undefine
      case 0x35: t = l >> 7; l = (l << 1) | 1; f = (t) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //undefine
      case 0x36:                                                              //undefine
        tstates += 7; val = fetch(addr);
        t = val >> 7; val = (val << 1) | 1; f = (t) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case 0x37: t = a >> 7; a = (a << 1) | 1; f = (t) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //undefine


      case 0x38: t = b & 1; b >>= 1; f = (t) | (b & 0xa8) | ((!b) << 6) | parity(b); break; //SRL B
      case 0x39: t = c & 1; c >>= 1; f = (t) | (c & 0xa8) | ((!c) << 6) | parity(c); break; //SRL C
      case 0x3a: t = d & 1; d >>= 1; f = (t) | (d & 0xa8) | ((!d) << 6) | parity(d); break; //SRL D
      case 0x3b: t = e & 1; e >>= 1; f = (t) | (e & 0xa8) | ((!e) << 6) | parity(e); break; //SRL E
      case 0x3c: t = h & 1; h >>= 1; f = (t) | (h & 0xa8) | ((!h) << 6) | parity(h); break; //SRL H
      case 0x3d: t = l & 1; l >>= 1; f = (t) | (l & 0xa8) | ((!l) << 6) | parity(l); break; //SRL L
      case 0x3e:                                                        //SRL (HL/IX+e/IY+e)
        tstates += 7; val = fetch(addr);
        t = val & 1; val >>= 1; f = (t) | (val & 0xa8) | ((!val) << 6) | parity(val);
        store(addr, val);
        break;
      case 0x3f: t = a & 1; a >>= 1; f = (t) | (a & 0xa8) | ((!a) << 6) | parity(a); break; //SRL A

    }
  } else {
    unsigned char n = (op >> 3) & 7;
    switch (op & 0xc7) {
      case 0x40: f = (f & 1) | ((b & (1 << n)) ? 0x10 : 0x54) | (b & 0x28); break; //BIT 0-7,B
      case 0x41: f = (f & 1) | ((c & (1 << n)) ? 0x10 : 0x54) | (c & 0x28); break; //BIT 0-7,C
      case 0x42: f = (f & 1) | ((d & (1 << n)) ? 0x10 : 0x54) | (d & 0x28); break; //BIT 0-7,D
      case 0x43: f = (f & 1) | ((e & (1 << n)) ? 0x10 : 0x54) | (e & 0x28); break; //BIT 0-7,E
      case 0x44: f = (f & 1) | ((h & (1 << n)) ? 0x10 : 0x54) | (h & 0x28); break; //BIT 0-7,H
      case 0x45: f = (f & 1) | ((l & (1 << n)) ? 0x10 : 0x54) | (l & 0x28); break; //BIT 0-7,L
      case 0x46:                                                 //BIT 0-7,(HL/IX+e/IY+e)
        tstates += 4;
        val = fetch(addr);
        f = (f & 1) | ((val & (1 << n)) ? 0x10 : 0x54) | (val & 0x28);
        store(addr, val);
        break;
      case 0x47: f = (f & 1) | ((a & (1 << n)) ? 0x10 : 0x54) | (a & 0x28); break; //BIT 0-7,A

      case 0x80: b &= ~(1 << n); break; //RES 0-7,B
      case 0x81: c &= ~(1 << n); break; //RES 0-7,C
      case 0x82: d &= ~(1 << n); break; //RES 0-7,D
      case 0x83: e &= ~(1 << n); break; //RES 0-7,E
      case 0x84: h &= ~(1 << n); break; //RES 0-7,H
      case 0x85: l &= ~(1 << n); break; //RES 0-7,L
      case 0x86:                    //RES 0-7,(HL/IX+e/IY+e)
        tstates += 4;
        val = fetch(addr);
        val &= ~(1 << n);
        store(addr, val);
        break;
      case 0x87: a &= ~(1 << n); break; //RES 0-7,A

      case 0xc0: b |= (1 << n); break; //SET 0-7,B
      case 0xc1: c |= (1 << n); break; //SET 0-7,C
      case 0xc2: d |= (1 << n); break; //SET 0-7,D
      case 0xc3: e |= (1 << n); break; //SET 0-7,E
      case 0xc4: h |= (1 << n); break; //SET 0-7,H
      case 0xc5: l |= (1 << n); break; //SET 0-7,L
      case 0xc6:                   //SET 0-7,(HL/IX+e/IY+e)
        tstates += 4;
        val = fetch(addr);
        val |= (1 << n);
        store(addr, val);
        break;
      case 0xc7: a |= (1 << n); break; //SET 0-7,A
    }
  }
  if (ixoriy) {
    switch (reg) {
      case 0: b = val; break;
      case 1: c = val; break;
      case 2: d = val; break;
      case 3: e = val; break;
      case 4: h = val; break;
      case 5: l = val; break;
      case 7: a = val; break;
    }
  }
}

void	fnc_0xcc(void)
{
  // CALL  Z,nn
  tstates += 10;
  if (f & 0x40) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xcd(void)
{
  // CALL  nn
  tstates += 17;
  sp -= 2;
  store2(sp, (pc + 2));
  pc = fetch2(pc);
}

void	fnc_0xce(void)
{
  // ADC  A,n
  unsigned short y;
  unsigned char z;
  tstates += 7;
  z = fetch(pc);
  y = a + z + ((f & 1));
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) + (z & 0x0f) + ((f & 1)) > 15) << 4) | (((~a ^ z) & 0x80 & (y ^ a)) >> 5);
  f |= (!(a = y)) << 6;
  pc++;
}

void	fnc_0xcf(void)
{
  // RST  8H
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 8;
}

void	fnc_0xd0(void)
{
  // RET  NC
  tstates += 5;
  if (!(f & 1)) {
    tstates += 6;
    pc = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xd1(void)
{
  // POP  DE
  tstates += 10;
  e = fetch(sp);
  d = fetch(sp + 1);
  sp += 2;
}

void	fnc_0xd2(void)
{
  // JP  NC,nn
  tstates += 10;
  if (!(f & 1)) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xd3(void)
{
  // OUT  (n),A
  tstates += 11;
  tstates += out(a, fetch(pc), a);
  pc++;
}

void	fnc_0xd4(void)
{
  // CALL  NC,nn
  tstates += 10;
  if (!(f & 1)) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xd5(void)
{
  // PUSH  DE
  tstates += 11;
  sp -= 2;
  store2b(sp, d, e);
}

void	fnc_0xd6(void)
{
  // SUB  n
  unsigned short y;
  unsigned char z;
  tstates += 7;
  z = (fetch(pc));
  y = (a - z - (0)) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + (0)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
  pc++;
}

void	fnc_0xd7(void)
{
  // RST  10H
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 0x10;
}

void	fnc_0xd8(void)
{
  // RET  C
  tstates += 5;
  if (f & 1) {
    tstates += 6;
    pc = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xd9(void)
{
  // EXX
  unsigned char t;
  tstates += 4;
  t = b; b = b1; b1 = t;
  t = c; c = c1; c1 = t;
  t = d; d = d1; d1 = t;
  t = e; e = e1; e1 = t;
  t = h; h = h1; h1 = t;
  t = l; l = l1; l1 = t;
}

void	fnc_0xda(void)
{
  // JP  C,nn
  tstates += 10;
  if (f & 1) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xdb(void)
{
  // IN  A,n
  unsigned short t;
  tstates += 11;
  a = t = in(a, fetch(pc));
  tstates += t >> 8;
  pc++;
}

void	fnc_0xdc(void)
{
  // CALL  C,nn
  tstates += 10;
  if (f & 1) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xdd(void)
{
  // precode (IX+e)
  tstates += 4;
  new_ixoriy = 1;
}

void	fnc_0xde(void)
{
  // SBC  A,n
  unsigned short y;
  unsigned char z;
  tstates += 7;
  z = (fetch(pc));
  y = (a - z - ((f & 1))) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f) + ((f & 1))) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2;
  f |= (!(a = y)) << 6;
  pc++;
}

void	fnc_0xdf(void)
{
  // RST  18H
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 0x18;
}

void	fnc_0xe0(void)
{
  // RET  PO
  tstates += 5;
  if (!(f & 4)) {
    tstates += 6;
    pc = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xe1(void)
{
  // POP  HL
  // POP  IX
  // POP  IY
  tstates += 10;
  if (!ixoriy) {
    l = fetch(sp);
    h = fetch(sp + 1);
    sp += 2;
  } else if (ixoriy == 1) {
    ix = fetch2(sp);
    sp += 2;
  } else {
    iy = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xe2(void)
{
  // JP  PO,nn
  tstates += 10;
  if (!(f & 4)) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xe3(void)
{
  // EX  (SP),HL
  // EX  (SP),IX
  // EX  (SP),IY
  unsigned short t;
  tstates += 19;
  if (!ixoriy) {
    t = fetch2(sp);
    store2b(sp, h, l);
    l = t;
    h = t >> 8;
  } else if (ixoriy == 1) {
    t = fetch2(sp);
    store2(sp, ix);
    ix = t;
  } else {
    t = fetch2(sp);
    store2(sp, iy);
    iy = t;
  }
}

void	fnc_0xe4(void)
{
  // CALL  PO,nn
  tstates += 10;
  if (!(f & 4)) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xe5(void)
{
  // PUSH  HL
  // PUSH  IX
  // PUSH  IY
  tstates += 11;
  if (!ixoriy) {
    sp -= 2;
    store2b(sp, h, l);
  } else if (ixoriy == 1) {
    sp -= 2;
    store2(sp, (ix));
  } else {
    sp -= 2;
    store2(sp, (iy));
  }
}

void	fnc_0xe6(void)
{
  // AND  n
  tstates += 7;
  a &= (fetch(pc));
  f = (a & 0xa8) | ((!a) << 6) | 0x10 | parity(a);
  pc++;
}

void	fnc_0xe7(void)
{
  // RST  20H
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 0x20;
}

void	fnc_0xe8(void)
{
  // RET  PE
  tstates += 5;
  if (f & 4) {
    tstates += 6;
    pc = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xe9(void)
{
  // JP (HL)
  // JP (IX)
  // JP (IY)
  tstates += 4;
  pc = !ixoriy ? hl : ixoriy == 1 ? ix : iy;
}

void	fnc_0xea(void)
{
  // JP  PE,nn
  tstates += 10;
  if (f & 4) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xeb(void)
{
  // EX  DE,HL
  unsigned char t;
  tstates += 4;
  t = h; h = d; d = t;
  t = e; e = l; l = t;
}

void	fnc_0xec(void)
{
  // CALL  PE,nn
  tstates += 10;
  if (f & 4) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xed(void)
{
  unsigned char op;
  tstates += 4;
  op = fetch(pc);
  pc++;
  radjust++;


  switch (op) {
    case 0xfc: fnc_0xedfc(); break;
    case 0xfd: fnc_0xedfd(); break;
    case 0xfe: fnc_0xedfe(); break;
    case 0xff: fnc_0xedff(); break;
    default:
      if (op >= 0x40 && op <= 0xbf) {
        (*z80edops[op - 0x40])();
      } else {
        fnc_0xedXX();
      }
      break;
  }
}


void	fnc_0xedXX(void)
{
  tstates += 4;
}

void	fnc_0xed40(void)
{
  // IN  B,(C)
  unsigned short u;
  tstates += 8;
  b = u = in(b, c);
  tstates += u >> 8;
  f = (f & 1) | (b & 0xa8) | ((!b) << 6) | parity(b);
}

void	fnc_0xed41(void)
{
  // OUT  (C),B
  tstates += 8;
  tstates += out(b, c, b);
}

void	fnc_0xed42(void)
{
  // SBC  HL,BC
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (bc);
  t = (hl - z - (f & 1)) & 0x1ffff;
  f = ((t >> 8) & 0xa8) | (t >> 16) | 2 | (((hl & 0xfff) < (z & 0xfff) + (f & 1)) << 4) | (((hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed43(void)
{
  // LD  (nn),BC
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  store2b(addr, b, c);
}

void	fnc_0xed44(void)
{
  // NEG
  tstates += 4;
  a = -a;
  f = (a & 0xa8) | ((!a) << 6) | (((a & 15) > 0) << 4) | ((a == 128) << 2) | 2 | (a > 0);
}

void	fnc_0xed45(void)
{
  // RETN
  tstates += 10;
  iff1 = iff2;
  pc = fetch2(sp);
  sp += 2;
}

void	fnc_0xed46(void)
{
  // IM  0
  tstates += 4;
  im = 0;
}

void	fnc_0xed47(void)
{
  // LD  I,A
  tstates += 5;
  i = a;
}

void	fnc_0xed48(void)
{
  // IN  C,(C)
  unsigned short u;
  tstates += 8;
  c = u = in(b, c);
  tstates += u >> 8;
  f = (f & 1) | (c & 0xa8) | ((!c) << 6) | parity(c);
}

void	fnc_0xed49(void)
{
  // OUT  (C),C
  tstates += 8;
  tstates += out(b, c, c);
}

void	fnc_0xed4a(void)
{
  // ADC  HL,BC
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (bc);
  t = hl + z + (f & 1);
  f = ((t >> 8) & 0xa8) | (t >> 16) | (((hl & 0xfff) + (z & 0xfff) + (f & 1) > 0xfff) << 4) | (((~hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed4b(void)
{
  // LD  BC,(nn)
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  c = fetch(addr);
  b = fetch(addr + 1);
}

void	fnc_0xed4d(void)
{
  // RETI
  tstates += 10;
  pc = fetch2(sp);
  sp += 2;
}

void	fnc_0xed4f(void)
{
  // LD  R,A
  tstates += 5;
  r = a;
  radjust = r;
}

void	fnc_0xed50(void)
{
  // IN  D,(C)
  unsigned short u;
  tstates += 8;
  d = u = in(b, c);
  tstates += u >> 8;
  f = (f & 1) | (d & 0xa8) | ((!d) << 6) | parity(d);
}

void	fnc_0xed51(void)
{
  // OUT  (C),D
  tstates += 8;
  tstates += out(b, c, d);
}

void	fnc_0xed52(void)
{
  // SBC  HL,DE
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (de);
  t = (hl - z - (f & 1)) & 0x1ffff;
  f = ((t >> 8) & 0xa8) | (t >> 16) | 2 | (((hl & 0xfff) < (z & 0xfff) + (f & 1)) << 4) | (((hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed53(void)
{
  // LD  (nn),DE
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  store2b(addr, d, e);
}

void	fnc_0xed56(void)
{
  // IM  1
  tstates += 4;
  im = 2;
}

void	fnc_0xed57(void)
{
  // LD  A,I
  tstates += 5;
  a = i;
  f = (f & 1) | (a & 0xa8) | ((!a) << 6) | (iff2 << 2);
}

void	fnc_0xed58(void)
{
  // IN  E,(C)
  unsigned short u;
  tstates += 8;
  e = u = in(b, c);
  tstates += u >> 8;
  f = (f & 1) | (e & 0xa8) | ((!e) << 6) | parity(e);
}

void	fnc_0xed59(void)
{
  // OUT  (C),E
  tstates += 8;
  tstates += out(b, c, e);
}

void	fnc_0xed5a(void)
{
  // ADC  HL,DE
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (de);
  t = hl + z + (f & 1);
  f = ((t >> 8) & 0xa8) | (t >> 16) | (((hl & 0xfff) + (z & 0xfff) + (f & 1) > 0xfff) << 4) | (((~hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed5b(void)
{
  // LD  DE,(nn)
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  e = fetch(addr);
  d = fetch(addr + 1);
}

void	fnc_0xed5e(void)
{
  // IM  2
  tstates += 4;
  im = 3;
}

void	fnc_0xed5f(void)
{
  // LD  A,R
  tstates += 5;
  r = (r & 0x80) | (radjust & 0x7f);
  a = r;
  f = (f & 1) | (a & 0xa8) | ((!a) << 6) | (iff2 << 2);
}

void	fnc_0xed60(void)
{
  // IN  H,(C)
  unsigned short u;
  tstates += 8;
  h = u = in(b, c);
  tstates += u >> 8;
  f = (f & 1) | (h & 0xa8) | ((!h) << 6) | parity(h);
}

void	fnc_0xed61(void)
{
  // OUT  (C),H
  tstates += 8;
  tstates += out(b, c, h);
}

void	fnc_0xed62(void)
{
  // SBC  HL,HL
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (hl);
  t = (hl - z - (f & 1)) & 0x1ffff;
  f = ((t >> 8) & 0xa8) | (t >> 16) | 2 | (((hl & 0xfff) < (z & 0xfff) + (f & 1)) << 4) | (((hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed63(void)
{
  // LD  (nn),HL
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  store2b(addr, h, l);
}

void	fnc_0xed67(void)
{
  // RRD
  unsigned char t;
  unsigned char u;
  tstates += 14;
  t = fetch(hl);
  u = (a << 4) | (t >> 4);
  a = (a & 0xf0) | (t & 0x0f);
  store(hl, u);
  f = (f & 1) | (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xed68(void)
{
  // IN  L,(C)
  unsigned short u;
  tstates += 8;
  l = u = in(b, c);
  tstates += u >> 8;
  f = (f & 1) | (l & 0xa8) | ((!l) << 6) | parity(l);
}

void	fnc_0xed69(void)
{
  // OUT  (C),L
  tstates += 8;
  tstates += out(b, c, l);
}

void	fnc_0xed6a(void)
{
  // ADC  HL,HL
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (hl);
  t = hl + z + (f & 1);
  f = ((t >> 8) & 0xa8) | (t >> 16) | (((hl & 0xfff) + (z & 0xfff) + (f & 1) > 0xfff) << 4) | (((~hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed6b(void)
{
  // LD  HL,(nn)
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  l = fetch(addr);
  h = fetch(addr + 1);
}

void	fnc_0xed6f(void)
{
  // RLD
  unsigned char t;
  unsigned char u;
  tstates += 5;
  t = fetch(hl);
  u = (a & 0x0f) | (t << 4);
  a = (a & 0xf0) | (t >> 4);
  store(hl, u);
  f = (f & 1) | (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xed72(void)
{
  // SBC  HL,SP
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (sp);
  t = (hl - z - (f & 1)) & 0x1ffff;
  f = ((t >> 8) & 0xa8) | (t >> 16) | 2 | (((hl & 0xfff) < (z & 0xfff) + (f & 1)) << 4) | (((hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed73(void)
{
  // LD  (nn),SP
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  store2(addr, sp);
}

void	fnc_0xed78(void)
{
  // IN  A,(C)
  unsigned short u;
  tstates += 8;
  a = u = in(b, c);
  tstates += u >> 8;
  f = (f & 1) | (a & 0xa8) | ((!a) << 6) | parity(a);
}

void	fnc_0xed79(void)
{
  // OUT  (C),A
  tstates += 8;
  tstates += out(b, c, a);
}

void	fnc_0xed7a(void)
{
  // ADC  HL,SP
  unsigned short z;
  unsigned long t;
  tstates += 11;
  z = (sp);
  t = hl + z + (f & 1);
  f = ((t >> 8) & 0xa8) | (t >> 16) | (((hl & 0xfff) + (z & 0xfff) + (f & 1) > 0xfff) << 4) | (((~hl ^ z) & (hl ^ t) & 0x8000) >> 13) | ((!(t & 0xffff)) << 6) | 2;
  l = t;
  h = t >> 8;
}

void	fnc_0xed7b(void)
{
  // LD  SP,(nn)
  unsigned short addr;
  tstates += 16;
  addr = fetch2(pc);
  pc += 2;
  sp = fetch2(addr);
}

void	fnc_0xeda0(void)
{
  // LDI
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  store(de, x);
  if (!++l)h++;
  if (!++e)d++;
  if (!c--)b--;
  f = (f & 0xc1) | (x & 0x28) | (((b | c) > 0) << 2);
}

void	fnc_0xeda1(void)
{
  // CPI
  unsigned char carry;
  unsigned short y;
  unsigned char z;
  tstates += 12;
  carry = (f & 1);
  z = (fetch(hl));
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
  if (!++l)h++;
  if (!c--)b--;
  f = (f & 0xfa) | carry | (((b | c) > 0) << 2);
}

void	fnc_0xeda2(void)
{
  // INI
  unsigned short t;
  tstates += 12;
  t = in(b, c);
  store(hl, t);
  tstates += t >> 8;
  if (!++l)h++;
  b--;
  f = (b & 0xa8) | ((b > 0) << 6) | 2 | ((parity(b)^c) & 4);
}

void	fnc_0xeda3(void)
{
  // OUTI
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  tstates += out(b, c, x);
  if (!++l)h++;
  b--;
  f = (f & 1) | 0x12 | (b & 0xa8) | ((b == 0) << 6);
}

void	fnc_0xeda8(void)
{
  // LDD
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  store(de, x);
  if (!l--)h--;
  if (!e--)d--;
  if (!c--)b--;
  f = (f & 0xc1) | (x & 0x28) | (((b | c) > 0) << 2);
}

void	fnc_0xeda9(void)
{
  // CPD
  unsigned char carry;
  unsigned short y;
  unsigned char z;
  tstates += 12;
  carry = (f & 1);
  z = (fetch(hl));
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
  if (!l--)h--;
  if (!c--)b--;
  f = (f & 0xfa) | carry | (((b | c) > 0) << 2);
}

void	fnc_0xedaa(void)
{
  // IND
  unsigned short t;
  tstates += 12;
  t = in(b, c);
  store(hl, t);
  tstates += t >> 8;
  if (!l--)h--;
  b--;
  f = (b & 0xa8) | ((b > 0) << 6) | 2 | ((parity(b)^c ^ 4) & 4);
}

void	fnc_0xedab(void)
{
  // OUTD
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  tstates += out(b, c, x);
  if (!l--)h--;
  b--;
  f = (f & 1) | 0x12 | (b & 0xa8) | ((b == 0) << 6);
}

void	fnc_0xedb0(void)
{
  // LDIR
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  store(de, x);
  if (!++l)h++;
  if (!++e)d++;
  if (!c--)b--;
  f = (f & 0xc1) | (x & 0x28) | (((b | c) > 0) << 2);
  if (b | c)pc -= 2, tstates += 5;
}

void	fnc_0xedb1(void)
{
  // CPIR
  unsigned char carry;
  unsigned short y;
  unsigned char z;
  tstates += 12;
  carry = (f & 1);
  z = (fetch(hl));
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
  if (!++l)h++;
  if (!c--)b--;
  f = (f & 0xfa) | carry | (((b | c) > 0) << 2);
  if ((f & 0x44) == 4)pc -= 2, tstates += 5;
}

void	fnc_0xedb2(void)
{
  // INIR
  unsigned short t;
  tstates += 12;
  t = in(b, c);
  store(hl, t);
  tstates += t >> 8;
  if (!++l)h++;
  b--;
  f = (b & 0xa8) | ((b > 0) << 6) | 2 | ((parity(b)^c) & 4);
  if (b)pc -= 2, tstates += 5;
}

void	fnc_0xedb3(void)
{
  // OTIR
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  tstates += out(b, c, x);
  if (!++l)h++;
  b--;
  f = (f & 1) | 0x12 | (b & 0xa8) | ((b == 0) << 6);
  if (b)pc -= 2, tstates += 5;
}

void	fnc_0xedb8(void)
{
  // LDDR
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  store(de, x);
  if (!l--)h--;
  if (!e--)d--;
  if (!c--)b--;
  f = (f & 0xc1) | (x & 0x28) | (((b | c) > 0) << 2);
  if (b | c)pc -= 2, tstates += 5;
}

void	fnc_0xedb9(void)
{
  // CPDR
  unsigned char carry;
  unsigned short y;
  unsigned char z;
  tstates += 12;
  carry = (f & 1);
  z = (fetch(hl));
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
  if (!l--)h--;
  if (!c--)b--;
  f = (f & 0xfa) | carry | (((b | c) > 0) << 2);
  if ((f & 0x44) == 4)pc -= 2, tstates += 5;
}

void	fnc_0xedba(void)
{
  // INDR
  unsigned short t;
  tstates += 12;
  t = in(b, c);
  store(hl, t);
  tstates += t >> 8;
  if (!l--)h--;
  b--;
  f = (b & 0xa8) | ((b > 0) << 6) | 2 | ((parity(b)^c ^ 4) & 4);
  if (b)pc -= 2, tstates += 5;
}

void	fnc_0xedbb(void)
{
  // OTDR
  unsigned char x;
  tstates += 12;
  x = fetch(hl);
  tstates += out(b, c, x);
  if (!l--)h--;
  b--;
  f = (f & 1) | 0x12 | (b & 0xa8) | ((b == 0) << 6);
  if (b)pc -= 2, tstates += 5;
}

// mzf disk file access
//  read_inf()
void	fnc_0xedfc(void)
{
  tstates += 4;
  //if (read_inf() == 0) f = a = 0; else f = 1, a = 2;
  // JP RTP4
  //pc = 0x0552;
}

// mzf disk file access
//  read_data()
void	fnc_0xedfd(void)
{
  tstates += 4;
  //if (read_data() == 0) f = a = 0; else f = 1, a = 2;
  // RET (jump to C9 instruction)
  //pc = 0x0562;
}

// mzf disk file access
//  write_inf()
void	fnc_0xedfe(void)
{
  tstates += 4;
  //if (write_inf() == 0) f = 0; else f = 1;
  //pc = 0x04ce;
}

// mzf disk file access
//  write_data()
void	fnc_0xedff(void)
{
  tstates += 4;
  //if (write_data() == 0) f = 0; else f = 1;
  //pc = 0x04ce;
}


void	fnc_0xee(void)
{
  // XOR  n
  tstates += 7;
  a ^= (fetch(pc));
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
  pc++;
}

void	fnc_0xef(void)
{
  // RST  28H
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 0x28;
}

void	fnc_0xf0(void)
{
  // RET  P
  tstates += 5;
  if (!(f & 0x80)) {
    tstates += 6;
    pc = fetch2(sp);
    sp += 2;
  }
}

void	fnc_0xf1(void)
{
  // POP  AF
  tstates += 10;
  f = fetch(sp);
  a = fetch(sp + 1);
  sp += 2;
}

void	fnc_0xf2(void)
{
  // JP  P,nn
  tstates += 10;
  if (!(f & 0x80)) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xf3(void)
{
  // DI
  tstates += 4;
  iff1 = iff2 = 0;
}

void	fnc_0xf4(void)
{
  // CALL  P,nn
  tstates += 10;
  if (!(f & 0x80)) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xf5(void)
{
  // PUSH AF
  tstates += 11;
  sp -= 2;
  store2b(sp, a, f);
}

void	fnc_0xf6(void)
{
  // OR  n
  tstates += 7;
  a |= (fetch(pc));
  f = (a & 0xa8) | ((!a) << 6) | parity(a);
  pc++;
}

void	fnc_0xf7(void)
{
  // RST  30H
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 0x30;
}

void	fnc_0xf8(void)
{
  // RET  M
  tstates += 5;
  if (f & 0x80) {
    tstates += 6;
    pc = fetch2(sp); sp += 2;
  }
}

void	fnc_0xf9(void)
{
  // LD  SP,HL
  // LD  SP,IX
  // LD  SP,IY
  tstates += 6;
  sp = !ixoriy ? hl : ixoriy == 1 ? ix : iy;
}

void	fnc_0xfa(void)
{
  // JP  M,nn
  tstates += 10;
  if (f & 0x80) {
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xfb(void)
{
  // EI
  tstates += 4;
  iff1 = iff2 = 1;
}

void	fnc_0xfc(void)
{
  // CALL  M,nn
  tstates += 10;
  if (f & 0x80) {
    tstates += 7;
    sp -= 2;
    store2(sp, (pc + 2));
    pc = fetch2(pc);
  } else {
    pc += 2;
  }
}

void	fnc_0xfd(void)
{
  // precode IY+e
  tstates += 4;
  new_ixoriy = 2;
}

void	fnc_0xfe(void)
{
  // CP  n
  unsigned short y;
  unsigned char  z;
  tstates += 7;
  z = (fetch(pc));
  y = (a - z) & 0x1ff;
  f = (y & 0xa8) | (y >> 8) | (((a & 0x0f) < (z & 0x0f)) << 4) | (((a ^ z) & 0x80 & (y ^ a)) >> 5) | 2 | ((!y) << 6);
  pc++;
}

void	fnc_0xff(void)
{
  // RST 38H
  tstates += 11;
  sp -= 2;
  store2(sp, (pc));
  pc = 0x38;
}

/*** end of z80.c ***************************************************************************/
