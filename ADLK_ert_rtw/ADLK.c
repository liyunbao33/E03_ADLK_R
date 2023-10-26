/*
 * File: ADLK.c
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

#include "ADLK.h"
#include "rtwtypes.h"
#include "Rte_Type.h"
#include "ADLK_private.h"

/* Named constants for Chart: '<S3>/FLADLKDriver' */
#define ADLK_IN_Check                  ((uint8_T)1U)
#define ADLK_IN_Delay                  ((uint8_T)2U)
#define ADLK_IN_Idle                   ((uint8_T)1U)
#define ADLK_IN_LastCheck              ((uint8_T)2U)
#define ADLK_IN_Lock                   ((uint8_T)2U)
#define ADLK_IN_LockAct                ((uint8_T)3U)
#define ADLK_IN_NO_ACTIVE_CHILD        ((uint8_T)0U)
#define ADLK_IN_Normal                 ((uint8_T)1U)
#define ADLK_IN_PowerOn                ((uint8_T)2U)
#define ADLK_IN_Release                ((uint8_T)2U)
#define ADLK_IN_Reset                  ((uint8_T)3U)
#define ADLK_IN_Stall_Handle           ((uint8_T)4U)
#define ADLK_IN_Step1_Ajar             ((uint8_T)5U)
#define ADLK_IN_Step2_Open             ((uint8_T)6U)
#define ADLK_IN_Unlock                 ((uint8_T)4U)
#define ADLK_IN_UnlockAct              ((uint8_T)5U)
#define ADLK_IN_Wait                   ((uint8_T)3U)

/* Block signals (default storage) */
B_ADLK_T ADLK_B;

/* Block states (default storage) */
DW_ADLK_T ADLK_DW;

/* External inputs (root inport signals with default storage) */
ExtU_ADLK_T ADLK_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_ADLK_T ADLK_Y;

/* Real-time model */
static RT_MODEL_ADLK_T ADLK_M_;
RT_MODEL_ADLK_T *const ADLK_M = &ADLK_M_;

/* Forward declaration for local functions */
static real_T ADLK_GetPwm(real_T x, uint8_T rtu_SI_e_Volt100mV);
static void ADLK_Rls(uint8_T rtu_SI_e_Volt100mV, Boolean rtu_SI_b_DoorAjar,
                     Boolean rtu_SI_b_DoorOpen, uint8_T
                     rtu_SI_e_DoorRlsDelayTime, uint8_T *rty_SO_e_MotorCmd,
                     uint8_T *rty_SO_e_MotStateMachine, uint8_T
                     *rty_SO_e_MotorPwm, boolean_T *rty_SO_b_Error,
                     DW_FLADLKDriver_ADLK_T *localDW);

/* Function for Chart: '<S3>/FLADLKDriver' */
static real_T ADLK_GetPwm(real_T x, uint8_T rtu_SI_e_Volt100mV)
{
  real_T y;
  y = x * 100.0 / (real_T)rtu_SI_e_Volt100mV;

  /*  扩大100倍，浮点转整型  */
  if ((y > 100.0) || (rtu_SI_e_Volt100mV == 0)) {
    y = 100.0;
  }

  return y;
}

