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



void test_writeData_given_0xCD_and_addr_0xDEAD_and_data_0xC0_should_send_out_0xCDDEADC0(void){

  int i;

  uint32_t fullData1, fullData2;

  fullData1 = 0xCDDEADC0;



  setPinToOutput_CMockExpect(56, 4);

  setPinHigh_CMockExpect(57, 5);

  setPinLow_CMockExpect(58, 5);



  for (i=0; i<32; i++){

    fullData2 = fullData1 & 0x00000001;

    if (fullData2 == 0){

      setPinLow_CMockExpect(63, 4);

      setPinLow_CMockExpect(64, 5);

      setPinHigh_CMockExpect(65, 5);

    }

    else{

      setPinHigh_CMockExpect(68, 4);

      setPinLow_CMockExpect(69, 5);

      setPinHigh_CMockExpect(70, 5);

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



  setPinToOutput_CMockExpect(83, 4);

  setPinHigh_CMockExpect(84, 5);

  setPinLow_CMockExpect(85, 5);



  for (i=0; i<24; i++){

    fullData2 = fullData1 & 0x000001;

    if (fullData2 == 0){

      setPinLow_CMockExpect(90, 4);

      setPinLow_CMockExpect(91, 5);

      setPinHigh_CMockExpect(92, 5);

    }

    else{

      setPinHigh_CMockExpect(95, 4);

      setPinLow_CMockExpect(96, 5);

      setPinHigh_CMockExpect(97, 5);

    }

    fullData1 = fullData1 >> 1;

  }



  setPinToInput_CMockExpect(102, 4);

  setPinLow_CMockExpect(103, 5);

  setPinHigh_CMockExpect(104, 5);



  setPinHigh_CMockExpect(106, 5);

  setPinLow_CMockExpect(107, 5);

  getPin_CMockExpectAndReturn(108, 4, 0);

  setPinHigh_CMockExpect(109, 5);

  setPinLow_CMockExpect(110, 5);

  getPin_CMockExpectAndReturn(111, 4, 1);

  setPinHigh_CMockExpect(112, 5);

  setPinLow_CMockExpect(113, 5);

  getPin_CMockExpectAndReturn(114, 4, 1);

  setPinHigh_CMockExpect(115, 5);

  setPinLow_CMockExpect(116, 5);

  getPin_CMockExpectAndReturn(117, 4, 1);

  setPinHigh_CMockExpect(118, 5);

  setPinLow_CMockExpect(119, 5);

  getPin_CMockExpectAndReturn(120, 4, 1);

  setPinHigh_CMockExpect(121, 5);

  setPinLow_CMockExpect(122, 5);

  getPin_CMockExpectAndReturn(123, 4, 1);

  setPinHigh_CMockExpect(124, 5);

  setPinLow_CMockExpect(125, 5);

  getPin_CMockExpectAndReturn(126, 4, 0);

  setPinHigh_CMockExpect(127, 5);

  setPinLow_CMockExpect(128, 5);

  getPin_CMockExpectAndReturn(129, 4, 1);



  data = readData(0xAB, 0xFACE);



  UnityAssertEqualNumber((_U_SINT)((190)), (_U_SINT)((data)), (((void *)0)), (_U_UINT)133, UNITY_DISPLAY_STYLE_INT);

}
