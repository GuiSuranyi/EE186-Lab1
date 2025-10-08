# EE186-Lab1

## 2 Flashing & Debugging Code

### Part a.
Describe what happens during the flashing process. What files are generated when you build the project? What part of memory is written to on the MCU? What enables STM32CubeIDE to communicate with your board? What tool or protocol is used to transfer the compiled binary to the microcontroller? 
# FIX

### Part b.
Before running the code:
<img width="1265" height="196" alt="Pasted Graphic" src="https://github.com/user-attachments/assets/e1a8ad03-b2b7-4422-b7fc-757c8f3833de" />

After running the code:
<img width="1266" height="190" alt="Pasted Graphic 1" src="https://github.com/user-attachments/assets/60b550be-4de8-4999-9940-710afbea2bc7" />

## 3 Blinking LEDs

# FIX
### Part a 
There are three user LEDs available in the NUCLEO board we are using: User LD1 - which is connected to PC7-, User LD2 - which is connected to PB7 - and User LD3 - which is connected to PB14. These are all pins which should be configured as GPIOs for the LEDs, such that you can turn the LED on by setting the I/O to High, and turn the LED off by setting the I/O to Low. Since those have not been configured as GPIOs yet, we will need to go through the desired registers, and set the appropriate bits - such as turning the RCC Since these are GPIO pins, one could write and read to/from them. This is why there are solder bridges which can be connected or disconnected in order to give the user of the board the ability to select whether the LED is connected or not to the GPIO.

### Part B
<img width="1117" height="393" alt="image" src="https://github.com/user-attachments/assets/d0a1374c-e28d-4196-bc8d-fc80d0a25af6" />

### Part C
Please view "part3-blinking-leds" for the video of the LEDs and the code.

## 4 Blinking LED in Assembly
Please view "part4-blinking-led-in-assembly" for the code.

