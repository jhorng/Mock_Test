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
void readTurnaroundIO(int pinNo){
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
void writeTurnaroundIO(int pinNo){
  setPinToOutput(pinNo);
  setPinHigh(CLK_PIN);
  setPinLow(CLK_PIN);
}


uint32_t readBit(int pinNo){
  setPinHigh(5);
  setPinLow(5);
  return getPin(pinNo);
}

void writeData(uint8_t data, uint16_t address, uint8_t cmd){
  int i;
  writeTurnaroundIO(IO_PIN);
  
  // cmd = 0xCD
  for (i=0; i<8; i++){
    if (cmd&0x0001 == 1){
      sendBitHigh(IO_PIN);
      cmd&0x0001;
      cmd = cmd>>1;
    }
    else{
      sendBitLow(IO_PIN);
      cmd&0x0001;
      cmd = cmd>>1;
    }
  }
  
  // address = 0xDEAD
  for(i=0; i<16; i++){
    if (address&0x0001 == 1){
      sendBitHigh(IO_PIN);
      address&0x0001;
      address = address>>1;
    }
    else{
      sendBitLow(IO_PIN);
      address&0x0001;
      address = address>>1;
    }
  }
  
  // data = 0xC0
  for (i=0; i<8; i++){
    if (data&0x0001 == 1){
      sendBitHigh(IO_PIN);
      data&0x0001;
      data = data>>1;
    }
    else{
      sendBitLow(IO_PIN);
      data&0x00000001;
      data = data>>1;
    }
  }
}


uint8_t readData(uint8_t cmd, uint16_t address){
  int i;
  int data;
  writeTurnaroundIO(IO_PIN);
  
  // cmd = 0xAB
  for (i=0; i<8; i++){
    if (cmd&0x0001 == 1){
      cmd&0x0001;
      cmd = cmd>>1;
    }
    else{
      cmd&0x00000001;
      cmd = cmd>>1;
    }
  }
  
  // address = 0xFACE
  for(i=0; i<16; i++){
    if (address&0x0001 == 1){
      address&0x0001;
      address = address>>1;
    }
    else{
      address&0x0001;
      address = address>>1;
    }
  }
  
  readTurnaroundIO(IO_PIN);
  data = readBit(IO_PIN);
  // data = 0xBE
  for (i=0; i<8; i++){
    if (data&0x0001 == 1){
      data&0x0001;
      data = data<<i;
    }
    else{
      data&0x0001;
      data = data<<i;
    }
  }
  return data;
  
  
}