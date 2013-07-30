#include <string.h>

#include "globals.h"
#include "command.h"
#include "pins.h"


void process_byte(uint8_t inbyte)
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


uint8_t is_valid_command(uint8_t cmd)
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
	uint8_t err = 0;
	switch (_current_command)
	{
		case CMD_SET_BITRATE:
			if (_can_initialized) {
				err = 1;
			} else {
				switch (_data_in[0]) {
					case '0':
						_can_bitrate = 10000;
						break;
					case '1':
						_can_bitrate = 20000;
						break;
					case '2':
						_can_bitrate = 50000;
						break;
					case '3':
						_can_bitrate = 100000;
						break;
					case '4':
						_can_bitrate = 125000;
						break;
					case '5':
						_can_bitrate = 250000;
						break;
					case '6':
						_can_bitrate = 500000;
						break;
					case '7':
						_can_bitrate = 800000;
						break;
					case '8':
						_can_bitrate = 1000000;
						break;
					default:
						err = 1;
						break;
				}
				
				if (!err) {
					_can_initialized = 1;
				}
			}	
			
			break;
		
		case CMD_SET_CUSTOM_BITRATE:
			
			//btr0 = _data_in[0];
			//btr1 = _data_in[1];
			// Todo...
			break;
		
		case CMD_OPEN:
			if (!_can_initialized || _can_open) {
				err = 1;
			} else {
				_can_open = 1;
			}
			break;
		
		case CMD_OPEN_LISTEN:
			// Todo...
			break;
		
		case CMD_CLOSE:
			if (!_can_open) {
				err = 1;
			} else {
				_can_open = 0;
			}
			break;
		
		case CMD_TRANSMIT_11BIT:
			
			break;
		
		case CMD_TRANSMIT_29BIT:
			
			break;
		
		case CMD_TRANSMIT_RTR_11BIT:
			
			break;
		
		case CMD_TRANSMIT_RTR_29BIT:
			
			break;
		
		case CMD_GET_STATUS:
			break;

		default:
			break;
	}
	
	if (err) {
		udi_cdc_putc(ERROR);
	} else {
		udi_cdc_putc(CR);
	}
}