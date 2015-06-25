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

void test_writeData_given_0xCD_and_addr_0xDEAD_and_data_0xC0_should_send_out_0xCDDEADC0(void){
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

void test_readData_given_0xAB_and_addr_0xFACE_should_send_0xABFACE_and_turnaround_and_receive_0xBE(){
  int i;
  uint8_t data;
  uint32_t fullData1, fullData2;
  fullData1 = 0xABFACE;

  setPinToOutput_Expect(IO_PIN);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);

  for (i=0; i<24; i++){
    fullData2 = fullData1 & 0x000001;
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

  setPinToInput_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);

  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 0);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 1);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 1);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 1);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 1);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 1);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 0);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  getPin_ExpectAndReturn(IO_PIN, 1);

  data = readData(0xAB, 0xFACE);

  TEST_ASSERT_EQUAL(190, data); // 190 = 0xBE
}