#include "task.h"
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include "list.h"

typedef (*func_entry)(void* param);


typedef enum {
    TASK_STATE_RUNNING =  0x10000,
    TASK_STATE_STOP,
    TASK_STATE_MUTEXING,
    TASK_STATE_SLEEP
} task_state;
typedef struct {
    void *param;
    unsigned long stack;
    ListEntry * list_node;
    uint32_t task_state;
    uint64_t left_ticks;
}task_struct_t;

static ListEntry *task_list_head = NULL;


static void *idle(void *param)
{
    for(;;){

    }
    return NULL;
}

static int myOs_start(uhos_void)
{
#define IDLE_STACK_SIZE   (48)
    uint8_t *task_stack = malloc(IDLE_STACK_SIZE);
    return myOs_task_init(idle,NULL,48,task_stack);
}


int myOs_task_init(func_entry entry,void* param,int stack_size,uint8_t* stack_base)
{

    uint32_t* stack_top = (uint32_t*)&stack_base[stack_size];
    *stack_top = (uint32_t)entry;
    *(--stack_top) = (uint32_t)param;
    *(--stack_top) = (uint32_t)stack_size;
    //*(--stack_top) =
    task_struct_t *task = malloc(sizeof (task_struct_t));
    memset(task,0x00,sizeof (task_struct_t));
    task->task_state = TASK_STATE_STOP;
    task->stack = (unsigned long)stack_top;
    task->list_node = list_append(&task_list_head,task);
    return 0;
}

void task_delay(int mesc)
{

}
