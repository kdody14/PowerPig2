#include <atmel_start.h>

#define DELAY_VAL (50)

// LED EMIT
#define LED_EMIT (PORT_PB02)
#define LED_EMIT_GROUP (1)
#define LED_EMIT_PIN (PIN_PB02%32)

static volatile uint32_t millis = 0;

// PB02 is the port for the LED emitter

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	SysTick_Config(48000);
	pwm_enable(&PWM_0);
	
		// Set up IO pin for LED_EMIT
		PORT->Group[LED_EMIT_GROUP].DIRSET.reg = LED_EMIT;

		// Initialize values
		PORT->Group[LED_EMIT_GROUP].OUTCLR.reg = LED_EMIT;

	uint8_t buffer[2];
	adc_sync_enable_channel(&ADC_0, 0);

	/* Replace with your application code */
	while (1) 
	{
		if (millis >= DELAY_VAL)
		{
			NVIC_DisableIRQ(SysTick_IRQn);
			millis = 0; // reset millis
			NVIC_EnableIRQ(SysTick_IRQn);
			adc_sync_read_channel(&ADC_0, 0, buffer, 2);
			pwm_set_parameters(&PWM_0, 215, buffer[0]);
		}
	}
}

void SysTick_Handler()
{
	millis++;
}




