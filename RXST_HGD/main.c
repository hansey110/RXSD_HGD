#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
//#include "CLAShared.h"
#include <string.h>
#include <stdint.h>

__interrupt void epwm1_isr(void);
__interrupt void epwm1_tzint_isr(void);
__interrupt void epwm2_tzint_isr(void);
__interrupt void epwm3_tzint_isr(void);
void PI_CUR_MACRO(PI_CUR_CONTROLLER *v);
void RESET_PI_CUR(PI_CUR_CONTROLLER *v);
void InitDriverParam(void);
void InitOffset(void);
Uint16 temp1;
Uint16 temp2;
Uint16 index=0;
Uint16 SampleSize=1000;
Uint16 SampleFlag=0;
Uint32 SumA=0;
Uint32 SumB=0;
Uint32 SumC=0;
Uint32 SumD=0;


void InitCLA(void);

#define PWM_OFF()             EPwm1Regs.AQCSFRC.all = 0x05;       \
                              EPwm2Regs.AQCSFRC.all = 0x05;       \
                              EPwm4Regs.AQCSFRC.all = 0x05;       \
                              EPwm5Regs.AQCSFRC.all = 0x05;

#define PWM_ON()              EPwm1Regs.AQCSFRC.all = 0x0;       \
                              EPwm2Regs.AQCSFRC.all = 0x0;       \
                              EPwm4Regs.AQCSFRC.all = 0x0;       \
                              EPwm5Regs.AQCSFRC.all = 0x0;

Uint16 HallTest=0;
#pragma DATA_SECTION(c_stDriverParamA,"ControlParams") //不需要在线烧写参数，就不需要分配flash地址
const TDriverParam c_stDriverParamA ={
                                      MOTOR_L_A,
                                      MOTOR_R_A,
                                      MOTOR_POLES_A,
                                      MOTOR_TYPE_A,
                                      POWER_VOLTAGE_LIMIT_A,
                                      POWER_CURRENT_LIMIT_A,
                                      MAX_WORK_AREA_A ,
                                      MIN_WORK_AREA_A,
                                      CURRENT_PI_KP_A,
                                      CURRENT_PI_TI_A,
                                      CURRENT_PI_KC_A,
                                      DRIVER_VOLTAGE_LIMIT_A,
                                      VELOCITY_PI_KP_A,
                                      VELOCITY_PI_TI_A,
                                      VELOCITY_PI_KC_A,
                                      VELOCITY_LP_A1,
                                      VELOCITY_LP_A2,
                                      DRIVER_CURRENT_LIMIT_A,
                                      ACC_MAX_A,
                                      POSITION_PI_OUTER_KP_A,
                                      POSITION_PI_INNER_KP_A,
                                      POSITION_PI_TI_A,
                                      POSITION_PI_KC_A,
                                      POSITION_PI_THRESHOLD_A,
                                      VELOCITY_MAX_LIMIT_A,
                                      ELE_ANGLE_OFFSET_A,
                                      RESOLVER_EXCITE_FREQ_A,
                                        };


main()
{
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
    InitSysCtrl();

    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2803x_PieCtrl.c file.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2803x_DefaultIsr.c.
    // This function is found in DSP2803x_PieVect.c.
    InitPieVectTable();

#ifdef _FLASH
    // Copy time critical code and Flash setup code to RAM
    // The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the F28069.cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

       // Copy CLA code from flash to RAM
    memcpy(&Cla1ProgRunStart, &Cla1ProgLoadStart, (Uint32)&Cla1ProgLoadSize);

       // Copy CLA math tabes from flash to RAM
    memcpy(&CLA1mathTablesRunStart, &CLA1mathTablesLoadStart,(Uint32)&CLA1mathTablesLoadSize);
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    //Flash28_API_RunStart
    InitFlash();
#endif //FLASH

    SetParameters();
    InitController();
    InitDriverParam();

    InitCLA();

    InitEPwm();

    EPwm1Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON
    EPwm2Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON
    EPwm4Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON
    EPwm5Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON

    // GPIO4(使能信号) GPIO53(Fault指示灯) GPIO55(Fault信号)
    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;     // Enable pull-up for GPIO10
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;    // 配置为GPIO4
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;     //配置为输入

    GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;     // Enable pull-up for GPIO55
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;    // 配置为GPIO55
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;     //配置为输出

    GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;     // Enable pull-up for GPIO55
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;    // 配置为GPIO55
    GpioCtrlRegs.GPBDIR.bit.GPIO55 = 1;     //配置为输出

    EDIS;

//    //IGBT 欠压和故障
//    // GPIO43(DRV_UVLO),GPIO52(DRV_FAULT)
//    EALLOW;
//    GpioCtrlRegs.GPBPUD.bit.GPIO43 = 0;    // Enable pull-up for GPIO43
//    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;    // 配置为GPIO43
//    GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;     //配置为输入
//
//    GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;    // Enable pull-up for GPIO52
//    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;    // 配置为GPIO52
//    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;     //配置为输入
//
//    GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1;          // output : MCU_PWMEN
//    EDIS;
//
//    PWM_ENABLE();





    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    EALLOW;  // This is needed to write to EALLOW protected register
    //   PieVectTable.CLA1_INT1 = &cla1_isr1;
    PieVectTable.EPWM1_INT = &epwm1_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    // Step 4. Initialize all the Device Peripherals:
    InitAdc();         // For this example, init the ADC
//    InitAdcAio();      //配置比较器
    // Step 5. User specific code, enable interrupts:

    // Enable EPWM INTn in the PIE: Group 2 interrupt 1-3

    PieCtrlRegs.PIEIER3.bit.INTx1 = 1; // Enable INT 3.1 in the PIER

    IER |= M_INT3;


    EINT;                                    // Enable Global interrupt INTM
    ERTM;                                    // Enable Global realtime interrupt DBGM

    for(;;)
    {

    }
}

