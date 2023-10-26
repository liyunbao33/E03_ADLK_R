/*
 * File: ADLK.h
 *
 * Code generated for Simulink model 'ADLK'.
 *
 * Model version                  : 1.36
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Wed Oct 25 13:17:41 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ADLK_h_
#define RTW_HEADER_ADLK_h_
#ifndef ADLK_COMMON_INCLUDES_
#define ADLK_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ADLK_COMMON_INCLUDES_ */

#include "ADLK_types.h"
#include "Rte_Type.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<S3>/FLADLKDriver' */
typedef struct {
  uint16_T temporalCounter_i2;         /* '<S3>/FLADLKDriver' */
  uint8_T is_active_c19_ADLKDriver;    /* '<S3>/FLADLKDriver' */
  uint8_T is_DLK;                      /* '<S3>/FLADLKDriver' */
  uint8_T is_Rls;                      /* '<S3>/FLADLKDriver' */
  uint8_T is_MainProgress;             /* '<S3>/FLADLKDriver' */
  uint8_T is_Release;                  /* '<S3>/FLADLKDriver' */
  uint8_T is_Step2_Open;               /* '<S3>/FLADLKDriver' */
  uint8_T is_CLK;                      /* '<S3>/FLADLKDriver' */
  uint8_T SL_e_CycleCount;             /* '<S3>/FLADLKDriver' */
  uint8_T SL_e_DoorRlsDelayTime;       /* '<S3>/FLADLKDriver' */
  uint8_T temporalCounter_i1;          /* '<S3>/FLADLKDriver' */
  uint8_T temporalCounter_i3;          /* '<S3>/FLADLKDriver' */
  boolean_T SL_b_MotorMutexFlg;        /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_DoorUnlockFlg_prev;   /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_DoorUnlockFlg_start;  /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_DoorLockFlg_prev;     /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_DoorLockFlg_start;    /* '<S3>/FLADLKDriver' */
  boolean_T SO_b_DoorRlsReq_prev;      /* '<S3>/FLADLKDriver' */
  boolean_T SO_b_DoorRlsReq_start;     /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_ClkUnlockFlg_prev;    /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_ClkUnlockFlg_start;   /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_ClkLockFlg_prev;      /* '<S3>/FLADLKDriver' */
  boolean_T SI_b_ClkLockFlg_start;     /* '<S3>/FLADLKDriver' */
} DW_FLADLKDriver_ADLK_T;

