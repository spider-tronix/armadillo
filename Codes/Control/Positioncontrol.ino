#include<avr/io.h>
#include<avr/interrupt.h>

int pulse_per_rev=203;
int count=0;
float kp=0,ki=0,kd=0;
int enca=0,encb=0;
int rpm=0,polarity=0;
long dt1=0,dtprev=0;
void interrupt_init()
{   
    EICRA |= (1 << ISC11)|(1 << ISC10)|(1 << ISC01)|(1 << ISC00);                                 
    EIMSK |= (1 << INT0)|(1 << INT1);
    TCCR0A |= (1 << WGM00)|(1 << COM0A1)|(1 << COM0B1);                                   
    TCCR0B |= (1 << CS02)|(1 << CS00);                                                    
    TIMSK0 |= (1 << OCIE0A)|(1 << OCIE0B);
    DDRD |=(1<<5)|(1<<6);           
    sei();                                   
}

ISR (INT0_vect)  
{ 
  enca++;
}
ISR (INT1_vect)  
{ 
  encb++;
}

float theta(int count)
{
  float rpm=(count/(pulse_per_rev*2*3.14));
  return rpm
}
int main()
{
    interrupt_init();
    Serial.begin(9600);
    while(1)
    { 
        dt=millis()-dtprev;
        error=theta(enca)-thetaref;
        errorsum=error+errorsum;
        errordiff=error-errorprev;
        ut=kp*error+ki*errorsum*dt+kd*errordiff/dt;
        if(ut>255)
        ut=255;
        if(ut<-255)
        ut=-255;
        errorprev=error;
        dtprev=dt;
    }

}