__interrupt void epwm1_isr(void)
{
//    TimeSequence = (TimeSequence>=10)?(1):(TimeSequence++);
//
//    //每10ms没有数据来就清一次
//    g_iNewDataTimeCount++;
//    if(g_iNewDataTimeCount>=100)
//    {
//        g_iNewDataTimeCount = 0;
//        g_iRecvCount = 0;
//    }
//
//    //50khz的频率返回数据
//    if(g_iSendStateCount>=g_iRefreshCount)
//    {
//        g_iSendStateCount = 1;
//        g_iSendCount=0;
//        g_bSendFlag=1;
//    }
//    else
//    {
//        g_iSendStateCount++;
//    }
//
//    //如果停止模式就清除故障，把能清除掉的清除了
//    if(g_stCommand.WorkMode==ewmHold && g_stCpuToClaData.iWorkMode==ewmHold)
//    {
//        g_stRespond.State.all=0x00;
//    }
//
    while(AdcRegs.ADCINTFLG.bit.ADCINT1==0){}
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;    // Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE;



//    if(!SampleFlag)
//    {
//        if( index < SampleSize )
//        {
//
//            SumA += AdcResult.ADCRESULT0;               //Get sample
//            SumB += AdcResult.ADCRESULT1;               //Get sample
//            SumC += AdcResult.ADCRESULT2;
//            SumD += AdcResult.ADCRESULT3;
//
//            index++;
//        }
//        else
//        {
//            SampleFlag=1;
//        }
//
//        g_stCpuToClaData.fRefCurrentOffsetA = SumA / SampleSize;    //Calculate average ADC sample value
//        g_stCpuToClaData.fMeaCurrentOffsetA = SumB / SampleSize;    //Calculate average ADC sample value
//        g_stCpuToClaData.fRefCurrentOffsetB = SumC / SampleSize;
//        g_stCpuToClaData.fMeaCurrentOffsetB = SumD / SampleSize;
//
//
//    }





    g_stCpuToClaData.fRefCurrentA=(int16)(AdcResult.ADCRESULT0-g_stCpuToClaData.fRefCurrentOffsetA)*0.0054;  //
    g_stCpuToClaData.fMeaCurrentA=(int16)(AdcResult.ADCRESULT1-g_stCpuToClaData.fMeaCurrentOffsetA)*0.006;  // 200mV/A

    g_stCpuToClaData.fRefCurrentB=(int16)(AdcResult.ADCRESULT2-g_stCpuToClaData.fRefCurrentOffsetB)*0.0054;  //
    g_stCpuToClaData.fMeaCurrentB=(int16)(AdcResult.ADCRESULT3-g_stCpuToClaData.fMeaCurrentOffsetB)*0.006;


    //Fault
    GpioDataRegs.GPBCLEAR.bit.GPIO55=1;

    //Led
    GpioDataRegs.GPBCLEAR.bit.GPIO53=1;

    if(GpioDataRegs.GPADAT.bit.GPIO4)
    {
        PWM_ON();
        g_piCurLoopA.Ref = g_stCpuToClaData.fRefCurrentA;
        g_piCurLoopA.Fbk = g_stCpuToClaData.fMeaCurrentA;
        PI_CUR_MACRO(&g_piCurLoopA);

        temp1 = (Uint16)(PWM_Halfperiod-g_piCurLoopA.Out*PWM_Halfperiod/27);
        temp2 = (EPwm1Regs.CMPA.half.CMPA<Dead_Time)?(0):(EPwm1Regs.CMPA.half.CMPA-Dead_Time);

        EPwm1Regs.CMPA.half.CMPA = temp1;
        EPwm1Regs.CMPB = temp2;

        EPwm2Regs.CMPA.half.CMPA = temp2;
        EPwm2Regs.CMPB = temp1;

//        EPwm1Regs.CMPA.half.CMPA = (Uint16)(PWM_Halfperiod-g_piCurLoopA.Out*PWM_Halfperiod/g_stDriverParamA.fDcPowerVoltage);
//        EPwm1Regs.CMPB = (EPwm1Regs.CMPA.half.CMPA<Dead_Time)?(0):(EPwm1Regs.CMPA.half.CMPA-Dead_Time);
//
//        EPwm2Regs.CMPA.half.CMPA = EPwm1Regs.CMPB;
//        EPwm2Regs.CMPB = EPwm1Regs.CMPA.half.CMPA;

        g_piCurLoopB.Ref = g_stCpuToClaData.fRefCurrentB;
        g_piCurLoopB.Fbk = g_stCpuToClaData.fMeaCurrentB;
        PI_CUR_MACRO(&g_piCurLoopB);

        temp1=(Uint16)(PWM_Halfperiod-g_piCurLoopB.Out*PWM_Halfperiod/27);
        temp2=(EPwm4Regs.CMPA.half.CMPA<Dead_Time)?(0):(EPwm4Regs.CMPA.half.CMPA-Dead_Time);

        EPwm4Regs.CMPA.half.CMPA =temp1;
        EPwm4Regs.CMPB=temp2;

        EPwm5Regs.CMPA.half.CMPA = temp2;
        EPwm5Regs.CMPB = temp1;

//        EPwm4Regs.CMPA.half.CMPA = (Uint16)(PWM_Halfperiod-g_piCurLoopB.Out*PWM_Halfperiod/24);
//        EPwm4Regs.CMPB = (EPwm4Regs.CMPA.half.CMPA<Dead_Time)?(0):(EPwm4Regs.CMPA.half.CMPA-Dead_Time);
//
//        EPwm5Regs.CMPA.half.CMPA = EPwm4Regs.CMPB;
//        EPwm5Regs.CMPB = EPwm4Regs.CMPA.half.CMPA;
    }
    else
    {
        InitOffset();
        RESET_PI_CUR(&g_piCurLoopA);
        RESET_PI_CUR(&g_piCurLoopB);

        EPwm1Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON
        EPwm2Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON
        EPwm4Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON
        EPwm5Regs.AQCSFRC.all = 0x09;  //上桥臂off，下桥臂ON
    }


    // Clear INT flag for this timer
    EPwm1Regs.ETCLR.bit.INT = 1;

    // Acknowledge this interrupt to receive more interrupts from group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


void InitCLA(void)
{
//#ifdef _FLASH
//    MemCopy(&Cla1funcsLoadStart, &Cla1funcsLoadEnd, &Cla1funcsRunStart);
//    MemCopy(&Cla1mathTablesLoadStart, &Cla1mathTablesLoadEnd, &Cla1mathTablesRunStart);
//#endif
    EALLOW;
    Cla1Regs.MVECT1 = (Uint16) (&Cla1Task1);   //PMSM
    Cla1Regs.MVECT2 = (Uint16) (&Cla1Task2);   //BLDC
    Cla1Regs.MVECT8 = (Uint16) (&Cla1Task8);   //需要在Task8里面对CLA的参数进行初始化
    Cla1Regs.MPISRCSEL1.bit.PERINT1SEL = CLA_INT1_NONE; // ADCINT1 starts Task 1
    Cla1Regs.MPISRCSEL1.bit.PERINT2SEL = CLA_INT2_NONE; // ADCINT1 starts Task 1
    Cla1Regs.MMEMCFG.bit.PROGE = 1;          // Map CLA program memory to the CLA
    Cla1Regs.MCTL.bit.IACKE = 1;             // Enable IACK to start tasks via software
    Cla1Regs.MIER.all = 0xFF; //(M_INT1 | M_INT2 | M_INT8);   // Enable Task 1 and Task 8
    Cla1Regs.MMEMCFG.bit.RAM0E   = 1;
    Cla1Regs.MMEMCFG.bit.RAM1E   = 1;
    EDIS;

    Cla1ForceTask8();
}


void InitOffset(void)
{
    if( index < SampleSize )
    {
        SumA += AdcResult.ADCRESULT0;               //Get sample
        SumB += AdcResult.ADCRESULT1;               //Get sample
        SumC += AdcResult.ADCRESULT2;
        SumD += AdcResult.ADCRESULT3;

        index++;
    }
    else
    {
        g_stCpuToClaData.fRefCurrentOffsetA = SumA / SampleSize;    //Calculate average ADC sample value
        g_stCpuToClaData.fMeaCurrentOffsetA = SumB / SampleSize;    //Calculate average ADC sample value
        g_stCpuToClaData.fRefCurrentOffsetB = SumC / SampleSize;
        g_stCpuToClaData.fMeaCurrentOffsetB = SumD / SampleSize;

        index=0;
        SumA=0;
        SumB=0;
        SumC=0;
        SumD=0;
    }



}

//初始化驱动器参数
void InitDriverParam(void)
{
    g_piCurLoopA.Freq = INT_FREQ;
    g_piCurLoopA.Kp = g_stDriverParamA.fCurPidKp;
    g_piCurLoopA.Ti = g_stDriverParamA.fCurPidTi;
    g_piCurLoopA.Ki = 1.0/(2.0*g_piCurLoopA.Ti*g_piCurLoopA.Freq);
    g_piCurLoopA.Kc = g_stDriverParamA.fCurPidKc;

    g_piCurLoopA.OutMax = g_stDriverParamA.fDcPowerVoltage;
    g_piCurLoopA.OutMin = -g_stDriverParamA.fDcPowerVoltage;


    g_piCurLoopB.Freq = g_piCurLoopA.Freq;
    g_piCurLoopB.Kp = g_piCurLoopA.Kp;
    g_piCurLoopB.Ti = g_piCurLoopA.Ti;
    g_piCurLoopB.Ki = g_piCurLoopA.Ki;
    g_piCurLoopB.Kc =  g_piCurLoopA.Kc;

    g_piCurLoopB.OutMax = g_stDriverParamA.fDcPowerVoltage;
    g_piCurLoopB.OutMin = -g_stDriverParamA.fDcPowerVoltage;

//
//    //初始化PWM参考低通
//    g_lpfPwmPercent.Umax = 100;
//    g_lpfPwmPercent.Umin = -100;
//    g_lpfPwmPercent.LpFreq= 0.05;
//
//    temp  = 3.14159f*g_lpfPwmPercent.LpFreq;
//    temp = ((float)INT_FREQ)/temp;
//    g_lpfPwmPercent.KOut = (temp-1)/(temp+1);
//    g_lpfPwmPercent.KIn =  1.0/(temp+1);
//
//
//    //初始化Q轴电流参考低通
//    g_lpfRefCurrentQ.Umax = 150;
//    g_lpfRefCurrentQ.Umin = -150;
//    g_lpfRefCurrentQ.LpFreq = 0.2;
//    temp  = 3.14159f*g_lpfRefCurrentQ.LpFreq;
//    temp = ((float)INT_FREQ)/temp;
//    g_lpfRefCurrentQ.KOut = (temp-1)/(temp+1);
//    g_lpfRefCurrentQ.KIn =  1.0/(temp+1);

}


void PI_CUR_MACRO(PI_CUR_CONTROLLER *v)
{
   if(v->Ti>0)
   {
       v->Ki = 1.0/(2.0*v->Ti*v->Freq);
   }

   // Compute the error
   v->Err = v->Ref - v->Fbk;

   // Compute the proportional output
   v->Up = v->Kp*v->Err;

   if(v->Ti<=0)
   {
       v->Ui = 0;
   }
   else
   {
       if(v->Kc<0)    // Kc>0和Kc<0时才有的两种不同的退饱和方法
       {
           v->Ui = ( v->Ui + v->Ki*(v->Up+v->Up1) )*v->ClampingSign;
       }
       else
       {
           v->Ui = v->Ui + v->Ki*(v->Up+v->Up1) + v->Kc*v->SatErr;
       }
   }

    // Compute the pre-saturated output
    v->OutPreSat = v->Up + v->Ui;

    // Saturate the output
    if (v->OutPreSat > v->OutMax)
    {
        v->Out = v->OutMax;
        v->ClampingSign = 0;
    }
    else
    {
        if (v->OutPreSat < v->OutMin)
        {
            v->Out = v->OutMin;
            v->ClampingSign = 0;
        }
        else
        {
            v->Out = v->OutPreSat;
            v->ClampingSign = 1;
        }
    }

    // Compute the saturate difference
    v->SatErr = v->Out - v->OutPreSat;

    // Update the previous proportional output
    v->Up1 = v->Up;

}

void RESET_PI_CUR(PI_CUR_CONTROLLER *v)
{
    v->Out = 0;
    v->Up = 0;
    v->Up1 = 0;
    v->Ui = 0;
    v->OutPreSat = 0;
    v->SatErr = 0;
    v->ClampingSign = 1;
    v->Err = 0;
    v->Fbk = 0;
    v->Ref = 0;
}
