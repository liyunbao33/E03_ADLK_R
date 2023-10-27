/*
 * File: ADLK.c
 *
 * Code generated for Simulink model 'ADLK'.
 *
 * Model version                  : 1.13
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Fri Oct 27 15:43:46 2023
 *
 * Target selection: autosar.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ADLK.h"
#include "rtwtypes.h"
#include "Rte_Type.h"
#include "ADLK_private.h"

/* Named constants for Chart: '<S3>/FLADLKDriver' */
#define ADLK_IN_Check                  ((uint8)1U)
#define ADLK_IN_Delay                  ((uint8)2U)
#define ADLK_IN_Idle                   ((uint8)1U)
#define ADLK_IN_LastCheck              ((uint8)2U)
#define ADLK_IN_Lock                   ((uint8)2U)
#define ADLK_IN_LockAct                ((uint8)3U)
#define ADLK_IN_NO_ACTIVE_CHILD        ((uint8)0U)
#define ADLK_IN_Normal                 ((uint8)1U)
#define ADLK_IN_PowerOn                ((uint8)2U)
#define ADLK_IN_Release                ((uint8)2U)
#define ADLK_IN_Reset                  ((uint8)3U)
#define ADLK_IN_Stall_Handle           ((uint8)4U)
#define ADLK_IN_Step1_Ajar             ((uint8)5U)
#define ADLK_IN_Step2_Open             ((uint8)6U)
#define ADLK_IN_Unlock                 ((uint8)4U)
#define ADLK_IN_UnlockAct              ((uint8)5U)
#define ADLK_IN_Wait                   ((uint8)3U)

/* Block signals (default storage) */
B_ADLK_T ADLK_B;

/* Block states (default storage) */
DW_ADLK_T ADLK_DW;

/* Forward declaration for local functions */
static uint8 ADLK_GetPwm(uint8 x, uint8 rtu_SI_e_Volt100mV);
static void ADLK_Rls(uint8 rtu_SI_e_Volt100mV, Boolean rtu_SI_b_DoorAjar,
                     Boolean rtu_SI_b_DoorOpen, uint8 rtu_SI_e_DoorRlsDelayTime,
                     uint8 *rty_SO_e_MotorCmd, uint8 *rty_SO_e_MotStateMachine,
                     uint8 *rty_SO_e_MotorPwm, boolean *rty_SO_b_Error,
                     DW_FLADLKDriver_ADLK_T *localDW);

/* Function for Chart: '<S3>/FLADLKDriver' */
static uint8 ADLK_GetPwm(uint8 x, uint8 rtu_SI_e_Volt100mV)
{
  sint32 tmp;
  uint8 y;
  if (rtu_SI_e_Volt100mV == 0) {
    tmp = MAX_int32_T;

    /* Divide by zero handler */
  } else {
    tmp = x * 100 / rtu_SI_e_Volt100mV;
  }

  if (tmp > 255) {
    tmp = 255;
  }

  y = (uint8)tmp;

  /*  扩大100倍，浮点转整型  */
  if (((uint8)tmp > 100) || (rtu_SI_e_Volt100mV == 0)) {
    y = 100U;
  }

  return y;
}

