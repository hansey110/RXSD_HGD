//###########################################################################
//
// FILE:    F2806x_Adc.c
//
// TITLE:   F2806x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V136 $
// $Release Date: Apr 15, 2013 $
//###########################################################################
#include "DSP28x_Project.h"     // Headerfile Include File
#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

#define ADC_usDELAY  1000L

Uint16 g_iMotorTempOffset;          // 温度采样，单位:摄氏度
Uint16 g_iDriverTempOffset;          // 温度采样，单位:摄氏度
Uint16 g_iMeaDCVoltageOffset;          // 母线电压
//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
// NOTE: ADC INIT IS DIFFERENT ON F2806x DEVICES COMPARED TO OTHER 28X DEVICES
//
//  *IMPORTANT*
//  IF RUNNING FROM FLASH, PLEASE COPY OVER THE SECTION "ramfuncs"  FROM FLASH
//  TO RAM PRIOR TO CALLING InitSysCtrl(). THIS PREVENTS THE MCU FROM THROWING 
//  AN EXCEPTION WHEN A CALL TO DELAY_US() IS MADE. 
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);

    // *IMPORTANT*
    // The Device_cal function, which copies the ADC calibration values from TI reserved
    // OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
    // Boot ROM. If the boot ROM code is bypassed during the debug process, the
    // following function MUST be called for the ADC to function according
    // to specification. The clocks to the ADC MUST be enabled before calling this
    // function.
    // See the device data manual and/or the ADC Reference
    // Manual for more information.

        EALLOW;
        SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
        (*Device_cal)();
        EDIS;

    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
    // after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
    // CPU_RATE define statement in the F2806x_Examples.h file must
    // contain the correct CPU clock period in nanoseconds.
    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC BG
    AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
    AdcRegs.ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC
    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;      // Select interal BG
    EDIS;

    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

    EALLOW;
    AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1;
    EDIS;

    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

    AdcOffsetSelfCal();

    User_InitADC();

    User_AdcOffset();
}

void InitAdcAio()
{

   EALLOW;

/* Configure ADC pins using AIO regs*/
// This specifies which of the possible AIO pins will be Analog input pins.
// NOTE: AIO1,3,5,7-9,11,13,15 are analog inputs in all AIOMUX1 configurations.
// Comment out other unwanted lines.


    Comp1Regs.COMPCTL.bit.COMPDACEN =1;    //enable compare
    Comp1Regs.DACCTL.bit.DACSOURCE = 0;
    Comp1Regs.DACVAL.bit.DACVAL= 930;  //  3.15V对应200A  对应值930
    Comp1Regs.COMPCTL.bit.COMPSOURCE = 0;
    Comp1Regs.COMPCTL.bit.QUALSEL = 0;
    Comp1Regs.COMPCTL.bit.SYNCSEL = 1;
    Comp1Regs.COMPCTL.bit.CMPINV = 0;


    Comp2Regs.COMPCTL.bit.COMPDACEN =1;    //enable compare
    Comp2Regs.DACCTL.bit.DACSOURCE = 0;
    Comp2Regs.DACVAL.bit.DACVAL=  930;  //0xc1c;
    Comp2Regs.COMPCTL.bit.COMPSOURCE = 0;
    Comp2Regs.COMPCTL.bit.QUALSEL = 0;
    Comp2Regs.COMPCTL.bit.SYNCSEL = 1;
    Comp2Regs.COMPCTL.bit.CMPINV = 0;


    Comp3Regs.COMPCTL.bit.COMPDACEN =1;    //enable compare
    Comp3Regs.DACCTL.bit.DACSOURCE = 0;
    Comp3Regs.DACVAL.bit.DACVAL=   930;  //0xc1c;
    Comp3Regs.COMPCTL.bit.COMPSOURCE = 0;
    Comp3Regs.COMPCTL.bit.QUALSEL = 0;
    Comp3Regs.COMPCTL.bit.SYNCSEL = 1;
    Comp3Regs.COMPCTL.bit.CMPINV = 0;


    GpioCtrlRegs.AIOMUX1.bit.AIO2 = 0;    // Configure AIO2 for A2 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO4 = 0;    // Configure AIO4 for A4 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 0;    // Configure AIO6 for A6 (analog input) operation

    GpioCtrlRegs.AIODIR.bit.AIO2 = 0;
    GpioCtrlRegs.AIODIR.bit.AIO4 = 0;
    GpioCtrlRegs.AIODIR.bit.AIO6 = 0;


    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;   // Configure AIO10 for B2 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;   // Configure AIO12 for B4 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;   // Configure AIO14 for B6 (analog input) operation

    EDIS;
}


