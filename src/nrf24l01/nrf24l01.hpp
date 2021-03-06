/*
 * Author: Yevgeniy Kiveisha <yevgeniy.kiveisha@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 * BLE Beaconing based on http://dmitry.gr/index.php?r=05.Projects&proj=11.%20Bluetooth%20LE%20fakery
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <string>
#include <mraa/aio.hpp>
#include <mraa/common.hpp>

#include <mraa/gpio.hpp>

#include <mraa/spi.hpp>
#include <cstring>

#if defined(SWIGJAVA) || defined(JAVACALLBACK)
#include "Callback.hpp"
#endif

/* Memory Map */
#define CONFIG              0x00
#define EN_AA               0x01
#define EN_RXADDR           0x02
#define SETUP_AW            0x03
#define SETUP_RETR          0x04
#define RF_CH               0x05
#define RF_SETUP            0x06
#define STATUS              0x07
#define OBSERVE_TX          0x08
#define CD                  0x09
#define RX_ADDR_P0          0x0A
#define RX_ADDR_P1          0x0B
#define RX_ADDR_P2          0x0C
#define RX_ADDR_P3          0x0D
#define RX_ADDR_P4          0x0E
#define RX_ADDR_P5          0x0F
#define TX_ADDR             0x10
#define RX_PW_P0            0x11
#define RX_PW_P1            0x12
#define RX_PW_P2            0x13
#define RX_PW_P3            0x14
#define RX_PW_P4            0x15
#define RX_PW_P5            0x16
#define FIFO_STATUS         0x17
#define DYNPD               0x1C
#define FEATURE             0x1D

/* Bit Mnemonics */
#define MASK_RX_DR          6
#define MASK_TX_DS          5
#define MASK_MAX_RT         4
#define EN_CRC              3
#define CRCO                2
#define PWR_UP              1
#define PRIM_RX             0
#define ENAA_P5             5
#define ENAA_P4             4
#define ENAA_P3             3
#define ENAA_P2             2
#define ENAA_P1             1
#define ENAA_P0             0
#define ERX_P5              5
#define ERX_P4              4
#define ERX_P3              3
#define ERX_P2              2
#define ERX_P1              1
#define ERX_P0              0
#define AW                  0
#define ARD                 4
#define ARC                 0
#define PLL_LOCK            4
#define RF_DR               3
#define RF_PWR              1
#define LNA_HCURR           0
#define RX_DR               6
#define TX_DS               5
#define MAX_RT              4
#define RX_P_NO             1
#define TX_FULL             0
#define PLOS_CNT            4
#define ARC_CNT             0
#define TX_REUSE            6
#define FIFO_FULL           5
#define TX_EMPTY            4
#define RX_FULL             1
#define RX_EMPTY            0

/* Instruction Mnemonics */
#define R_REGISTER            0x00
#define W_REGISTER            0x20
#define REGISTER_MASK         0x1F
#define R_RX_PAYLOAD          0x61
#define W_TX_PAYLOAD          0xA0
#define FLUSH_TX              0xE1
#define FLUSH_RX              0xE2
#define REUSE_TX_PL           0xE3
#define NOP                   0xFF

#define RF_DR_LOW   5
#define RF_DR_HIGH  3
#define RF_PWR_LOW  1
#define RF_PWR_HIGH 2

/* Nrf24l settings */
#define ADDR_LEN        5
#define _CONFIG         ((1<<EN_CRC) | (0<<CRCO) )

#define MAX_BUFFER            32

#define HIGH                  1
#define LOW                    0

/* BLE beaconing */
#define BLE_MAC_0           0xEF
#define BLE_MAC_1           0xFF
#define BLE_MAC_2           0xC0
#define BLE_MAC_3           0xAA
#define BLE_MAC_4           0x18
#define BLE_MAC_5           0x00

#define BLE_PAYLOAD_OFFSET  13

namespace upm {

#if defined(SWIGJAVA) || defined(JAVACALLBACK)
typedef void (* funcPtrVoidVoid) (Callback *);
#else
typedef void (* funcPtrVoidVoid) ();
#endif

typedef enum {
    NRF_250KBPS = 0,
    NRF_1MBPS   = 1,
    NRF_2MBPS   = 2,
} speed_rate_t;

typedef enum {
    NRF_0DBM    = 0,
    NRF_6DBM    = 1,
    NRF_12DBM   = 2,
    NRF_18DBM   = 3,
} power_t;

/**
 * @brief NRF24L01 Transceiver library
 * @defgroup nrf24l01 libupm-nrf24l01
 * @ingroup seeed sparkfun spi wifi
 */
/**
 * @library nrf24l01
 * @sensor nrf24l01
 * @comname NRF24L01 Transceiver
 * @type wifi
 * @man seeed sparkfun
 * @web http://www.seeedstudio.com/depot/nRF24L01Module-p-1394.html
 * @con spi
 *
 * id
 * @brief API for the NRF24L01 Transceiver Module
 *
 * This module defines the NRF24L01 interface for libnrf24l01
 *
 * @image html nrf24l01.jpg
 * @snippet nrf24l01-receiver.cxx Interesting
 * @snippet nrf24l01-transmitter.cxx Interesting
 * @snippet nrf24l01-broadcast.cxx Interesting
 */
class NRF24L01 {
    public:
        /**
         * Instantiates an NRF24l01 object
         *
         * @param cs Chip select pin
         */
        NRF24L01 (uint8_t cs, uint8_t ce);

        /**
         * Returns the name of the component
         */
        std::string name()
        {
            return m_name;
        }

