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

void test_writeData_given_0xCD_and_addr_0xDEAD_and_data_0xC0_should_sent_out_0xC0DECDCD(){
	// Your test code here...
  
  setPinToOutput_Expect(IO_PIN);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  
  int i;
  int data1 = 0xCD;
  int data2 = 0xDEAD;
  int data3 = 0xC0;
  int dataShift = 0xC0DECDCD >> 1;  
  
  for (i=31; i>0; i--){
    if (dataShift & 0x0001 == 1){
      // setPinHigh_Expect(CLK_PIN);
      // setPinLow_Expect(CLK_PIN);
      sendBitHigh(IO_PIN);
    }
    else
      sendBitLow(IO_PIN);
    dataShift = dataShift >> 1;
    printf("%d", dataShift);
  }
  writeData(data3, data2, data1);
}

void test_readData_given_0xAB_and_addr_0xFACE_should_sent_out_0xABFACE_and_turnaround_and_receive_0xBE(){
	// Your test code here...
  
  setPinToInput_Expect(IO_PIN);
  setPinToOutput_Expect(IO_PIN);
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  
  
}
