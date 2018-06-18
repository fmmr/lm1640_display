Library to display digits and strings on a JY-LM1640 using a esp8266.  Tested on wemos d1 mini.


create a directory under /.../Arduino/libraries and download the h- and cpp-files.  Restart arduino.  You should be good to go:

```
#include <LM1640Display.h>

const int CLK = D6; //Set the CLK pin connection to the display
const int DIO = D5; //Set the DIO pin connection to the display
 
int numCounter = 0;
 
LM1640Display display(CLK, DIO); //set up the 4-Digit Display.

void setup()
{
  Serial.begin(115200);
  display.setBrightness(7); //set the diplay to maximum brightness
  display.showString("STARING UP"); 
}

void loop()
{
 for(numCounter = 0; numCounter < 1000; numCounter++) //Iterate numCounter
 {
    display.showNumberDec(numCounter, false); //Display the numCounter value;
    delay(200);
  }
}
```