/* AdcoffsetSelfCal-
   This function re-calibrates the ADC zero offset error by converting the VREFLO reference with
   the ADC and modifying the ADCOFFTRIM register. VREFLO is sampled by the ADC using an internal
   MUX select which connects VREFLO to A5 without sacrificing an external ADC pin. This
   function calls two other functions:
   - AdcChanSelect(channel) � selects the ADC channel to convert
   - AdcConversion() � initiates several ADC conversions and returns the average
*/
void AdcOffsetSelfCal()
{
    Uint16 AdcConvMean;
    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;                  //Select internal reference mode
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 1;                 //Select VREFLO internal connection on B5
    AdcChanSelect(13);                                  //Select channel B5 for all SOC
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM = 80;                //Apply artificial offset (+80) to account for a negative offset that may reside in the ADC core
    AdcConvMean = AdcConversion();                      //Capture ADC conversion on VREFLO
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM = 80 - AdcConvMean;  //Set offtrim register with new value (i.e remove artical offset (+80) and create a two's compliment of the offset error)
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 0;                 //Select external ADCIN5 input pin on B5
    EDIS;
}

/*  AdcChanSelect-
    This function selects the ADC channel to convert by setting all SOC channel selects to a single channel.

     * IMPORTANT * This function will overwrite previous SOC channel select settings. Recommend saving
           the previous settings.
 */
void AdcChanSelect(Uint16 ch_no)
{
    AdcRegs.ADCSOC0CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC1CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC2CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC3CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC4CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC5CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC6CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC7CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC8CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC9CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC10CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC11CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC12CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC13CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC14CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC15CTL.bit.CHSEL= ch_no;
} //end AdcChanSelect

/* AdcConversion -
   This function initiates several ADC conversions and returns the average. It uses ADCINT1 and ADCINT2
   to "ping-pong" between SOC0-7 and SOC8-15 and is referred to as "ping-pong" sampling.

     * IMPORTANT * This function will overwrite previous ADC settings. Recommend saving previous settings.
*/
Uint16 AdcConversion(void)
{
    Uint16 index, SampleSize, Mean, ACQPS_Value;
    Uint32 Sum;

    index       = 0;            //initialize index to 0
    SampleSize  = 256;          //set sample size to 256 (**NOTE: Sample size must be multiples of 2^x where is an integer >= 4)
    Sum         = 0;            //set sum to 0
    Mean        = 999;          //initialize mean to known value

    //Set the ADC sample window to the desired value (Sample window = ACQPS + 1)
    ACQPS_Value = 6;
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC1CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC2CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC3CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC4CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC5CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC6CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC7CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC8CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC9CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC10CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC11CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC12CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC13CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC14CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC15CTL.bit.ACQPS = ACQPS_Value;


    //Enable ping-pong sampling

    // Enabled ADCINT1 and ADCINT2
    AdcRegs.INTSEL1N2.bit.INT1E = 1;
    AdcRegs.INTSEL1N2.bit.INT2E = 1;

    // Disable continuous sampling for ADCINT1 and ADCINT2
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0;
    AdcRegs.INTSEL1N2.bit.INT2CONT = 0;

    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINTs trigger at end of conversion

    // Setup ADCINT1 and ADCINT2 trigger source
    AdcRegs.INTSEL1N2.bit.INT1SEL = 6;      //EOC6 triggers ADCINT1
    AdcRegs.INTSEL1N2.bit.INT2SEL = 14;     //EOC14 triggers ADCINT2

    // Setup each SOC's ADCINT trigger source
    AdcRegs.ADCINTSOCSEL1.bit.SOC0  = 2;    //ADCINT2 starts SOC0-7
    AdcRegs.ADCINTSOCSEL1.bit.SOC1  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC2  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC3  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC4  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC5  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC6  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC7  = 2;
    AdcRegs.ADCINTSOCSEL2.bit.SOC8  = 1;    //ADCINT1 starts SOC8-15
    AdcRegs.ADCINTSOCSEL2.bit.SOC9  = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC10 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC11 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC12 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC13 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC14 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC15 = 1;

    DELAY_US(ADC_usDELAY);                  // Delay before converting ADC channels


    //ADC Conversion

    AdcRegs.ADCSOCFRC1.all = 0x00FF;  // Force Start SOC0-7 to begin ping-pong sampling

    while( index < SampleSize ){

        //Wait for ADCINT1 to trigger, then add ADCRESULT0-7 registers to sum
        while (AdcRegs.ADCINTFLG.bit.ADCINT1 == 0){}
        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;   //Must clear ADCINT1 flag since INT1CONT = 0
        Sum += AdcResult.ADCRESULT0;
        Sum += AdcResult.ADCRESULT1;
        Sum += AdcResult.ADCRESULT2;
        Sum += AdcResult.ADCRESULT3;
        Sum += AdcResult.ADCRESULT4;
        Sum += AdcResult.ADCRESULT5;
        Sum += AdcResult.ADCRESULT6;
        Sum += AdcResult.ADCRESULT7;

        //Wait for ADCINT2 to trigger, then add ADCRESULT8-15 registers to sum
        while (AdcRegs.ADCINTFLG.bit.ADCINT2 == 0){}
        AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;   //Must clear ADCINT2 flag since INT2CONT = 0
        Sum += AdcResult.ADCRESULT8;
        Sum += AdcResult.ADCRESULT9;
        Sum += AdcResult.ADCRESULT10;
        Sum += AdcResult.ADCRESULT11;
        Sum += AdcResult.ADCRESULT12;
        Sum += AdcResult.ADCRESULT13;
        Sum += AdcResult.ADCRESULT14;
        Sum += AdcResult.ADCRESULT15;

        index+=16;

    } // end data collection

    //Disable ADCINT1 and ADCINT2 to STOP the ping-pong sampling
    AdcRegs.INTSEL1N2.bit.INT1E = 0;
    AdcRegs.INTSEL1N2.bit.INT2E = 0;

    Mean = Sum / SampleSize;    //Calculate average ADC sample value

    return Mean;                //return the average

}//end AdcConversion

