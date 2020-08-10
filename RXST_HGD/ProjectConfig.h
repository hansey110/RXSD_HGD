#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSP28x_Project.h"
//#include "pi_pos.h"                     // PI控制算法
//#include "pi_vel.h"
//#include "pi_cur.h"
//#include "LpFilter.h"               // 低通滤波器算法
//#include "speed_est.h"              // 通过位置进行速度估计算法


#define HallU  GpioDataRegs.GPBDAT.bit.GPIO40
#define HallV  GpioDataRegs.GPADAT.bit.GPIO27
#define HallW  GpioDataRegs.GPADAT.bit.GPIO10
#define PWM_ENABLE()      GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1

/*********************电机性能************************/
// DC Motor:AKM63L
#define MOTOR_L_A       0.0093        // 电感 单位: 9.3mH
#define MOTOR_R_A       6.2          // 电阻 单位: ohm
#define MOTOR_POLES_A   5           // 电机极对数  5对极
#define MOTOR_TYPE_A    0           // 电机类型  1：PMSM  0：BLDC
/**************************************************/

/*****************设备性能设置*********************************/
#define POWER_CURRENT_LIMIT_A 3         // 电源最大电流 单位: Ampere
#define POWER_VOLTAGE_LIMIT_A 25        // 最大驱动27V;
#define DRIVER_CURRENT_LIMIT_A 10        // 驱动最大电流 单位: Ampere
#define DRIVER_VOLTAGE_LIMIT_A 25       // 驱动最大电压 单位: Volt
#define MAX_WORK_AREA_A 360             // 最大工作角度
#define MIN_WORK_AREA_A 0               // 最小工作角度
#define VELOCITY_MAX_LIMIT_A 35         // 最大速度 单位: Deg/s
#define ACC_MAX_A 500                    // 最大加速度
#define ELE_ANGLE_OFFSET_A  16.875       //  电气零位
#define RESOLVER_EXCITE_FREQ_A   10      //  旋变激磁频率 10Khz
/******************************************************/

/******************电流回路PI控制器设置***************************/
#define CURRENT_PI_KP_A 40 // 2*pi*f*L   700hZ
#define CURRENT_PI_TI_A 0.005 // L/R
#define CURRENT_PI_KC_A 1       //位于[0,1]之内
/***********************************************************/

/*******************速度回路PI控制器以及低通滤波器设置*******************/
#define VELOCITY_PI_KP_A 6
#define VELOCITY_PI_TI_A 0.5        // Set 0 when not used,or positive real number as the integral time
#define VELOCITY_PI_KC_A -1     //位于[0,1]之内
#define VELOCITY_LP_A1 28       // Set 0 when not used,or positive real number  as the lowpass filter freq
#define VELOCITY_LP_A2 28
/*********************************************************/

/*********************位置回路积分分离控制器设置*********************/
#define POSITION_PI_OUTER_KP_A 4                //外回路比例值
#define POSITION_PI_INNER_KP_A 20               //内回路比例值
#define POSITION_PI_TI_A 0.5                    //Ki = Tsample/Ti
#define POSITION_PI_KC_A -1
#define POSITION_PI_THRESHOLD_A 0.1         //分离阈值 单位：度
/*********************************************************/

/*******************驱动器内部参数*****************************/
#define INT_FREQ 16000      // 16kHZ频率
#define VEL_FREQ 1000       // 1kHz速度回路频率
#define POS_FREQ 1000       // 1kHz位置回路频率
#define DATA_REFRESH_RATE  100      // 返回上位机数据的刷新频率,200Hz
#define SHORTEST_A_ROUTINE  1   //最短路径
#define DATA_LENGTH       34   //串口数据长度
/*********************************************************/


/*******************BLDC配置参数*****************************/
#define UH EPwm1Regs.CMPA.half.CMPA
#define UL EPwm1Regs.CMPB
#define VH EPwm2Regs.CMPA.half.CMPA
#define VL EPwm2Regs.CMPB
#define WH EPwm3Regs.CMPA.half.CMPA
#define WL EPwm3Regs.CMPB
#define MOSFET_H_ON 0
#define MOSFET_H_OFF 4500     //等于PWM_Period
#define MOSFET_L_ON 4500      //等于PWM_Period
#define MOSFET_L_OFF 0
#define DRV_UVLO  GpioDataRegs.GPBDAT.bit.GPIO43
#define DRV_FAULT GpioDataRegs.GPBDAT.bit.GPIO52
/*********************************************************/




