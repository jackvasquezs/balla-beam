////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  File: arduino.ino                                                                                                     //
//  Date: 5/12/2020                                                                                                  //
//  Copyright (c) 1989-2020 Altair Engineering Inc. All Rights Reserved. Contains trade secrets of Altair Engineering Inc.          //
//  Copyright notice does not imply publication. Decompilation or disassembly of this software is strictly prohibited.//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* This file is used by Activate to communicate with the Arduino board during simulation

 */  


#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define INTERNAL INTERNAL1V1
#endif

#define ACT_SIMULATION_MODE 1

#include "src/types.h"
#include "src/serial.h"
#include "src/pin.h"
#include "src/digital.h"
#include "src/analog.h"
#include "src/servo.h"
#include "src/touchscreen.h"
#include "src/uart.h"
#include "src/i2c.h"
#include "src/spi.h"
#include "src/mpu6050.h"
#include "src/lcd.h"
#include "src/rotaryencoder.h"

void setup() {                                      
    Serial.begin(115200);
}

void loop() {
    int  val =  0;            
    if (Serial.available() > 0) {
        val = read_uint8();
        switch (val) {
        case ANALOG_N : {
            ActAnalog::loop();
            break;
        }
        case I2C_N : {
            ActI2C::loop();
            break;
        }
        case DIGITAL_N : {
            ActDigital::loop();
            break;
        }
        case MPU6050_N : {
            ActMPU6050::loop();
            break;
        }
        case SPI_N : {
            ActSPI::loop();
            break;
        }
        case SERVO_N : {
            ActServo::loop();
            break;
        }
        case TOUCHSCREEN_N : {
            ActTouchScreen::loop();
            break;
        }
        case UART_N : {
            ActUART::loop();
            break;
        }
        case LCD_N : {
            ActLCD::loop();
            break;
        }
        case ROTARYENCODER_N : {
            ActRotaryEncoder::loop();
            break;
        }
        }
        val=-1;
    }
}
