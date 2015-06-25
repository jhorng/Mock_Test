#include <stdint.h>
#include <stdio.h>
#include "unity.h"
#include "Communication.h"
#include "mock_Signal.h"

void setUp(void) {}

void tearDown(void) {}

void test_sendBitHigh_given_xxx_should_xxxx(){
  setPinHigh_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);

  sendBitHigh(IO_PIN);
}

void test_sendBitLow_given_xxx_should_xxxx(){
  setPinLow_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);

  sendBitLow(IO_PIN);
}

void test_readBit_given_xxx_should_xxxx(){
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 1);

  readBit(IO_PIN);
}

void test_writeTurnAround_given_input_become_output(){
  setPinToOutput_Expect(IO_PIN);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);

  writeTurnAroundIO(IO_PIN);
}

void test_readTurnAround_given_input_become_input(void){
  setPinToInput_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);

  readTurnAroundIO(IO_PIN);
}

/* void test(){
  uint8_t data1, data3;
  uint32_t data2;
  int i;
  data1 = 0xCD;
  data2 = 0xDEAD;
  data3 = 0xC0;
  for (i=0; i<8; i++){
    if(data1 & 0x01 >> 1 == 1){
      printf("%d\n", data1);
      data1 & 0x01;
      data1 = data1 >> 1;
    }
    else{
      printf("%d\n", data1);
      data1 & 0x01;
      data1 = data1 >> 1;
    }
  }

  for (i=0; i<16; i++){
    if(data2 & 0x01 >> 1 == 1){
      printf("%d\n", data2);
      data2 & 0x01;
      data2 = data2 >> 1;
    }
    else{
      printf("%d\n", data2);
      data2 & 0x01;
      data2 = data2 >> 1;
    }
  }

  for (i=0; i<8; i++){
    if(data3 & 0x01 >> 1 == 1){
      printf("%d\n", data3);
      data3 & 0x01;
      data3 = data3 >> 1;
    }
    else{
      printf("%d\n", data3);
      data3 & 0x01;
      data3 = data3 >> 1;
    }
  }

  writeData(0xCD, 0xDEAD, 0xC0);
} */

void test(void){
  int i;
  uint32_t fullData1, fullData2;
  fullData1 = 0xCDDEADC0;

  setPinToOutput_Expect(IO_PIN);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);

  for (i=0; i<32; i++){
    fullData2 = fullData1 & 0x00000001;
    if (fullData2 == 0){
      setPinLow_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    else{
      setPinHigh_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    fullData1 = fullData1 >> 1;
  }
  writeData(0xC0, 0xDEAD, 0xCD);
}