#define ENCODER_BITS    16      //编码器位数
#define Dead_Time       45        //Deadband time--Dead_Time=number*11.11ns
//#define PWM_Period      4500       //PWM frequency=10kHz TB_COUNT_UPDOWN 90M/10k/2=4500
//#define PWM_Halfperiod  2250       //PWM half period
#define PWM_Period      2812       //PWM frequency=10kHz TB_COUNT_UPDOWN 90M/16k/2=2812
#define PWM_Halfperiod  1406       //PWM half period


#define E_AXIS  1      // 有俯仰轴时
//#define NodeID  0x03
//#define EleAngleOffset  147.5518798828125     //电角度0位

#define NodeID  0x02
#define EleAngleOffset  352.3095703125     //电角度0位



// 驱动器参数结构体
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


// 工作模式命令类型
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


    // 设备参数
    ewmRefreshInductance=0x10,              // 电枢电感
    ewmRefreshResistance,                   // 电枢电阻
    ewmRefreshMotorPoles,                   // 电机极对数
    ewmRefreshMotorType,                    // 电机类型
    ewmRefreshPowerRatedVoltage,            // 电源额定电压
    ewmRefreshPowerRatedCurrent,            // 电源额定电流
    ewmRefreshPowerBusVoltage,              // 电源母线电压
    ewmRefreshMotorPeakCurrent,             // 电源母线电压
    ewmRefreshMaxWorkArea,                  // 最大工作位置
    ewmRefreshMinWorkArea,                  // 最小工作位置
    ewmRefreshExcitationFreq,               // 旋变激磁频率

    // 电流回路参数
    ewmRefreshCLoopKp=0x20,                 // 比例系数
    ewmRefreshCLoopTi,                      // 积分系数
    ewmRefreshCLoopKc,
    ewmRefreshCLoopLimit,                   // 输出阈值

    // 速度回路参数
    ewmRefreshVLoopKp=0x30,                 // 比例系数
    ewmRefreshVLoopTi,                      // 积分系数
    ewmRefreshVLoopKc,
    ewmRefreshVLoopLpFreq1,                 // 低通滤波器1
    ewmRefreshVLoopLpFreq2,                 // 低通滤波器2
    ewmRefreshVLoopOutLimit,                // 输出阈值
    ewmRefreshVLoopVelLpFreq,               // 测量速度低通滤波器
    ewmRefreshVLoopAccMax,                  // 最大加速度
    ewmRefreshVLoopAccAccuracy,             // 保精度加速度

    // 位置回路参数
    ewmRefreshPLoopOuterK=0x40,             // 外环比例系数
    ewmRefreshPLoopInnerKp,                 // 内环比例系数
    ewmRefreshPLoopThreshold,               // 分离阈值
    ewmRefreshPLoopTi,                      // 积分系数
    ewmRefreshPLoopKc,
    ewmRefreshPLoopOutMaxLimit,             // 输出最大阈值
    ewmRefreshPLoopOutAccuLimit,            // 输出保精度阈值
    ewmRefreshJoystickMaxLimit,             // 单杆最大速度阈值
    ewmRefreshJosytickDeadzone              // 单杆死区参数
}TWorkMode;


// 控制命令结构体
typedef struct Command{
    unsigned short Header;
    unsigned short iSequence;      // 报文序号
    unsigned short WorkMode;
    unsigned short Param4;
    unsigned short Param3;
    unsigned short Param2;
    unsigned short Param1;
    unsigned short Checksum;
    unsigned short End;
}TCommand;

extern TCommand g_stCommand;

// 命令初始化结构体
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
    unsigned short ENCODER_FAULT0:          1;     // 编码器故障
    unsigned short OVER_TEMP1:                1;      // 过温
    unsigned short OVER_CURRENT2:              1;    // 过流
    unsigned short OVER_VOLTAGE3:               1;   // 过压
    unsigned short COMMAND_FAULT4:           1;
    unsigned short FLASH_FAULT5:        1;
    unsigned short IGBT_FAULT6:           1;   //IGBT 故障
    unsigned short LOW_VOLTAGE7:   1;           // 欠压
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

// 响应命令结构体
typedef struct Respond{
    unsigned short Header;          // 报文头
    unsigned short iCurrentHallState;      // 报文序号
    unsigned short WorkMode;        // 工作模式
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

// 响应结构体初始化
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

// 电机相电压
typedef struct MotorVoltage{
    float VoltageResolution;       // 电压分辨力
    float U;
    float V;
    float W;
    float MotherVol;
}stMotorVoltage;




// 电压结构体初始化
#define VOLTAGE_DEFAULTS {        \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0,    \
                           0.0    \
                          }

