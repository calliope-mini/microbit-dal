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
*/

/**
  * Class definition for MicroBitLightSensor.
  *
  * This is an object that interleaves light sensing with MicroBitDisplay.
  */

#include "MicroBitConfig.h"
#include "MicroBitLightSensor.h"
#include "MicroBitDisplay.h"

/**
  * After the startSensing method has been called, this method will be called
  * MICROBIT_LIGHT_SENSOR_AN_SET_TIME after.
  *
  * It will then read from the currently selected channel using the AnalogIn
  * that was configured in the startSensing method.
  */
void MicroBitLightSensor::analogReady()
{
    this->results[chan] = this->sensePin->read_u16();

    analogDisable();

    DigitalOut((PinName)(matrixMap.columnStart + chan)).write(1);

    chan++;

    chan = chan % MICROBIT_LIGHT_SENSOR_CHAN_NUM;
}



/**
  * Constructor.
  *
  * Create a representation of the light sensor.
  *
  * @param map The mapping information that relates pin inputs/outputs to physical screen coordinates.
  *            Defaults to microbitMatrixMap, defined in MicroBitMatrixMaps.h.
  */
MicroBitLightSensor::MicroBitLightSensor(const MatrixMap &map) :
    analogTrigger(),
    matrixMap(map)
{
    this->chan = 0;

    for(int i = 0; i < MICROBIT_LIGHT_SENSOR_CHAN_NUM; i++)
        results[i] = 0;

    if (EventModel::defaultEventBus)
        EventModel::defaultEventBus->listen(MICROBIT_ID_DISPLAY, MICROBIT_DISPLAY_EVT_LIGHT_SENSE, this, &MicroBitLightSensor::startSensing, MESSAGE_BUS_LISTENER_IMMEDIATE);

    this->sensePin = NULL;
}

/**
  * This method returns a summed average of the three sections of the display.
  *

  *
  * Where each number represents a different section on the 5 x 5 matrix display.
  *
  * @return returns a value in the range 0 - 255 where 0 is dark, and 255
  * is very bright
  */
int MicroBitLightSensor::read()
{
    int sum = 0;

    for(int i = 0; i < MICROBIT_LIGHT_SENSOR_CHAN_NUM; i++)
        sum += results[i];

    int average = sum / MICROBIT_LIGHT_SENSOR_CHAN_NUM;

    average = min(average, MICROBIT_LIGHT_SENSOR_MAX_VALUE);

    average = max(average, MICROBIT_LIGHT_SENSOR_MIN_VALUE);

    int inverted = (MICROBIT_LIGHT_SENSOR_MAX_VALUE - average) + MICROBIT_LIGHT_SENSOR_MIN_VALUE;

    int a = 0;

    int b = 255;

    int normalised = a + ((((inverted - MICROBIT_LIGHT_SENSOR_MIN_VALUE)) * (b - a))/ (MICROBIT_LIGHT_SENSOR_MAX_VALUE - MICROBIT_LIGHT_SENSOR_MIN_VALUE));

    return normalised;
}

/**
  * The method that is invoked by sending MICROBIT_DISPLAY_EVT_LIGHT_SENSE
  * using the id MICROBIT_ID_DISPLAY.
  *
  * @note this can be manually driven by calling this member function, with
  *       a MicroBitEvent using the CREATE_ONLY option of the MicroBitEvent
  *       constructor.
  */
void MicroBitLightSensor::startSensing(MicroBitEvent)
{
    for(int rowCount = 0; rowCount < matrixMap.rows; rowCount++)
        DigitalOut((PinName)(matrixMap.rowStart + rowCount)).write(0);

    PinName currentPin = (PinName)(matrixMap.columnStart + chan);

    DigitalOut(currentPin).write(1);

    DigitalIn(currentPin, PullNone).~DigitalIn();

    if(this->sensePin != NULL)
        delete this->sensePin;

    this->sensePin = new AnalogIn(currentPin);

    analogTrigger.attach_us(this, &MicroBitLightSensor::analogReady, MICROBIT_LIGHT_SENSOR_AN_SET_TIME);
}

/**
  * A destructor for MicroBitLightSensor.
  *
  * The destructor removes the listener, used by MicroBitLightSensor from the default EventModel.
  */
MicroBitLightSensor::~MicroBitLightSensor()
{
    if (EventModel::defaultEventBus)
        EventModel::defaultEventBus->ignore(MICROBIT_ID_DISPLAY, MICROBIT_DISPLAY_EVT_LIGHT_SENSE, this, &MicroBitLightSensor::startSensing);
}
