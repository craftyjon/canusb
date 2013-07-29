#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <asf.h>

#ifdef GLOBALS_ALLOC
#define EXTERN
#else
#define EXTERN extern
#endif

typedef enum {
	STATE_IDLE,
	STATE_RECEIVING
} command_state_type;

EXTERN command_state_type _command_state;

EXTERN unsigned char _current_command;
EXTERN unsigned char _desired_data_bytes;
EXTERN unsigned char _data_in[32];
EXTERN unsigned char _data_in_ptr;

#endif