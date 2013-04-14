/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#include "pins.h"

void board_init(void)
{
	ioport_enable_pin(LED1);
	ioport_enable_pin(LED2);
	ioport_set_pin_dir(LED1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LED2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED1, 1);
	ioport_set_pin_level(LED2, 1);
}
