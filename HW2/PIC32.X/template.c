
#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

void wait(float waitMs);

int main(void) {
  // Generate sine wave and store in array
  int numPoints = 100;
  double sinewave[numPoints];
  
  for (int i = 0; i < numPoints; i++) {
      sinewave[i] = (3.3/2) * sin(((double)i/numPoints) * 2 * M_PI) + (3.3/2);
  }
  
  char message[100]; // Huge to prevent overflow, although this is not 100% bullet proof
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
	if (!NU32DIP_USER){
		// Read out sine array
        for (int i = 0; i < numPoints; i++) {
            sprintf(message, "%f\n", sinewave[i]);
            NU32DIP_WriteUART1(message);
            
            wait(1000.0f/numPoints);
        }
	}
  }
}
	
void wait(float waitMs) {
    unsigned long t = _CP0_GET_COUNT(); 
    // the core timer ticks at half the SYSCLK, so 24000000 times per second
    // so each millisecond is 24000 ticks
    while(_CP0_GET_COUNT() < t + 24000*waitMs){}
}


/*
#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  unsigned int blinks=0, period=0;
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  NU32DIP_WriteUART1("Don't Push Me So Hard UwU");
  while (1) {
    NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
    sscanf(message, "%d %d", &blinks, &period);
    NU32DIP_WriteUART1(message); // send message back
    NU32DIP_WriteUART1("\r\n"); // carriage return and newline
	if (NU32DIP_USER){
		blink(blinks, period); // # of blinks; period between each blink in ms
        }
    }
  }

// blink the LEDs
void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}
*/		
