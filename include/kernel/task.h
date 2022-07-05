#ifndef _MY_OS_TASK_H_
#define _MY_OS_TASK_H_


#ifdef __cplusplus
extern "C" {
#endif

int myOs_task_init(func_entry entry,void* param,int stack_size,uint8_t* stack_base);
int myOs_start(uhos_void);
void task_delay(int mesc);



#ifdef __cplusplus
}
#endif

#endif

