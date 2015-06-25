#include <stdio.h>
#include "Communication.h"
#include "Signal.h"

void sendBitHigh(int pinNo){
  setPinHigh(pinNo);
  setPinLow(CLK_PIN);
  setPinHigh(CLK_PIN);
}

void sendBitLow(int pinNo){
  setPinLow(pinNo);
  setPinLow(CLK_PIN);
  setPinHigh(CLK_PIN);
}

/**
 *  @brief Perform write-to-read turnaround.
 *  @param pinNo is the pin to do turnaround
 *  @step 1) set IO pin as input
 *  @step 2) set CLK pin as low
 *  @step 3) set CLK pin as High
 */
void readTurnAroundIO(int pinNo){
  setPinToInput(pinNo);
  setPinLow(CLK_PIN);
  setPinHigh(CLK_PIN);
}

/**
 *  @brief Perform read-to-write turnaround.
 *  @param pinNo is the pin to do turnaround
 *  @step 1) set IO pin as output
 *  @step 2) set CLK pin as High
 *  @step 3) set CLK pin as Low
 */
void writeTurnAroundIO(int pinNo){
  setPinToOutput(pinNo);
  setPinHigh(CLK_PIN);
  setPinLow(CLK_PIN);
}

uint32_t readBit(int pinNo){
  setPinHigh(CLK_PIN);
  setPinLow(CLK_PIN);
  return getPin(pinNo);
}

void writeData(uint8_t data, uint16_t address, uint8_t cmd){
  int i;
  uint8_t newCmd, newData;
  uint16_t newAddress;

  // turn IO to Output
  writeTurnAroundIO(IO_PIN);

  // send data
  for (i=0; i<8; i++){
    newData = data & 0x01;
    if(newData == 1){
      sendBitHigh(IO_PIN);
    }
    else{
      sendBitLow(IO_PIN);
    }
    data = data >> 1;
  }

  // send address
  for (i=0; i<16; i++){
    newAddress = address & 0x0001;
    if(newAddress == 1){
      sendBitHigh(IO_PIN);
    }
    else{
      sendBitLow(IO_PIN);
    }
    address = address >> 1;
  }

  // send commend
  for (i=0; i<8; i++){
    newCmd = cmd & 0x01;
    if(newCmd == 1){
      sendBitHigh(IO_PIN);
    }
    else{
      sendBitLow(IO_PIN);
    }
    cmd = cmd >> 1;
  }
}

uint8_t readData(uint8_t cmd, uint16_t address){
  int i;
  uint8_t newCmd, data, getData;
  uint16_t newAddress;

  //  turn IO to Output
  writeTurnAroundIO(IO_PIN);

  // send address
  for (i=0; i<16; i++){
    newAddress = address & 0x0001;
    if(newAddress == 1){
      sendBitHigh(IO_PIN);
    }
    else{
      sendBitLow(IO_PIN);
    }
    address = address >> 1;
  }

  // send commend
  for (i=0; i<8; i++){
    newCmd = cmd & 0x01;
    if(newCmd == 1){
      sendBitHigh(IO_PIN);
    }
    else{
      sendBitLow(IO_PIN);
    }
    cmd = cmd >> 1;
  }

  // turn IO to Input
  readTurnAroundIO(IO_PIN);

  // read the bit at IO
  for (i=0; i<8; i++){
    data = readBit(IO_PIN);
    getData = getData | (data << i);
    printf("%d", getData);
  }

  return getData;
}