void User_InitADC(void)
{
    EALLOW;

    AdcRegs.ADCINTFLGCLR.all = 0xFFFF;      //
    AdcRegs.ADCINTOVFCLR.all = 0xFFFF;      //
    AdcRegs.ADCSOCOVFCLR1.all = 0xFFFF;     //

    AdcRegs.ADCCTL1.bit.TEMPCONV    = 1;    //Connect internal temp sensor to channel ADCINA5.
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;  //Enable non-overlap mode       1:不允许过采样(效果要好)；0：允许过采样；
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 1;     //Select vrefLO input pin on B5
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINT1 trips after AdcResults latch


    AdcRegs.ADCINTSOCSEL1.all  = 0;         //
    AdcRegs.ADCINTSOCSEL2.all  = 0;         //
    AdcRegs.INTSEL1N2.bit.INT1E     = 1;       // Enable ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;     // Disable ADCINT1 Continuous mode
    AdcRegs.INTSEL1N2.bit.INT1SEL   = 0;     // setup EOC5 to trigger ADCINT1 to fire  通道0采样完成触发ADCINT1中断

    /******* CHANNEL SELECT *******/                                                                                                                                                    \
    AdcRegs.ADCSOC0CTL.bit.CHSEL  = 0;       // ChSelect: ADC A0-> AIN_1
    AdcRegs.ADCSOC1CTL.bit.CHSEL  = 1;       // ChSelect: ADC A1-> A_I
    AdcRegs.ADCSOC2CTL.bit.CHSEL  = 8;       // ChSelect: ADC B0-> AIN_2
    AdcRegs.ADCSOC3CTL.bit.CHSEL  = 9;       // ChSelect: ADC B1-> B_I
    AdcRegs.ADCSOC4CTL.bit.CHSEL  = 2;       // ChSelect: ADC A2-> VBUS_DSP
    AdcRegs.ADCSOC5CTL.bit.CHSEL  = 10;      // ChSelect: ADC B2-> Driver NTC
//    AdcRegs.ADCSOC6CTL.bit.CHSEL  = 3;       // ChSelect: ADC A3-> IW
//    AdcRegs.ADCSOC7CTL.bit.CHSEL  = 11;      // ChSelect: ADC B3-> Driver NTC
//    AdcRegs.ADCSOC8CTL.bit.CHSEL  = 4;       // ChSelect: ADC A3-> Idc
//    AdcRegs.ADCSOC9CTL.bit.CHSEL  = 12;      // ChSelect: ADC B3-> Vdc
//    AdcRegs.ADCSOC10CTL.bit.CHSEL = 5;      // ChSelect: ADC A5-> MCU Temperature
//    AdcRegs.ADCSOC11CTL.bit.CHSEL = 13;      // ChSelect: ADC B5-> 0
//    AdcRegs.ADCSOC12CTL.bit.CHSEL = 7;      // ChSelect: ADC A7-> Ain
//    AdcRegs.ADCSOC13CTL.bit.CHSEL = 15;     // ChSelect: ADC B7-> 0

    //5:epmw1 SOCA触发；1:timer0触发；0：软件触发
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 5; /* Set SOC0 start trigger on EPWM1A */
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5; /* Set SOC1 start trigger on EPWM1A */
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL  = 5;
//    AdcRegs.ADCSOC6CTL.bit.TRIGSEL  = 5;
//    AdcRegs.ADCSOC7CTL.bit.TRIGSEL  = 5;
//    AdcRegs.ADCSOC8CTL.bit.TRIGSEL  = 5;
//    AdcRegs.ADCSOC9CTL.bit.TRIGSEL  = 5;
//    AdcRegs.ADCSOC10CTL.bit.TRIGSEL = 5;
//    AdcRegs.ADCSOC11CTL.bit.TRIGSEL = 5;
//    AdcRegs.ADCSOC12CTL.bit.TRIGSEL = 5;
//    AdcRegs.ADCSOC13CTL.bit.TRIGSEL = 5;

    //采样窗口长度不是随便设的，要找到一个最好值
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = 6;  //set SOC0 S/H Window to 26 ADC Clock Cycles, (25 ACQPS plus 1)
    AdcRegs.ADCSOC1CTL.bit.ACQPS  = 6;
    AdcRegs.ADCSOC2CTL.bit.ACQPS  = 6;
    AdcRegs.ADCSOC3CTL.bit.ACQPS  = 6;
    AdcRegs.ADCSOC4CTL.bit.ACQPS  = 6;
    AdcRegs.ADCSOC5CTL.bit.ACQPS  = 6;
//    AdcRegs.ADCSOC6CTL.bit.ACQPS  = 26;
//    AdcRegs.ADCSOC7CTL.bit.ACQPS  = 26;
//    AdcRegs.ADCSOC8CTL.bit.ACQPS  = 26;
//    AdcRegs.ADCSOC9CTL.bit.ACQPS  = 26;
//    AdcRegs.ADCSOC10CTL.bit.ACQPS = 26;
//    AdcRegs.ADCSOC11CTL.bit.ACQPS = 26;
//    AdcRegs.ADCSOC12CTL.bit.ACQPS = 26;
//    AdcRegs.ADCSOC13CTL.bit.ACQPS = 26;

    EDIS;
}

