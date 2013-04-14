
#include <asf.h>

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

	while(1) {
		
	}

}
