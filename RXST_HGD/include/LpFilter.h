/* =================================================================================
File name:       LpFilter.H
===================================================================================*/


#ifndef __LP_FILTER_H__
#define __LP_FILTER_H__

typedef struct {  float  Ref;   			// Input: reference set-point
				  float  Out;   			// Output: controller output
				  float  LpFreq;            //截止频率
				  float  KIn;				// Parameter: 输入增益
				  float  KOut;			    // Parameter: 输出增益
				  float  Umax;			    // Parameter: upper saturation limit
				  float  Umin;			    // Parameter: lower saturation limit
				  float  v1;				// Data: pre-saturated output
				  float  w1;				// Data: last input storage : ref(k-1)
				} LP_FILTER;


/*-----------------------------------------------------------------------------
Default initalisation values for the lowpass filter objects
-----------------------------------------------------------------------------*/                     

#define LP_FILTER_DEFAULTS {		\
						   0, 			\
                           0, 			\
                           100,  \
                           1.0,	\
                           1.0,	\
                           1.0,	\
                           -1.0, 	\
                           0.0,	\
                           0.0	\
              			  }

/*------------------------------------------------------------------------------
	LP_FILTER Macro Definition
------------------------------------------------------------------------------*/

#define LP_FILTER_MACRO(v)												\
    if(v.LpFreq==0){															\
        v.v1=v.Ref;}                               \
	else{                   \
	/* 计算预饱和输出 */ 									\
	v.v1 = v.KOut*v.v1 + v.KIn*(v.Ref+v.w1);						\
																\
	/* 保存当前的输入*/        \
	v.w1 = v.Ref;}               \
	                                                    \
	/* control output */ 										\
	v.Out= (v.v1>v.Umax)?(v.Umax) : ((v.v1<v.Umin)?(v.Umin) : (v.v1));	\

// *************************************************
//  Reset lowpass filter to zero initial conditions
// *************************************************
#define RESET_LP_FILTER(v)                                             \
    v.Out = 0;                                                  \
    v.v1  = 0;  \
    v.w1  = 0;   \
    v.Ref = 0;   \



#endif // __LP_FILTER_H__

