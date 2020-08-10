//###########################################################################
//
// FILE:   F2806x_EPwm.c
//
// TITLE:  F2806x EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File
#include "ProjectConfig.h"
//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the EPwm(s) to a known state.
//
void InitEPwm(void)
{
   // Initialize EPwm1/2/3/4/5/6/7/8
    InitEPwm1Gpio();
    InitEPwm2Gpio();

    InitEPwm4Gpio();
    InitEPwm5Gpio();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    InitEPwm1();
    InitEPwm2();

    InitEPwm4();
    InitEPwm5();
//    InitEPwm7();
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
   //tbd...

}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitEPwmGpio(void)
{
   #if DSP28_EPWM1
       InitEPwm1Gpio();
   #endif // endif DSP28_EPWM1
   #if DSP28_EPWM2
       InitEPwm2Gpio();
   #endif // endif DSP28_EPWM2
   #if DSP28_EPWM3
       InitEPwm3Gpio();
   #endif // endif DSP28_EPWM3
   #if DSP28_EPWM4
       InitEPwm4Gpio();
   #endif // endif DSP28_EPWM4
   #if DSP28_EPWM5
       InitEPwm5Gpio();
   #endif // endif DSP28_EPWM5
   #if DSP28_EPWM6
       InitEPwm6Gpio();
   #endif // endif DSP28_EPWM6
   #if DSP28_EPWM7
       InitEPwm7Gpio();
   #endif // endif DSP28_EPWM7
   #if DSP28_EPWM8
       InitEPwm8Gpio();
   #endif // endif DSP28_EPWM8
}

#if DSP28_EPWM1
void InitEPwm1Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

/* Configure EPWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}
#endif // endif DSP28_EPWM1

#if DSP28_EPWM2
void InitEPwm2Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)

/* Configure EPwm-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    EDIS;
}
#endif // endif DSP28_EPWM2

#if DSP28_EPWM3
void InitEPwm3Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)

/* Configure EPwm-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}
#endif // endif DSP28_EPWM3

#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)

/* Configure EPWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

    EDIS;
}
#endif // endif DSP28_EPWM4

#if DSP28_EPWM5
void InitEPwm5Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;    // Disable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;    // Disable pull-up on GPIO9 (EPWM5B)

/* Configure EPWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B

    EDIS;
}
#endif // endif DSP28_EPWM5

#if DSP28_EPWM6
void InitEPwm6Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO11 (EPWM6B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B

    EDIS;
}
#endif // endif DSP28_EPWM6

#if DSP28_EPWM7
void InitEPwm7Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO30 = 1;	   // Disable pull-up on GPIO30 (EPWM7A)
    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;    // Disable pull-up on GPIO40 (EPWM7A)
//  GpioCtrlRegs.GPBPUD.bit.GPIO58 = 1;	   // Disable pull-up on GPIO58 (EPWM7A)

    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;    // Disable pull-up on GPIO41 (EPWM7B)
//  GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1;	   // Disable pull-up on GPIO44 (EPWM7B)

/* Configure EPWM-7 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM7 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 3;   // Configure GPIO30 as EPWM7A
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;   // Configure GPIO40 as EPWM7A
//  GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 3;   // Configure GPIO58 as EPWM7A

    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;   // Configure GPIO41 as EPWM7B
//  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 3;   // Configure GPIO44 as EPWM7B

    EDIS;
}
#endif // endif DSP28_EPWM7

#if DSP28_EPWM8
void InitEPwm8Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;	   // Disable pull-up on GPIO30 (EPWM8A)
    GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1;    // Disable pull-up on GPIO42 (EPWM8A)
    GpioCtrlRegs.GPBPUD.bit.GPIO43 = 1;    // Disable pull-up on GPIO43 (EPWM8B)

/* Configure EPWM-7 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM7 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 3;   // Configure GPIO30 as EPWM8A
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;   // Configure GPIO42 as EPWM8A
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 1;   // Configure GPIO43 as EPWM8B

    EDIS;
}
#endif // endif DSP28_EPWM8

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm Synch pins
//

void InitEPwmSyncGpio(void)
{

//   EALLOW;

/* Configure EPWMSYNCI  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;     // Enable pull-up on GPIO6 (EPWMSYNCI)
   GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up on GPIO32 (EPWMSYNCI)

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
   GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Configures GPIO6 for EPWMSYNCI operation
   GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Configures GPIO32 for EPWMSYNCI operation.

/* Configure EPWMSYNC0  */

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWMSYNCO)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;   // Disable pull-up on GPIO33 (EPWMSYNCO)

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;   // Configures GPIO6 for EPWMSYNCO
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;  // Configures GPIO33 for EPWMSYNCO

}

