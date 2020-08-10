#include "DSP28x_Project.h"

//Uint16 k=0;
//Uint16 i;
//Uint16 *p;
unsigned short *g_pCommand = (unsigned short *)&g_stCommand;
unsigned short *g_pRespond = (unsigned short *)&g_stRespond;

float g_fVdctest;
Uint16 g_iPostest;

struct ECAN_REGS ECanaShadow;
extern void FlashControlParams(TDriverParam stDriverParamA);
//===========================================================================
// No more.
//===========================================================================

void SetParameters(void)
{   // flash的常量参数赋值给全局变量参数
    g_stDriverParamA = c_stDriverParamA;
}

/*
 * 初始化控制器，速度前向低通滤波器，反馈低通滤波器
 */
void InitController(void)
{
    // 初始化编码器分辨力
    g_stPositionDataA.ldEncoderResolution = ((long double)360.0)/((long double)powf(2,ENCODER_BITS));
    g_stPositionDataA.ldEleAngleOffset=g_stDriverParamA.fEleAngleOffset;

}
// 获取编码器的值
void GetEncoder(void)
{

    Uint16 XB_tmp[3];

    static int16 g_iVelCnt=0;
    static Uint16 g_iFault=0;


    AD2S1210_Read((Uint16 *)&XB_tmp);               //大约花费10us，获取旋变的位置速度系信息
    g_iPosCnt = ((Uint16)XB_tmp[0]) & 0xFFFF;
    g_iVelCnt = (int16)XB_tmp[1];    // 用的是补码

    Spia_xmit(XB_FAULT_REG);
    g_iFault = Spia_xmit(XB_POSITIONH_REG) & 0xFF;
    if(g_iFault!=0)
    {
//        g_stRespond.State.bit.ENCODER_FAULT0 = 1;
    }



    g_stPositionDataA.ldPosition=g_iPosCnt*g_stPositionDataA.ldEncoderResolution;
    g_stCpuToClaData.fPosition = (float)g_stPositionDataA.ldPosition;
    g_stCpuToClaData.fMotorVel=g_iVelCnt*1.6764;  //速度反馈不滤波，在前向通道上加   °/s
    g_stCpuToClaData.fMotorVel=g_stCpuToClaData.fMotorVel*0.166667;  //rpm

}

// 处理编码器数据 计算速度、电角度等
void ProcessEncoder(void)
{
    GetEncoder(); // 获取编码器数据

    static float32 ele_angle=0.0;
    switch((g_stCpuToClaData.iWorkMode&0x0F))
    {
        //  寻找电气零位
        case ewmMcEleAngleZero:
            g_stPositionDataA.ldEleAngleOffset = g_stCpuToClaData.fPosition;
            break;
        default:
            ;
            break;
    }

    //计算电角度
    ele_angle = g_stDriverParamA.fMotorPoles*(g_stPositionDataA.ldPosition-g_stPositionDataA.ldEleAngleOffset);  //degree

    if(ele_angle>0)
    {
        ele_angle=ele_angle-(long)ele_angle/360*360;
    }
    else
    {
        ele_angle=ele_angle+((long)ele_angle/360*(-1)+1)*360;
    }

    g_stPositionDataA.ldEleAngle=2*3.1415926*(ele_angle)/360;

    EleAngleA = g_stPositionDataA.ldEleAngle;
}

