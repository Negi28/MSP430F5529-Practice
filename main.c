#include <msp430.h> 

#define SYS_PWRONZ      BIT4
#define MSP_PWREN_INTF  BIT6
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    P2DIR   = SYS_PWRONZ;
    P2OUT   = SYS_PWRONZ;

    // enable MSP power INTF
    P3DIR   |= MSP_PWREN_INTF;
    P3OUT   |= MSP_PWREN_INTF;

    // 1MHz main clock
    // Read valid calibration data and store in appropriate registers
    if ( (CALDCO_1MHZ != 0xFF) && (CALBC1_1MHZ != 0xFF) )
    {
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = CALDCO_1MHZ;
    }
    else
    { // calibration data is invalid
        BCSCTL1 = 0x87;
        DCOCTL = 0x6F;
    }


    unsigned int i = 0;
    unsigned int j = 0;

    while (1)
    {
        P2OUT ^= SYS_PWRONZ;
            // delay for a while
      // __delay_cycles(100000);
        for (j=0; j<100; j++);
            for (i=0; i<10000; i++);

    }

	return 0;
}
