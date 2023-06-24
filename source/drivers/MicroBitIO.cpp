/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Modifications Copyright (c) 2016 Calliope gGmbH
Modifications are provided by DELTA Systems (Georg Sommer) - Thomas Kern
und Björn Eberhardt GbR by arrangement with Calliope GbR.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

/**
  * Class definition for MicroBit IO.
  *
  * Represents a collection of all I/O pins on the edge connector.
  */

#include "MicroBitConfig.h"
#include "MicroBitIO.h"

/**
  * Constructor.
  *
  * Create a representation of all given I/O pins on the edge connector
  *
  * Accepts a sequence of unique ID's used to distinguish events raised
  * by MicroBitPin instances on the default EventModel.
  */
MicroBitIO::MicroBitIO(int ID_P0, int ID_P1, int ID_P2,
                       int ID_P3, int ID_P4, int ID_P5,
                       int ID_P6, int ID_P7, int ID_P8,
                       int ID_P9, int ID_P10,int ID_P11,
                       int ID_P12,int ID_P13,int ID_P14,
                       int ID_P15,
// #ifdef TARGET_NRF51_CALLIOPE
                       int ID_A0SCL,
                       int ID_A0SDA,
                       int ID_A1RX,
                       int ID_A1TX,
                       int ID_MIC
// #else
//                       
//                       int ID_P16,
//                       int ID_P19,
//                       int ID_P20
// #endif
    ) :
    P0   (ID_P0,  MICROBIT_PIN_P0, PIN_CAPABILITY_ALL),     
    P1   (ID_P1,  MICROBIT_PIN_P1, PIN_CAPABILITY_ALL),     
    P2   (ID_P2,  MICROBIT_PIN_P2, PIN_CAPABILITY_ALL),     
    P3   (ID_P3,  MICROBIT_PIN_P3, PIN_CAPABILITY_STANDARD),     
    P4   (ID_P4,  MICROBIT_PIN_P4, PIN_CAPABILITY_ALL),     
    P5   (ID_P5,  MICROBIT_PIN_P5, PIN_CAPABILITY_ALL),
    P6   (ID_P6,  MICROBIT_PIN_P6, PIN_CAPABILITY_ALL),
    P7   (ID_P7,  MICROBIT_PIN_P7, PIN_CAPABILITY_STANDARD),
    P8   (ID_P8,  MICROBIT_PIN_P8, PIN_CAPABILITY_STANDARD),
    P9   (ID_P9,  MICROBIT_PIN_P9, PIN_CAPABILITY_STANDARD),
    P10  (ID_P10, MICROBIT_PIN_P10,PIN_CAPABILITY_STANDARD),     
    P11  (ID_P11, MICROBIT_PIN_P11,PIN_CAPABILITY_STANDARD),
    P12  (ID_P12, MICROBIT_PIN_P12,PIN_CAPABILITY_STANDARD),
    P13  (ID_P13, MICROBIT_PIN_P13,PIN_CAPABILITY_STANDARD),
    P14  (ID_P14, MICROBIT_PIN_P14,PIN_CAPABILITY_STANDARD),
    P15  (ID_P15, MICROBIT_PIN_P15,PIN_CAPABILITY_STANDARD),

    A0SCL(ID_A0SCL,MICROBIT_ID_A0_SCL,PIN_CAPABILITY_STANDARD),
    A0SDA(ID_A0SDA,MICROBIT_ID_A0_SDA,PIN_CAPABILITY_STANDARD),
    A1RX (ID_A1RX,MICROBIT_ID_A1_RX,PIN_CAPABILITY_ALL),
    A1TX (ID_A1TX,MICROBIT_ID_A1_TX,PIN_CAPABILITY_ALL),
   
    MICROPHONE(ID_MIC,MICROBIT_PIN_MICROPHONE,PIN_CAPABILITY_ANALOG_IN)

// #else
//   
//   P16(ID_P16,MICROBIT_PIN_P16,PIN_CAPABILITY_STANDARD),
//   P19(ID_P19,MICROBIT_PIN_P19,PIN_CAPABILITY_STANDARD),
//   P20(ID_P20,MICROBIT_PIN_P20,PIN_CAPABILITY_STANDARD) 
// #endif
{
}