//---------------------------------------------------------------------------
// Example: InitTzGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitTzGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
// GpioCtrlRegs.GPBPUD.bit.GPIO42 = 0;	  // Enable pull-up on GPIO42 (TZ1)
// GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;	  // Enable pull-up on GPIO50 (TZ1)
   GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ2)
// GpioCtrlRegs.GPBPUD.bit.GPIO43 = 0;	  // Enable pull-up on GPIO43 (TZ2)
// GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;    // Enable pull-up on GPIO51 (TZ2)
   GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ3)
// GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;    // Enable pull-up on GPIO52 (TZ3)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO42 = 3;  // Asynch input GPIO42 (TZ1)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 3;  // Asynch input GPIO50 (TZ1)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ2)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO43 = 3;  // Asynch input GPIO43 (TZ2)
// GpioCtrlRegs.GPBQAEL2.bit.GPIO51 = 3;  // Asynch input GPIO51 (TZ2)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ3)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 3;  // Asynch input GPIO52 (TZ3)


/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
// GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 2;  // Configure GPIO42 as TZ1
// GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 3;  // Configure GPIO50 as TZ1
   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ2
// GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 2;  // Configure GPIO43 as TZ2
// GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 3;  // Configure GPIO51 as TZ2
   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ3
// GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 3;  // Configure GPIO52 as TZ3

   EDIS;

}

//---------------------------------------------------------------------------
// Example: InitEPwm:
//---------------------------------------------------------------------------

void InitEPwm1(void)
{

      EPwm1Regs.TBPRD =PWM_Period;// Set timer period 16KHz
      EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
      EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

      // Setup compare
      EPwm1Regs.CMPA.half.CMPA = PWM_Halfperiod;           //50% Duty        EPwm1Regs.TBPRD*0.8
      EPwm1Regs.CMPB = (PWM_Halfperiod-Dead_Time);               //50% Duty

      // Setup TBCLK
      EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up
      EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Disable phase loading
      EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
      EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
      EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;         // Clock ratio to SYSCLKOUT
      EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//      EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;

      EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;      // Load registers every ZERO or PRD
      EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;      //0:影子模式; 1:立即模式
      EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
      EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;    //计数寄存器CTR=0是装载新的比较值

      // Set actions
      EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;         // Set PWM1A 斩波
      EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

      EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Set PWM1A 斩波
      EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;

     //死区模块   因为需要兼容BLDC和PMSM，所以不能用自带的死区模块，需要自己生成。
//      EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;       //输入都是PWMA
//      EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;    //IRS2003  B路取反        负逻辑
//      EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //
//      //设置死区， 主频90M DBZone = 11.11ns*DBRED us
//      EPwm1Regs.DBRED = Dead_Time;           //死区时间1us
//      EPwm1Regs.DBFED = Dead_Time;

      // 设置ePWM中断生成
      EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // 在计数为零的时候生成中断事件
      EPwm1Regs.ETSEL.bit.INTEN = 1;                  // 使能中断
      EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;             // 每个事件生成中断，选择INTCNT和INTPRD作为事件判断标志

      // 设置ePWM的SOCA的生成
      EPwm1Regs.ETSEL.bit.SOCAEN = 1;              //
      EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;    //等于PRD时触发启动转换ADC脉冲，上桥臂关闭中间采样  ET_CTR_PRD
      EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;         //电流环16KHz      ET_1ST
//      EPwm1Regs.ETCLR.bit.SOCA = 1;                //Clear SOCA flag

      //EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTRU_CMPB;
      //比较器B的值触发启动转换ADC脉冲, B值设置为A值的一半，即PWM高有效中间采样

//      EALLOW;
//      //保护设置
//      EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;       //COMP1OUT输出连接到DCAH
//      EPwm1Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP1OUT;       //COMP1OUT输出连接到DCBH
//      EPwm1Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              //DCAH高触发DCAEVT2事件
//      EPwm1Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCBH_HI;              //DCBH高触发DCBEVT2事件
//      EPwm1Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;                 //过流保护触发  cycle by cycle
//      EPwm1Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;                 //过流保护触发  cycle by cycle
//      EPwm1Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;               //过流时PWMA输出高阻  TZ_HIZ
//      EPwm1Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;               //过流时PWMB输出高阻  TZ_HIZ
//      EPwm1Regs.TZEINT.bit.DCAEVT2=1;      // cycle by cycle
////      EPwm1Regs.TZSEL.bit.CBC1 =1;
//      EPwm1Regs.TZCLR.all = 0;                                 //清除所有中断标志
//
//      EDIS;
}


