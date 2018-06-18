//  lib for JY-LM1640 - inspired by: https://github.com/avishorp/TM1637
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef __LM1640DISPLAY__
#define __LM1640DISPLAY__

#include <inttypes.h>

//            A
//          -----
//         |     |     
//       F |     | B    
//         |  G  |     
//          -----
//         |     |     
//       E |     | C    
//         |     |     
//          -----   * DP
//            D  
//
#define S7_A    0x0001
#define S7_B    0x0002
#define S7_C    0x0004
#define S7_D    0x0008
#define S7_E    0x0010
#define S7_F    0x0020
#define S7_G    0x0040 
#define S7_DP   0x0080 




// Segment bit positions for 7 Segment display using the CATALEX and ROBOTDYN mapping for TM1637
// Modify this table for different 'bit-to-segment' mappings. The ASCII character defines and the FONT_7S const table below 
// will be adapted automatically according to the bit-to-segment mapping. Obviously this will only work when the segment
// mapping is identical for every digit position. This will be the case unless the hardware designer really hates software developers.
//
//            A
//          -----
//         |     |     
//       F |     | B    
//         |  G  |     
//          -----
//         |     |     
//       E |     | C    
//         |     |     
//          -----   * DP
//            D  
//
#define S7_A    0x0001
#define S7_B    0x0002
#define S7_C    0x0004
#define S7_D    0x0008
#define S7_E    0x0010
#define S7_F    0x0020
#define S7_G    0x0040 
#define S7_DP   0x0080 
 
#define SIZE   16
 
//Mask for blending out and setting 7 segments digits
#define MASK_7S_ALL = (S7_A | S7_B | S7_C | S7_D | S7_E | S7_F | S7_G}
 
//The CATALAX mapping between Digit positions or Columns (Left to Right) and Grids (ie memory address) are:
//The column numbers are:
//   0   1   2   3
//The Grids are:
//  GR1 GR2 GR3 GR4
//The memory addresses are:
//   0   1   2   3
 
 
//The ROBOTDYN mapping between Digit positions or columns (Left to Right) and Grids (ie memory address) are:
//The column numbers are:
//   0   1   2   3   4   5
//The Grids are:
//  GR3 GR2 GR1 GR6 GR5 GR4
//The memory addresses are:
//   2   1   0   5   4   3
 
 
//The EYEWINK mapping between Digit positions or columns (Left to Right) and Grids (ie memory address) are:
//The column numbers are:
//   0   1   2   3   4   5
//The Grids are:
//  GR1 GR2 GR3 GR4 GR5 GR6
//The memory addresses are:
//   0   1   2   3   4   5
 
 
//Icons Grid 1
#define S7_DP1  0x0080
#define S7_ICON_GR1 (0x0000)
//#define S7_ICON_GR1 (S7_DP1)
 
//Icons Grid 2
#define S7_DP2  0x0080
#define S7_COL2 0x0080
#define S7_ICON_GR2 (0x0000)
//#define S7_ICON_GR2 (S7_DP2)
 
//Icons Grid 3
#define S7_DP3  0x0080
#define S7_ICON_GR3 (0x0000)
//#define S7_ICON_GR3 (S7_DP3)
 
//Icons Grid 4
#define S7_DP4  0x0080
#define S7_ICON_GR4 (0x0000)
//#define S7_ICON_GR4 (S7_DP4)
 
//Icons Grid 5
#define S7_DP5  0x0080
#define S7_ICON_GR5 (0x0000)
//#define S7_ICON_GR5 (S7_DP5)
 
//Icons Grid 6
#define S7_DP6  0x0080
#define S7_ICON_GR6 (0x0000)
//#define S7_ICON_GR6 (S7_DP6)
 
 
//Mask for blending out and restoring Icons
extern const char MASK_ICON_GRID[]; 
 
 
// ASCII Font definitions for segments in each character
//
//32 0x20  Symbols
#define C7_SPC  (0x0000)
#define C7_EXC  (S7_B | S7_C) //!
#define C7_QTE  (S7_B | S7_F) //"
#define C7_HSH  (S7_C | S7_D | S7_E | S7_G) //#
#define C7_DLR  (S7_A | S7_C | S7_D | S7_F | S7_G) //$
#define C7_PCT  (S7_C | S7_F) //%
#define C7_AMP  (S7_A | S7_C | S7_D | S7_E | S7_F | S7_G) //&
#define C7_ACC  (S7_B) //'
#define C7_LBR  (S7_A | S7_D | S7_E | S7_F) //(
#define C7_RBR  (S7_A | S7_B | S7_C | S7_D) //)
#define C7_MLT  (S7_B | S7_C | S7_E | S7_F | S7_G)  //*
#define C7_PLS  (S7_B | S7_C | S7_G) //+
#define C7_CMA  (S7_DP)
#define C7_MIN  (S7_G)
#define C7_DPT  (S7_DP)
#define C7_RS   (S7_B | S7_E  | S7_G)  // /
 