/* Function for Chart: '<S3>/FLADLKDriver' */
static void ADLK_Rls(uint8_T rtu_SI_e_Volt100mV, Boolean rtu_SI_b_DoorAjar,
                     Boolean rtu_SI_b_DoorOpen, uint8_T
                     rtu_SI_e_DoorRlsDelayTime, uint8_T *rty_SO_e_MotorCmd,
                     uint8_T *rty_SO_e_MotStateMachine, uint8_T
                     *rty_SO_e_MotorPwm, boolean_T *rty_SO_b_Error,
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
              Boolean tmp_0;
              boolean_T tmp_1;
              tmp_0 = !rtu_SI_b_DoorAjar;
              tmp_1 = !localDW->SL_b_MotorMutexFlg;
              if ((localDW->temporalCounter_i2 >= 5) && tmp_0 &&
                  (localDW->SL_e_CycleCount < 3) && tmp_1) {
                localDW->is_Release = ADLK_IN_Stall_Handle;
                localDW->temporalCounter_i2 = 0U;
                *rty_SO_e_MotorCmd = 1U;
                *rty_SO_e_MotorPwm = 100U;
                localDW->SL_e_CycleCount++;
                localDW->SL_b_MotorMutexFlg = true;
              } else if ((localDW->temporalCounter_i2 >= 5) && tmp_0 &&
                         (localDW->SL_e_CycleCount >= 3) && tmp_1) {
                real_T tmp;
                *rty_SO_b_Error = true;
                localDW->is_Release = ADLK_IN_Reset;
                localDW->temporalCounter_i2 = 0U;
                *rty_SO_e_MotorCmd = 2U;
                tmp = ADLK_GetPwm(70.0, rtu_SI_e_Volt100mV);
                if (tmp < 256.0) {
                  if (tmp >= 0.0) {
                    *rty_SO_e_MotorPwm = (uint8_T)tmp;
                  } else {
                    *rty_SO_e_MotorPwm = 0U;
                  }
                } else {
                  *rty_SO_e_MotorPwm = MAX_uint8_T;
                }

                localDW->SL_b_MotorMutexFlg = true;
                *rty_SO_e_MotStateMachine = 3U;
              }
            }
          }
          break;

         case ADLK_IN_Delay:
          {
            if ((localDW->temporalCounter_i2 >= localDW->SL_e_DoorRlsDelayTime) &&
                (!localDW->SL_b_MotorMutexFlg)) {
              real_T tmp;
              localDW->is_Release = ADLK_IN_Step1_Ajar;
              localDW->temporalCounter_i2 = 0U;
              *rty_SO_e_MotorCmd = 1U;
              tmp = ADLK_GetPwm(105.0, rtu_SI_e_Volt100mV);
              if (tmp < 256.0) {
                if (tmp >= 0.0) {
                  *rty_SO_e_MotorPwm = (uint8_T)tmp;
                } else {
                  *rty_SO_e_MotorPwm = 0U;
                }
              } else {
                *rty_SO_e_MotorPwm = MAX_uint8_T;
              }

              localDW->SL_b_MotorMutexFlg = true;
            }
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
          {
            /* case IN_Step2_Open: */
            if (localDW->is_Step2_Open == ADLK_IN_Idle) {
              if ((localDW->temporalCounter_i2 < 270) && rtu_SI_b_DoorOpen) {
                real_T tmp;
                *rty_SO_b_Error = false;
                localDW->is_Step2_Open = ADLK_IN_NO_ACTIVE_CHILD;
                localDW->is_Release = ADLK_IN_Reset;
                localDW->temporalCounter_i2 = 0U;
                *rty_SO_e_MotorCmd = 2U;
                tmp = ADLK_GetPwm(70.0, rtu_SI_e_Volt100mV);
                if (tmp < 256.0) {
                  if (tmp >= 0.0) {
                    *rty_SO_e_MotorPwm = (uint8_T)tmp;
                  } else {
                    *rty_SO_e_MotorPwm = 0U;
                  }
                } else {
                  *rty_SO_e_MotorPwm = MAX_uint8_T;
                }

                localDW->SL_b_MotorMutexFlg = true;
                *rty_SO_e_MotStateMachine = 3U;
              } else if (localDW->temporalCounter_i2 >= 300) {
                localDW->is_Step2_Open = ADLK_IN_LastCheck;
              }
            } else {
              real_T tmp;

              /* case IN_LastCheck: */
              localDW->is_Step2_Open = ADLK_IN_NO_ACTIVE_CHILD;
              localDW->is_Release = ADLK_IN_Reset;
              localDW->temporalCounter_i2 = 0U;
              *rty_SO_e_MotorCmd = 2U;
              tmp = ADLK_GetPwm(70.0, rtu_SI_e_Volt100mV);
              if (tmp < 256.0) {
                if (tmp >= 0.0) {
                  *rty_SO_e_MotorPwm = (uint8_T)tmp;
                } else {
                  *rty_SO_e_MotorPwm = 0U;
                }
              } else {
                *rty_SO_e_MotorPwm = MAX_uint8_T;
              }

              localDW->SL_b_MotorMutexFlg = true;
              *rty_SO_e_MotStateMachine = 3U;
            }
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
    {
      /* case IN_Wait: */
      if (!localDW->SL_b_MotorMutexFlg) {
        real_T tmp;
        localDW->is_Rls = ADLK_IN_PowerOn;
        localDW->temporalCounter_i2 = 0U;

        /*  上电释放电机执行一次复位  */
        *rty_SO_e_MotorCmd = 2U;
        tmp = ADLK_GetPwm(70.0, rtu_SI_e_Volt100mV);
        if (tmp < 256.0) {
          if (tmp >= 0.0) {
            *rty_SO_e_MotorPwm = (uint8_T)tmp;
          } else {
            *rty_SO_e_MotorPwm = 0U;
          }
        } else {
          *rty_SO_e_MotorPwm = MAX_uint8_T;
        }

        localDW->SL_b_MotorMutexFlg = true;
        *rty_SO_e_MotStateMachine = 3U;
      }
    }
    break;
  }
}