//void ProcessPositionLoopA(void)
//{
//    /****************位置回路运算，并生成命令传递给CLA********************/
//    switch(g_stCpuToClaData.iWorkMode&0x0F)
//    {
//        case ewmHold:     // 待机工作模式
//            RESET_PI_POS(g_piPosLoopA);
//            RESET_PI_VEL(g_piVelLoopA);
//            RESET_LP_FILTER(g_lpfVelLoopA1);
//            RESET_LP_FILTER(g_lpfVelLoopA2);
//            RESET_LP_FILTER(g_lpfMeasureVelA);
////            g_stCpuToClaData.fRefPos = 0;
//            g_stCpuToClaData.fRefPos=g_stCpuToClaData.fPosition;
//            g_stCpuToClaData.fDeltaPos=0;
//            g_stCpuToClaData.fRefCurrentQ = 0;
//            g_stCpuToClaData.fLastRefVel = 0;
//            g_stCpuToClaData.fRefVel = 0;
//            g_iPosRef=g_stCpuToClaData.fPosition;
//            g_stRespond.WorkMode = g_stCpuToClaData.iWorkMode&0x0F;
//            break;
//
//        case ewmPositionCloseGuide:     // 位置闭环工作模式
//            g_piPosLoopA.Ref = g_stCpuToClaData.fPosition +g_stCpuToClaData.fDeltaPos;  //位置参考
//
////            g_piPosLoopA.Ref = g_iPosRef;  //位置参考
//
//            g_piPosLoopA.Fbk = g_stCpuToClaData.fPosition; //位置反馈
//            PI_POS_MACRO(g_piPosLoopA);   //  位置环PI运算
//            break;
//
//        default:    // 其他状态
//            ;
//            g_stCpuToClaData.fRefPos=g_stCpuToClaData.fPosition;
////            g_stCpuToClaData.fRefVoltage = 0;
////            g_stRespond.WorkMode = 0;
//            break;
//        }
//
//}
//
//void ProcessVelocityLoopA(void)
//{
//    errVel = g_stCpuToClaData.fRefVel-g_stCpuToClaData.fLastRefVel;
//    if(fabs(errVel)>g_stCpuToClaData.fVelIncrement)
//    {
//        if(errVel>0)
//        {
//            g_stCpuToClaData.fLastRefVel = g_stCpuToClaData.fLastRefVel + g_stCpuToClaData.fVelIncrement;
//        }
//        else
//        {
//            g_stCpuToClaData.fLastRefVel = g_stCpuToClaData.fLastRefVel - g_stCpuToClaData.fVelIncrement;
//        }
//    }
//    else
//    {
//        g_stCpuToClaData.fLastRefVel = g_stCpuToClaData.fRefVel;
//
//    }
//
//    //限速
//    if(fabs(g_stCpuToClaData.fLastRefVel)>g_stDriverParamA.fVelMaxLimit)
//    {
//        g_stCpuToClaData.fLastRefVel = (g_stCpuToClaData.fLastRefVel>0)?(g_stDriverParamA.fVelMaxLimit):(-g_stDriverParamA.fVelMaxLimit);
//    }
//
//
//
//    switch(g_stCpuToClaData.iWorkMode&0x0F)
//    {
//        case ewmHold:     // 待机工作模式
//            RESET_PI_POS(g_piPosLoopA);
//            RESET_PI_VEL(g_piVelLoopA);
//            RESET_LP_FILTER(g_lpfVelLoopA1);
//            RESET_LP_FILTER(g_lpfVelLoopA2);
//            RESET_LP_FILTER(g_lpfMeasureVelA);
////            g_stCpuToClaData.fRefPos = 0;
//            g_stCpuToClaData.fRefPos=g_stCpuToClaData.fPosition;
//            g_stCpuToClaData.fDeltaPos=0;
//            g_stCpuToClaData.fRefCurrentQ = 0;
//            g_stCpuToClaData.fLastRefVel = 0;
//            g_stCpuToClaData.fRefVel = 0;
//            g_stRespond.WorkMode = g_stCpuToClaData.iWorkMode&0x0F;
//            break;
//
//        case ewmPositionCloseGuide:
//            // 速度控制器运算
//            g_stCpuToClaData.fLastRefVel = g_piPosLoopA.Out;  //速度环速度参考
//            g_piVelLoopA.Ref = g_stCpuToClaData.fLastRefVel;
//            g_piVelLoopA.Fbk = g_stCpuToClaData.fMotorVel;
//            PI_VEL_MACRO(g_piVelLoopA);
//
//            // 前向第一个低通滤波器
//            g_lpfVelLoopA1.Ref = g_piVelLoopA.Out;
//            LP_FILTER_MACRO(g_lpfVelLoopA1);
//            g_stCpuToClaData.fRefCurrentQ = g_lpfVelLoopA1.Out;
//            g_stRespond.WorkMode = g_stCpuToClaData.iWorkMode&0x0F;
//            break;
//
//        case ewmVelocityCloseGuide:
//            RESET_PI_POS(g_piPosLoopA);
//            g_piVelLoopA.Ref = g_stCpuToClaData.fLastRefVel;  // 参考来自主控
//            g_piVelLoopA.Fbk = g_stCpuToClaData.fMotorVel;
//            PI_VEL_MACRO(g_piVelLoopA);
//
//            // 前向第一个低通滤波器
//            g_lpfVelLoopA1.Ref = g_piVelLoopA.Out;
//            LP_FILTER_MACRO(g_lpfVelLoopA1);
//            g_stCpuToClaData.fRefCurrentQ = g_lpfVelLoopA1.Out;
//            g_stRespond.WorkMode = g_stCpuToClaData.iWorkMode&0x0F;
//            break;
//
//        default:
//            ;
//            g_stCpuToClaData.fRefPos=g_stCpuToClaData.fPosition;
//            break;
//    }
//
//}


