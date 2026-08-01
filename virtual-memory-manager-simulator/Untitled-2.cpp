#include <P18f458.h>
void main(void){
TRISCbits.CCP1=0;
TRISCbits.T3CK1=1;

T3CON=0;
T1CON=6;

CCPR1L=0xE8;
CCPR1H=0x3;


CCP1CON=2;
while(1){
TMR1H=0; 
TMR1L=0;
T1CONbits.TMR1ON=1;
PIR1bits.CCP1IF=0;
while (PIR1bits.CCP1IF!=1);
TICONbits.TMR1ON=1;
}
}