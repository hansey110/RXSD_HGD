/* =================================================================================
File name:       SVGEN_DQ.H  (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro  definitions for the SVGEN_DQ module .
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 4-15-2010	Version 1.1                                                 
------------------------------------------------------------------------------*/
#ifndef __SVGEN_DQ_H__
#define __SVGEN_DQ_H__



typedef struct 	{ float32  Ualpha; 			// Input: reference alpha-axis phase voltage
				  float32  Ubeta;			// Input: reference beta-axis phase voltage
				  Uint32   svpwm_Period;    // Input: reference SVPWM period counter value(T0)
				  Uint16   CMPA1;           // Output: reference phase-U(1/a) SVPWM CMP1 reg 
				  Uint16   CMPA2;			// Output: reference phase-V(2/b) SVPWM CMP2 reg
				  Uint16   CMPA3;			// Output: reference phase-W(3/c) SVPWM CMP3 reg
				  float32  Va;
				  float32  Vb;
				  float32  Vc;
				  float32  t1;
				  float32  t2;
				  float32  temp_sv1;
				  float32  temp_sv2;
				  float32  tt;
				  float32  Ta;
				  float32  Tb;
				  float32  Tc;
				  Uint16   Sector;
				} SVGENDQ;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
typedef SVGENDQ *SVGENDQ_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SVGENDQ object.
-----------------------------------------------------------------------------*/                     
#define SVGENDQ_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }                       

/*------------------------------------------------------------------------------
	Space Vector PWM Generator (SVGEN_DQ) Macro Definition
------------------------------------------------------------------------------*/

#define SVGEN_MACRO(v)															\
																				\
	v.Sector = 0;																	\
	v.temp_sv1=0.5*v.Ubeta; 					/*divide by 2*/					\
	v.temp_sv2=0.8660254*v.Ualpha;	        /* 0.8660254 = sqrt(3)/2*/		\
																				\
/* Inverse clarke transformation */												\
	v.Va = v.Ubeta;																\
	v.Vb = -v.temp_sv1 + v.temp_sv2;													\
	v.Vc = -v.temp_sv1 - v.temp_sv2;													\
/* 60 degree Sector determination */											\
	if (v.Va>0) v.Sector = 1;													\
	if (v.Vb>0) v.Sector = v.Sector+2;											\
	if (v.Vc>0) v.Sector = v.Sector+4;											\
/* X,Y,Z (Va,Vb,Vc) calculations X = Va, Y = Vb, Z = Vc */						\
	v.Va = v.Ubeta;																\
	v.Vb = v.temp_sv1 + v.temp_sv2;													\
	v.Vc = v.temp_sv1 - v.temp_sv2;													\
/* Sector 0: this is special case for (Ualpha,Ubeta) = (0,0)*/					\
																				\
