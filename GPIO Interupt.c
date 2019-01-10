/*Test Project for MCU*/
/*Author: phatv90@gmail.com*/

#include "io430f5529.h"
volatile int flag = 0;

void main()
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    
    P2REN |= BIT1;                 // Enable internal pull-up/down resistors
    P2OUT = BIT1;                 //Select pull-up mode for P1.3 
    P2DIR &= (~BIT1);             // Set P2.1 SEL as Input
    P2IE |= BIT1;                    // P1.3 interrupt enabled
    P2IES |= BIT1;                  // P1.3 Hi/lo edge
    P2IFG &= ~BIT1;               // P1.3 IFG cleared
    
    P1DIR |= BIT0;
    P1OUT ^= BIT0;
    
    __enable_interrupt(); // Enable Global Interrupts
    
    while(1)
    {
        if(flag == 1)
        {
            // Toggle leb
            P1OUT ^= BIT0;
            flag = 0;
        }
    }

}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
  if ((P2IN & BIT1) == 0)
  {
    // using the software delay for avoiding the vibration button
    __delay_cycles(10000);
      if ((P2IN & BIT1) == 0)
        flag = 1;
  }
   
    P2IFG &= (~BIT1); // P2.1 IFG clear
}