//48 0x30  Digits
#define C7_0    (S7_A | S7_B | S7_C | S7_D | S7_E | S7_F)
#define C7_1    (S7_B | S7_C)
#define C7_2    (S7_A | S7_B | S7_D | S7_E | S7_G)
#define C7_3    (S7_A | S7_B | S7_C | S7_D | S7_G)
#define C7_4    (S7_B | S7_C | S7_F | S7_G)
#define C7_5    (S7_A | S7_C | S7_D | S7_F | S7_G)
#define C7_6    (S7_A | S7_C | S7_D | S7_E | S7_F | S7_G)
#define C7_7    (S7_A | S7_B | S7_C)
#define C7_8    (S7_A | S7_B | S7_C | S7_D | S7_E | S7_F | S7_G)
#define C7_9    (S7_A | S7_B | S7_C | S7_D | S7_F | S7_G)
 
//58 0x3A
#define C7_COL  (S7_D | S7_G) // :
#define C7_SCL  (S7_D | S7_G) // ;
#define C7_LT   (S7_D | S7_E | S7_G)             // <
#define C7_EQ   (S7_D | S7_G)                    // =
#define C7_GT   (S7_C | S7_D | S7_G)             // >   
#define C7_QM   (S7_A | S7_B | S7_E | S7_G)      // ?
#define C7_AT   (S7_A | S7_B | S7_C | S7_D | S7_E  | S7_G)  // @
 
//65 0x41  Upper case alphabet
#define C7_A    (S7_A | S7_B | S7_C | S7_E | S7_F | S7_G )
#define C7_B    (S7_C | S7_D | S7_E | S7_F | S7_G)
#define C7_C    (S7_A | S7_D | S7_E | S7_F)
#define C7_D    (S7_B | S7_C | S7_D | S7_E | S7_G)
#define C7_E    (S7_A | S7_D | S7_E | S7_F | S7_G)
#define C7_F    (S7_A | S7_E | S7_F | S7_G)
 
#define C7_G    (S7_A | S7_C | S7_D | S7_E | S7_F)
#define C7_H    (S7_B | S7_C | S7_E | S7_F | S7_G)
#define C7_I    (S7_B | S7_C)
#define C7_J    (S7_B | S7_C | S7_D | S7_E)
#define C7_K    (S7_B | S7_C | S7_E | S7_F | S7_G)
#define C7_L    (S7_D | S7_E | S7_F)
#define C7_M    (S7_A | S7_C | S7_E)
#define C7_N    (S7_A | S7_B | S7_C | S7_E | S7_F)
#define C7_O    (S7_A | S7_B | S7_C | S7_D | S7_E | S7_F)
#define C7_P    (S7_A | S7_B | S7_E | S7_F | S7_G)
#define C7_Q    (S7_A | S7_B | S7_C | S7_F | S7_G)
#define C7_R    (S7_E | S7_G )
#define C7_S    (S7_A | S7_C | S7_D | S7_F | S7_G)
#define C7_T    (S7_D | S7_E | S7_F | S7_G)
#define C7_U    (S7_B | S7_C | S7_D | S7_E | S7_F)
#define C7_V    (S7_B | S7_C | S7_D | S7_E | S7_F)
#define C7_W    (S7_B | S7_D | S7_F)
#define C7_X    (S7_B | S7_C | S7_E | S7_F | S7_G)
#define C7_Y    (S7_B | S7_C | S7_D | S7_F | S7_G)
#define C7_Z    (S7_A | S7_B | S7_D | S7_E | S7_G)
 
//91 0x5B
#define C7_SBL  (S7_A | S7_D | S7_E | S7_F) // [
#define C7_LS   (S7_C | S7_F | S7_G)        // left slash
#define C7_SBR  (S7_A | S7_B | S7_C | S7_D) // ]
#define C7_PWR  (S7_A | S7_B | S7_F)        // ^
#define C7_UDS  (S7_D)                      // _
#define C7_DSH  (S7_F)                      // `  
 
//97 0x61  Lower case alphabet
#define C7_a     C7_A
#define C7_b     C7_B
#define C7_c     C7_C
#define C7_d     C7_D
#define C7_e     C7_E
#define C7_f     C7_H
 
#define C7_g     C7_G
#define C7_h     C7_H
#define C7_i     C7_I
#define C7_j     C7_J
#define C7_k     C7_K
#define C7_l     C7_L
#define C7_m     C7_M
//#define C7_n     C7_N
#define C7_n    (S7_C | S7_E | S7_G)
//#define C7_o     C7_O
#define C7_o    (S7_C | S7_D | S7_E | S7_G)
#define C7_p     C7_P
#define C7_q     C7_Q
//#define C7_r     C7_R
#define C7_r    (S7_E | S7_G)
#define C7_s     C7_S
#define C7_t     C7_T
#define C7_u     C7_U
#define C7_v     C7_V
#define C7_w     C7_W
#define C7_x     C7_X
#define C7_y     C7_Y
#define C7_z     C7_Z
 
