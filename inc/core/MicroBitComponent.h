/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

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

==================
Modifications Copyright (c) 2016 Calliope GbR
Modifications are provided by DELTA Systems (Georg Sommer) - Thomas Kern
und Björn Eberhardt GbR by arrangement with Calliope GbR.
*/

#ifndef MICROBIT_COMPONENT_H
#define MICROBIT_COMPONENT_H

#include "MicroBitConfig.h"

// Enumeration of core components.
#define MICROBIT_ID_BUTTON_A            1
#define MICROBIT_ID_BUTTON_B            2
#define MICROBIT_ID_BUTTON_AB           3           // Button A+B multibutton
#define MICROBIT_ID_BUTTON_RESET        4
#define MICROBIT_ID_ACCELEROMETER       5
#define MICROBIT_ID_COMPASS             6
#define MICROBIT_ID_DISPLAY             7
#define MICROBIT_ID_THERMOMETER         8
#define MICROBIT_ID_RADIO               9
#define MICROBIT_ID_RADIO_DATA_READY    10
#define MICROBIT_ID_MULTIBUTTON_ATTACH  11
#define MICROBIT_ID_SERIAL              12
#define MICROBIT_ID_GESTURE             13          // Gesture events

#define MICROBIT_ID_IO_P0               100
#define MICROBIT_ID_IO_P1               101
#define MICROBIT_ID_IO_P2               102
#define MICROBIT_ID_IO_P3               103
#define MICROBIT_ID_IO_P4               104
#define MICROBIT_ID_IO_P5               105
#define MICROBIT_ID_IO_P6               106
#define MICROBIT_ID_IO_P7               107
#define MICROBIT_ID_IO_P8               108
#define MICROBIT_ID_IO_P9               109
#define MICROBIT_ID_IO_P10              110
#define MICROBIT_ID_IO_P11              111
#define MICROBIT_ID_IO_P12              112
#define MICROBIT_ID_IO_P13              113
#define MICROBIT_ID_IO_P14              114
#define MICROBIT_ID_IO_P15              115
#define MICROBIT_ID_IO_A1_RX            116
#define MICROBIT_ID_IO_A1_TX            117
#define MICROBIT_ID_IO_P18              118 // dummy to align with codal / not used in mini 1 & 2
#define MICROBIT_ID_IO_A0_SCL           119
#define MICROBIT_ID_IO_A0_SDA           120
#define MICROBIT_ID_LOGO                121 // MIC

#define MICROBIT_ID_IO_INT1             130         //INT1
#define MICROBIT_ID_IO_INT2             131         //INT2
#define MICROBIT_ID_IO_INT3             132         //INT3

#define MICROBIT_ID_IO_RGB              151
#define MICROBIT_ID_IO_M_A_IN1          152
#define MICROBIT_ID_IO_M_A_IN2          153
#define MICROBIT_ID_IO_M_B_IN1          154
#define MICROBIT_ID_IO_M_B_IN2          155
#define MICROBIT_ID_IO_M_MODE           156

// System Softwarre components
#define MICROBIT_ID_PARTIAL_FLASHING                200

#define MICROBIT_ID_MESSAGE_BUS_LISTENER            1021          // Message bus indication that a handler for a given ID has been registered.
#define MICROBIT_ID_NOTIFY_ONE                      1022          // Notfication channel, for general purpose synchronisation
#define MICROBIT_ID_NOTIFY                          1023          // Notfication channel, for general purpose synchronisation

// Universal flags used as part of the status field
#define MICROBIT_COMPONENT_RUNNING		0x01


/**
  * Class definition for MicroBitComponent.
  *
  * All components should inherit from this class.
  *
  * If a component requires regular updates, then that component can be added to the 
  * to the systemTick and/or idleTick queues. This provides a simple, extensible mechanism
  * for code that requires periodic/occasional background processing but does not warrant
  * the complexity of maintaining its own thread. 
  *
  * Two levels of support are available. 
  *
  * systemTick() provides a periodic callback during the
  * micro:bit's system timer interrupt. This provides a guaranteed periodic callback, but in interrupt context
  * and is suitable for code with lightweight processing requirements, but strict time constraints.
  * 
  * idleTick() provides a periodic callback whenever the scheduler is idle. This provides occasional, callbacks
  * in the main thread context, but with no guarantees of frequency. This is suitable for non-urgent background tasks.
  *
  * Components wishing to use these facilities should override the systemTick and/or idleTick functions defined here, and
  * register their components using system_timer_add_component() fiber_add_idle_component() respectively.
  *
  */
class MicroBitComponent
{
    protected:

    uint16_t id;                    // Event Bus ID of this component
    uint8_t status;                 // Component defined state.

    public:

    /**
      * The default constructor of a MicroBitComponent
      */
    MicroBitComponent()
    {
        this->id = 0;
        this->status = 0;
    }

    /**
      * The system timer will call this member function once the component has been added to
      * the array of system components using system_timer_add_component. This callback
      * will be in interrupt context.
      */
    virtual void systemTick()
    {
    }

    /**
      * The idle thread will call this member function once the component has been added to the array
      * of idle components using fiber_add_idle_component. 
      */
    virtual void idleTick()
    {
    }

    /**
      * If you have added your component to the idle or system tick component arrays,
      * you must remember to remove your component from them if your component is destructed.
      */
    virtual ~MicroBitComponent()
    {
    }
};

#endif
