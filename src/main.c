#include <asf.h>
#include <string.h>

#define GLOBALS_ALLOC
#include "globals.h"
#undef GLOBALS_ALLOC

#include "pins.h"
#include "command.h"
#include "init.h"

int main (void)
{
	// ASF board initialization
	sysclk_init();
	pmic_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	
	udc_start();
	udc_attach();
	
	board_init();
	
	uint8_t usbbyte;
	
	init_comms();
	init_can();
	
	ioport_set_pin_level(LED1, 0);
	ioport_set_pin_level(LED2, 0);

	while(1) {
		if (udi_cdc_is_rx_ready()) {
			usbbyte = udi_cdc_getc();
			process_byte(usbbyte);
		}
	}
}