/* Function for Chart: '<S3>/FLADLKDriver' */
static void ADLK_Rls(uint8 rtu_SI_e_Volt100mV, Boolean rtu_SI_b_DoorAjar,
                     Boolean rtu_SI_b_DoorOpen, uint8 rtu_SI_e_DoorRlsDelayTime,
                     uint8 *rty_SO_e_MotorCmd, uint8 *rty_SO_e_MotStateMachine,
                     uint8 *rty_SO_e_MotorPwm, boolean *rty_SO_b_Error,
                     DW_FLADLKDriver_ADLK_T *localDW)
{
  switch (localDW->is_Rls) {
   case ADLK_IN_Normal:
    {
      if (localDW->is_MainProgress == ADLK_IN_Idle) {
        if ((localDW->SO_b_DoorRlsReq_prev != localDW->SO_b_DoorRlsReq_start) &&
            localDW->SO_b_DoorRlsReq_start) {
          localDW->SL_e_DoorRlsDelayTime = rtu_SI_e_DoorRlsDelayTime;
          *rty_SO_e_MotStateMachine = 1U;
          localDW->is_MainProgress = ADLK_IN_Release;
          localDW->SL_e_CycleCount = 0U;
          localDW->is_Release = ADLK_IN_Delay;
          localDW->temporalCounter_i2 = 0U;

          /*  无框车门电释放延时  */
        }
      } else {
        /* case IN_Release: */
        switch (localDW->is_Release) {
         case ADLK_IN_Check:
          {
            if ((localDW->temporalCounter_i2 >= 5) && rtu_SI_b_DoorAjar) {
              localDW->is_Release = ADLK_IN_Step2_Open;
              localDW->is_Step2_Open = ADLK_IN_Idle;
              localDW->temporalCounter_i2 = 0U;
              *rty_SO_e_MotorCmd = 0U;
              *rty_SO_e_MotorPwm = 0U;
              localDW->SL_b_MotorMutexFlg = false;
              *rty_SO_e_MotStateMachine = 2U;
            } else {
              Boolean tmp;
              boolean tmp_0;
              tmp = !rtu_SI_b_DoorAjar;
              tmp_0 = !localDW->SL_b_MotorMutexFlg;
              if ((localDW->temporalCounter_i2 >= 5) && tmp &&
                  (localDW->SL_e_CycleCount < 3) && tmp_0) {
                localDW->is_Release = ADLK_IN_Stall_Handle;
                localDW->temporalCounter_i2 = 0U;
                *rty_SO_e_MotorCmd = 1U;
                *rty_SO_e_MotorPwm = 100U;
                localDW->SL_e_CycleCount++;
                localDW->SL_b_MotorMutexFlg = true;
              } else if ((localDW->temporalCounter_i2 >= 5) && tmp &&
                         (localDW->SL_e_CycleCount >= 3) && tmp_0) {
                *rty_SO_b_Error = true;
                localDW->is_Release = ADLK_IN_Reset;
                localDW->temporalCounter_i2 = 0U;
                *rty_SO_e_MotorCmd = 2U;
                *rty_SO_e_MotorPwm = ADLK_GetPwm(70, rtu_SI_e_Volt100mV);
                localDW->SL_b_MotorMutexFlg = true;
                *rty_SO_e_MotStateMachine = 3U;
              }
            }
          }
          break;

         case ADLK_IN_Delay:
          if ((localDW->temporalCounter_i2 >= localDW->SL_e_DoorRlsDelayTime) &&
              (!localDW->SL_b_MotorMutexFlg)) {
            localDW->is_Release = ADLK_IN_Step1_Ajar;
            localDW->temporalCounter_i2 = 0U;
            *rty_SO_e_MotorCmd = 1U;
            *rty_SO_e_MotorPwm = ADLK_GetPwm(105, rtu_SI_e_Volt100mV);
            localDW->SL_b_MotorMutexFlg = true;
          }
          break;

         case ADLK_IN_Reset:
          if (localDW->temporalCounter_i2 >= 30) {
            localDW->SL_b_MotorMutexFlg = false;
            *rty_SO_e_MotStateMachine = 4U;
            localDW->is_Release = ADLK_IN_NO_ACTIVE_CHILD;
            localDW->is_MainProgress = ADLK_IN_Idle;
            *rty_SO_e_MotorCmd = 0U;
            *rty_SO_e_MotorPwm = 0U;
          }
          break;

         case ADLK_IN_Stall_Handle:
          if (localDW->temporalCounter_i2 >= 30) {
            localDW->is_Release = ADLK_IN_Check;
            localDW->temporalCounter_i2 = 0U;
            *rty_SO_e_MotorCmd = 0U;
            *rty_SO_e_MotorPwm = 0U;
            localDW->SL_b_MotorMutexFlg = false;
          }
          break;

         case ADLK_IN_Step1_Ajar:
          if (localDW->temporalCounter_i2 >= 30) {
            localDW->is_Release = ADLK_IN_Check;
            localDW->temporalCounter_i2 = 0U;
            *rty_SO_e_MotorCmd = 0U;
            *rty_SO_e_MotorPwm = 0U;
            localDW->SL_b_MotorMutexFlg = false;
          }
          break;

         default:
          /* case IN_Step2_Open: */
          if (localDW->is_Step2_Open == ADLK_IN_Idle) {
            if ((localDW->temporalCounter_i2 < 270) && rtu_SI_b_DoorOpen) {
              *rty_SO_b_Error = false;
              localDW->is_Step2_Open = ADLK_IN_NO_ACTIVE_CHILD;
              localDW->is_Release = ADLK_IN_Reset;
              localDW->temporalCounter_i2 = 0U;
              *rty_SO_e_MotorCmd = 2U;
              *rty_SO_e_MotorPwm = ADLK_GetPwm(70, rtu_SI_e_Volt100mV);
              localDW->SL_b_MotorMutexFlg = true;
              *rty_SO_e_MotStateMachine = 3U;
            } else if (localDW->temporalCounter_i2 >= 300) {
              localDW->is_Step2_Open = ADLK_IN_LastCheck;
            }
          } else {
            /* case IN_LastCheck: */
            localDW->is_Step2_Open = ADLK_IN_NO_ACTIVE_CHILD;
            localDW->is_Release = ADLK_IN_Reset;
            localDW->temporalCounter_i2 = 0U;
            *rty_SO_e_MotorCmd = 2U;
            *rty_SO_e_MotorPwm = ADLK_GetPwm(70, rtu_SI_e_Volt100mV);
            localDW->SL_b_MotorMutexFlg = true;
            *rty_SO_e_MotStateMachine = 3U;
          }
          break;
        }
      }
    }
    break;

   case ADLK_IN_PowerOn:
    if (localDW->temporalCounter_i2 >= 30) {
      localDW->SL_b_MotorMutexFlg = false;
      *rty_SO_e_MotStateMachine = 4U;
      localDW->is_Rls = ADLK_IN_Normal;

      /*  非电动门  */
      localDW->is_MainProgress = ADLK_IN_Idle;
      *rty_SO_e_MotorCmd = 0U;
      *rty_SO_e_MotorPwm = 0U;
    }
    break;

   default:
    /* case IN_Wait: */
    if (!localDW->SL_b_MotorMutexFlg) {
      localDW->is_Rls = ADLK_IN_PowerOn;
      localDW->temporalCounter_i2 = 0U;

      /*  上电释放电机执行一次复位  */
      *rty_SO_e_MotorCmd = 2U;
      *rty_SO_e_MotorPwm = ADLK_GetPwm(70, rtu_SI_e_Volt100mV);
      localDW->SL_b_MotorMutexFlg = true;
      *rty_SO_e_MotStateMachine = 3U;
    }
    break;
  }
}

