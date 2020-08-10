#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSP28x_Project.h"
//#include "pi_pos.h"                     // PI�����㷨
//#include "pi_vel.h"
//#include "pi_cur.h"
//#include "LpFilter.h"               // ��ͨ�˲����㷨
//#include "speed_est.h"              // ͨ��λ�ý����ٶȹ����㷨


#define HallU  GpioDataRegs.GPBDAT.bit.GPIO40
#define HallV  GpioDataRegs.GPADAT.bit.GPIO27
#define HallW  GpioDataRegs.GPADAT.bit.GPIO10
#define PWM_ENABLE()      GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1

/*********************�������************************/
// DC Motor:AKM63L
#define MOTOR_L_A       0.0093        // ��� ��λ: 9.3mH
#define MOTOR_R_A       6.2          // ���� ��λ: ohm
#define MOTOR_POLES_A   5           // ���������  5�Լ�
#define MOTOR_TYPE_A    0           // �������  1��PMSM  0��BLDC
/**************************************************/

/*****************�豸��������*********************************/
#define POWER_CURRENT_LIMIT_A 3         // ��Դ������ ��λ: Ampere
#define POWER_VOLTAGE_LIMIT_A 25        // �������27V;
#define DRIVER_CURRENT_LIMIT_A 10        // ���������� ��λ: Ampere
#define DRIVER_VOLTAGE_LIMIT_A 25       // ��������ѹ ��λ: Volt
#define MAX_WORK_AREA_A 360             // ������Ƕ�
#define MIN_WORK_AREA_A 0               // ��С�����Ƕ�
#define VELOCITY_MAX_LIMIT_A 35         // ����ٶ� ��λ: Deg/s
#define ACC_MAX_A 500                    // �����ٶ�
#define ELE_ANGLE_OFFSET_A  16.875       //  ������λ
#define RESOLVER_EXCITE_FREQ_A   10      //  ���伤��Ƶ�� 10Khz
/******************************************************/

/******************������·PI����������***************************/
#define CURRENT_PI_KP_A 40 // 2*pi*f*L   700hZ
#define CURRENT_PI_TI_A 0.005 // L/R
#define CURRENT_PI_KC_A 1       //λ��[0,1]֮��
/***********************************************************/

/*******************�ٶȻ�·PI�������Լ���ͨ�˲�������*******************/
#define VELOCITY_PI_KP_A 6
#define VELOCITY_PI_TI_A 0.5        // Set 0 when not used,or positive real number as the integral time
#define VELOCITY_PI_KC_A -1     //λ��[0,1]֮��
#define VELOCITY_LP_A1 28       // Set 0 when not used,or positive real number  as the lowpass filter freq
#define VELOCITY_LP_A2 28
/*********************************************************/

/*********************λ�û�·���ַ������������*********************/
#define POSITION_PI_OUTER_KP_A 4                //���·����ֵ
#define POSITION_PI_INNER_KP_A 20               //�ڻ�·����ֵ
#define POSITION_PI_TI_A 0.5                    //Ki = Tsample/Ti
#define POSITION_PI_KC_A -1
#define POSITION_PI_THRESHOLD_A 0.1         //������ֵ ��λ����
/*********************************************************/

/*******************�������ڲ�����*****************************/
#define INT_FREQ 16000      // 16kHZƵ��
#define VEL_FREQ 1000       // 1kHz�ٶȻ�·Ƶ��
#define POS_FREQ 1000       // 1kHzλ�û�·Ƶ��
#define DATA_REFRESH_RATE  100      // ������λ�����ݵ�ˢ��Ƶ��,200Hz
#define SHORTEST_A_ROUTINE  1   //���·��
#define DATA_LENGTH       34   //�������ݳ���
/*********************************************************/


/*******************BLDC���ò���*****************************/
#define UH EPwm1Regs.CMPA.half.CMPA
#define UL EPwm1Regs.CMPB
#define VH EPwm2Regs.CMPA.half.CMPA
#define VL EPwm2Regs.CMPB
#define WH EPwm3Regs.CMPA.half.CMPA
#define WL EPwm3Regs.CMPB
#define MOSFET_H_ON 0
#define MOSFET_H_OFF 4500     //����PWM_Period
#define MOSFET_L_ON 4500      //����PWM_Period
#define MOSFET_L_OFF 0
#define DRV_UVLO  GpioDataRegs.GPBDAT.bit.GPIO43
#define DRV_FAULT GpioDataRegs.GPBDAT.bit.GPIO52
/*********************************************************/




