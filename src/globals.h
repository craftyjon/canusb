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

EXTERN uint8_t _current_command;
EXTERN uint8_t _desired_data_bytes;
EXTERN uint8_t _data_in[32];
EXTERN uint8_t _data_in_ptr;

// CAN state
EXTERN uint8_t _can_initialized;
EXTERN uint8_t _can_open;
EXTERN uint32_t _can_bitrate;


#endif