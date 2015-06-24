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



void test_writeData_given_0xCD_and_addr_0xDEAD_and_data_0xC0_should_sent_out_0xC0DECDCD(){





  setPinToOutput_CMockExpect(38, 4);

  setPinHigh_CMockExpect(39, 5);

  setPinLow_CMockExpect(40, 5);



  int i;

  int data1 = 0xCD;

  int data2 = 0xDEAD;

  int data3 = 0xC0;

  int dataShift = 0xC0DECDCD >> 1;



  for (i=31; i>0; i--){

    if (dataShift & 0x0001 == 1){





      sendBitHigh(4);

    }

    else

      sendBitLow(4);

    dataShift = dataShift >> 1;

    printf("%d", dataShift);

  }

  writeData(data3, data2, data1);

}



void test_readData_given_0xAB_and_addr_0xFACE_should_sent_out_0xABFACE_and_turnaround_and_receive_0xBE(){





  setPinToInput_CMockExpect(65, 4);

  setPinToOutput_CMockExpect(66, 4);

  setPinHigh_CMockExpect(67, 5);

  setPinLow_CMockExpect(68, 5);





}