/*
 * System initialize for atomic system:
 *    '<S3>/FLADLKDriver'
 *    '<S3>/RLADLKDriver'
 */
void ADLK_FLADLKDriver_Init(uint8_T *rty_SO_e_MotorCmd, uint8_T
  *rty_SO_e_MotStateMachine, uint8_T *rty_SO_e_MotorPwm, boolean_T
  *rty_SO_b_Error, boolean_T *rty_SO_b_DoorUnlockCmd, boolean_T
  *rty_SO_b_DoorLockCmd, boolean_T *rty_SO_b_ClkUnlockCmd, boolean_T
  *rty_SO_b_ClkLockCmd)
{
  *rty_SO_e_MotorCmd = 0U;
  *rty_SO_e_MotStateMachine = 0U;
  *rty_SO_e_MotorPwm = 0U;
  *rty_SO_b_Error = false;
  *rty_SO_b_DoorUnlockCmd = false;
  *rty_SO_b_DoorLockCmd = false;
  *rty_SO_b_ClkUnlockCmd = false;
  *rty_SO_b_ClkLockCmd = false;
}

/*
 * Output and update for atomic system:
 *    '<S3>/FLADLKDriver'
 *    '<S3>/RLADLKDriver'
 */
void ADLK_FLADLKDriver(uint8_T rtu_SI_e_Volt100mV, Boolean rtu_SO_b_DoorRlsReq,
  Boolean rtu_SI_b_DoorAjar, Boolean rtu_SI_b_DoorOpen, uint8_T
  rtu_SI_e_DoorRlsDelayTime, Boolean rtu_SI_b_DoorUnlockFlg, Boolean
  rtu_SI_b_DoorLockFlg, boolean_T rtu_SI_b_ClkUnlockFlg, boolean_T
  rtu_SI_b_ClkLockFlg, uint8_T *rty_SO_e_MotorCmd, uint8_T
  *rty_SO_e_MotStateMachine, uint8_T *rty_SO_e_MotorPwm, boolean_T
  *rty_SO_b_Error, boolean_T *rty_SO_b_DoorUnlockCmd, boolean_T
  *rty_SO_b_DoorLockCmd, boolean_T *rty_SO_b_ClkUnlockCmd, boolean_T
  *rty_SO_b_ClkLockCmd, DW_FLADLKDriver_ADLK_T *localDW)
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

  localDW->SI_b_DoorUnlockFlg_prev = localDW->SI_b_DoorUnlockFlg_start;
  localDW->SI_b_DoorUnlockFlg_start = rtu_SI_b_DoorUnlockFlg;
  localDW->SI_b_DoorLockFlg_prev = localDW->SI_b_DoorLockFlg_start;
  localDW->SI_b_DoorLockFlg_start = rtu_SI_b_DoorLockFlg;
  localDW->SO_b_DoorRlsReq_prev = localDW->SO_b_DoorRlsReq_start;
  localDW->SO_b_DoorRlsReq_start = rtu_SO_b_DoorRlsReq;
  localDW->SI_b_ClkUnlockFlg_prev = localDW->SI_b_ClkUnlockFlg_start;
  localDW->SI_b_ClkUnlockFlg_start = rtu_SI_b_ClkUnlockFlg;
  localDW->SI_b_ClkLockFlg_prev = localDW->SI_b_ClkLockFlg_start;
  localDW->SI_b_ClkLockFlg_start = rtu_SI_b_ClkLockFlg;

  /* Chart: '<S3>/FLADLKDriver' */
  if (localDW->is_active_c19_ADLKDriver == 0U) {
    localDW->SI_b_DoorUnlockFlg_prev = rtu_SI_b_DoorUnlockFlg;
    localDW->SI_b_DoorLockFlg_prev = rtu_SI_b_DoorLockFlg;
    localDW->SO_b_DoorRlsReq_prev = rtu_SO_b_DoorRlsReq;
    localDW->SI_b_ClkUnlockFlg_prev = rtu_SI_b_ClkUnlockFlg;
    localDW->SI_b_ClkLockFlg_prev = rtu_SI_b_ClkLockFlg;
    localDW->is_active_c19_ADLKDriver = 1U;
    localDW->is_DLK = ADLK_IN_Idle;
    localDW->is_CLK = ADLK_IN_Idle;
    localDW->is_Rls = ADLK_IN_Wait;

    /*  等待电机资源空闲  */
  } else {
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
        localDW->temporalCounter_i1 = 0U;
        *rty_SO_b_DoorLockCmd = true;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     case ADLK_IN_LockAct:
      if (localDW->temporalCounter_i1 >= 20) {
        *rty_SO_b_DoorLockCmd = false;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_DLK = ADLK_IN_Idle;
      }
      break;

     case ADLK_IN_Unlock:
      if (!localDW->SL_b_MotorMutexFlg) {
        localDW->is_DLK = ADLK_IN_UnlockAct;
        localDW->temporalCounter_i1 = 0U;
        *rty_SO_b_DoorUnlockCmd = true;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     default:
      /* case IN_UnlockAct: */
      if (localDW->temporalCounter_i1 >= 20) {
        *rty_SO_b_DoorUnlockCmd = false;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_DLK = ADLK_IN_Idle;
      }
      break;
    }

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
        localDW->temporalCounter_i3 = 0U;
        *rty_SO_b_ClkLockCmd = true;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     case ADLK_IN_LockAct:
      if (localDW->temporalCounter_i3 >= 20) {
        *rty_SO_b_ClkLockCmd = false;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_CLK = ADLK_IN_Idle;
      }
      break;

     case ADLK_IN_Unlock:
      if (!localDW->SL_b_MotorMutexFlg) {
        localDW->is_CLK = ADLK_IN_UnlockAct;
        localDW->temporalCounter_i3 = 0U;
        *rty_SO_b_ClkUnlockCmd = true;
        localDW->SL_b_MotorMutexFlg = true;
      }
      break;

     default:
      /* case IN_UnlockAct: */
      if (localDW->temporalCounter_i3 >= 20) {
        *rty_SO_b_ClkUnlockCmd = false;
        localDW->SL_b_MotorMutexFlg = false;
        localDW->is_CLK = ADLK_IN_Idle;
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
  uint8_T SO_e_MotorPwm_d;
  boolean_T SO_b_ClkLockCmd_f;
  boolean_T SO_b_ClkUnlockCmd_h;
  boolean_T SO_b_Error_j;

  /* RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' incorporates:
   *  SubSystem: '<Root>/ADLK_Step_sys'
   */
  /* Chart: '<S3>/FLADLKDriver' incorporates:
   *  Constant: '<S3>/Constant1'
   *  Inport: '<Root>/VbINP_HWA_FRDoorAjar_flg_VbINP_HWA_FRDoorAjar_flg'
   *  Inport: '<Root>/VbOUT_DLK_FRLock_flg_VbOUT_DLK_FRLock_flg'
   *  Inport: '<Root>/VbOUT_DLK_FRUnlock_flg_VbOUT_DLK_FRUnlock_flg'
   *  Inport: '<Root>/VbOUT_HWA_FRDoorFullOpen_flg_VbOUT_HWA_FRDoorFullOpen_flg'
   *  Inport: '<Root>/VbOUT_REL_FRDoorRlsReq_flg_VbOUT_REL_FRDoorRlsReq_flg'
   *  Outport: '<Root>/VbOUT_ADLK_FRLock_flg_VbOUT_ADLK_FRLock_flg'
   *  Outport: '<Root>/VbOUT_ADLK_FRUnlock_flg_VbOUT_ADLK_FRUnlock_flg'
   *  Outport: '<Root>/VeOUT_ADLK_FRReleaseLatchStatus_sig_VeOUT_ADLK_FRReleaseLatchStatus_sig'
   */
  ADLK_FLADLKDriver(0U, ADLK_U.VbOUT_REL_FRDoorRlsReq_flg_VbOU,
                    ADLK_U.VbINP_HWA_FRDoorAjar_flg_VbINP_,
                    ADLK_U.VbOUT_HWA_FRDoorFullOpen_flg_Vb, 20,
                    ADLK_U.VbOUT_DLK_FRUnlock_flg_VbOUT_DL,
                    ADLK_U.VbOUT_DLK_FRLock_flg_VbOUT_DLK_, false, false,
                    &ADLK_B.SO_e_MotorCmd_c,
                    &ADLK_Y.VeOUT_ADLK_FRReleaseLatchStatus, &SO_e_MotorPwm_d,
                    &SO_b_Error_j, &ADLK_Y.VbOUT_ADLK_FRUnlock_flg_VbOUT_A,
                    &ADLK_Y.VbOUT_ADLK_FRLock_flg_VbOUT_ADL,
                    &SO_b_ClkUnlockCmd_h, &SO_b_ClkLockCmd_f,
                    &ADLK_DW.sf_FLADLKDriver);

  /* Outport: '<Root>/VbOUT_ADLK_FRDoorMotorA_flg_VbOUT_ADLK_FRDoorMotorA_flg' incorporates:
   *  Constant: '<S4>/Constant'
   *  RelationalOperator: '<S4>/Compare'
   */
  ADLK_Y.VbOUT_ADLK_FRDoorMotorA_flg_VbO = (ADLK_B.SO_e_MotorCmd_c == 1);

  /* Outport: '<Root>/VbOUT_ADLK_FRDoorMotorB_flg_VbOUT_ADLK_FRDoorMotorB_flg' incorporates:
   *  Constant: '<S5>/Constant'
   *  RelationalOperator: '<S5>/Compare'
   */
  ADLK_Y.VbOUT_ADLK_FRDoorMotorB_flg_VbO = (ADLK_B.SO_e_MotorCmd_c == 2);

  /* Chart: '<S3>/RLADLKDriver' incorporates:
   *  Constant: '<S3>/Constant1'
   *  Inport: '<Root>/VbINP_HWA_RRDoorAjar_flg_VbINP_HWA_RRDoorAjar_flg'
   *  Inport: '<Root>/VbOUT_DLK_RRLock_flg_VbOUT_DLK_RRLock_flg'
   *  Inport: '<Root>/VbOUT_DLK_RRUnlock_flg_VbOUT_DLK_RRUnlock_flg'
   *  Inport: '<Root>/VbOUT_HWA_RRDoorFullOpen_flg_VbOUT_HWA_RRDoorFullOpen_flg'
   *  Inport: '<Root>/VbOUT_REL_RRDoorRlsReq_flg_VbOUT_REL_RRDoorRlsReq_flg'
   *  Outport: '<Root>/VbOUT_ADLK_RRLock_flg_VbOUT_ADLK_RRLock_flg'
   *  Outport: '<Root>/VbOUT_ADLK_RRUnlock_flg_VbOUT_ADLK_RRUnlock_flg'
   *  Outport: '<Root>/VeOUT_ADLK_RRReleaseLatchStatus_sig_VeOUT_ADLK_RRReleaseLatchStatus_sig'
   */
  ADLK_FLADLKDriver(0U, ADLK_U.VbOUT_REL_RRDoorRlsReq_flg_VbOU,
                    ADLK_U.VbINP_HWA_RRDoorAjar_flg_VbINP_,
                    ADLK_U.VbOUT_HWA_RRDoorFullOpen_flg_Vb, 20,
                    ADLK_U.VbOUT_DLK_RRUnlock_flg_VbOUT_DL,
                    ADLK_U.VbOUT_DLK_RRLock_flg_VbOUT_DLK_, false, false,
                    &ADLK_B.SO_e_MotorCmd,
                    &ADLK_Y.VeOUT_ADLK_RRReleaseLatchStatus, &SO_e_MotorPwm_d,
                    &SO_b_Error_j, &ADLK_Y.VbOUT_ADLK_RRUnlock_flg_VbOUT_A,
                    &ADLK_Y.VbOUT_ADLK_RRLock_flg_VbOUT_ADL,
                    &SO_b_ClkUnlockCmd_h, &SO_b_ClkLockCmd_f,
                    &ADLK_DW.sf_RLADLKDriver);

  /* Outport: '<Root>/VbOUT_ADLK_RRDoorMotorA_flg_VbOUT_ADLK_RRDoorMotorA_flg' incorporates:
   *  Constant: '<S6>/Constant'
   *  RelationalOperator: '<S6>/Compare'
   */
  ADLK_Y.VbOUT_ADLK_RRDoorMotorA_flg_VbO = (ADLK_B.SO_e_MotorCmd == 1);

  /* Outport: '<Root>/VbOUT_ADLK_RRDoorMotorB_flg_VbOUT_ADLK_RRDoorMotorB_flg' incorporates:
   *  Constant: '<S7>/Constant'
   *  RelationalOperator: '<S7>/Compare'
   */
  ADLK_Y.VbOUT_ADLK_RRDoorMotorB_flg_VbO = (ADLK_B.SO_e_MotorCmd == 2);

  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' */
}

/* Model initialize function */
void ADLK_initialize(void)
{
  {
    uint8_T SO_e_MotorPwm_d;
    boolean_T SO_b_ClkLockCmd_f;
    boolean_T SO_b_ClkUnlockCmd_h;
    boolean_T SO_b_Error_j;

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' incorporates:
     *  SubSystem: '<Root>/ADLK_Step_sys'
     */

    /* SystemInitialize for Chart: '<S3>/FLADLKDriver' incorporates:
     *  Outport: '<Root>/VbOUT_ADLK_FRLock_flg_VbOUT_ADLK_FRLock_flg'
     *  Outport: '<Root>/VbOUT_ADLK_FRUnlock_flg_VbOUT_ADLK_FRUnlock_flg'
     *  Outport: '<Root>/VeOUT_ADLK_FRReleaseLatchStatus_sig_VeOUT_ADLK_FRReleaseLatchStatus_sig'
     */
    ADLK_FLADLKDriver_Init(&ADLK_B.SO_e_MotorCmd_c,
      &ADLK_Y.VeOUT_ADLK_FRReleaseLatchStatus, &SO_e_MotorPwm_d, &SO_b_Error_j,
      &ADLK_Y.VbOUT_ADLK_FRUnlock_flg_VbOUT_A,
      &ADLK_Y.VbOUT_ADLK_FRLock_flg_VbOUT_ADL, &SO_b_ClkUnlockCmd_h,
      &SO_b_ClkLockCmd_f);

    /* SystemInitialize for Chart: '<S3>/RLADLKDriver' incorporates:
     *  Outport: '<Root>/VbOUT_ADLK_RRLock_flg_VbOUT_ADLK_RRLock_flg'
     *  Outport: '<Root>/VbOUT_ADLK_RRUnlock_flg_VbOUT_ADLK_RRUnlock_flg'
     *  Outport: '<Root>/VeOUT_ADLK_RRReleaseLatchStatus_sig_VeOUT_ADLK_RRReleaseLatchStatus_sig'
     */
    ADLK_FLADLKDriver_Init(&ADLK_B.SO_e_MotorCmd,
      &ADLK_Y.VeOUT_ADLK_RRReleaseLatchStatus, &SO_e_MotorPwm_d, &SO_b_Error_j,
      &ADLK_Y.VbOUT_ADLK_RRUnlock_flg_VbOUT_A,
      &ADLK_Y.VbOUT_ADLK_RRLock_flg_VbOUT_ADL, &SO_b_ClkUnlockCmd_h,
      &SO_b_ClkLockCmd_f);

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ADLK_Step' */
  }
}

/* Model terminate function */
void ADLK_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
