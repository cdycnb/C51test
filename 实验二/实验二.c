#include <stdio.h>
#include <reg51.h>

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 1275; j++);
    }
}

void main() {
	  unsigned int i;
    P0 = 0x00;
    delay(1);
    P0 = 0x01;
    while (1)
    {
        if(P0 == 0x80){
            P0 = 0x01;
					delay(100);
        }
        else{
            P0 = P0<<1 | 0x00;
						delay(100);
				}
    }
}