// 所有故障判断在此函数执行
void CheckFault(void)
{
    // 过流保护=====current overtop checking===================
    if((g_stMotorCurrentA.U>g_stDriverParamA.fPeakDriveCurrent)
            ||(g_stMotorCurrentA.V>g_stDriverParamA.fPeakDriveCurrent)
            ||(g_stMotorCurrentA.W>g_stDriverParamA.fPeakDriveCurrent)
            ||g_iEPwmTZIntCount>500)
    {
        g_stRespond.State.bit.OVER_CURRENT2 = 1;
    }

    //过压
//    if(g_iMeaDCVoltage>800)
//    {
//        g_stRespond.State.bit.OVER_VOLTAGE3 = 1;
//    }
//
//    //欠压故障 高电平正常 低电平故障；
//    if(DRV_UVLO==0)
//    {
//        g_stRespond.State.bit.LOW_VOLTAGE7 = 1;
//    }

    //IGBT故障  高电平正常 低电平故障；
    if(DRV_FAULT==0)
    {
        g_stRespond.State.bit.IGBT_FAULT6 = 1;
    }

    //过热
//    if(g_iDriverTemp>80 || g_iMotorTemp>80)
//    {
//        g_stRespond.State.bit.OVER_TEMP1 = 1;
//    }

    g_stCpuToClaData.iState.all=g_stRespond.State.all;

}

void CanTx(void)
{
    if((GpioDataRegs.GPBDAT.bit.GPIO33==0) || (GpioDataRegs.GPBDAT.bit.GPIO42==0))
    {
        ECanaMboxes.MBOX0.MDL.byte.BYTE0=0x01;
    }
    else
    {
        ECanaMboxes.MBOX0.MDL.byte.BYTE0=0x00;
    }
    ECanaShadow.CANTRS.all = 0;
    ECanaShadow.CANTRS.bit.TRS0 = 1;             // Set TRS for mailbox under test
    ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

}

void GetCanCommand(void)
{
    float Ref=0;
    Uint16 DataH=0;
    Uint16 DataL=0;
    Uint16 Data=0;
    ECanaMboxes.MBOX16.MDL.all=0;
//    if(ECanaRegs.CANRMP.all== 0x00010000)
    if(ECanaRegs.CANRMP.bit.RMP16)
    {
        ECanaShadow.CANRMP.all = ECanaRegs.CANRMP.all;
        ECanaShadow.CANRMP.bit.RMP16 = 1;
        ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;

        DataH=ECanaMboxes.MBOX16.MDL.byte.BYTE2;
        DataL=ECanaMboxes.MBOX16.MDL.byte.BYTE3;
        Data=(DataH<<8)|DataL;
        if(NodeID==0x03)
        {
            Ref=0.01*Data*40;    //每个轴减速比不一样
        }
        if(NodeID==0x02)
        {
            Ref=0.01*Data*30;
        }

        if(NodeID==0x01)
        {
            Ref=0.01*Data*15;
        }

        if(ECanaMboxes.MBOX16.MDL.byte.BYTE1==1)
        {
            Ref=-Ref;
        }

        switch(ECanaMboxes.MBOX16.MDL.byte.BYTE0&0xFF)
        {
        case 0x0:
            g_stCpuToClaData.iWorkMode = ewmHold;
            break;
        case 0x01:
            g_stCpuToClaData.iWorkMode = ewmPositionCloseGuide;
            g_stCpuToClaData.fDeltaPos = Ref;
            break;
        case 0x02:
            g_stCpuToClaData.iWorkMode = ewmVelocityCloseGuide;
            g_stCpuToClaData.fRefVel = Ref;
            break;
        default:
            g_stCpuToClaData.iWorkMode = 0;
            g_stCpuToClaData.fRefCurrentQ = 0;
            break;
        }
    }

}

