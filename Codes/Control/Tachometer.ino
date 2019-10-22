#include<avr/io.h>
#include<avr/interrupt.h>

int pulse_per_rev=180;
int count=0;
float kp=0,ki=0,kd=0;
int enca=0,encb=0;
float dt=50;                             //sampling time in millis
int spee=255;
float rpm=0,error=0,prev_error=0,u_t=0,error_sum=0,error_diff=0;    
int rpm_sp=80;                                          

void timer_init()
{   
    TCCR0A |= (1 << WGM00)|(1 << COM0A1)|(1 << COM0B1);                                   
    TCCR0B |= (1 << CS02)|(1 << CS00);                                                    
    TIMSK0 |= (1 << OCIE0A)|(1 << OCIE0B);
    DDRD |=(1<<5)|(1<<6);
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
  error= rpm_sp-rpm;
  error_sum+=error*(dt*10^-3);
  error_diff=(error-prev_error)/(dt*10^-3);
  u_t=(kp*error)+(ki*error_sum)+(kd*error_diff);
  if(u_t>255)
  u_t=255;
  else if(u_t<0)
  u_t=0;
  OCR0A = u_t;
  prev_error=error;
}
1
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