// 电机相电流
typedef struct MotorCurrent{
    float SampleVolResolution;      //采样电压分辨力
    float CurrentResolution;       // 电流分辨力
    float fEffectiveCurrent;
    float fCurrent[3];
    float SampleVol[3];                // 采样电压值
    float fCaliCurrent[3];
    float iCaliNum[3];       // 每相的校正计数
    float iSampleNum[3];     // 采集数据
    unsigned short iQueue;
    unsigned short bInit;       // 初始化标志
    unsigned short iInitCount;  // 初始化计数
    float U;
    float V;
    float W;
    float D;
    float Q;
}stMotorCurrent;

// 电流结构体初始化
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



// 编码器类型
typedef enum
{
    eETVoid=0x00,             // 编码器未选择
    eETIncrementalType,         // 增量式
    eETAbsEndat23,                // 23位绝对式Endat2.2接口
    eETAbsBiss,                // 绝对式Biss接口
    eETAbsSSI,                // 绝对式SSI接口

}TEncoderType;


// 电流回路控制器
extern PI_CUR_CONTROLLER g_piCurdLoopA;
extern PI_CUR_CONTROLLER g_piCurqLoopA;

extern PI_CUR_CONTROLLER g_piCurLoopA;
extern PI_CUR_CONTROLLER g_piCurLoopB;


extern LP_FILTER g_lpfPwmPercent;

extern LP_FILTER g_lpfRefCurrentQ;

extern stMotorCurrent g_stMotorCurrentA;

extern TDriverParam g_stDriverParamA;            // A轴驱动器参数变量
extern const TDriverParam c_stDriverParamA;      // A轴驱动器参数常量
//
//
extern CLARKE ClarkeA;                 // A轴CLARK变换
extern PARK ParkA;                     // A轴PARK变换
extern IPARK IparkA;                   // A轴PARK逆变换
extern SVGENDQ Svgen_dqA;              // A轴SVPWM产生


// C28写，Cla读取数据结构体**注意CLA只能辨识32位数据
typedef struct CpuToClaData{
    float fPosition;
    float fRefPos;              // 参考位置
    float fDeltaPos;              // 相对参考位置
    float fRefVel;              // 参考速度
    float fRefCurrentA;          // A电机参考电流
    float fRefCurrentB;          // B电机参考电流
    float fMeaCurrentA;          // A电机反馈电流
    float fMeaCurrentB;          // B电机反馈电流
    float fRefCurrentQ;          // 参考电流
    float fRefCurrentD;          // 参考电流
    float fRefVoltageQ;          // 参考电压
    float fRefPwmPercent;              // 参考PWM占空比
    float fMeaCurrentOffsetA;    //A路电机电流反馈
    float fRefCurrentOffsetA;    //A路电机参考电流
    float fMeaCurrentOffsetB;    //B路电机电流反馈
    float fRefCurrentOffsetB;    //B路电机参考电流
    float fMotorVel;
    float fMotorVelRpm;
    float fVelIncrement;            // 速度增量，根据加速度得到
    float fLastRefVel;              // 历史参考速度
    unsigned short iCurrentHallState;     // 当前霍尔状态
    unsigned short iWorkMode;    // 工作模式
    STATE_SIGN iState;                      // 驱动器的状态，1为有故障，0为无故障
} stCpuToClaData;


// CPU传递给CLA的结构体初始化
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

// 双精度浮点型位置参数结构体
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


// Cla写，Cpu读取数据结构体
typedef struct ClaToCpuData{
    float fMeaDcVol;        // 测量母线电压
    float fMeaCurrent;      // 测量电流
    float fMeaCurrentFiltered;       // 滤波后电流
    float fMeaTemp;         // 测量温度
    float fDriveVoltage;               // 电机驱动电压
    float fPwmReso;                   // PWM分辨率
    float fTempResolution;          // 温度分辨力
    float fHallVelRpm;                  // 霍尔速度
    unsigned short iCurrentHallState;     // 当前霍尔状态
    unsigned short iLastHallState ;    // 历史霍尔状态
    unsigned short bMoveDir;                  // 电流方向，0为正，1为负
    unsigned short bDir;                      // 电机运动方向，电压正负代表电机运动正负方向
    unsigned short iCmp;                        // EPWM的比较寄存器数值
    unsigned short iInterruptCount;             // 16kHz中断计数
    unsigned short iIntCount;
    unsigned short iHallCount;                  // 霍尔速度计数
    STATE_SIGN iState;                      // 驱动器的状态，1为有故障，0为无故障
} stClaToCpuData;

// CLA传递给CPU的结构体初始化
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

