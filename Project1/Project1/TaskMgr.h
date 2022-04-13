/*
 * TaskMgr.h
 *
 * Created: 28.3.2022 11.26.14
 *  Author: Luigi Catello
 */ 


#ifndef TASKMGR_H_
#define TASKMGR_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define TASK_MAX 6
#define NULLPTR 0
#define OVF_MAX 62	// 62 gives ~1ms tick

struct TList {
	void (*task_function)(void);	// pointer to the function of the task
	int16_t delay;					// delay until the task is to run next time
	uint16_t interval;				// interval between runs
	int8_t run;						// if the task is ready to run
};

struct TList Task_list[TASK_MAX];

uint16_t overflows;
uint8_t addTaskIndex;

void TM_init(void);
void TM_add_task(void (*function)(void), int16_t delay, int16_t interval);
void TM_dispatcher(void);


#endif /* TASKMGR_H_ */