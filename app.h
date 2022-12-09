#ifdef __cplusplus

extern "C" void __sync_synchronize() {}
extern "C" {
#endif

#include "ev3api.h"
#include "settings.h"

#define MAIN_PRIORITY    (TMIN_APP_TPRI + 1)
#define ORDER_PRIORITY  (TMIN_APP_TPRI + 2)
#define BLUETOOTH_PRIORITY  (TMIN_APP_TPRI + 3)

#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void order_task(intptr_t exinf);
extern void bluetooth_task(intptr_t exinf);
extern void order_cyc(intptr_t exinf);
extern void bluetooth_cyc(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif