/*
 * Code in assembly to turn on the Blue LED (User_LD2) located on PB7. This code configures the 
 * MODER (to output), TYPER (to push-pull), SPEED (to low) and the PUPD (to disabled - no pull-up, pull-down).
 * It finally turns the GPIO PB7 on.
 */

int main (void) {
	__asm__ volatile (
		".EQU RCC_AHB2ENR_ADDR, 0x4002104C\n\t"  	// Create a variable which holds the address of the RCC_AHB2 register
		"MOVW R0, #:lower16:RCC_AHB2ENR_ADDR\n\t"	// Move the lower part of RCC into r0
		"MOVT R0, #:upper16:RCC_AHB2ENR_ADDR\n\t"	// Move the upper part of RCC into r0
		"LDR R1, [R0]\n\t" 							// Load to r1 the value address at the memory address contained in r0
		"ORR R1, R1, #0x02\n\t" 					// We only want the 2nd bit to be true (only using GPIO group B)
		"STR R1, [R0]\n\t" 							// We then write to memory this new value in r1 (which turns on RCC)

		"LDR R0, =0x48000400\n\t"  					// Save the memory address for group B
		"LDR R2, =0x3\n\t"         					// This is the mask we want to add to CLEAR the bits
		"LSL R2, R2, #14\n\t"      					// Shift it 14 bits left (PB7 position)
		"MVN R2, R2\n\t" 		   					// Negate the bits make an and mask - save to R1
		"LDR R1, [R0]\n\t" 		   					// Load the value at [R0]
		"AND R1, R1, R2\n\t"       					// Clear bits 14 and 15
		"LDR R2, =0x1\n\t"							// Load 0x1 into R2
		"LSL R2, R2, #14\n\t"						// Shift 0x1 14 bits to the left
		"ORR R1, R1, R2\n\t"						// We then OR the masked value of R2 with R1
		"STR R1, [R0]\n\t"							// Finally write to the GPIOA_MODER register

		// Set the output to push-pull type
		"LDR R0, =0x48000404\n\t" 					// Load the GPIOB_TYPER
		"MOV R2, #0x3\n\t"							// We want to set the two bits of PB7 to 0 (push-pull)
		"LSL R2, R2, #14\n\t"						// Shift them 14 bits left (PB7)
		"MVN R2, R2\n\t"							// Negate all of the bits (we want to clear bits [15:14]
		"LDR R1,[R0]\n\t"   						// Load the current value at memory address stored in R0
		"AND R1, R1, R2\n\t"						// And the values to clear bits [15:14]
		"STR R1, [R0]\n\t"							// Write to GPIOB_TYPER memory address

		// Since we are only turning the GPIO on, I will leave the speed at low (bits 00)
		"LDR R0, =0x48000408\n\t" 					// Load the GPIOB_SPEEDR
		"MOV R2, #0x3\n\t"							// We want to set the two bits of PB7 to 0 (low-speed)
		"LSL R2, R2, #14\n\t"						// Shift them 14 bits left (PB7)
		"MVN R2, R2\n\t"							// Negate all of the bits (we want to clear bits [15:14]
		"LDR R1,[R0]\n\t"   						// Load the current value at memory address stored in R0
		"AND R1, R1, R2\n\t"						// And the values to clear bits [15:14]
		"STR R1, [R0]\n\t"							// Write to GPIOB_SPEEDR memory address

		// Since we have the GPIO set to push-pull mode, we can disable the pull-up and pull-down resistors
		"LDR R0, =0x4800040C\n\t" 					// Load the GPIOB_PUPDR
		"MOV R2, #0x3\n\t"							// We want to set the two bits of PB7 to 0 (no pull-up, pull-down)
		"LSL R2, R2, #14\n\t"
		"MVN R2, R2\n\t"
		"LDR R1,[R0]\n\t"
		"AND R1, R1, R2\n\t"
		"STR R1, [R0]\n\t"							// Write to GPION_PUPDR memory address

		//Finally turn on the GPIO
		"LDR R0, =0x48000414\n\t"					// Load the GPIOB_ODR
		"MOV R2, #1\n\t"							// We want to change the bit for the output of PB7
		"LSL R2, R2, #7\n\t"						// Bit shift R1 7 places to the left (PB7 = bit 7)
		"LDR R1, [R0]\n\t"
		"ORR R1, R1, R2\n\t"						// We use or to turn only PB7 on
		"STR R1, [R0]\n\t"							// Write the GPIOB_ODR
	);


	while (1);
}