#define ENCODER_BITS    16      //������λ��
#define Dead_Time       45        //Deadband time--Dead_Time=number*11.11ns
//#define PWM_Period      4500       //PWM frequency=10kHz TB_COUNT_UPDOWN 90M/10k/2=4500
//#define PWM_Halfperiod  2250       //PWM half period
#define PWM_Period      2812       //PWM frequency=10kHz TB_COUNT_UPDOWN 90M/16k/2=2812
#define PWM_Halfperiod  1406       //PWM half period


#define E_AXIS  1      // �и�����ʱ
//#define NodeID  0x03
//#define EleAngleOffset  147.5518798828125     //��Ƕ�0λ

#define NodeID  0x02
#define EleAngleOffset  352.3095703125     //��Ƕ�0λ



// �����������ṹ��
typedef struct DriverParam{
    float fMotorL;
    float fMotorR;
    float fMotorPoles;
    float fMotorType;
    float fDcPowerVoltage;
    float fDcPowerCurrent;
    float fMaxWorkLimit;
    float fMinWorkLimit;
    float fCurPidKp;
    float fCurPidTi;
    float fCurPidKc;
    float fRatedDriveVoltage;
    float fVelPidKp;
    float fVelPidTi;
    float fVelPidKc;
    float fVelLpfreq1;
    float fVelLpfreq2;
    float fPeakDriveCurrent;
    float fAccMax;
    float fPosPidOuterKp;
    float fPosPidInnerKp;
    float fPosPidTi;
    float fPosPidKc;
    float fPosPidThreshold;
    float fVelMaxLimit;
    float fEleAngleOffset;
    float fExcitationFreq;
}TDriverParam,*PTSingleControlParam;


// ����ģʽ��������
typedef enum
{
    ewmHold=0x00,
    ewmCurrentOpenGuide,
    ewmCurrentCloseGuide,
    ewmVelocityCloseGuide,
    ewmPositionCloseGuide,
    ewmSafeProtection,
    ewmMcEleAngleZero,
    ewmReadAllControlParam,
    ewmResetParam,
    ewmFlashControlParam,
    ewmBLDCOpenGuide,


    // �豸����
    ewmRefreshInductance=0x10,              // ������
    ewmRefreshResistance,                   // �������
    ewmRefreshMotorPoles,                   // ���������
    ewmRefreshMotorType,                    // �������
    ewmRefreshPowerRatedVoltage,            // ��Դ���ѹ
    ewmRefreshPowerRatedCurrent,            // ��Դ�����
    ewmRefreshPowerBusVoltage,              // ��Դĸ�ߵ�ѹ
    ewmRefreshMotorPeakCurrent,             // ��Դĸ�ߵ�ѹ
    ewmRefreshMaxWorkArea,                  // �����λ��
    ewmRefreshMinWorkArea,                  // ��С����λ��
    ewmRefreshExcitationFreq,               // ���伤��Ƶ��

    // ������·����
    ewmRefreshCLoopKp=0x20,                 // ����ϵ��
    ewmRefreshCLoopTi,                      // ����ϵ��
    ewmRefreshCLoopKc,
    ewmRefreshCLoopLimit,                   // �����ֵ

    // �ٶȻ�·����
    ewmRefreshVLoopKp=0x30,                 // ����ϵ��
    ewmRefreshVLoopTi,                      // ����ϵ��
    ewmRefreshVLoopKc,
    ewmRefreshVLoopLpFreq1,                 // ��ͨ�˲���1
    ewmRefreshVLoopLpFreq2,                 // ��ͨ�˲���2
    ewmRefreshVLoopOutLimit,                // �����ֵ
    ewmRefreshVLoopVelLpFreq,               // �����ٶȵ�ͨ�˲���
    ewmRefreshVLoopAccMax,                  // �����ٶ�
    ewmRefreshVLoopAccAccuracy,             // �����ȼ��ٶ�

    // λ�û�·����
    ewmRefreshPLoopOuterK=0x40,             // �⻷����ϵ��
    ewmRefreshPLoopInnerKp,                 // �ڻ�����ϵ��
    ewmRefreshPLoopThreshold,               // ������ֵ
    ewmRefreshPLoopTi,                      // ����ϵ��
    ewmRefreshPLoopKc,
    ewmRefreshPLoopOutMaxLimit,             // ��������ֵ
    ewmRefreshPLoopOutAccuLimit,            // �����������ֵ
    ewmRefreshJoystickMaxLimit,             // ��������ٶ���ֵ
    ewmRefreshJosytickDeadzone              // ������������
}TWorkMode;


// ��������ṹ��
typedef struct Command{
    unsigned short Header;
    unsigned short iSequence;      // �������
    unsigned short WorkMode;
    unsigned short Param4;
    unsigned short Param3;
    unsigned short Param2;
    unsigned short Param1;
    unsigned short Checksum;
    unsigned short End;
}TCommand;