void InitEPwm2(void)
{
   EPwm2Regs.TBPRD = EPwm1Regs.TBPRD;// Set timer period 20KHz=80/4000
   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup compare
   EPwm2Regs.CMPA.half.CMPA = PWM_Halfperiod;           //50% Duty
   EPwm2Regs.CMPB = (PWM_Halfperiod-Dead_Time);               //50% Duty

   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//   EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;

   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO or PRD
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Set PWM1A 斩波
   EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;

   EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;         // Set PWM1A 斩波
   EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;

//   EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;       //输入都是PWMA
//   EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;    //B路不取反  IRS2103        负逻辑
//   EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //
//
//   EPwm2Regs.DBRED = Dead_Time;           //死区时间1us
//   EPwm2Regs.DBFED = Dead_Time;

   EALLOW;

   //保护设置
   EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP2OUT;       //COMP1OUT输出连接到DCAH
   EPwm2Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP2OUT;       //COMP1OUT输出连接到DCBH
   EPwm2Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              //DCAH高触发DCAEVT1事件
   EPwm2Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCBH_HI;              //DCBH高触发DCBEVT1事件
   EPwm2Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;                 //过流保护触发  cycle by cycle
   EPwm2Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;                 //过流保护触发  cycle by cycle
   EPwm2Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;               //过流时PWMA输出高阻      TZ_HIZ
   EPwm2Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;               //过流时PWMB输出高阻
   EPwm2Regs.TZEINT.bit.DCAEVT2=1;      // cycle by cycle
//   EPwm2Regs.TZSEL.bit.CBC1 =1;
   EPwm2Regs.TZCLR.all = 0;                                 //清除所有中断标志


   EDIS;

}

void InitEPwm3(void)
{
   EPwm3Regs.TBPRD = EPwm1Regs.TBPRD;// Set timer period 20KHz=80/4000
   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm3Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup compare
   EPwm3Regs.CMPA.half.CMPA = PWM_Halfperiod;           //50% Duty
   EPwm3Regs.CMPB = (PWM_Halfperiod-Dead_Time);               //50% Duty

   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//   EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;

   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO or PRD
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;         // Set PWM1A 斩波
   EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Set PWM1A 斩波
   EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;

//   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;       //输入都是PWMA
//   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;    //B路不取反  IRS2103        负逻辑
//   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //
//
//   EPwm3Regs.DBRED = Dead_Time;           //死区时间1us
//   EPwm3Regs.DBFED = Dead_Time;

   EALLOW;

   //保护设置
   EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP3OUT;       //COMP1OUT输出连接到DCAH
   EPwm3Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP3OUT;       //COMP1OUT输出连接到DCBH
   EPwm3Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              //DCAH高触发DCAEVT1事件
   EPwm3Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCBH_HI;              //DCBH高触发DCBEVT1事件
   EPwm3Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;                 //过流保护触发  cycle by cycle
   EPwm3Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;                 //过流保护触发  cycle by cycle
   EPwm3Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;               //过流时PWMA输出高阻
   EPwm3Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;               //过流时PWMB输出高阻
   EPwm3Regs.TZEINT.bit.DCAEVT2=1;      // cycle by cycle
//   EPwm3Regs.TZSEL.bit.CBC1 =1;
   EPwm3Regs.TZCLR.all = 0;                                 //清除所有中断标志

   EDIS;

}


void InitEPwm4(void)
{
   EPwm4Regs.TBPRD = EPwm1Regs.TBPRD;// Set timer period 20KHz=80/4000
   EPwm4Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm4Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup compare
   EPwm4Regs.CMPA.half.CMPA = PWM_Halfperiod;           //50% Duty
   EPwm4Regs.CMPB = (PWM_Halfperiod-Dead_Time);               //50% Duty

   // Setup TBCLK
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up
   EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//   EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;

   EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO or PRD
   EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;         // Set PWM1A 斩波
   EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Set PWM1A 斩波
   EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;

//   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;       //输入都是PWMA
//   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;    //B路不取反  IRS2103        负逻辑
//   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //
//
//   EPwm3Regs.DBRED = Dead_Time;           //死区时间1us
//   EPwm3Regs.DBFED = Dead_Time;

}