/*
 * System initialize for atomic system:
 *    '<S3>/FLADLKDriver'
 *    '<S3>/RLADLKDriver'
 */
void ADLK_FLADLKDriver_Init(uint8 *rty_SO_e_MotorCmd, uint8
  *rty_SO_e_MotStateMachine, uint8 *rty_SO_e_MotorPwm, boolean *rty_SO_b_Error,
  uint8 *rty_SO_e_DoorLockCmd, uint8 *rty_SO_e_ClkLockCmd)
{
  *rty_SO_e_MotorCmd = 0U;
  *rty_SO_e_MotStateMachine = 0U;
  *rty_SO_e_MotorPwm = 0U;
  *rty_SO_b_Error = false;
  *rty_SO_e_DoorLockCmd = 0U;
  *rty_SO_e_ClkLockCmd = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S3>/FLADLKDriver'
 *    '<S3>/RLADLKDriver'
 */
void ADLK_FLADLKDriver(uint8 rtu_SI_e_Volt100mV, Boolean rtu_SO_b_DoorRlsReq,
  Boolean rtu_SI_b_DoorAjar, Boolean rtu_SI_b_DoorOpen, uint8
  rtu_SI_e_DoorRlsDelayTime, Boolean rtu_SI_b_DoorUnlockFlg, Boolean
  rtu_SI_b_DoorLockFlg, boolean rtu_SI_b_ClkUnlockFlg, boolean
  rtu_SI_b_ClkLockFlg, uint8 *rty_SO_e_MotorCmd, uint8 *rty_SO_e_MotStateMachine,
  uint8 *rty_SO_e_MotorPwm, boolean *rty_SO_b_Error, uint8 *rty_SO_e_DoorLockCmd,
  uint8 *rty_SO_e_ClkLockCmd, DW_FLADLKDriver_ADLK_T *localDW)
{
  if (localDW->temporalCounter_i1 < 31U) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->temporalCounter_i2 < 511U) {
    localDW->temporalCounter_i2++;
  }

  if (localDW->temporalCounter_i3 < 31U) {
    localDW->temporalCounter_i3++;
  }

  localDW->SI_b_ClkUnlockFlg_prev = localDW->SI_b_ClkUnlockFlg_start;
  localDW->SI_b_ClkUnlockFlg_start = rtu_SI_b_ClkUnlockFlg;
  localDW->SI_b_ClkLockFlg_prev = localDW->SI_b_ClkLockFlg_start;
  localDW->SI_b_ClkLockFlg_start = rtu_SI_b_ClkLockFlg;
  localDW->SO_b_DoorRlsReq_prev = localDW->SO_b_DoorRlsReq_start;
  localDW->SO_b_DoorRlsReq_start = rtu_SO_b_DoorRlsReq;
  localDW->SI_b_DoorUnlockFlg_prev = localDW->SI_b_DoorUnlockFlg_start;
  localDW->SI_b_DoorUnlockFlg_start = rtu_SI_b_DoorUnlockFlg;
  localDW->SI_b_DoorLockFlg_prev = localDW->SI_b_DoorLockFlg_start;
  localDW->SI_b_DoorLockFlg_start = rtu_SI_b_DoorLockFlg;

  /* Chart: '<S3>/FLADLKDriver' */
  if (localDW->is_active_c19_ADLKDriver == 0U) {
    localDW->SI_b_ClkUnlockFlg_prev = rtu_SI_b_ClkUnlockFlg;
    localDW->SI_b_ClkLockFlg_prev = rtu_SI_b_ClkLockFlg;
    localDW->SO_b_DoorRlsReq_prev = rtu_SO_b_DoorRlsReq;
    localDW->SI_b_DoorUnlockFlg_prev = rtu_SI_b_DoorUnlockFlg;
    localDW->SI_b_DoorLockFlg_prev = rtu_SI_b_DoorLockFlg;
    localDW->is_active_c19_ADLKDriver = 1U;
    localDW->is_CLK = ADLK_IN_Idle;
    localDW->is_DLK = ADLK_IN_Idle;
    localDW->is_Rls = ADLK_IN_Wait;

    /*  等待电机资源空闲  */
  } else {
    switch (localDW->is_CLK) {
     case ADLK_IN_Idle:
      if ((localDW->SI_b_ClkUnlockFlg_prev != localDW->SI_b_ClkUnlockFlg_start) &&
          localDW->SI_b_ClkUnlockFlg_start) {
        localDW->is_CLK = ADLK_IN_Unlock;
      } else if ((localDW->SI_b_ClkLockFlg_prev !=
                  localDW->SI_b_ClkLockFlg_start) &&
                 localDW->SI_b_ClkLockFlg_start) {
        localDW->is_CLK = ADLK_IN_Lock;
      }
      break;

     case ADLK_IN_Lock:
      if (!localDW->SL_b_MotorMutexFlg) {
        localDW->is_CLK = ADLK_IN_LockAct;
        localDW->temporalCounter_i1 = 0U;
        *rty_SO_e_ClkLockCmd = 2U;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     case ADLK_IN_LockAct:
      if (localDW->temporalCounter_i1 >= 20) {
        *rty_SO_e_ClkLockCmd = 0U;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_CLK = ADLK_IN_Idle;
      }
      break;

     case ADLK_IN_Unlock:
      if (!localDW->SL_b_MotorMutexFlg) {
        localDW->is_CLK = ADLK_IN_UnlockAct;
        localDW->temporalCounter_i1 = 0U;
        *rty_SO_e_ClkLockCmd = 1U;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     default:
      /* case IN_UnlockAct: */
      if (localDW->temporalCounter_i1 >= 20) {
        *rty_SO_e_ClkLockCmd = 0U;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_CLK = ADLK_IN_Idle;
      }
      break;
    }

    switch (localDW->is_DLK) {
     case ADLK_IN_Idle:
      if ((localDW->SI_b_DoorUnlockFlg_prev != localDW->SI_b_DoorUnlockFlg_start)
          && localDW->SI_b_DoorUnlockFlg_start) {
        localDW->is_DLK = ADLK_IN_Unlock;
      } else if ((localDW->SI_b_DoorLockFlg_prev !=
                  localDW->SI_b_DoorLockFlg_start) &&
                 localDW->SI_b_DoorLockFlg_start) {
        localDW->is_DLK = ADLK_IN_Lock;
      }
      break;

     case ADLK_IN_Lock:
      if (!localDW->SL_b_MotorMutexFlg) {
        localDW->is_DLK = ADLK_IN_LockAct;
        localDW->temporalCounter_i3 = 0U;
        *rty_SO_e_DoorLockCmd = 2U;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     case ADLK_IN_LockAct:
      if (localDW->temporalCounter_i3 >= 20) {
        *rty_SO_e_DoorLockCmd = 0U;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_DLK = ADLK_IN_Idle;
      }
      break;

     case ADLK_IN_Unlock:
      if (!localDW->SL_b_MotorMutexFlg) {
        localDW->is_DLK = ADLK_IN_UnlockAct;
        localDW->temporalCounter_i3 = 0U;
        *rty_SO_e_DoorLockCmd = 1U;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     default:
      /* case IN_UnlockAct: */
      if (localDW->temporalCounter_i3 >= 20) {
        *rty_SO_e_DoorLockCmd = 0U;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_DLK = ADLK_IN_Idle;
      }
      break;
    }

    ADLK_Rls(rtu_SI_e_Volt100mV, rtu_SI_b_DoorAjar, rtu_SI_b_DoorOpen,
             rtu_SI_e_DoorRlsDelayTime, rty_SO_e_MotorCmd,
             rty_SO_e_MotStateMachine, rty_SO_e_MotorPwm, rty_SO_b_Error,
             localDW);
  }

  /* End of Chart: '<S3>/FLADLKDriver' */
}

/* Model step function for TID1 */
void ADLK_Step(void)                   /* Explicit Task: ADLK_Step */
{
  uint8 SO_e_ClkLockCmd_h;
  Boolean tmpRead;
  Boolean tmpRead_0;
  Boolean tmpRead_1;
  Boolean tmpRead_2;
  Boolean tmpRead_3;
  Boolean tmpRead_4;
  Boolean tmpRead_5;
  Boolean tmpRead_6;
  Boolean tmpRead_7;
  boolean SO_b_Error;
  boolean SO_b_Error_c;

  /* Inport: '<Root>/VbOUT_HWA_RRDoorFullOpen_flg_VbOUT_HWA_RRDoorFullOpen_flg' */
  (void)Rte_Read_VbOUT_HWA_RRDoorFullOpen_flg_VbOUT_HWA_RRDoorFullOpen_flg
    (&tmpRead_7);

  /* Inport: '<Root>/VbOUT_HWA_FRDoorFullOpen_flg_VbOUT_HWA_FRDoorFullOpen_flg' */
  (void)Rte_Read_VbOUT_HWA_FRDoorFullOpen_flg_VbOUT_HWA_FRDoorFullOpen_flg
    (&SO_b_Error);

  /* Inport: '<Root>/VbINP_HWA_RRDoorAjar_flg_VbINP_HWA_RRDoorAjar_flg' */
  (void)Rte_Read_VbINP_HWA_RRDoorAjar_flg_VbINP_HWA_RRDoorAjar_flg(&tmpRead_6);

  /* Inport: '<Root>/VbINP_HWA_FRDoorAjar_flg_VbINP_HWA_FRDoorAjar_flg' */
  (void)Rte_Read_VbINP_HWA_FRDoorAjar_flg_VbINP_HWA_FRDoorAjar_flg(&tmpRead_5);

  /* Inport: '<Root>/VbOUT_REL_RRDoorRlsReq_flg_VbOUT_REL_RRDoorRlsReq_flg' */
  (void)Rte_Read_VbOUT_REL_RRDoorRlsReq_flg_VbOUT_REL_RRDoorRlsReq_flg
    (&tmpRead_4);

  /* Inport: '<Root>/VbOUT_REL_FRDoorRlsReq_flg_VbOUT_REL_FRDoorRlsReq_flg' */
  (void)Rte_Read_VbOUT_REL_FRDoorRlsReq_flg_VbOUT_REL_FRDoorRlsReq_flg
    (&tmpRead_3);

  /* Inport: '<Root>/VbOUT_DLK_RRLock_flg_VbOUT_DLK_RRLock_flg' */
  (void)Rte_Read_VbOUT_DLK_RRLock_flg_VbOUT_DLK_RRLock_flg(&tmpRead_2);

  /* Inport: '<Root>/VbOUT_DLK_RRUnlock_flg_VbOUT_DLK_RRUnlock_flg' */
  (void)Rte_Read_VbOUT_DLK_RRUnlock_flg_VbOUT_DLK_RRUnlock_flg(&tmpRead_1);

  /* Inport: '<Root>/VbOUT_DLK_FRLock_flg_VbOUT_DLK_FRLock_flg' */
  (void)Rte_Read_VbOUT_DLK_FRLock_flg_VbOUT_DLK_FRLock_flg(&tmpRead_0);

  /* Inport: '<Root>/VbOUT_DLK_FRUnlock_flg_VbOUT_DLK_FRUnlock_flg' */
  (void)Rte_Read_VbOUT_DLK_FRUnlock_flg_VbOUT_DLK_FRUnlock_flg(&tmpRead);

  /* RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' incorporates:
   *  SubSystem: '<Root>/ADLK_Step_sys'
   */
  /* DataStoreWrite: '<S3>/Data Store Write' incorporates:
   *  Constant: '<S3>/Constant'
   */
  ADLK_DW.E03_ADLK_R = 0U;

  /* Chart: '<S3>/FLADLKDriver' incorporates:
   *  Constant: '<S3>/Constant1'
   */
  ADLK_FLADLKDriver(0U, tmpRead_3, tmpRead_5, SO_b_Error, 20, tmpRead, tmpRead_0,
                    false, false, &ADLK_B.SO_e_MotorCmd_p,
                    &ADLK_B.SO_e_MotStateMachine_c, &ADLK_B.SO_e_MotorPwm_b,
                    &SO_b_Error_c, &ADLK_B.SO_e_DoorLockCmd_f,
                    &SO_e_ClkLockCmd_h, &ADLK_DW.sf_FLADLKDriver);

  /* Chart: '<S3>/RLADLKDriver' incorporates:
   *  Constant: '<S3>/Constant1'
   */
  ADLK_FLADLKDriver(0U, tmpRead_4, tmpRead_6, tmpRead_7, 20, tmpRead_1,
                    tmpRead_2, false, false, &ADLK_B.SO_e_MotorCmd,
                    &ADLK_B.SO_e_MotStateMachine, &ADLK_B.SO_e_MotorPwm,
                    &SO_b_Error, &ADLK_B.SO_e_DoorLockCmd, &SO_e_ClkLockCmd_h,
                    &ADLK_DW.sf_RLADLKDriver);

  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' */

  /* Outport: '<Root>/VeOUT_ADLK_FRLockReq_sig_VeOUT_ADLK_FRLockReq_sig' */
  (void)Rte_Write_VeOUT_ADLK_FRLockReq_sig_VeOUT_ADLK_FRLockReq_sig
    (ADLK_B.SO_e_DoorLockCmd_f);

  /* Outport: '<Root>/VeOUT_ADLK_RRLockReq_sig_VeOUT_ADLK_RRLockReq_sig' */
  (void)Rte_Write_VeOUT_ADLK_RRLockReq_sig_VeOUT_ADLK_RRLockReq_sig
    (ADLK_B.SO_e_DoorLockCmd);

  /* Outport: '<Root>/VeOUT_ADLK_FRReleaseLatchStatus_sig_VeOUT_ADLK_FRReleaseLatchStatus_sig' */
  (void)
    Rte_Write_VeOUT_ADLK_FRReleaseLatchStatus_sig_VeOUT_ADLK_FRReleaseLatchStatus_sig
    (ADLK_B.SO_e_MotStateMachine_c);

  /* Outport: '<Root>/VeOUT_ADLK_RRReleaseLatchStatus_sig_VeOUT_ADLK_RRReleaseLatchStatus_sig' */
  (void)
    Rte_Write_VeOUT_ADLK_RRReleaseLatchStatus_sig_VeOUT_ADLK_RRReleaseLatchStatus_sig
    (ADLK_B.SO_e_MotStateMachine);

  /* Outport: '<Root>/VeOUT_ADLK_FRDoorMotorCmd_sig_VeOUT_ADLK_FRDoorMotorCmd_sig' */
  (void)Rte_Write_VeOUT_ADLK_FRDoorMotorCmd_sig_VeOUT_ADLK_FRDoorMotorCmd_sig
    (ADLK_B.SO_e_MotorCmd_p);

  /* Outport: '<Root>/VeOUT_ADLK_RRDoorMotorCmd_sig_VeOUT_ADLK_RRDoorMotorCmd_sig' */
  (void)Rte_Write_VeOUT_ADLK_RRDoorMotorCmd_sig_VeOUT_ADLK_RRDoorMotorCmd_sig
    (ADLK_B.SO_e_MotorCmd);

  /* Outport: '<Root>/VeOUT_ADLK_FRDoorMotorPWM_pct_VeOUT_ADLK_FRDoorMotorPWM_pct' */
  (void)Rte_Write_VeOUT_ADLK_FRDoorMotorPWM_pct_VeOUT_ADLK_FRDoorMotorPWM_pct
    (ADLK_B.SO_e_MotorPwm_b);

  /* Outport: '<Root>/VeOUT_ADLK_RRDoorMotorPWM_pct_VeOUT_ADLK_RRDoorMotorPWM_pct' */
  (void)Rte_Write_VeOUT_ADLK_RRDoorMotorPWM_pct_VeOUT_ADLK_RRDoorMotorPWM_pct
    (ADLK_B.SO_e_MotorPwm);
}

/* Model initialize function */
void ADLK_Init(void)
{
  {
    uint8 SO_e_ClkLockCmd_h;
    boolean SO_b_Error_c;

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' incorporates:
     *  SubSystem: '<Root>/ADLK_Step_sys'
     */

    /* SystemInitialize for Chart: '<S3>/FLADLKDriver' */
    ADLK_FLADLKDriver_Init(&ADLK_B.SO_e_MotorCmd_p,
      &ADLK_B.SO_e_MotStateMachine_c, &ADLK_B.SO_e_MotorPwm_b, &SO_b_Error_c,
      &ADLK_B.SO_e_DoorLockCmd_f, &SO_e_ClkLockCmd_h);

    /* SystemInitialize for Chart: '<S3>/RLADLKDriver' */
    ADLK_FLADLKDriver_Init(&ADLK_B.SO_e_MotorCmd, &ADLK_B.SO_e_MotStateMachine,
      &ADLK_B.SO_e_MotorPwm, &SO_b_Error_c, &ADLK_B.SO_e_DoorLockCmd,
      &SO_e_ClkLockCmd_h);

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' */

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_FRLockReq_sig_VeOUT_ADLK_FRLockReq_sig' */
    (void)Rte_Write_VeOUT_ADLK_FRLockReq_sig_VeOUT_ADLK_FRLockReq_sig
      (ADLK_B.SO_e_DoorLockCmd_f);

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_RRLockReq_sig_VeOUT_ADLK_RRLockReq_sig' */
    (void)Rte_Write_VeOUT_ADLK_RRLockReq_sig_VeOUT_ADLK_RRLockReq_sig
      (ADLK_B.SO_e_DoorLockCmd);

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_FRReleaseLatchStatus_sig_VeOUT_ADLK_FRReleaseLatchStatus_sig' */
    (void)
      Rte_Write_VeOUT_ADLK_FRReleaseLatchStatus_sig_VeOUT_ADLK_FRReleaseLatchStatus_sig
      (ADLK_B.SO_e_MotStateMachine_c);

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_RRReleaseLatchStatus_sig_VeOUT_ADLK_RRReleaseLatchStatus_sig' */
    (void)
      Rte_Write_VeOUT_ADLK_RRReleaseLatchStatus_sig_VeOUT_ADLK_RRReleaseLatchStatus_sig
      (ADLK_B.SO_e_MotStateMachine);

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_FRDoorMotorCmd_sig_VeOUT_ADLK_FRDoorMotorCmd_sig' */
    (void)Rte_Write_VeOUT_ADLK_FRDoorMotorCmd_sig_VeOUT_ADLK_FRDoorMotorCmd_sig
      (ADLK_B.SO_e_MotorCmd_p);

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_RRDoorMotorCmd_sig_VeOUT_ADLK_RRDoorMotorCmd_sig' */
    (void)Rte_Write_VeOUT_ADLK_RRDoorMotorCmd_sig_VeOUT_ADLK_RRDoorMotorCmd_sig
      (ADLK_B.SO_e_MotorCmd);

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_FRDoorMotorPWM_pct_VeOUT_ADLK_FRDoorMotorPWM_pct' */
    (void)Rte_Write_VeOUT_ADLK_FRDoorMotorPWM_pct_VeOUT_ADLK_FRDoorMotorPWM_pct
      (ADLK_B.SO_e_MotorPwm_b);

    /* SystemInitialize for Outport: '<Root>/VeOUT_ADLK_RRDoorMotorPWM_pct_VeOUT_ADLK_RRDoorMotorPWM_pct' */
    (void)Rte_Write_VeOUT_ADLK_RRDoorMotorPWM_pct_VeOUT_ADLK_RRDoorMotorPWM_pct
      (ADLK_B.SO_e_MotorPwm);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
