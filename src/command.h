#ifndef _COMMAND_H
#define _COMMAND_H

void process_byte(unsigned char inbyte);
unsigned char is_valid_command(unsigned char cmd);
unsigned char get_desired_data_bytes(unsigned char cmd);
void dispatch_command(void);

#define CR 0x0B
#define ERROR 0x07

#define CMD_SET_BITRATE			0x53	// 'S'
#define CMD_SET_CUSTOM_BITRATE	0x73	// 's'
#define CMD_OPEN				0x4F	// 'O'
#define CMD_OPEN_LISTEN			0x4C	// 'L'
#define CMD_CLOSE				0x43	// 'C'
#define CMD_TRANSMIT_11BIT		0x74	// 't'
#define CMD_TRANSMIT_29BIT		0x54	// 'T'
#define CMD_TRANSMIT_RTR_11BIT	0x72	// 'r'
#define CMD_TRANSMIT_RTR_29BIT	0x52	// 'R'
#define CMD_GET_STATUS			0x46	// 'F'

#endif
