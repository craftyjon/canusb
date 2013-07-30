#include <string.h>

#include "init.h"
#include "globals.h"


void init_comms()
{
	_command_state = STATE_IDLE;
	_current_command = 0;
	_desired_data_bytes = 0;
	_data_in_ptr = 0;
	memset(_data_in, 0, sizeof(_data_in));
}


void init_can()
{
	// Init variables
	_can_initialized = 0;  // Set to true when the host sends 'S' or 's' command
	_can_open = 0;
	_can_bitrate = 10000;
	
	
	// Setup the transceiver
}