/* Block signals (default storage) */
typedef struct {
  uint8_T SO_e_MotorCmd;               /* '<S3>/RLADLKDriver' */
  uint8_T SO_e_MotorCmd_c;             /* '<S3>/FLADLKDriver' */
} B_ADLK_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  DW_FLADLKDriver_ADLK_T sf_RLADLKDriver;/* '<S3>/RLADLKDriver' */
  DW_FLADLKDriver_ADLK_T sf_FLADLKDriver;/* '<S3>/FLADLKDriver' */
} DW_ADLK_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  Boolean VbOUT_DLK_FRUnlock_flg_VbOUT_DL;
                    /* '<Root>/VbOUT_DLK_FRUnlock_flg_VbOUT_DLK_FRUnlock_flg' */
  Boolean VbOUT_DLK_FRLock_flg_VbOUT_DLK_;
                        /* '<Root>/VbOUT_DLK_FRLock_flg_VbOUT_DLK_FRLock_flg' */
  Boolean VbOUT_DLK_RRUnlock_flg_VbOUT_DL;
                    /* '<Root>/VbOUT_DLK_RRUnlock_flg_VbOUT_DLK_RRUnlock_flg' */
  Boolean VbOUT_DLK_RRLock_flg_VbOUT_DLK_;
                        /* '<Root>/VbOUT_DLK_RRLock_flg_VbOUT_DLK_RRLock_flg' */
  Boolean VbOUT_REL_FRDoorRlsReq_flg_VbOU;
            /* '<Root>/VbOUT_REL_FRDoorRlsReq_flg_VbOUT_REL_FRDoorRlsReq_flg' */
  Boolean VbOUT_REL_RRDoorRlsReq_flg_VbOU;
            /* '<Root>/VbOUT_REL_RRDoorRlsReq_flg_VbOUT_REL_RRDoorRlsReq_flg' */
  Boolean VbINP_HWA_FRDoorAjar_flg_VbINP_;
                /* '<Root>/VbINP_HWA_FRDoorAjar_flg_VbINP_HWA_FRDoorAjar_flg' */
  Boolean VbINP_HWA_RRDoorAjar_flg_VbINP_;
                /* '<Root>/VbINP_HWA_RRDoorAjar_flg_VbINP_HWA_RRDoorAjar_flg' */
  Boolean VbOUT_HWA_FRDoorFullOpen_flg_Vb;
        /* '<Root>/VbOUT_HWA_FRDoorFullOpen_flg_VbOUT_HWA_FRDoorFullOpen_flg' */
  Boolean VbOUT_HWA_RRDoorFullOpen_flg_Vb;
        /* '<Root>/VbOUT_HWA_RRDoorFullOpen_flg_VbOUT_HWA_RRDoorFullOpen_flg' */
} ExtU_ADLK_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  Boolean VbOUT_ADLK_FRUnlock_flg_VbOUT_A;
                  /* '<Root>/VbOUT_ADLK_FRUnlock_flg_VbOUT_ADLK_FRUnlock_flg' */
  Boolean VbOUT_ADLK_FRLock_flg_VbOUT_ADL;
                      /* '<Root>/VbOUT_ADLK_FRLock_flg_VbOUT_ADLK_FRLock_flg' */
  Boolean VbOUT_ADLK_RRUnlock_flg_VbOUT_A;
                  /* '<Root>/VbOUT_ADLK_RRUnlock_flg_VbOUT_ADLK_RRUnlock_flg' */
  Boolean VbOUT_ADLK_RRLock_flg_VbOUT_ADL;
                      /* '<Root>/VbOUT_ADLK_RRLock_flg_VbOUT_ADLK_RRLock_flg' */
  Boolean VbOUT_ADLK_FRDoorMotorA_flg_VbO;
          /* '<Root>/VbOUT_ADLK_FRDoorMotorA_flg_VbOUT_ADLK_FRDoorMotorA_flg' */
  Boolean VbOUT_ADLK_FRDoorMotorB_flg_VbO;
          /* '<Root>/VbOUT_ADLK_FRDoorMotorB_flg_VbOUT_ADLK_FRDoorMotorB_flg' */
  Boolean VbOUT_ADLK_RRDoorMotorA_flg_VbO;
          /* '<Root>/VbOUT_ADLK_RRDoorMotorA_flg_VbOUT_ADLK_RRDoorMotorA_flg' */
  Boolean VbOUT_ADLK_RRDoorMotorB_flg_VbO;
          /* '<Root>/VbOUT_ADLK_RRDoorMotorB_flg_VbOUT_ADLK_RRDoorMotorB_flg' */
  UInt8 VeOUT_ADLK_FRReleaseLatchStatus;
  /* '<Root>/VeOUT_ADLK_FRReleaseLatchStatus_sig_VeOUT_ADLK_FRReleaseLatchStatus_sig' */
  UInt8 VeOUT_ADLK_RRReleaseLatchStatus;
  /* '<Root>/VeOUT_ADLK_RRReleaseLatchStatus_sig_VeOUT_ADLK_RRReleaseLatchStatus_sig' */
} ExtY_ADLK_T;

/* Real-time Model Data Structure */
struct tag_RTM_ADLK_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_ADLK_T ADLK_B;

/* Block states (default storage) */
extern DW_ADLK_T ADLK_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_ADLK_T ADLK_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_ADLK_T ADLK_Y;

/* Model entry point functions */
extern void ADLK_initialize(void);
extern void ADLK_terminate(void);

/* Exported entry point function */
extern void ADLK_Step(void);

/* Real-time Model object */
extern RT_MODEL_ADLK_T *const ADLK_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ADLK'
 * '<S1>'   : 'ADLK/ADLK_Init'
 * '<S2>'   : 'ADLK/ADLK_Step_sys'
 * '<S3>'   : 'ADLK/ADLK_Step_sys/ADLK'
 * '<S4>'   : 'ADLK/ADLK_Step_sys/ADLK/Compare To Constant'
 * '<S5>'   : 'ADLK/ADLK_Step_sys/ADLK/Compare To Constant1'
 * '<S6>'   : 'ADLK/ADLK_Step_sys/ADLK/Compare To Constant2'
 * '<S7>'   : 'ADLK/ADLK_Step_sys/ADLK/Compare To Constant3'
 * '<S8>'   : 'ADLK/ADLK_Step_sys/ADLK/FLADLKDriver'
 * '<S9>'   : 'ADLK/ADLK_Step_sys/ADLK/RLADLKDriver'
 * '<S10>'  : 'ADLK/ADLK_Step_sys/ADLK/Recycle Bin'
 */
#endif                                 /* RTW_HEADER_ADLK_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