extern TCommand g_stCommand;

// �����ʼ���ṹ��
#define COMMAND_DEFAULTS {        \
                           0x0FF, \
                           0,    \
                           0,    \
                           0,    \
                           0,    \
                           0,    \
                           0,    \
                           0,   \
                           0x0D  \
                          }

typedef struct{
    unsigned short ENCODER_FAULT0:          1;     // ����������
    unsigned short OVER_TEMP1:                1;      // ����
    unsigned short OVER_CURRENT2:              1;    // ����
    unsigned short OVER_VOLTAGE3:               1;   // ��ѹ
    unsigned short COMMAND_FAULT4:           1;
    unsigned short FLASH_FAULT5:        1;
    unsigned short IGBT_FAULT6:           1;   //IGBT ����
    unsigned short LOW_VOLTAGE7:   1;           // Ƿѹ
    unsigned short Rsvd4:                     8;
}STATE_SIGN_BITS;

//! union of the fault sign
/*!

    Define the union of the fault sign.
*/
typedef union{
   unsigned short all;
   STATE_SIGN_BITS bit;
}STATE_SIGN;

// ��Ӧ����ṹ��
typedef struct Respond{
    unsigned short Header;          // ����ͷ
    unsigned short iCurrentHallState;      // �������
    unsigned short WorkMode;        // ����ģʽ
    STATE_SIGN State;
    unsigned short EncoderHigh;
    unsigned short EncoderLow;
    unsigned short VelHigh;
    unsigned short VelLow;
    unsigned short MeaDcVoltageHigh;
    unsigned short MeaDCVoltageLow;
    unsigned short CurrentDHigh;
    unsigned short CurrentDLow;
    unsigned short CurrentQHigh;
    unsigned short CurrentQLow;
    unsigned short CurrentUHigh;
    unsigned short CurrentULow;
    unsigned short CurrentVHigh;
    unsigned short CurrentVLow;
    unsigned short CurrentWHigh;
    unsigned short CurrentWLow;
    unsigned short MotorType;
    unsigned short MotorPoles;
    unsigned short SetDcVoltageHigh;
    unsigned short SetDCVoltageLow;
    unsigned short PeakCurrentHigh;
    unsigned short PeakCurrentLow;
    unsigned short CurPidKpHigh;
    unsigned short CurPidKpLow;
    unsigned short CurPidTiHigh;
    unsigned short CurPidTiLow;
    unsigned short ExcitationFreqHigh;
    unsigned short ExcitationFreqLow;
    unsigned short Checksum;
    unsigned short End;
}TRespond;

// ��Ӧ�ṹ���ʼ��
#define RESPOND_DEFAULTS {        \
                           0x0FF,           \
                           0,    \
                           0,    \
                           0,    \
                           0,    \
                           0,    \
                           0,   \
                           0,   \
                           0,   \
                           0,    \
                          0,   \
                          0,   \
                          0,   \
                          0,   \
                          0,   \
                           0x0D  \
                          }

extern TRespond g_stRespond;

// ������ѹ
typedef struct MotorVoltage{
    float VoltageResolution;       // ��ѹ�ֱ���
    float U;
    float V;
    float W;
    float MotherVol;
}stMotorVoltage;




// ��ѹ�ṹ���ʼ��
#define VOLTAGE_DEFAULTS {        \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0    \
                          }

// ��������
typedef struct MotorCurrent{
    float SampleVolResolution;      //������ѹ�ֱ���
    float CurrentResolution;       // �����ֱ���
    float fEffectiveCurrent;
    float fCurrent[3];
    float SampleVol[3];                // ������ѹֵ
    float fCaliCurrent[3];
    float iCaliNum[3];       // ÿ���У������
    float iSampleNum[3];     // �ɼ�����
    unsigned short iQueue;
    unsigned short bInit;       // ��ʼ����־
    unsigned short iInitCount;  // ��ʼ������
    float U;
    float V;
    float W;
    float D;
    float Q;
}stMotorCurrent;

// �����ṹ���ʼ��
#define CURRENT_DEFAULTS {        \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           2400,    \
                           2400,    \
                           2400,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0,    \
                           0,    \
                           0    \
                          }



// ����������
typedef enum
{
    eETVoid=0x00,             // ������δѡ��
    eETIncrementalType,         // ����ʽ
    eETAbsEndat23,                // 23λ����ʽEndat2.2�ӿ�
    eETAbsBiss,                // ����ʽBiss�ӿ�
    eETAbsSSI,                // ����ʽSSI�ӿ�

}TEncoderType;