void GetSerialCommand(void)
{

    if(1==ScibRegs.SCIRXST.bit.RXERROR)
    { // SCI的故障位进行判断，如果出现故障，则对SCI复位
        ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
        DELAY_US(5); // 延时5us
        ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;

        ScibRegs.SCICTL1.bit.SWRESET = 0;
        DELAY_US(5); // 延时5us
        ScibRegs.SCICTL1.bit.SWRESET = 1;

        DELAY_US(5); // 延时5us
        DELAY_US(50); // 延时50us
    }
    else
    {// 当处于接收状态时，连续接收数据，如果中断打断也不会影响接收的连续性
        while(ScibRegs.SCIFFRX.bit.RXFFST!=0)
        {
            iRevData = ScibRegs.SCIRXBUF.all;

            if(g_iRecvCount<9)
            {
                *(g_pCommand+g_iRecvCount) = iRevData&0x0FF;
            }
            g_iRecvCount++;

            if(g_iRecvCount>=9)
            {
                g_bNewCommandArrived = 1;
                g_iRecvCount=0;
            }
//            g_iRecvCount=(g_iRecvCount>=9)?(0):(g_iRecvCount);
        }
    }

    ////    if(k==4)
    ////    {
    ////        SciaRegs.SCIFFRX.bit.RXFIFORESET=0;
    ////        SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
    ////    }

//        k=(k>=9)?(0):(k);
//    //    if(i>=9)
//    //    {
//    //        i=0;
//    //    }
//        p = (unsigned short*)&g_stCommand;
//        while((SciaRegs.SCIFFRX.bit.RXFFST!=0)&&(k<9))
//        {
//            iRevData = SciaRegs.SCIRXBUF.all;
//            if(k<9)
//            {
//                *(p+k) = iRevData&0x0FF;
//            }
//            k++;
//        }
//
//        g_bNewCommandArrived = 1;
//
//            ScibRegs.SCICTL1.bit.SWRESET = 0;
//            ScibRegs.SCICTL1.bit.SWRESET = 1;
//    //    }
}


void ProcessSerialCommand(void)
{
    Uint16 i;
    if(g_bNewCommandArrived)
    {
        g_bNewCommandArrived = 0;
        // 首先判断帧头和帧尾
        if((0x0FF==g_stCommand.Header)&&(0x0D==g_stCommand.End))
        {
            iChecksum = 0;
            // 判断校验码
            for(i=0;i<6;i++)
            {
                iChecksum += (*(g_pCommand+i+1))&0x00FF;
            }

            iChecksum = iChecksum&0x0FF;

            // 如果校验码正确，进行命令解码
            if(iChecksum==g_stCommand.Checksum)
            {
                g_stRespond.State.bit.COMMAND_FAULT4 = 0;
                switch(g_stCommand.WorkMode&0xFF)
                {
                case ewmHold:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_iEPwmTZIntCount=0;  //停止按钮清除 pwm cycle by cycle 计数值；
                    break;
                case ewmCurrentOpenGuide:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_stCpuToClaData.fRefVoltageQ = CtoF32(&g_stCommand.Param4);
                    break;
                case ewmCurrentCloseGuide:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_stCpuToClaData.fRefCurrentQ = CtoF32(&g_stCommand.Param4);
                    break;
                case ewmVelocityCloseGuide:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_stCpuToClaData.fRefVel = CtoF32(&g_stCommand.Param4)*6;
//                    g_stCpuToClaData.fRefVoltageQ = 0;
                    break;
                case ewmPositionCloseGuide:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_stCpuToClaData.fRefPos = CtoF32(&g_stCommand.Param4);
//                    g_stCpuToClaData.fRefVoltageQ = 0;
                    break;
                case ewmMcEleAngleZero:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_stCpuToClaData.fRefCurrentD = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefVoltageQ = 0;
                    break;

                case ewmBLDCOpenGuide:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_stCpuToClaData.fRefPwmPercent = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefVoltageQ = 0;
                    break;

                case ewmRefreshInductance:
                    g_stDriverParamA.fMotorL = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    break;

                case ewmRefreshResistance:
                    g_stDriverParamA.fMotorR = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    break;

                case ewmRefreshMotorPoles:
                    g_stDriverParamA.fMotorPoles = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    break;

                case ewmRefreshMotorType:
                    g_stDriverParamA.fMotorType = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    break;

                case ewmRefreshExcitationFreq:
                    g_stDriverParamA.fExcitationFreq = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
                    AD2S1210_Resolver.EXC_Frq = (Uint16)(g_stDriverParamA.fExcitationFreq*32768/10000+0.5);
                    AD2S1210_SetPara(XB_EXC_FRQ_REG, AD2S1210_Resolver.EXC_Frq<<8);         // 设置激磁频率
                    break;


                case ewmRefreshMotorPeakCurrent:
                    g_stDriverParamA.fPeakDriveCurrent = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    Cla1ForceTask8();
                    break;

                case ewmRefreshPowerBusVoltage:
                    g_stDriverParamA.fDcPowerVoltage = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    Cla1ForceTask8();
                    break;

                case ewmRefreshCLoopKp:
                    g_stDriverParamA.fCurPidKp = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    Cla1ForceTask8();
                    break;

                case ewmRefreshCLoopTi:
                    g_stDriverParamA.fCurPidTi = CtoF32(&g_stCommand.Param4);
                    g_stCpuToClaData.fRefCurrentQ = 0;
//                    InitController();
                    Cla1ForceTask8();
                    break;


                case ewmFlashControlParam:
                    g_stCommand.WorkMode=ewmHold;
                    g_bNewCommandArrived = 0;
                    FlashControlParams(g_stDriverParamA);
                    break;


                default:
                    g_stCpuToClaData.iWorkMode = 0;
                    g_stCpuToClaData.fRefCurrentQ = 0;
                    break;
                }
            }
            else
            {
                g_stRespond.State.bit.COMMAND_FAULT4 = 1;
            }
        }
        else
        {
            g_stRespond.State.bit.COMMAND_FAULT4 = 1;
        }
    }
}