//123 0x7B
#define C7_CBL  (S7_A | S7_D | S7_E | S7_F)        // {
#define C7_OR   (S7_B | S7_C)                      // |
#define C7_CBR  (S7_A | S7_B | S7_C | S7_D)        // }
#define C7_TLD  (S7_B | S7_E | S7_G )              // ~
#define C7_DEL  (0x0000)
 
 
//User Defined Characters (some examples)
#define C7_DGR   (S7_A | S7_B | S7_F | S7_G)  //Degrees
                                                                         
// Font data selection for transmission to TM1637 memory
#define LO(x)  ( x & 0xFF)
#define HI(x)  ((x >> 8) & 0xFF)
 
 
// ASCII Font definition table
//
#define FONT_7S_START     0x20
#define FONT_7S_END       0x7F
//#define FONT_7S_NR_CHARS (FONT_7S_END - FONT_7S_START + 1)




class LM1640Display {

public:
  //! Initialize a LM1640Display object, setting the clock and
  //! data pins.
  //!
  //! @param pinClk - The number of the digital pin connected to the clock pin of the module
  //! @param pinDIO - The number of the digital pin connected to the DIO pin of the module
  LM1640Display(uint8_t pinClk, uint8_t pinDIO);

  //! Sets the brightness of the display.
  //!
  //! The setting takes effect when a command is given to change the data being
  //! displayed.
  //!
  //! @param brightness A number from 0 (lowes brightness) to 7 (highest brightness)
  //! @param on Turn display on or off
  void setBrightness(uint8_t brightness, bool on = true);

  //! Display arbitrary data on the module
  //!
  //! This function receives raw segment values as input and displays them. The segment data
  //! is given as a byte array, each byte corresponding to a single digit. Within each byte,
  //! bit 0 is segment A, bit 1 is segment B etc.
  //! The function may either set the entire display or any desirable part on its own. The first
  //! digit is given by the @ref pos argument with 0 being the leftmost digit. The @ref length
  //! argument is the number of digits to be set. Other digits are not affected.
  //!
  //! @param segments An array of size @ref length containing the raw segment values
  //! @param length The number of digits to be modified
  //! @param pos The position from which to start the modification (0 - leftmost, 3 - rightmost)
  void setSegments(const uint8_t segments[], uint8_t length = 16, uint8_t pos = 0);

  //! Displayes a decimal number
  //!
  //! Dispalyes the given argument as a decimal number
  //!
  //! @param num The number to be shown
  //! @param leading_zero When true, leading zeros are displayed. Otherwise unnecessary digits are
  //!        blank
  //! @param length The number of digits to set. The user must ensure that the number to be shown
  //!        fits to the number of digits requested (for example, if two digits are to be displayed,
  //!        the number must be between 0 to 99)
  //! @param pos The position most significant digit (0 - leftmost, 3 - rightmost)
  void showNumberDec(int num, bool leading_zero = false, uint8_t length = 16, uint8_t pos = 0);

  //! Displayes a decimal number, with dot control
  //!
  //! Dispalyes the given argument as a decimal number. The dots between the digits (or colon)
  //! can be individually controlled
  //!
  //! @param num The number to be shown
  //! @param dots Dot/Colon enable. The argument is a bitmask, with each bit corresponding to a dot
  //!        between the digits (or colon mark, as implemented by each module). i.e.
  //!        For displays with dots between each digit:
  //!        * 0.000 (0b10000000)
  //!        * 00.00 (0b01000000)
  //!        * 000.0 (0b00100000)
  //!        * 0.0.0.0 (0b11100000)
  //!        For displays with just a colon:
  //!        * 00:00 (0b01000000)
  //!        For displays with dots and colons colon:
  //!        * 0.0:0.0 (0b11100000)
  //! @param leading_zero When true, leading zeros are displayed. Otherwise unnecessary digits are
  //!        blank
  //! @param length The number of digits to set. The user must ensure that the number to be shown
  //!        fits to the number of digits requested (for example, if two digits are to be displayed,
  //!        the number must be between 0 to 99)
  //! @param pos The position least significant digit (0 - leftmost, 3 - rightmost)
  void showNumberDecEx(int num, uint8_t dots = 0, bool leading_zero = false, uint8_t length = 16, uint8_t pos = 0);


  void clear(uint8_t length = 16);

  //! Translate a single digit into 7 segment code
  //!
  //! The method accepts a number between 0 - 15 and converts it to the
  //! code required to display the number on a 7 segment display.
  //! Numbers between 10-15 are converted to hexadecimal digits (A-F)
  //!
  //! @param digit A number between 0 to 15
  //! @return A code representing the 7 segment image of the digit (LSB - segment A;
  //!         bit 6 - segment G; bit 7 - always zero)
  uint8_t encodeDigit(uint8_t digit);

	uint8_t encodeChar(char ch);
		
	void showString(char str[]);
		
protected:
   void bitDelay();

   void start();

   void stop();

   bool writeByte(uint8_t b);

private:
	uint8_t m_pinClk;
	uint8_t m_pinDIO;
	uint8_t m_brightness;
};

#endif // __LM1640Display__
