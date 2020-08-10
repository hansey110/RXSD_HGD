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
{   // flash�ĳ���������ֵ��ȫ�ֱ�������
    g_stDriverParamA = c_stDriverParamA;
}

/*
 * ��ʼ�����������ٶ�ǰ���ͨ�˲�����������ͨ�˲���
 */
void InitController(void)
{
    // ��ʼ���������ֱ���
    g_stPositionDataA.ldEncoderResolution = ((long double)360.0)/((long double)powf(2,ENCODER_BITS));
    g_stPositionDataA.ldEleAngleOffset=g_stDriverParamA.fEleAngleOffset;

}
// ��ȡ��������ֵ
void GetEncoder(void)
{

    Uint16 XB_tmp[3];

    static int16 g_iVelCnt=0;
    static Uint16 g_iFault=0;


    AD2S1210_Read((Uint16 *)&XB_tmp);               //��Լ����10us����ȡ�����λ���ٶ�ϵ��Ϣ
    g_iPosCnt = ((Uint16)XB_tmp[0]) & 0xFFFF;
    g_iVelCnt = (int16)XB_tmp[1];    // �õ��ǲ���

    Spia_xmit(XB_FAULT_REG);
    g_iFault = Spia_xmit(XB_POSITIONH_REG) & 0xFF;
    if(g_iFault!=0)
    {
//        g_stRespond.State.bit.ENCODER_FAULT0 = 1;
    }



    g_stPositionDataA.ldPosition=g_iPosCnt*g_stPositionDataA.ldEncoderResolution;
    g_stCpuToClaData.fPosition = (float)g_stPositionDataA.ldPosition;
    g_stCpuToClaData.fMotorVel=g_iVelCnt*1.6764;  //�ٶȷ������˲�����ǰ��ͨ���ϼ�   ��/s
    g_stCpuToClaData.fMotorVel=g_stCpuToClaData.fMotorVel*0.166667;  //rpm

}