void User_AdcOffset(void)
{
//    Uint16 index, SampleSize;
//    Uint32 SumA, SumB, SumC, SumD;
//
//    index       = 0;            //initialize index to 0
//    SampleSize  = 1000;          //set sample size to 256 (**NOTE: Sample size must be multiples of 2^x where is an integer >= 4)
//    SumA         = 0;           //set sum to 0
//    SumB         = 0;           //set sum to 0
//    SumC         = 0;           //set sum to 0
//    SumD         = 0;           //set sum to 0
//
//    while( index < SampleSize )
//    {
//        AdcRegs.ADCSOCFRC1.all = 0xFFFF;              //强制触发
//        while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0){} //Wait for ADCINT1
//        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1
//
//        SumA += AdcResult.ADCRESULT0;               //Get sample
//        SumB += AdcResult.ADCRESULT1;               //Get sample
//        SumC += AdcResult.ADCRESULT2;
//        SumD += AdcResult.ADCRESULT3;
//
//        DELAY_US(ADC_usDELAY);                  // Delay before converting ADC channels
//
//        index++;
//    }
//
//    g_stCpuToClaData.fRefCurrentOffsetA = SumA / SampleSize;    //Calculate average ADC sample value
//    g_stCpuToClaData.fMeaCurrentOffsetA = SumB / SampleSize;    //Calculate average ADC sample value
//    g_stCpuToClaData.fRefCurrentOffsetB = SumC / SampleSize;
//    g_stCpuToClaData.fMeaCurrentOffsetB = SumD / SampleSize;

}
//===========================================================================
// End of file.
//===========================================================================
