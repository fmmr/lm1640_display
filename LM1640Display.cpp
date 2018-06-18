//  Inspired by LM1640Display,  Author: avishorp@gmail.com, https://github.com/avishorp/TM1637
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

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}

#include <LM1640Display.h>
#include <Arduino.h>

#define TM1637_I2C_COMM1    0b01000000
#define TM1637_I2C_COMM2    0b11000000
#define TM1637_I2C_COMM3    0b10000000
#define S7_DP   0x0080 

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D

const uint8_t digitToSegment[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // b
  0b00111001,    // C
  0b01011110,    // d
  0b01111001,    // E
  0b01110001     // F
  };

 const uint8_t clr[] = {
 // XGFEDCBA
  0b00000000,    // 0
  0b00000000,    // 1
  0b00000000,    // 2
  0b00000000,    // 3
  0b00000000,    // 4
  0b00000000,    // 5
  0b00000000,    // 6
  0b00000000,    // 7
  0b00000000,    // 8
  0b00000000,    // 9
  0b00000000,    // A
  0b00000000,    // b
  0b00000000,    // C
  0b00000000,    // d
  0b00000000,    // E
  0b00000000     // F
  };

const short FONT_7S[]  = { 
                             C7_SPC, //32 0x20, Space
                             C7_EXC,
                             C7_QTE,
                             C7_HSH,
                             C7_DLR,
                             C7_PCT,
                             C7_AMP,
                             C7_ACC,
                             C7_LBR,
                             C7_RBR,                   
                             C7_MLT,                            
                             C7_PLS,
                             C7_CMA,
                             C7_MIN,
                             C7_DPT,                             
                             C7_RS,
                             C7_0,   //48 0x30
                             C7_1,
                             C7_2,
                             C7_3,
                             C7_4,                   
                             C7_5,
                             C7_6,
                             C7_7,
                             C7_8,
                             C7_9,
                             C7_COL, //58 0x3A
                             C7_SCL,
                             C7_LT,
                             C7_EQ,
                             C7_GT,
                             C7_QM,                             
                             C7_AT,  //64 0x40
                             C7_A,   //65 0x41, A
                             C7_B,
                             C7_C,
                             C7_D,
                             C7_E,
                             C7_F,
                             C7_G,
                             C7_H,
                             C7_I,
                             C7_J,                   
                             C7_K,
                             C7_L,
                             C7_M,
                             C7_N,
                             C7_O,
                             C7_P,
                             C7_Q,
                             C7_R,
                             C7_S,
                             C7_T,
                             C7_U,
                             C7_V,
                             C7_W,
                             C7_X,
                             C7_Y,
                             C7_Z,   //90 0x5A, Z
                             C7_SBL, //91 0x5B
                             C7_LS,
                             C7_SBR,
                             C7_PWR,
                             C7_UDS,  
                             C7_ACC,                             
                             C7_A,   //97 0x61, A replacing a
                             C7_B,
                             C7_C,
                             C7_D,
                             C7_E,
                             C7_F,
                             C7_G,
                             C7_H,
                             C7_I,
                             C7_J,                   
                             C7_K,
                             C7_L,
                             C7_M,
                             C7_N,
                             C7_O,
                             C7_P,
                             C7_Q,
                             C7_R,
                             C7_S,
                             C7_T,
                             C7_U,
                             C7_V,
                             C7_W,
                             C7_X,
                             C7_Y,
                             C7_Z,   // 122 0x7A, Z replacing z
                             C7_CBL, // 123 0x7B
                             C7_OR,
                             C7_CBR,
                             C7_TLD,
                             C7_DEL  // 127                             
                        };
 


LM1640Display::LM1640Display(uint8_t pinClk, uint8_t pinDIO)
{
	// Copy the pin numbers
	m_pinClk = pinClk;
	m_pinDIO = pinDIO;

	// Set the pin direction and default value.
	// Both pins are set as inputs, allowing the pull-up resistors to pull them up
  pinMode(m_pinClk, INPUT);
  pinMode(m_pinDIO,INPUT);
	digitalWrite(m_pinClk, LOW);
	digitalWrite(m_pinDIO, LOW);
}



