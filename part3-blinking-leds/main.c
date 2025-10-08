#include <stdint.h>

// Base addresses
uint32_t* RCC_AHB2ENR = (uint32_t*) 0x4002104C; //base address is 0x40021000 and offset 0x4C.

uint32_t* GPIOB = (uint32_t*) 0x48000400;
uint32_t* GPIOB_OTYPER = (uint32_t*) 0x48000404;
uint32_t* GPIOB_OSPEEDR = (uint32_t*) 0x48000408;
uint32_t* GPIOB_PUPDR = (uint32_t*) 0x4800040C;
uint32_t* GPIOB_ODR = (uint32_t*) 0x48000414;

uint32_t* GPIOC = (uint32_t*) 0x48000800;
uint32_t* GPIOC_OTYPER = (uint32_t*) 0x48000804;
uint32_t* GPIOC_OSPEEDR = (uint32_t*) 0x48000808;
uint32_t* GPIOC_PUPDR = (uint32_t*) 0x4800080C;
uint32_t* GPIOC_ODR = (uint32_t*) 0x48000814;


void software_delay(){
	uint32_t counter = 0x2FFFF;
	while(counter > 0){
		counter --;
	}
}

int main(void)
{
	// Turn the RCC on for GPIOs B and C
	*RCC_AHB2ENR |= 0x6; 		//we need to configure the Bit 3 and 2 to high, as we want to enable the clock for GPIOs C and B.

	*GPIOC = *GPIOC & ~(3<<14); //first clear the bits (15:14) for PC7
	*GPIOC = *GPIOC | (1<<14); 	//then we set the bits to value 01.

	*GPIOB = *GPIOB & ~(3<<14); //first clear the bits (15:14) for PB7
	*GPIOB = *GPIOB | (1<<14); 	//then we set the bits to value 01.

	*GPIOB = *GPIOB & ~(3<<28); //first clear the bits (15:14) for PB14
	*GPIOB = *GPIOB | (1<<28); 	//then we set the bits to value 01.

	// Set the type to push-pull - we must set the bits for the GPIOs to be 0
	*GPIOC_OTYPER &= ~(1<<7);   // set the bit in position [7] of GPIOC_OTYPER to be 0
	*GPIOB_OTYPER &= ~(1<<7);	// set the bit in position [7] of GPIOB_OTYPER to be 0
	*GPIOB_OTYPER &= ~(1<<14);	// set the bit in position [14] of GPIOB_OTYPER to be 0

	//Set the speed to low (turning the LEDs on does not seem to require a different configuration)
	*GPIOC_OSPEEDR &= ~(3<<14);
	*GPIOB_OSPEEDR &= ~(3<<14);

	//Since I have configured the type to be push/pull, there is no need for pull-up/down
	*GPIOC_PUPDR = *GPIOC_PUPDR & ~(3<<14); //set bits [15:14] to zero
	*GPIOB_PUPDR = *GPIOB_PUPDR & ~(3<<14); //set bits [15:14] to zero
	*GPIOB_PUPDR = *GPIOB_PUPDR & ~(3<<28); //set bits [29:28] to zero

	// In the sequence below I am assuming that we turn off one LED and turn on the following one without a delay.
	// If we wanted the feeling that each individual LED was blinking, we could use a delay (commented out delays)
	// in between turning off the led and turning on the following one.
	while (1){
		*GPIOC_ODR |= 1 << 7; //turn green led on
		software_delay();
		*GPIOC_ODR &= ~(1 << 7); //turn the green led off
//		software_delay();
		*GPIOB_ODR |= 1 << 7; //turn blue led on
		software_delay();
		*GPIOB_ODR &= ~(1 << 7); //turn the blue led off
//		software_delay();
		*GPIOB_ODR |= 1 << 14; //turn red led on
		software_delay();
		*GPIOB_ODR &= ~(1 << 14); //turn red led off
//		software_delay();
	}

}
