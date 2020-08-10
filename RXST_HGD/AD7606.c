//###########################################################################
//
// FILE:   F2806x_Spi.c
//
// TITLE:  F2806x SPI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Headerfile Include File
#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

int  AD_sample[4]={0,0,0,0};      //AD_sample[0] U  AD_sample[1] V  AD_sample[2] W   AD_sample[3]  VDC
float g_fMeaCurrentOffsetU;
float g_fMeaCurrentOffsetV;
float g_fMeaCurrentOffsetW;
float g_fMeaDCVoltageOffset;
//---------------------------------------------------------------------------
// InitSPI:
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitialAD7606(void)
{

    EALLOW;
     //ADC BUSY
    GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 0; // Asynch  GPIO57
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0; // Configure GPIO57 as GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0; // Configure GPIO57 as input
    //ADC SAMPLE
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 0; // Asynch  GPIO21
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0; // Configure GPIO21 as GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1; // Configure GPIO21 as output
    //ADC RST
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0; // Asynch  GPIO21
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0; // Configure GPIO21 as GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; // Configure GPIO21 as output
    EDIS;

    AD_SAMPLE_Stop();
    //reset AD7606 after powerup
    AD_Reset_Clear();
    DELAY_US(10);
    AD_Reset_Set();
    DELAY_US(10);
    AD_Reset_Clear();
//     EDIS;

}


void InitialAD7606Offset()
{
    Uint16 i=0;
    Uint16 index, SampleSize;
    int32 SumA, SumB, SumC, SumD;

    index       = 0;            //initialize index to 0
    SampleSize  = 1000;          //set sample size to 256 (**NOTE: Sample size must be multiples of 2^x where is an integer >= 4)
    SumA         = 0;           //set sum to 0
    SumB         = 0;           //set sum to 0
    SumC         = 0;           //set sum to 0
    SumD         = 0;           //set sum to 0

    while( index < SampleSize )
    {
        AD_SAMPLE_Start(); //starts sampling at rising edge
        DELAY_US(0.5);
        AD_SAMPLE_Stop();
        DELAY_US(2);  //wait 2us for conversion completed 实际上2us后busy信号就为低了 不用判断busy信号

        for(i=0;i<4;i++)
        {
            SpibRegs.SPITXBUF = 0x0000;
            while(SpibRegs.SPISTS.bit.BUFFULL_FLAG){}   //从示波器看，这句代码不要，一样有64个CLK
        }

        while(SpibRegs.SPIFFRX.bit.RXFFST !=4) { }

        for(i=0;i<4;i++)
        {
            AD_sample[i]=SpibRegs.SPIRXBUF;
        }

        SumA += AD_sample[0];               //Get sample
        SumB += AD_sample[1];               //Get sample
        SumC += AD_sample[2];
        SumD += AD_sample[3];
        index++;
    }

    g_fMeaCurrentOffsetU = SumA / SampleSize*10.0/65536.0;    //Calculate average ADC sample value
    g_fMeaCurrentOffsetV = SumB / SampleSize*10.0/65536.0;    //Calculate average ADC sample value
    g_fMeaCurrentOffsetW = SumC / SampleSize*10.0/65536.0;
//    g_fMeaDCVoltageOffset = SumD / SampleSize;

}


void ReadAD7606()
{
    Uint16 i=0;
    AD_SAMPLE_Start(); //starts sampling at rising edge
    DELAY_US(0.5);
    AD_SAMPLE_Stop();
    DELAY_US(2);  //wait 2us for conversion completed 实际上2us后busy信号就为低了 不用判断busy信号
//    while(GpioDataRegs.GPADAT.bit.GPIO21==1)
//    {}
//
    for(i=0;i<4;i++)
    {
        SpibRegs.SPITXBUF = 0x0000;
        while(SpibRegs.SPISTS.bit.BUFFULL_FLAG){}   //从示波器看，这句代码不要，一样有64个CLK
     }

    while(SpibRegs.SPIFFRX.bit.RXFFST !=4) { }

    for(i=0;i<4;i++)
    {
      AD_sample[i]=SpibRegs.SPIRXBUF;
    }

    g_fMeaCurrentU=(AD_sample[0]*10.0/65536.0-g_fMeaCurrentOffsetU)*200;
    g_fMeaCurrentV=(AD_sample[1]*10.0/65536.0-g_fMeaCurrentOffsetV)*200;
    g_fMeaCurrentW=0-g_fMeaCurrentU-g_fMeaCurrentV;
//    g_fMeaCurrentW=0-g_fMeaCurrentU-g_fMeaCurrentV;

}

//===========================================================================
// End of file.
//===========================================================================
