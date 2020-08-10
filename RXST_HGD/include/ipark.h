/* =================================================================================
File name:       IPARK.H   (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definitions for the IPARK.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-15-2009	Version 1.0                                                  
------------------------------------------------------------------------------*/
#ifndef __IPARK_H__
#define __IPARK_H__

typedef struct {  float32  Alpha;  		// Output: stationary d-axis stator variable
                  float32  Beta;		// Output: stationary q-axis stator variable
                  float32  Angle;		// Input: rotating angle (pu)
                  float32  Ds;			// Input: rotating d-axis stator variable
                  float32  Qs;			// Input: rotating q-axis stator variable
                  float32  Sine;
                  float32  Cosine;
		 	 	} IPARK;	            

typedef IPARK *IPARK_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the IPARK object.
-----------------------------------------------------------------------------*/                     
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
						  0, \
                          0, \
              			  }

/*------------------------------------------------------------------------------
	Inverse PARK Transformation Macro Definition
------------------------------------------------------------------------------*/


#define IPARK_MACRO(v)										\
															\
v.Alpha = v.Ds*v.Cosine - v.Qs*v.Sine;		\
v.Beta = v.Qs*v.Cosine + v.Ds*v.Sine;

#endif // __IPARK_H__

