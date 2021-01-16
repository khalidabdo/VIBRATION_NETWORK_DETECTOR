#include "system.h"
/* Max delay is 200 ms */
/*

void Delay_ms(unsigned char Delay)
{
    unsigned long Iterations;
    unsigned long Counter;
    if(Delay <= 200)
    {
        Iterations = (_XTAL_FREQ/1000)/Delay;
        for(Counter = 0; Counter < Iterations; Counter++);
    }
    else
    {
        Iterations = (_XTAL_FREQ/1000)/200;
        for(Counter = 0; Counter < Iterations; Counter++);
    }
    
}
*/