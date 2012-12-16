/*==================================================================
  File name    : $Id: pid_reg.h,v 1.7 2004/05/13 20:51:00 emile Exp $
  Author       : E. vd Logt
  ------------------------------------------------------------------
  Purpose : This file contains the defines for the PID controller.
  ------------------------------------------------------------------
  $Log: pid_reg.h,v $
  Revision 1.7  2004/05/13 20:51:00  emile
  V0.1 060302 First version
  ==================================================================
*/
#ifndef PID_REG_H
#define PID_REG_H
#ifdef __cplusplus
extern "C" {
#endif
// These defines are needed for loop timing and PID controller timing
#define TWENTY_SECONDS (400)
#define TEN_SECONDS    (200)
#define FIVE_SECONDS   (100)
#define ONE_SECOND      (20)
#define T_50MSEC  (50)   // Period time of TTimer in msec.
#define GMA_HLIM (100.0) // PID controller upper limit [%]
#define GMA_LLIM   (0.0) // PID controller lower limit [%]
typedef struct _pid_params
{
   double kc; // Controller gain from Dialog Box
   double ti; // Time-constant for I action from Dialog Box
   double td; // Time-constant for D action from Dialog Box
   double ts; // Sample time [sec.] from Dialog Box
   double k_lpf; // Time constant [sec.] for LPF filter
   double k0; // k0 value for PID controller
   double k1; // k1 value for PID controller
   double k2; // k2 value for PID controller
   double k3; // k3 value for PID controller
   double lpf1; // value for LPF filter
   double lpf2; // value for LPF filter
   int    ts_ticks;  // ticks for timer
   int    pid_model; // PID Controller type [0..3]
   double pp; // debug
   double pi; // debug
   double pd; // debug
} pid_params; // struct pid_params
//--------------------
// Function Prototypes
//--------------------
void init_pid2(pid_params *p);
void pid_reg2(double xk, double *yk, double tset, pid_params *p, int vrg);
void init_pid3(pid_params *p);
void pid_reg3(double xk, double *yk, double tset, pid_params *p, int vrg);
void init_pid4(pid_params *p);
void pid_reg4(double xk, double *yk, double tset, pid_params *p, int vrg);
#ifdef __cplusplus
};
#endif
#endif
