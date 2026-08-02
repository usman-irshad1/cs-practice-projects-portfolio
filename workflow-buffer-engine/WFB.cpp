
// WFB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<P18F458.h>
void delay(unsigned char s)
    void main(void)
{
        TRISB = 0;
        PORTB = 0;
        while(1) {
            PORTB = ~PORTB;
            delay(250);
        }
        while (1);
}


    void delay(unsigned char s) {
        unsigned char g, h;

        for (g = 0; g < s; g++) {
            for (h = 0; h < 165; h++) {
            }
        }
    
    }