void LM1640Display::setBrightness(uint8_t brightness, bool on)
{
  m_brightness = (brightness & 0x7) | (on? 0x08 : 0x00);
}

void LM1640Display::clear(uint8_t length)
{
  setSegments(clr, length, 0);
}

void LM1640Display::setSegments(const uint8_t segments[], uint8_t length, uint8_t pos)
{
    // Write COMM1
	start();
	writeByte(TM1637_I2C_COMM1);
	stop();

	// Write COMM2 + first digit address
	start();
	writeByte(TM1637_I2C_COMM2 + (pos & 0x03));

	// Write the data bytes
	for (uint8_t k=0; k < length; k++)
	  writeByte(segments[k]);

	stop();

	// Write COMM3 + brightness
	start();
	writeByte(TM1637_I2C_COMM3 + (m_brightness & 0x0f));
	stop();
}

//void LM1640Display::showNumberDec(int num, bool leading_zero, uint8_t length, uint8_t pos)


void LM1640Display::showString(char str[]){
  // ensure str is 16 chars long
  uint8_t digits[SIZE];
  
  int to = min<int>(SIZE, strlen(str));
  for(int8_t k = 0; k < to; k++) {
   digits[k] = encodeChar(str[k]);
  }
  if (to < 16){
    for(int8_t k = to; k < 16; k++) {
      digits[k] = 0;
    }
  }
  setSegments(digits, 16, 0);
}

void LM1640Display::showNumberDec(int num, bool leading_zero, uint8_t length, uint8_t pos)
{
  uint8_t digits[length];
	const static int divisors[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000};
	bool leading = true;

  for(int8_t k = 0; k < length; k++) {
    if (leading_zero){
      digits[k] = encodeDigit(0);
    }
    else{
      digits[k] = 0;
    }
  }

  for(int8_t k = 5; k < 16; k++) {
	  int divisor = divisors[16 - k - 1];
		int d = num / divisor;
    uint8_t digit = 0;

		if (d == 0) {
		  if (leading_zero || !leading)
		      digit = encodeDigit(d);
	      else
		      digit = 0;
		}
		else {
			digit = encodeDigit(d);
			num -= d * divisor;
			leading = false;
		}
    digits[k] = digit;
	}
	setSegments(digits, length, pos);
}


void LM1640Display::bitDelay()
{
	delayMicroseconds(100);
}

void LM1640Display::start()
{
  pinMode(m_pinDIO, OUTPUT);
  bitDelay();
}

void LM1640Display::stop()
{
	pinMode(m_pinDIO, OUTPUT);  //LOW
	bitDelay();
	pinMode(m_pinClk, INPUT);  // HIGH
	bitDelay();
	pinMode(m_pinDIO, INPUT);   // HIGH
	bitDelay();
}

bool LM1640Display::writeByte(uint8_t b)
{
  uint8_t data = b;

  //Serial.print("DATA: ");
  //Serial.println(data);

  // 8 Data Bits
  for(uint8_t i = 0; i < 8; i++) {
    // CLK low
    pinMode(m_pinClk, OUTPUT);
    bitDelay();

    uint8_t heisan = data & 0x01;
   
	// Set data bit
    if (heisan)  // HIGH
      pinMode(m_pinDIO, INPUT);
    else  //LOW
      pinMode(m_pinDIO, OUTPUT);

    bitDelay();

	  // CLK high
    pinMode(m_pinClk, INPUT);
    bitDelay();
    data = data >> 1;
  }

  // CLK to zero
  pinMode(m_pinClk, OUTPUT);  // LOW
  bitDelay();
  return true;
}

uint8_t LM1640Display::encodeDigit(uint8_t digit)
{
  return digitToSegment[digit];
}

uint8_t LM1640Display::encodeChar(char ch)
{
  return FONT_7S[ch-32];
}




