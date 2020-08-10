/* =================================================================================
File name:       PI_CUR.H
note������tustin����������ɢ��
===================================================================================*/
#ifndef PI_CUR_H_
#define PI_CUR_H_


typedef struct {    float  Ref;               // Input: reference set-point
                    float  Fbk;               // Input: feedback
                    float  Err;               // Parameter: error
                    float  Out;               // Output: controller output
                    float  Kp;                // Parameter: proportional loop gain
                    float  Ti;                // Parameter: integral time
                    float  Ki;                // Parameter: integral gain
                    float  Kc;                // Parameter: Integral correction gain
                    float  Freq;              // Parameter: Sampling frequency
                    float  Up;                // Data: ���������
                    float  Up1;               // Data: ��һ�εı������
                    float  Ui;                // Data: �������
                    float  OutMax;            // Parameter: upper saturation limit
                    float  OutMin;            // Parameter: lower saturation limit
                    float  OutPreSat;         // Data: �����ж�ǰ���
                    float  SatErr;            // Data: integrator storage: ui(k-1)
                    float  ClampingSign;      // �����Ͳ��õ�clamping������0�����������öϿ�
                  } PI_CUR_CONTROLLER;


/*-----------------------------------------------------------------------------
Default initalisation values for the PI_GRANDO objects
-----------------------------------------------------------------------------*/

#define PI_CUR_CONTROLLER_DEFAULTS {        \
                           0,           \
                           0,           \
                           0,           \
                           1.0, \
                           0.0, \
                           1.0, \
                           -1.0,    \
                           0.0, \
                           0.0,     \
                           0.0, \
                           0.0, \
                           0.0  \
                          }

///*------------------------------------------------------------------------------
//    PI_GRANDO Macro Definition
//------------------------------------------------------------------------------*/
//
//#define PI_CUR_MACRO(v)                                             \
//                                                                \
//    /* ���������� */                                     \
//    v.up = v.Kp*(v.Ref - v.Fbk);                        \
//                                                                \
//    /* integral term */                                         \
//    v.ui = (v.Out == v.v1)?(v.Ki*(v.up+v.up1)+ v.i1) : v.i1;    \
//    v.i1 = v.ui;                                                \
//                                                                \
//    /* control output */                                        \
//    v.v1 = v.up + v.ui;                                         \
//    v.Out= (v.v1>v.Umax)?(v.Umax) : ((v.v1<v.Umin)?(v.Umin) : (v.v1));  \
//    /*���浱ǰ�ı������*/           \
//    v.up1 = v.up;                                       \


// *************************************************
//  Reset PI controller to zero initial conditions
// *************************************************
//#define RESET_PI_CUR(v)                                             \
//    v.Out = 0;                                                  \
//    v.Up = 0;                                                  \
//    v.Up1 = 0;                                                  \
//    v.Ui = 0;                                                  \
//    v.OutPreSat  = 0;                                                  \
//    v.SatErr    = 0;      \
//    v.ClampingSign = 1;    \

#endif