// ������·������
extern PI_CUR_CONTROLLER g_piCurdLoopA;
extern PI_CUR_CONTROLLER g_piCurqLoopA;

extern PI_CUR_CONTROLLER g_piCurLoopA;
extern PI_CUR_CONTROLLER g_piCurLoopB;


extern LP_FILTER g_lpfPwmPercent;

extern LP_FILTER g_lpfRefCurrentQ;

extern stMotorCurrent g_stMotorCurrentA;

extern TDriverParam g_stDriverParamA;            // A����������������
extern const TDriverParam c_stDriverParamA;      // A����������������
//
//
extern CLARKE ClarkeA;                 // A��CLARK�任
extern PARK ParkA;                     // A��PARK�任
extern IPARK IparkA;                   // A��PARK��任
extern SVGENDQ Svgen_dqA;              // A��SVPWM����


// C28д��Cla��ȡ���ݽṹ��**ע��CLAֻ�ܱ�ʶ32λ����
typedef struct CpuToClaData{
    float fPosition;
    float fRefPos;              // �ο�λ��
    float fDeltaPos;              // ��Բο�λ��
    float fRefVel;              // �ο��ٶ�
    float fRefCurrentA;          // A����ο�����
    float fRefCurrentB;          // B����ο�����
    float fMeaCurrentA;          // A�����������
    float fMeaCurrentB;          // B�����������
    float fRefCurrentQ;          // �ο�����
    float fRefCurrentD;          // �ο�����
    float fRefVoltageQ;          // �ο���ѹ
    float fRefPwmPercent;              // �ο�PWMռ�ձ�
    float fMeaCurrentOffsetA;    //A·�����������
    float fRefCurrentOffsetA;    //A·����ο�����
    float fMeaCurrentOffsetB;    //B·�����������
    float fRefCurrentOffsetB;    //B·����ο�����
    float fMotorVel;
    float fMotorVelRpm;
    float fVelIncrement;            // �ٶ����������ݼ��ٶȵõ�
    float fLastRefVel;              // ��ʷ�ο��ٶ�
    unsigned short iCurrentHallState;     // ��ǰ����״̬
    unsigned short iWorkMode;    // ����ģʽ
    STATE_SIGN iState;                      // ��������״̬��1Ϊ�й��ϣ�0Ϊ�޹���
} stCpuToClaData;


// CPU���ݸ�CLA�Ľṹ���ʼ��
#define CPU_TO_CLA_DEFAULTS {0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0}

extern stCpuToClaData g_stCpuToClaData;

// ˫���ȸ�����λ�ò����ṹ��
typedef struct PositionData{
    long double ldEncoderResolution;
    long double ldPosition;
    long double ldLastPosition;
    long double ldEleAngleOffset;
    long double ldEleAngle;
}stPositionData;

#define POSITION_DATA_DEFAULT {0.0,\
                                0.0,\
                                0.0}

extern stPositionData g_stPositionDataA;


// Claд��Cpu��ȡ���ݽṹ��
typedef struct ClaToCpuData{
    float fMeaDcVol;        // ����ĸ�ߵ�ѹ
    float fMeaCurrent;      // ��������
    float fMeaCurrentFiltered;       // �˲������
    float fMeaTemp;         // �����¶�
    float fDriveVoltage;               // ���������ѹ
    float fPwmReso;                   // PWM�ֱ���
    float fTempResolution;          // �¶ȷֱ���
    float fHallVelRpm;                  // �����ٶ�
    unsigned short iCurrentHallState;     // ��ǰ����״̬
    unsigned short iLastHallState ;    // ��ʷ����״̬
    unsigned short bMoveDir;                  // ��������0Ϊ����1Ϊ��
    unsigned short bDir;                      // ����˶����򣬵�ѹ�����������˶���������
    unsigned short iCmp;                        // EPWM�ıȽϼĴ�����ֵ
    unsigned short iInterruptCount;             // 16kHz�жϼ���
    unsigned short iIntCount;
    unsigned short iHallCount;                  // �����ٶȼ���
    STATE_SIGN iState;                      // ��������״̬��1Ϊ�й��ϣ�0Ϊ�޹���
} stClaToCpuData;

// CLA���ݸ�CPU�Ľṹ���ʼ��
#define CLA_TO_CPU_DEFAULTS {0.0, \
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0.0,\
                            0,\
                            0,\
                            0,\
                            0,\
                            0,\
                            0,\
                            0,\
                            0,\
                            0}


extern stClaToCpuData g_stClaToCpuData;


#ifdef __cplusplus
}
#endif /* extern "C" */
#endif   // - end of PROJECT_CONFIG_H