        /**
         * Initializes needed GPIO pins and SPI
         *
         * @param chipSelect Sets up the chip select pin
         * @param chipEnable Sets up the chip enable pin
         */
        void    init (uint8_t chipSelect, uint8_t chipEnable);

        /**
         * Configures the NRF24L01 transceiver
         */
        void    configure ();

        /**
         * Sends the buffer data
         *
         * @param *value Pointer to the buffer
         */
        void    send (uint8_t * value);

        /**
         * Sends the data located in an inner bufer; the user must fill the
         * m_txBuffer buffer
         */
        void    send ();

        /**
         * Sets a receiving address of the device
         *
         * @param addr 5-byte address
         */
        void    setSourceAddress (uint8_t * addr);

        /**
         * Sets a recipient address. The nrfSend method sends the data buffer
         * to this address
         *
         * @param addr 5-byte address
         */
        void    setDestinationAddress (uint8_t * addr);

        /**
         * Sets a broadcasting address
         *
         * @param addr 5-byte address
         */
        void    setBroadcastAddress (uint8_t * addr);

        /**
         * Sets the payload size
         *
         * @param load Size of the payload (MAX 32)
         */
        void    setPayload (uint8_t load);

#if defined(SWIGJAVA) || defined(JAVACALLBACK)
        /**
         * Sets the handler to be called when data has been
         * received
         * @param call_obj Object used for callback - Java
         */
        void setDataReceivedHandler (Callback *call_obj);
#else
        /**
         * Sets the handler to be called when data has been
         * received
         * @param handler Handler used for callback
         */
        void setDataReceivedHandler (funcPtrVoidVoid handler);
#endif
        /**
         * Checks if the data has arrived
         */
        bool    dataReady ();

        /**
         * Checks if the transceiver is in the sending mode
         */
        bool    dataSending ();

        /**
         * Sinks all the arrived data into a provided buffer
         *
         * @param load Size of the payload (MAX 32)
         */
        void    getData (uint8_t * data);

        /**
         * Checks the transceiver state
         */
        uint8_t getStatus ();

        /**
         * Checks if the receive stack is empty
         */
        bool    rxFifoEmpty ();

        /**
         * Powers the receiver up
         */
        void    rxPowerUp ();

        /**
         * Flushes the receive stack
         */
        void    rxFlushBuffer ();

        /**
         * Powers the transmitter up
         */
        void    txPowerUp ();

        /**
         * Powers everything down
         */
        void    powerDown ();

        void    setChannel (uint8_t channel);

        void    setPower (power_t power);

        uint8_t setSpeedRate (speed_rate_t rate);

        /**
         * Flushes the transmit stack
         */
        void    txFlushBuffer ();

        /**
         * Pulling the method listening for the arrived data,
         * dataRecievedHandler is triggered if data arrives
         */
        void    pollListener ();

        /**
         * Sets the chip enable pin to HIGH
         */
        mraa::Result ceHigh ();

        /**
         * Sets the chip enable pin to LOW
         */
        mraa::Result ceLow ();

        /**
         * Sets the chip select pin to LOW
         */
        mraa::Result csOn ();

        /**
         * Sets the chip select pin to HIGH
         */
        mraa::Result csOff ();

        /**
         * Configures the NRF24L01 transceiver to behave as a BLE
         * (Bluetooth Low Energy) beaconing devcie.
         */
        void setBeaconingMode ();

        /**
         * Beacons the provided message to BLE scanners.
         *
         * @param msg Beacons the provided message (max length is 16 bytes)
         */
        void sendBeaconingMsg (uint8_t * msg);

        uint8_t     m_rxBuffer[MAX_BUFFER]; /**< Receive buffer */
        uint8_t     m_txBuffer[MAX_BUFFER]; /**< Transmit buffer */
        uint8_t     m_bleBuffer [32];       /**< BLE buffer */

    private:
#if defined(SWIGJAVA) || defined(JAVACALLBACK)
        /**< Callback object to use for setting the handler from Java */
        Callback *callback_obj;
#endif
        funcPtrVoidVoid dataReceivedHandler; /**< Data arrived handler */

        /**
         * Writes bytes to an SPI device
         */
        void    writeBytes (uint8_t * dataout, uint8_t * datain, uint8_t len);
        /**
         * Sets the register value on an SPI device [one byte]
         */
        void    setRegister (uint8_t reg, uint8_t value);
        /**
         * Gets the register value from an SPI device [one byte]
         */
        uint8_t getRegister (uint8_t reg);
        /**
         * Reads an array of bytes from the given starting position in NRF24L01 registers
         */
        void    readRegister (uint8_t reg, uint8_t * value, uint8_t len);
        /**
         * Writes an array of bytes into NRF24L01 registers
         */
        void    writeRegister (uint8_t reg, uint8_t * value, uint8_t len);
        /**
         * Sends a command to NRF24L01
         */
        void    sendCommand (uint8_t cmd);

        void bleCrc (const uint8_t* data, uint8_t len, uint8_t* dst);

        void bleWhiten (uint8_t* data, uint8_t len, uint8_t whitenCoeff);

        void blePacketEncode(uint8_t* packet, uint8_t len, uint8_t chan);

        uint8_t swapbits (uint8_t a);

        mraa::Spi               m_spi;
        uint8_t                 m_ce;
        uint8_t                 m_csn;
        uint8_t                 m_channel;
        uint8_t                 m_power;
        uint8_t                 m_ptx;
        uint8_t                 m_payload;
        uint8_t                 m_localAddress[5];

        mraa::Gpio              m_csnPinCtx;
        mraa::Gpio              m_cePinCtx;

        std::string             m_name;
};

}
