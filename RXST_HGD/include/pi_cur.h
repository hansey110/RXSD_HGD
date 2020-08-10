/* =================================================================================
File name:       PI_CUR.H
note：采用tustin方法进行离散化
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
                    float  Up;                // Data: 比例输出项
                    float  Up1;               // Data: 上一次的比例输出
                    float  Ui;                // Data: 积分输出
                    float  OutMax;            // Parameter: upper saturation limit
                    float  OutMin;            // Parameter: lower saturation limit
                    float  OutPreSat;         // Data: 饱和判断前输出
                    float  SatErr;            // Data: integrator storage: ui(k-1)
                    float  ClampingSign;      // 抗饱和采用的clamping方法，0代表将积分作用断开
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
//    /* 比例计算项 */                                     \
//    v.up = v.Kp*(v.Ref - v.Fbk);                        \
//                                                                \
//    /* integral term */                                         \
//    v.ui = (v.Out == v.v1)?(v.Ki*(v.up+v.up1)+ v.i1) : v.i1;    \
//    v.i1 = v.ui;                                                \
//                                                                \
//    /* control output */                                        \
//    v.v1 = v.up + v.ui;                                         \
//    v.Out= (v.v1>v.Umax)?(v.Umax) : ((v.v1<v.Umin)?(v.Umin) : (v.v1));  \
//    /*保存当前的比例输出*/           \
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