void InitEPwm5(void)
{
   EPwm5Regs.TBPRD = EPwm1Regs.TBPRD;// Set timer period 20KHz=80/4000
   EPwm5Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm5Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup compare
   EPwm5Regs.CMPA.half.CMPA = PWM_Halfperiod;           //50% Duty
   EPwm5Regs.CMPB = (PWM_Halfperiod-Dead_Time);               //50% Duty

   // Setup TBCLK
   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up
   EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//   EPwm5Regs.TBCTL.bit.PHSDIR = TB_UP;

   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO or PRD
   EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Set PWM1A 斩波
   EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;

   EPwm5Regs.AQCTLB.bit.CBU = AQ_SET;         // Set PWM1A 斩波
   EPwm5Regs.AQCTLB.bit.CBD = AQ_CLEAR;

//   EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;       //输入都是PWMA
//   EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;    //B路不取反  IRS2103        负逻辑
//   EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //
//
//   EPwm5Regs.DBRED = Dead_Time;           //死区时间1us
//   EPwm5Regs.DBFED = Dead_Time;

}

void InitEPwm7(void)
{
    EPwm7Regs.TBPRD =2250; // PWM frequency=20kHz TB_COUNT_UPDOWN 90M/20k/2=2250
    EPwm7Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
    EPwm7Regs.TBCTR = 0x0000;                      // Clear counter

    // Setup compare
    EPwm7Regs.CMPA.half.CMPA = 1125;    //
    EPwm7Regs.CMPB = 2250;               //50% Duty

    // Setup TBCLK
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up
    EPwm7Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Disable phase loading
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    EPwm7Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;         // Clock ratio to SYSCLKOUT
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    //      EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;

    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;      // Load registers every ZERO or PRD
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;      //0:影子模式; 1:立即模式
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;    //计数寄存器CTR=0是装载新的比较值

    // Set actions
    EPwm7Regs.AQCTLA.bit.CAU = AQ_SET;         // Set PWM1A 斩波
    EPwm7Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm7Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Set PWM1A 斩波
    EPwm7Regs.AQCTLB.bit.CBD = AQ_SET;

    //死区模块   因为需要兼容BLDC和PMSM，所以不能用自带的死区模块，需要自己生成。
    //      EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;       //输入都是PWMA
    //      EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;    //IRS2003  B路取反        负逻辑
    //      EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //
    //      //设置死区， 主频90M DBZone = 11.11ns*DBRED us
    //      EPwm1Regs.DBRED = Dead_Time;           //死区时间1us
    //      EPwm1Regs.DBFED = Dead_Time;

    // 设置ePWM中断生成
    EPwm7Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // 在计数为零的时候生成中断事件
    EPwm7Regs.ETSEL.bit.INTEN = 1;                  // 使能中断
    EPwm7Regs.ETPS.bit.INTPRD = ET_1ST;             // 每个事件生成中断，选择INTCNT和INTPRD作为事件判断标志


    EALLOW;

    //保护设置
    EPwm7Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;       //COMP1OUT输出连接到DCAH
    EPwm7Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP1OUT;       //COMP1OUT输出连接到DCBH
    EPwm7Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI;              //DCAH高触发DCAEVT1事件
    EPwm7Regs.TZDCSEL.bit.DCBEVT1 = TZ_DCBH_HI;              //DCBH高触发DCBEVT1事件
    EPwm7Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;                 //过流保护触发  one-shot
    EPwm7Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;                 //过流保护触发  one-shot
    EPwm7Regs.TZCTL.bit.DCAEVT1 = TZ_FORCE_LO;               //过流时PWMA输出高阻  TZ_HIZ
    EPwm7Regs.TZCTL.bit.DCBEVT1 = TZ_FORCE_LO;               //过流时PWMB输出高阻  TZ_HIZ
    EPwm7Regs.TZEINT.bit.CBC=1;
    EPwm7Regs.TZSEL.bit.CBC1 =1;
    EPwm7Regs.TZCLR.all = 0;                                 //清除所有中断标志

    EDIS;

}

//===========================================================================
// End of file.
//===========================================================================
