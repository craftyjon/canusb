#include <string.h>

#include "globals.h"
#include "command.h"
#include "pins.h"


void process_byte(unsigned char inbyte)
{
	udi_cdc_putc('.');
	switch (_command_state)
	{
		case STATE_IDLE:
			if (is_valid_command(inbyte)) {
				_current_command = inbyte;
				_data_in_ptr = 0;
				_desired_data_bytes = get_desired_data_bytes(inbyte);
				_command_state = STATE_RECEIVING;
				ioport_set_pin_level(LED2, 1);
				udi_cdc_putc('A');
			} else {
				ioport_set_pin_level(LED1, 0);
				ioport_set_pin_level(LED2, 0);
				_current_command = 0;
				_desired_data_bytes = 0;
				_data_in_ptr = 0;
			}
			break;
			
		case STATE_RECEIVING:
			if (_data_in_ptr == _desired_data_bytes) {
				ioport_set_pin_level(LED1, 1);
				udi_cdc_putc('B');
				if (inbyte == CR) {
					udi_cdc_putc('C');
					dispatch_command();
					ioport_set_pin_level(LED1, 0);
					ioport_set_pin_level(LED2, 0);
				}
				_command_state = STATE_IDLE;
			} else {
				_data_in[_data_in_ptr++] = inbyte;
			}
			break;
		default:
			udi_cdc_putc('X');
			_command_state = STATE_IDLE;
			_current_command = 0;
			_desired_data_bytes = 0;
			_data_in_ptr = 0;
			memset(_data_in, 0, sizeof(_data_in));
	}
}


unsigned char is_valid_command(unsigned char cmd)
{
	switch (cmd)
	{
		case CMD_SET_BITRATE:
		case CMD_SET_CUSTOM_BITRATE:
		case CMD_OPEN:
		case CMD_OPEN_LISTEN:
		case CMD_CLOSE:
		case CMD_TRANSMIT_11BIT:
		case CMD_TRANSMIT_29BIT:
		case CMD_TRANSMIT_RTR_11BIT:
		case CMD_TRANSMIT_RTR_29BIT:
		case CMD_GET_STATUS:
			return 1;

		default:
			return 0;
	}
}


unsigned char get_desired_data_bytes(unsigned char cmd)
{
	switch (cmd)
	{
		case CMD_SET_BITRATE:
			return 1;
			
		case CMD_SET_CUSTOM_BITRATE:
			return 6;
			
		case CMD_OPEN:
			return 0;
			
		case CMD_OPEN_LISTEN:
			return 0;
			
		case CMD_CLOSE:
			return 0;
			
		case CMD_TRANSMIT_11BIT:
			return 12;
		
		case CMD_TRANSMIT_29BIT:
			return 17;
		
		case CMD_TRANSMIT_RTR_11BIT:
			return 4;
		
		case CMD_TRANSMIT_RTR_29BIT:
			return 9;
		
		case CMD_GET_STATUS:
			return 0;

		default:
			return 0;
	}
}


void dispatch_command()
{
	switch (_current_command)
	{
		case CMD_SET_BITRATE:
			udi_cdc_putc(CR);
			break;
		
		case CMD_SET_CUSTOM_BITRATE:
			udi_cdc_putc(CR);
			break;
		
		case CMD_OPEN:
			udi_cdc_putc(CR);
			break;
		
		case CMD_OPEN_LISTEN:
			udi_cdc_putc(CR);
			break;
		
		case CMD_CLOSE:
			udi_cdc_putc(CR);
			break;
		
		case CMD_TRANSMIT_11BIT:
			udi_cdc_putc(CR);
			break;
		
		case CMD_TRANSMIT_29BIT:
			udi_cdc_putc(CR);
			break;
		
		case CMD_TRANSMIT_RTR_11BIT:
			udi_cdc_putc(CR);
			break;
		
		case CMD_TRANSMIT_RTR_29BIT:
			udi_cdc_putc(CR);
			break;
		
		case CMD_GET_STATUS:
			udi_cdc_putc(CR);
			break;

		default:
			break;
	}
}