switch(v.Sector)																	\
{																				\
	case 0:																		\
	v.Ta = 0.25;															\
	v.Tb = 0.25;															\
	v.Tc = 0.25;															\
	break;																		\
	case 1:   /*Sector 1: t1=Z and t2=Y (abc ---> Tb,Ta,Tc)*/					\
	v.t1 = v.Vc;																	\
	v.t2 = v.Vb;																	\
	v.tt = v.t1+v.t2;                                                                 \
		if(v.tt>1){                                                               \
			v.t1=v.t1/v.tt;v.t2=v.t2/v.tt;                                                  \
		}                                                                       \
	v.Tb=0.25*(1-v.t1-v.t2); 												\
	v.Ta = v.Tb+0.5*v.t1;			 	/* taon = tbon+t1		*/						\
	v.Tc = v.Ta+0.5*v.t2;			  	/* tcon = taon+t2		*/						\
	break;																		\
	case 2:	  /* Sector 2: t1=Y and t2=-X (abc ---> Ta,Tc,Tb)*/ 				\
	v.t1 = v.Vb;																	\
	v.t2 = -v.Va;																	\
	v.tt = v.t1+v.t2;                                                                 \
		if(v.tt>1){                                                               \
			v.t1=v.t1/v.tt;v.t2=v.t2/v.tt;                                                  \
		}                                                                       \
	v.Ta=0.25*(1-v.t1-v.t2); 												\
	v.Tc = v.Ta+0.5*v.t1;				/*  tcon = taon+t1		*/						\
	v.Tb = v.Tc+0.5*v.t2;				/*  tbon = tcon+t2		*/						\
	break;																		\
	case 3:	  /* Sector 3: t1=-Z and t2=X (abc ---> Ta,Tb,Tc)*/					\
	v.t1 = -v.Vc;																	\
	v.t2 = v.Va;																	\
	v.tt = v.t1+v.t2;                                                                 \
		if(v.tt>1){                                                               \
			v.t1=v.t1/v.tt;v.t2=v.t2/v.tt;                                                  \
		}                                                                       \
	v.Ta=0.25*(1-v.t1-v.t2); 												\
	v.Tb = v.Ta+0.5*v.t1;				/*	tbon = taon+t1		*/						\
	v.Tc = v.Tb+0.5*v.t2;				/*	tcon = tbon+t2		*/						\
	break;																		\
	case 4:	  /* Sector 4: t1=-X and t2=Z (abc ---> Tc,Tb,Ta)*/					\
	v.t1 = -v.Va;																	\
	v.t2 = v.Vc;																	\
	v.tt = v.t1+v.t2;                                                                 \
		if(v.tt>1){                                                               \
			v.t1=v.t1/v.tt;v.t2=v.t2/v.tt;                                                  \
		}                                                                       \
	v.Tc=0.25*(1-v.t1-v.t2); 			/*	tbon = 0.25*(1-t1-t2)		*/									\
	v.Tb = v.Tc+0.5*v.t1;				/*	tbon = tcon+0.5t1		*/						\
	v.Ta = v.Tb+0.5*v.t2;				/*	taon = tbon+0.5t2		*/						\
	break;																		\
	case 5:	  /* Sector 5: t1=X and t2=-Y (abc ---> Tb,Tc,Ta)*/					\
	v.t1 = v.Va;																	\
	v.t2 = -v.Vb;					/*	tbon = (1-t1-t2)/2	*/						\
	v.tt = v.t1+v.t2;                                                                 \
		if(v.tt>1){                                                               \
			v.t1=v.t1/v.tt;v.t2=v.t2/v.tt;                                                  \
		}                                                                       \
	v.Tb=0.25*(1-v.t1-v.t2); 												\
	v.Tc = v.Tb+0.5*v.t1;				/*	taon = tcon+t2		*/						\
	v.Ta = v.Tc+0.5*v.t2;																\
	break;																		\
	case 6:	  /* Sector 6: t1=-Y and t2=-Z (abc ---> Tc,Ta,Tb)*/				\
	v.t1 = -v.Vb;																	\
	v.t2 = -v.Vc;																	\
	v.tt = v.t1+v.t2;                                                                 \
		if(v.tt>1){                                                               \
			v.t1=v.t1/v.tt;v.t2=v.t2/v.tt;                                                  \
		}                                                                       \
	v.Tc=0.25*(1-v.t1-v.t2); 												\
	v.Ta = v.Tc+0.5*v.t1;				/*	taon = tcon+t1		*/						\
	v.Tb = v.Ta+0.5*v.t2;				/*	tbon = taon+t2		*/						\
	break;																		\
}                                                                                 \
    v.CMPA1=(Uint16)((v.svpwm_Period*2)*v.Ta);                                     \
    v.CMPA2=(Uint16)((v.svpwm_Period*2)*v.Tb);                                    \
    v.CMPA3=(Uint16)((v.svpwm_Period*2)*v.Tc);
    
#endif // __SVGEN_DQ_H__