void ReturnDataToMc(void)
{
    Uint16 i;

    if(g_bSendFlag)
    {
    // 返回母线电压
    F32toC2(g_iMeaDCVoltage, (unsigned short*)(&(g_stRespond.MeaDcVoltageHigh)));

    // 返回q轴测量电流
    F32toC2(g_fMeaCurrentQ, (unsigned short*)(&(g_stRespond.CurrentQHigh)));

    // 返回d轴测量电流
    F32toC2(g_fMeaCurrentD, (unsigned short*)(&(g_stRespond.CurrentDHigh)));

    // 返回U相测量电流
    F32toC2(g_fMeaCurrentU, (unsigned short*)(&(g_stRespond.CurrentUHigh)));

    // 返回V相测量电流
    F32toC2(g_fMeaCurrentV, (unsigned short*)(&(g_stRespond.CurrentVHigh)));

    // 返回W相测量电流
    F32toC2(g_fMeaCurrentW, (unsigned short*)(&(g_stRespond.CurrentWHigh)));

    // 返回位置
    g_stRespond.EncoderLow=g_iPosCnt&0x00FF;
    g_stRespond.EncoderHigh=(g_iPosCnt>>8)&0x00FF;

//    g_stRespond.EncoderLow=g_iPostest&0x00FF;
//    g_stRespond.EncoderHigh=(g_iPostest>>8)&0x00FF;
//
//    g_iPostest=g_iPostest+200;


    // 返回设置的母线电压
    F32toC2(g_stDriverParamA.fDcPowerVoltage, (unsigned short*)(&(g_stRespond.SetDcVoltageHigh)));

    //返回电机类型
    g_stRespond.MotorType =(Uint16)g_stDriverParamA.fMotorType;

    //返回激磁频率
    F32toC2(g_stDriverParamA.fExcitationFreq, (unsigned short*)(&(g_stRespond.ExcitationFreqHigh)));

    //返回极对数
    g_stRespond.MotorPoles= (Uint16)g_stDriverParamA.fMotorPoles;

    //返回峰值电流
    F32toC2(g_stDriverParamA.fPeakDriveCurrent, (unsigned short*)(&(g_stRespond.PeakCurrentHigh)));

    //反馈比例值 相当于1000倍量纲
    F32toC2((g_stDriverParamA.fCurPidKp*10), (unsigned short*)(&(g_stRespond.CurPidKpHigh)));

    //反馈积分值  相当于1000倍量纲
    F32toC2((g_stDriverParamA.fCurPidTi*10), (unsigned short*)(&(g_stRespond.CurPidTiHigh)));

    // 返回速度
    F32toC2_3(g_stCpuToClaData.fMotorVel, (unsigned short*)(&(g_stRespond.VelHigh)));


    // 返回温度
 //    F32toC2(g_stClaToCpuData.fMeaTemp, (unsigned short*)(&(g_stRespond.TemperatureHigh)));
//    F32toC2(g_iMcuTemp, (unsigned short*)(&(g_stRespond.TemperatureHigh)));

    /****************返回驱动器数据和状态给主控********************/

        // 置返回数据帧头
        g_stRespond.Header = 0x055;

        // 霍尔状态
        g_stRespond.iCurrentHallState = g_stCpuToClaData.iCurrentHallState;

        // 生成校验码
        iChecksum = 0;
        for(i=1;i<DATA_LENGTH-2;i++)
        {
            iChecksum += (*(g_pRespond+i))&0x0FF;
        }
        g_stRespond.Checksum = iChecksum&0x0FF;

        // 置返回数据帧尾
        g_stRespond.End = 0x0D;

        // 发送数据
        while(g_iSendCount<DATA_LENGTH)
        {
            if(3>ScibRegs.SCIFFTX.bit.TXFFST)
            {
                ScibRegs.SCITXBUF= (*(g_pRespond+g_iSendCount))&0x0FF;
                g_iSendCount++;
            }
        }
        g_bSendFlag=0;

    }
}

