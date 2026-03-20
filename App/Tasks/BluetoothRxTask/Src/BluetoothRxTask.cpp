#include "BluetoothRxTask.hpp"
#include "IRx.hpp"
#include "BleRx.hpp"
#include "DataConfig.hpp"
#include "cmsis_os2.h"

#ifdef __cplusplus
extern "C"{
#endif
    #include "main.h"
#ifdef __cpluscplus
}
#endif

extern "C"
void BluetoothRxTaskHandler(void *argument){

    IRx *Rx = new BleRx();
    Rx->Init(nullptr);
    for(;;){
        Rx->GetFromRx(nullptr);
    }
}