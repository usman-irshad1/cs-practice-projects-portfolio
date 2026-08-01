#include <P18f458.h>
void main(void){
TRISbbits.TRISB3=0;
PORTBbits.RB3=0;
T0CON=0x8;
while(1){
TMR0H=0xCF; 
TMR0L=0x2C;
INTCONbits.TMR0IF=0;
T0CONbits.TMR0ON=1;
while (INTCONbits.TMR0IF!=1);
PORTBbits.RB3=~PORTBbits.RB3;
T0CONbits.TMR0ON=0;
}
}