// 将4个字节转换成浮点
//#pragma CODE_SECTION(CtoF32,"ramfunc");
float CtoF32(unsigned short* iChar)
{
    unsigned short j[2];
    unsigned short *i;
    float f;
    j[0] = 0;
    j[1] = 0;

    i = (unsigned short*)&f;
    j[0] = ((*iChar)&0x0ff) + (((*(iChar+1))&0x0ff)<<8);
    j[1] = ((*(iChar+2))&0x0ff) + (((*(iChar+3))&0x0ff)<<8);
    *i = j[0];
    *(i+1) = j[1];

    return f;
}

// 将浮点转换成4个字节
//#pragma CODE_SECTION(F32toC,"ramfunc");
void F32toC(float f, unsigned short* iChar)
{
    unsigned short j[2];
    unsigned short *i;
    j[0] = 0;
    j[1] = 0;

    i = (unsigned short*)&f;
    j[0] = *i;
    j[1] = *(i+1);

    *iChar = j[0]&0x0ff;
    *(++iChar) = (j[0]>>8)&0x0ff;
    *(++iChar) = j[1]&0x0ff;
    *(++iChar) = (j[1]>>8)&0x0ff;
}

// 将浮点转换成2个字节，其最高位为符号位 100倍量纲
//#pragma CODE_SECTION(F32toC2,"ramfunc");
void F32toC2(float f, unsigned short* iChar)
{
    unsigned short j;
// 量冈乘了100
    j = ((unsigned short)(fabs(f)*100))&0x7FFF;

    if(f<0)
    {
        *iChar = ((j>>8)&0x7f)|0x80;
    }
    else
    {
        *iChar = ((j>>8)&0x7f);
    }

    *(++iChar) = j&0x0ff;
}

//3倍量纲转换
void F32toC2_3(float f, unsigned short* iChar)
{
    unsigned short j;
// 量冈乘了5
    j = ((unsigned short)(fabs(f)*3))&0x7FFF;

    if(f<0)
    {
        *iChar = ((j>>8)&0x7f)|0x80;
    }
    else
    {
        *iChar = ((j>>8)&0x7f);
    }

    *(++iChar) = j&0x0ff;
}

void GetTemp(void)
{
//    while(AdcRegs.ADCINTFLG.bit.ADCINT1==0){}   //不屏蔽这句，会造成发送数据发不出去
//    g_iMotorTemp=(AdcResult.ADCRESULT0-g_iMotorTempOffset);          // 温度采样，单位:摄氏度
//    g_iDriverTemp=(AdcResult.ADCRESULT1-g_iDriverTempOffset);          // 温度采样，单位:摄
    g_iMeaDCVoltage=AdcResult.ADCRESULT0*0.2276;          //  母线电压  量纲
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;    // Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE;
}

