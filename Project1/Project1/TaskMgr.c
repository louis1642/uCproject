/*
 * TaskMgr.c
 *
 * Created: 28.3.2022 11.31.49
 *  Author: Luigi Catello
 */ 

#include "TaskMgr.h"


/* INTERNAL FUNCTIONS */
#pragma region INTERNAL_FUNC

// initialize timer0 to define the ticks
void TM_init_update(void) {
	// timer 0
	// normal mode, no prescaler
	TCCR0B |= (1<<CS00);
	// timer overflow interrupt enable
	TIMSK0 |= (1<<TOIE0);
	// enable interrupts
	sei();
}


// initialize the tasks
void TM_init_tasks(void){
	int i;
	for(i=0;i<TASK_MAX;i++) {
		// empty slots
		Task_list[i].task_function = NULLPTR;
	}
}


// on each tick, advance on the timetable
void TM_update(void) {
	int i;
	// check every task
	for(i=0;i<TASK_MAX;i++) {
		// if not an empty slot
		if(Task_list[i].task_function != NULLPTR) {
			// if it is time to run
			if(Task_list[i].delay == 0) {
				// increment the run counter
				Task_list[i].run += 1;
				// if the task is periodic
				if(Task_list[i].interval != 0) {
					Task_list[i].delay = Task_list[i].interval;
				}
			} else {
				// waiting time is decremented by one tick
				Task_list[i].delay -=1;
			}
		}
	}
}

// timer overflow interrupt handler
ISR (TIMER0_OVF_vect) {
	// the OVF_MAX is used to define the timing for the ticks
	if(overflows++ >= OVF_MAX) {
		// this is a tick
		TM_update();
		overflows = 0;
	}
}

/* END INTERNAL FUNCTIONS */
#pragma endregion INTERNAL_FUNC


// initialize task manager
void TM_init(void) {
	overflows = 0;
	addTaskIndex = 0;
	TM_init_tasks();
	TM_init_update();
}


// add a new task to the queue
void TM_add_task(void (*function)(void), int16_t delay, int16_t interval) {
	if (addTaskIndex >= TASK_MAX) {
		return;
	}
	Task_list[addTaskIndex].task_function = function;
	Task_list[addTaskIndex].delay = delay;
	Task_list[addTaskIndex].interval = interval;
	++addTaskIndex;
}


// execute the pending task
void TM_dispatcher(void) {
	int i;
	// check every task
	for(i=0;i<TASK_MAX;i++) {
		// if the slot is not empty
		if(Task_list[i].task_function != NULLPTR) {
			// if it is the right time to run
			if(Task_list[i].run > 0) {
				// execute the function
				Task_list[i].task_function();
				// decrease run request
				Task_list[i].run -= 1;
			}
		}
	}
}


