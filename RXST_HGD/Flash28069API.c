/*
 * Flash28035API.c
 *
 *  Created on: 2019年2月27日
 *      Author: QianJZ
 */

#include "DSP28x_Project.h"
#include "string.h"



typedef struct {
     Uint16 *StartAddr;
     Uint16 *EndAddr;
} SECTOR;

/*--- Global variables used to interface to the flash routines */
FLASH_ST FlashStatus;

/*--- Callback function.  Function specified by defining Flash_CallbackPtr */
void MyCallbackFunction(void);
Uint32 MyCallbackCounter; // Just increment a counter in the callback function

//void Servo28335_CallFlashAPI(TControlParam stControlParam);        // Kernel function that interfaces to the API
//void Servo28335_Error(Uint16 Status);      // If an error, stop here

#pragma CODE_SECTION(FlashControlParams,"ramfuncs");
void FlashControlParams(TDriverParam stDriverParamA)
{
    Uint16  *Flash_ptr;     // Pointer to a location in flash
    /*------------------------------------------------------------------
     To use the Flash API, the following steps
     must be followed:

          1. Modify Flash2803x_API_Config.h for your targets operating
             conditions.
          2. Include Flash2803x_API_Library.h in the application.
          3. Add the appropriate Flash API library to the project.

      The user's code is responsible for the following:

          4. Initialize the PLL to the proper CPU operating frequency.
          5. If required, copy the flash API functions into on-chip zero waitstate
             RAM.
          6. Initialize the Flash_CPUScaleFactor variable to SCALE_FACTOR
          7. Initialize the callback function pointer or set it to NULL
          8. Optional: Run the Toggle test to confirm proper frequency configuration
             of the API.
          9. Optional: Unlock the CSM.
         10. Make sure the PLL is not running in limp mode
         11. Call the API functions: Flash_Erase(), Flash_Program(), Flash_Verify()
         ********************************/
    Uint16 i;
    Uint16 Status;

    DINT;

    /*------------------------------------------------------------------
     Initalize the PLLCR value before calling any of the F2810, F2811
     or F281x Flash API functions.

     Check to see if the PLL needs to changed
     PLLCR_VALUE is defined in SCDServo_Flash281x_API.h
     1) Make the change
     2) Wait for the DSP to switch to the PLL clock
        This wait is performed to ensure that the flash API functions
        will be executed at the correct frequency.
     3) While waiting, feed the watchdog so it will not reset.
    ------------------------------------------------------------------*/

    if(SysCtrlRegs.PLLCR.bit.DIV != 0x12)
    {
       EALLOW;
       SysCtrlRegs.PLLCR.bit.DIV = 0x12;

       // Wait for PLL to lock
       // Each time through this loop takes ~14 cycles
       // PLL Lock time is 131072 Cycles
       for(i= 0; i< 131072/14; i++)
       {
            SysCtrlRegs.WDKEY = 0x0055;
            SysCtrlRegs.WDKEY = 0x00AA;
       }
       EDIS;
    }

    /*------------------------------------------------------------------
      Unlock the CSM.
     If the API functions are going to run in unsecured RAM
     then the CSM must be unlocked in order for the flash
     API functions to access the flash.

     If the flash API functions are executed from secure memory
     (L0/L1) then this step is not required.

     ------------------------------------------------------------------*/
    Status = CsmUnlock();
    if(Status != STATUS_SUCCESS)
    {
 //     Example_Error(Status);
    }


    /*------------------------------------------------------------------
        Copy API Functions into SARAM
        The flash API functions MUST be run out of internal
        zero-waitstate SARAM memory.  This is required for
        the algos to execute at the proper CPU frequency.
        If the algos are already in SARAM then this step
        can be skipped.
        DO NOT run the algos from Flash
        DO NOT run the algos from external memory
    ------------------------------------------------------------------*/

// Copy the Flash API functions to SARAM
    MemCopy(&Flash28_API_LoadStart, &Flash28_API_LoadEnd, &Flash28_API_RunStart);

/*------------------------------------------------------------------
  Initalize Flash_CPUScaleFactor.

   Flash_CPUScaleFactor is a 32-bit global variable that the flash
   API functions use to scale software delays. This scale factor
   must be initalized to SCALE_FACTOR by the user's code prior
   to calling any of the Flash API functions. This initalization
   is VITAL to the proper operation of the flash API functions.

   SCALE_FACTOR is defined in SCDServo_Flash281x_API.h as
     #define SCALE_FACTOR  1048576.0L*( (200L/CPU_RATE) )

   This value is calculated during the compile based on the CPU
   rate, in nanoseconds, at which the algorithums will be run.
------------------------------------------------------------------*/

    EALLOW;
    Flash_CPUScaleFactor = SCALE_FACTOR;
    EDIS;


/*------------------------------------------------------------------
Initalize Flash_CallbackPtr.

Flash_CallbackPtr is a pointer to a function.  The API uses
this pointer to invoke a callback function during the API operations.
If this function is not going to be used, set the pointer to NULL
NULL is defined in <stdio.h>.
------------------------------------------------------------------*/

    EALLOW;
//    Flash_CallbackPtr = &MyCallbackFunction;
    Flash_CallbackPtr = NULL;       // 千万不能用&MyCallbackFunction 否则拔掉仿真器用FLASH api 会报故障 STATUS_FAIL_PRECONDITION
    EDIS;

    MyCallbackCounter = 0; // Increment this counter in the callback function

/*------------------------------------------------------------------
Before programming make sure the sectors are Erased.

------------------------------------------------------------------*/
    Status = Flash_Erase(SECTORC,&FlashStatus);    //变量定义在E区的
    if(Status != STATUS_SUCCESS)
    {
//      Example_Error(Status);
        g_stRespond.State.bit.FLASH_FAULT5 = 1;
    }


/*------------------------------------------------------------------
Program Flash

------------------------------------------------------------------*/
// In this case just fill a buffer with data to program into the flash.
    Flash_ptr = (Uint16 *)0x3EC000;

    Status = Flash_Program(Flash_ptr,(Uint16 *)&stDriverParamA,sizeof(TDriverParam),&FlashStatus);
    if(Status != STATUS_SUCCESS)
    {
//      Example_Error(Status);
        g_stRespond.State.bit.FLASH_FAULT5 = 1;
    }

// Verify the values programmed.  The Program step itself does a verify
// as it goes.  This verify is a 2nd verification that can be done.
    Status = Flash_Verify(Flash_ptr,(Uint16 *)&stDriverParamA,sizeof(TDriverParam),&FlashStatus);
    if(Status != STATUS_SUCCESS)
    {
//    Example_Error(Status);
        g_stRespond.State.bit.FLASH_FAULT5 = 1;
    }
// to guarantee the protocol, the delay should be put in
// the judge sentence,and the time is longer.
    DELAY_US(10000);


    EINT;
// 跳转到复位地址条件是GPIO84-GPIO87为高状态，同时ENPIE为0
// 对于我们只烧写参数，我认为不需要进行复位。
// 为保证跳转正确，可以采用将以下管脚配置成输入
/*
 PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
 EALLOW;
 GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 0;  // GPIO84
 GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;  // GPIO85
 GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 0;  // GPIO86
 GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0;  // GPIO87
 EDIS; */
//    asm(" LB 0x3F7FF6");                // Jump and reset  cmd文件中 Begin的位置，也就是代码起始的位置


}

/*------------------------------------------------------------------
  Callback function - must be executed from outside flash/OTP
-----------------------------------------------------------------*/
#pragma CODE_SECTION(MyCallbackFunction,"ramfuncs");
void MyCallbackFunction(void)
{
    // Toggle pin, service external watchdog etc
    MyCallbackCounter++;
    asm("    NOP");
}


