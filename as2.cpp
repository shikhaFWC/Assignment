#include <Arduino.h>
int A=31, B;
int outputY;

void setup()
{
    pinMode(2,OUTPUT);
    pinMode(13, HIGH);
    noInterrupts();
    TCCR1A=0;
    TCCR1B=0;
    TCNT1= 0;
    TCCR1B |=(1<<CS11);
    TIMSK1 |= (1<<TOIE1);
    interrupts();
}

ISR(TIMER1_OVF_vect)
{
    TCNT1= 0;
    B=(--A);
    if (B==0){
    digitalWrite(13, digitalRead(13)^1 );
    A=31;
        }
    }
void loop(){
    
    bool bit15 = TCNT1 & 0x8000;
    bool bit14 = TCNT1 & 0x4000;
    bool outputY = bit15 || bit14;

    digitalWrite(2,outputY);
        
    
}
