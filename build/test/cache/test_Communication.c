#include "mock_Signal.h"
#include "Communication.h"
#include "unity.h"


void setUp(void) {}



void tearDown(void) {}



void test_sendBitHigh_given_xxx_should_xxxx(){

  setPinHigh_CMockExpect(12, 4);

  setPinLow_CMockExpect(13, 5);

  setPinHigh_CMockExpect(14, 5);



  sendBitHigh(4);

}



void test_sendBitLow_given_xxx_should_xxxx(){

  setPinLow_CMockExpect(20, 4);

  setPinLow_CMockExpect(21, 5);

  setPinHigh_CMockExpect(22, 5);



  sendBitLow(4);

}



void test_readBit_given_xxx_should_xxxx(){

  setPinHigh_CMockExpect(28, 5);

  setPinLow_CMockExpect(29, 5);

  getPin_CMockExpectAndReturn(30, 4, 1);



  readBit(4);

}



void test_writeTurnAround_given_input_become_output(){

  setPinToOutput_CMockExpect(36, 4);

  setPinHigh_CMockExpect(37, 5);

  setPinLow_CMockExpect(38, 5);



  writeTurnAroundIO(4);

}



void test_readTurnAround_given_input_become_input(void){

  setPinToInput_CMockExpect(44, 4);

  setPinLow_CMockExpect(45, 5);

  setPinHigh_CMockExpect(46, 5);



  readTurnAroundIO(4);

}

void test(void){

  int i;

  uint32_t fullData1, fullData2;

  fullData1 = 0xCDDEADC0;



  setPinToOutput_CMockExpect(105, 4);

  setPinHigh_CMockExpect(106, 5);

  setPinLow_CMockExpect(107, 5);



  for (i=0; i<32; i++){

    fullData2 = fullData1 & 0x00000001;

    if (fullData2 == 0){

      setPinLow_CMockExpect(112, 4);

      setPinLow_CMockExpect(113, 5);

      setPinHigh_CMockExpect(114, 5);

    }

    else{

      setPinHigh_CMockExpect(117, 4);

      setPinLow_CMockExpect(118, 5);

      setPinHigh_CMockExpect(119, 5);

    }

    fullData1 = fullData1 >> 1;

  }

  writeData(0xC0, 0xDEAD, 0xCD);

}
