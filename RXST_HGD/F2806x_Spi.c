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

#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

//---------------------------------------------------------------------------
// InitSPI:
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitSpi(void)
{
   // Initialize SPI-A/B
    // Initialize SPI-A
    InitSpiaGpio();     //�����SPI�ӿ�
    Spia_init();        //

    spi_fifo_init();    // AD7606������ʼ��
    InitSpibGpio();
    Spib_init();
   //tbd...

}

//---------------------------------------------------------------------------
// Example: InitSpiGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SPI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each SPI peripheral
// Only one GPIO pin should be enabled for SPISIMO operation.
// Only one GPIO pin should be enabled for SPISOMI operation.
// Only one GPIO pin should be enabled for SPICLK  operation.
// Only one GPIO pin should be enabled for SPISTE  operation.
// Comment out other unwanted lines.

void InitSpiGpio()
{
   #if DSP28_SPIA
       InitSpiaGpio();
   #endif // endif DSP28_SPIA
   #if DSP28_SPIB
       InitSpibGpio();
   #endif // endif DSP28_SPIB
}

#if DSP28_SPIA
void InitSpiaGpio()
{

   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (SPISOMIA)
//  GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (SPISIMOA)

    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up for GPIO11 (SPISTEA)

//    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

//  GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0;   // Enable pull-up on GPIO54 (SPISIMOA)
//  GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;   // Enable pull-up on GPIO55 (SPISOMIA)
//  GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;   // Enable pull-up on GPIO56 (SPICLKA)
//    GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0;   // Enable pull-up on GPIO57 (SPISTEA)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//	GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 3;  // Asynch input GPIO3 (SPISOMIA)
//	GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 3;  // Asynch input GPIO5 (SPISIMOA)

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)

//    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

//  GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3; // Asynch input GPIO54 (SPISIMOA)
//  GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input GPIO55 (SPISOMIA)
//  GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO56 (SPICLKA)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO57 (SPISTEA)


/* Configure SPI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 2;  // Configure GPIO3 as SPISOMIA
//  GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 2;  // Configure GPIO5 as SPISIMOA

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    //  Configure GPIO19 as GPIO (ģ��Ƭѡ)
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;     //����Ϊ���
//    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

//  GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1; // Configure GPIO54 as SPISIMOA
//  GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; // Configure GPIO55 as SPISOMIA
//  GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
//    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA

    EDIS;
}
#endif // endif DSP28_SPIA

#if DSP28_SPIB
void InitSpibGpio()
{

   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pull-up on GPIO12 (SPISIMOB)
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pull-up on GPIO13 (SPISOMIB)
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;   // Enable pull-up on GPIO14 (SPICLKB)
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;   // Enable pull-up on GPIO15 (SPISTEB)

//	GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pull-up on GPIO24 (SPISIMOB)
//	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;   // Enable pull-up on GPIO25 (SPISOMIB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;   // Enable pull-up on GPIO26 (SPICLKB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pull-up on GPIO27 (SPISTEB)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // Asynch input GPIO12 (SPISIMOB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Asynch input GPIO13 (SPISOMIB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // Asynch input GPIO14 (SPICLKB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3; // Asynch input GPIO15 (SPISTEB)

//	GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; // Asynch input GPIO24 (SPISIMOB)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3; // Asynch input GPIO25 (SPISOMIB)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3; // Asynch input GPIO26 (SPICLKB)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3; // Asynch input GPIO27 (SPISTEB)

/* Configure SPI-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 3; // Configure GPIO12 as SPISIMOB
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3; // Configure GPIO13 as SPISOMIB
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3; // Configure GPIO14 as SPICLKB
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3; // Configure GPIO15 as SPISTEB

//  GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3; // Configure GPIO24 as SPISIMOB
//  GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3; // Configure GPIO25 as SPISOMIB
//  GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3; // Configure GPIO26 as SPICLKB
//  GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3; // Configure GPIO27 as SPISTEB

    EDIS;
}
#endif // endif DSP28_SPIB

void Spia_init(void)
{
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;         // Reset on
    SpiaRegs.SPICCR.bit.SPICHAR = 0x7;          // 8-bit char bits
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;        // CLKƽʱΪ�͵�ƽ
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;          // �½��ط����ݣ�������������
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;       // Enable master mode, normal phase,
    SpiaRegs.SPICTL.bit.TALK = 1;               // enable transmission
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;          // SPI int disabled.
    SpiaRegs.SPIBRR =0x0008;                    // BAUD=LSPCLK/(BRR+1)=90MHz/9=10MHz
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;         // Relinquish SPI from Reset
    SpiaRegs.SPIPRI.bit.FREE = 1;               // Set so breakpoints don't disturb xmission
}

Uint16 Spia_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF = a;
    while(SpiaRegs.SPISTS.bit.INT_FLAG !=1) { }     //SpibRegs.SPIFFRX.bit.RXFFST == 0
    return SpiaRegs.SPIRXBUF;
}

void Spib_init()
{
    SpibRegs.SPICCR.bit.SPISWRESET = 0;         // Reset on
    SpibRegs.SPICCR.bit.SPICHAR = 0xF;          // 8-bit char bits
    SpibRegs.SPICCR.bit.CLKPOLARITY = 1;        // �����ط����ݣ��½���������
    SpibRegs.SPICTL.bit.CLK_PHASE = 1;          // ����λ�ӳ�
    SpibRegs.SPICTL.bit.MASTER_SLAVE = 1;       // Enable master mode, normal phase,
    SpibRegs.SPICTL.bit.TALK = 1;               // enable transmission
    SpibRegs.SPICTL.bit.SPIINTENA = 0;          // SPI int disabled.

    SpibRegs.SPIBRR =0x0008;                    // BAUD=LSPCLK/(BRR+1)=90MHz/9=10MHz
    SpibRegs.SPICCR.bit.SPISWRESET = 1;         // Relinquish SPI from Reset
    SpibRegs.SPIPRI.bit.FREE = 1;               // Set so breakpoints don't disturb xmission


}


void spi_fifo_init()
{
// Initialize SPI FIFO registers
    SpibRegs.SPIFFTX.all=0xE040;
    SpibRegs.SPIFFRX.all=0x2044;
    SpibRegs.SPIFFCT.all=0x0;

}
//===========================================================================
// End of file.
//===========================================================================