// ������������� �����ٶȡ���Ƕȵ�
void ProcessEncoder(void)
{
    GetEncoder(); // ��ȡ����������

    static float32 ele_angle=0.0;
    switch((g_stCpuToClaData.iWorkMode&0x0F))
    {
        //  Ѱ�ҵ�����λ
        case ewmMcEleAngleZero:
            g_stPositionDataA.ldEleAngleOffset = g_stCpuToClaData.fPosition;
            break;
        default:
            ;
            break;
    }

    //�����Ƕ�
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
//    /****************λ�û�·���㣬����������ݸ�CLA********************/
//    switch(g_stCpuToClaData.iWorkMode&0x0F)
//    {
//        case ewmHold:     // ��������ģʽ
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
//        case ewmPositionCloseGuide:     // λ�ñջ�����ģʽ
//            g_piPosLoopA.Ref = g_stCpuToClaData.fPosition +g_stCpuToClaData.fDeltaPos;  //λ�òο�
//
////            g_piPosLoopA.Ref = g_iPosRef;  //λ�òο�
//
//            g_piPosLoopA.Fbk = g_stCpuToClaData.fPosition; //λ�÷���
//            PI_POS_MACRO(g_piPosLoopA);   //  λ�û�PI����
//            break;
//
//        default:    // ����״̬
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
//    //����
//    if(fabs(g_stCpuToClaData.fLastRefVel)>g_stDriverParamA.fVelMaxLimit)
//    {
//        g_stCpuToClaData.fLastRefVel = (g_stCpuToClaData.fLastRefVel>0)?(g_stDriverParamA.fVelMaxLimit):(-g_stDriverParamA.fVelMaxLimit);
//    }
//
//
//
//    switch(g_stCpuToClaData.iWorkMode&0x0F)
//    {
//        case ewmHold:     // ��������ģʽ
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
//            // �ٶȿ���������
//            g_stCpuToClaData.fLastRefVel = g_piPosLoopA.Out;  //�ٶȻ��ٶȲο�
//            g_piVelLoopA.Ref = g_stCpuToClaData.fLastRefVel;
//            g_piVelLoopA.Fbk = g_stCpuToClaData.fMotorVel;
//            PI_VEL_MACRO(g_piVelLoopA);
//
//            // ǰ���һ����ͨ�˲���
//            g_lpfVelLoopA1.Ref = g_piVelLoopA.Out;
//            LP_FILTER_MACRO(g_lpfVelLoopA1);
//            g_stCpuToClaData.fRefCurrentQ = g_lpfVelLoopA1.Out;
//            g_stRespond.WorkMode = g_stCpuToClaData.iWorkMode&0x0F;
//            break;
//
//        case ewmVelocityCloseGuide:
//            RESET_PI_POS(g_piPosLoopA);
//            g_piVelLoopA.Ref = g_stCpuToClaData.fLastRefVel;  // �ο���������
//            g_piVelLoopA.Fbk = g_stCpuToClaData.fMotorVel;
//            PI_VEL_MACRO(g_piVelLoopA);
//
//            // ǰ���һ����ͨ�˲���
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


// ���й����ж��ڴ˺���ִ��
void CheckFault(void)
{
    // ��������=====current overtop checking===================
    if((g_stMotorCurrentA.U>g_stDriverParamA.fPeakDriveCurrent)
            ||(g_stMotorCurrentA.V>g_stDriverParamA.fPeakDriveCurrent)
            ||(g_stMotorCurrentA.W>g_stDriverParamA.fPeakDriveCurrent)
            ||g_iEPwmTZIntCount>500)
    {
        g_stRespond.State.bit.OVER_CURRENT2 = 1;
    }

    //��ѹ
//    if(g_iMeaDCVoltage>800)
//    {
//        g_stRespond.State.bit.OVER_VOLTAGE3 = 1;
//    }
//
//    //Ƿѹ���� �ߵ�ƽ���� �͵�ƽ���ϣ�
//    if(DRV_UVLO==0)
//    {
//        g_stRespond.State.bit.LOW_VOLTAGE7 = 1;
//    }

    //IGBT����  �ߵ�ƽ���� �͵�ƽ���ϣ�
    if(DRV_FAULT==0)
    {
        g_stRespond.State.bit.IGBT_FAULT6 = 1;
    }

    //����
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
            Ref=0.01*Data*40;    //ÿ������ٱȲ�һ��
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
    { // SCI�Ĺ���λ�����жϣ�������ֹ��ϣ����SCI��λ
        ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
        DELAY_US(5); // ��ʱ5us
        ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;

        ScibRegs.SCICTL1.bit.SWRESET = 0;
        DELAY_US(5); // ��ʱ5us
        ScibRegs.SCICTL1.bit.SWRESET = 1;

        DELAY_US(5); // ��ʱ5us
        DELAY_US(50); // ��ʱ50us
    }
    else
    {// �����ڽ���״̬ʱ�������������ݣ�����жϴ��Ҳ����Ӱ����յ�������
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
        // �����ж�֡ͷ��֡β
        if((0x0FF==g_stCommand.Header)&&(0x0D==g_stCommand.End))
        {
            iChecksum = 0;
            // �ж�У����
            for(i=0;i<6;i++)
            {
                iChecksum += (*(g_pCommand+i+1))&0x00FF;
            }

            iChecksum = iChecksum&0x0FF;

            // ���У������ȷ�������������
            if(iChecksum==g_stCommand.Checksum)
            {
                g_stRespond.State.bit.COMMAND_FAULT4 = 0;
                switch(g_stCommand.WorkMode&0xFF)
                {
                case ewmHold:
                    g_stCpuToClaData.iWorkMode = g_stCommand.WorkMode;
                    g_iEPwmTZIntCount=0;  //ֹͣ��ť��� pwm cycle by cycle ����ֵ��
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
                    AD2S1210_SetPara(XB_EXC_FRQ_REG, AD2S1210_Resolver.EXC_Frq<<8);         // ���ü���Ƶ��
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
    // ����ĸ�ߵ�ѹ
    F32toC2(g_iMeaDCVoltage, (unsigned short*)(&(g_stRespond.MeaDcVoltageHigh)));

    // ����q���������
    F32toC2(g_fMeaCurrentQ, (unsigned short*)(&(g_stRespond.CurrentQHigh)));

    // ����d���������
    F32toC2(g_fMeaCurrentD, (unsigned short*)(&(g_stRespond.CurrentDHigh)));

    // ����U���������
    F32toC2(g_fMeaCurrentU, (unsigned short*)(&(g_stRespond.CurrentUHigh)));

    // ����V���������
    F32toC2(g_fMeaCurrentV, (unsigned short*)(&(g_stRespond.CurrentVHigh)));

    // ����W���������
    F32toC2(g_fMeaCurrentW, (unsigned short*)(&(g_stRespond.CurrentWHigh)));

    // ����λ��
    g_stRespond.EncoderLow=g_iPosCnt&0x00FF;
    g_stRespond.EncoderHigh=(g_iPosCnt>>8)&0x00FF;

//    g_stRespond.EncoderLow=g_iPostest&0x00FF;
//    g_stRespond.EncoderHigh=(g_iPostest>>8)&0x00FF;
//
//    g_iPostest=g_iPostest+200;


    // �������õ�ĸ�ߵ�ѹ
    F32toC2(g_stDriverParamA.fDcPowerVoltage, (unsigned short*)(&(g_stRespond.SetDcVoltageHigh)));

    //���ص������
    g_stRespond.MotorType =(Uint16)g_stDriverParamA.fMotorType;

    //���ؼ���Ƶ��
    F32toC2(g_stDriverParamA.fExcitationFreq, (unsigned short*)(&(g_stRespond.ExcitationFreqHigh)));

    //���ؼ�����
    g_stRespond.MotorPoles= (Uint16)g_stDriverParamA.fMotorPoles;

    //���ط�ֵ����
    F32toC2(g_stDriverParamA.fPeakDriveCurrent, (unsigned short*)(&(g_stRespond.PeakCurrentHigh)));

    //��������ֵ �൱��1000������
    F32toC2((g_stDriverParamA.fCurPidKp*10), (unsigned short*)(&(g_stRespond.CurPidKpHigh)));

    //��������ֵ  �൱��1000������
    F32toC2((g_stDriverParamA.fCurPidTi*10), (unsigned short*)(&(g_stRespond.CurPidTiHigh)));

    // �����ٶ�
    F32toC2_3(g_stCpuToClaData.fMotorVel, (unsigned short*)(&(g_stRespond.VelHigh)));


    // �����¶�
 //    F32toC2(g_stClaToCpuData.fMeaTemp, (unsigned short*)(&(g_stRespond.TemperatureHigh)));
//    F32toC2(g_iMcuTemp, (unsigned short*)(&(g_stRespond.TemperatureHigh)));

    /****************�������������ݺ�״̬������********************/

        // �÷�������֡ͷ
        g_stRespond.Header = 0x055;

        // ����״̬
        g_stRespond.iCurrentHallState = g_stCpuToClaData.iCurrentHallState;

        // ����У����
        iChecksum = 0;
        for(i=1;i<DATA_LENGTH-2;i++)
        {
            iChecksum += (*(g_pRespond+i))&0x0FF;
        }
        g_stRespond.Checksum = iChecksum&0x0FF;

        // �÷�������֡β
        g_stRespond.End = 0x0D;

        // ��������
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

// ��4���ֽ�ת���ɸ���
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

// ������ת����4���ֽ�
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

// ������ת����2���ֽڣ������λΪ����λ 100������
//#pragma CODE_SECTION(F32toC2,"ramfunc");
void F32toC2(float f, unsigned short* iChar)
{
    unsigned short j;
// ���Գ���100
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

//3������ת��
void F32toC2_3(float f, unsigned short* iChar)
{
    unsigned short j;
// ���Գ���5
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
//    while(AdcRegs.ADCINTFLG.bit.ADCINT1==0){}   //��������䣬����ɷ������ݷ�����ȥ
//    g_iMotorTemp=(AdcResult.ADCRESULT0-g_iMotorTempOffset);          // �¶Ȳ�������λ:���϶�
//    g_iDriverTemp=(AdcResult.ADCRESULT1-g_iDriverTempOffset);          // �¶Ȳ�������λ:��
    g_iMeaDCVoltage=AdcResult.ADCRESULT0*0.2276;          //  ĸ�ߵ�ѹ  ����
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;    // Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE;
}

