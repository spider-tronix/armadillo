#include<avr/io.h>
#include<avr/interrupt.h>

int pulse_per_rev=5000;
int count=0;
int enca=0,encb=0;
float dt=50; //sampling time in millis
int spee=255;
float rpm=0;                                              
void timer_init()
{   
    TCCR0A |= (1<<WGM00)|(1<<COM0A1)|(1<<WGM01)|(1<<CS00);
    // make sure to make OC0 pin (pin PB3 for atmega32) as output pin
    DDRB |= (1<<PB3);
    OCR0A = spee;
    TCCR1B |= (1 << WGM12)|(1 << CS12);  // TIMER1 256 scale and CTC mode          
    count= (dt * 1000)/16;
    OCR1A = count;                        
    TIMSK1 |= (1 << OCIE1A);                                                
}

ISR(TIMER1_COMPA_vect)
{
  rpm=(enca*600)/(5*dt);
  enca=0;                                                                                                                     
  encb=0;
}

ISR (INT0_vect)  
{ 
  enca++;
}
ISR (INT1_vect)  
{ 
  encb++;
}
int main()
{   timer_init();
    Serial.begin(9600);
    EICRA |= (1 << ISC11)|(1 << ISC10)|(1 << ISC01)|(1 << ISC00);                                 
    EIMSK |= (1 << INT0)|(1 << INT1);
    sei();
    while(1)
    {
        Serial.println(rpm);
    }

   return 0;
}
