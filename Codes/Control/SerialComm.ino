
boolean motor_start = true;
int factor =10;
const byte pin_a = 2;   //for encoder pulse A
const byte pin_b = 3;   //for encoder pulse B

const byte motordir[2] = {12,13}; 

const byte motorpwm[2] = {5,6}; //for H-bridge: motor speed

int encoder[2] = {0,0};
double pv_speed[2] = {0,0};
double set_speed[2] = {50,50};
double e_speed[2] = {0,0}; //error of speed = set_speed - pv_speed
double e_speed_pre[2] ={0,0};  //last error of speed
double e_speed_sum[2] ={0,0};  //sum error of speed
double pwm_pulse[2] = {0,0};     //this value is 0~255


// -------------------- CASCADED PID PARAMETERS----------------------------//


double delomega_setp = set_speed[0]-set_speed[1];
double delomega_pv = 0;
double e_speed_delomega = 0; //error of speed = set_speed - pv_speed
double e_speed_prev_delomega = 0;  //last error of speed
double e_speed_sum_delomega = 0;  //sum error of speed
double delomegacorrection = 0;     //this value is 0~255

double kpo=0.005,kio=0.05,kdo=0.0;



// ------------------------------------------------------------------------//  



double pv_speedb = 0;
double set_speedb = 60;
double e_speedb = 0; //error of speed = set_speed - pv_speed
double e_speed_preb = 0;  //last error of speed
double e_speed_sumb = 0;  //sum error of speed
double pwm_pulseb = 0;     //this value is 0~255


double kp[2] = {0.9,0.9};
double ki[2] = {0.5,0.5};
double kd[2] = {0.0,0.0};
int timer1_counter; //for timer
int i=0;

void serialEvent() 
{
  char inp;
  while (Serial.available()) 
  {
    inp = (char)Serial.read();
   // Serial.println(inp);
  }

  if( inp == 'w')
  {
    set_speed[0]+=factor;                             // EXPAND 
  }
  else if (inp == 's')
  {
    set_speed[0]-=factor;
  }
  else if (inp == 'e' )
  {
    set_speed[1]+=factor;
  }
  else if (inp == 'd')
  {
    set_speed[1]-=factor;
  }
  else if (inp == 'f')
  {
    Serial.println("Current RPM details");
    Serial.println(pv_speed[0]);
    Serial.println(pv_speed[1]);
    Serial.println("Current Setpoint Details");
    Serial.println(set_speed[0]);
    Serial.println(set_speed[1]);
    
  }

  if( inp == 'b')
  {
    motor_start= false;
    //set_speed[0]=set_speed[1]=0;
    analogWrite(motorpwm[0],0);
    analogWrite(motorpwm[1],0);
    Serial.println("MOTORS STOPPED");
  }
  else if ( inp == 'n')
  {
    motor_start = true;
    Serial.println("MOTORS STARTED");

  }


}

void setup()
 {

  //---------------         //TIMER FUNCTIONS DECLARATIONS 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz (34286 for 0.5sec) (59286 for 0.1sec)
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
  //---------------

  pinMode(pin_a,INPUT_PULLUP);
  pinMode(pin_b,INPUT_PULLUP);

  for(int i=0;i<2;i++)
  {
  pinMode(motordir[i],OUTPUT);
  pinMode(motorpwm[i],OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(pin_a), detect_0, RISING);
  attachInterrupt(digitalPinToInterrupt(pin_b), detect_1, RISING);

  Serial.begin(9600);


 }
 
 
 ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.1sec

 {
  //Serial.println("timer");
  TCNT1 = timer1_counter;   // set timer
  for(int i=0;i<2;i++)
  {
  pv_speed[i] = 60.0*(encoder[i]/3690.0)/0.5;
  //Serial.print("motor");//calculate motor speed, unit is rpm
  //Serial.print(i);
  //Serial.print(" ");
  //Serial.println(pv_speed[i]);
  encoder[i]=0;
 // Serial.print("speed :");
 
  }
  pid();
  
 }

 
 void detect_0()
 {
   encoder[0]++;
 }

void detect_1()
 {
   encoder[1]++;
 }

void loop()
{
  
}

void pid() 

{
  if(motor_start)
  //PID program
   // Serial.print("Relative Omega");
 {
   // Serial.println(pv_speed[0]-pv_speed[1]);
    for(int i=0;i<2;i++)
    {
    e_speed[i] = set_speed[i] - pv_speed[i];
    pwm_pulse[i] = e_speed[i]*kp[i] + e_speed_sum[i]*ki[i] + (e_speed[i] - e_speed_pre[i])*kd[i];
    e_speed_pre[i] = e_speed[i];  //save last (previous) error
    e_speed_sum[i] += e_speed[i];
    }

     // CASCADED PID STATISTICAL APPROACH
    e_speed_delomega=pv_speed[0]-pv_speed[1];
    delomegacorrection=(e_speed_delomega*kpo)+(e_speed_sum_delomega*kio)+((e_speed_delomega-e_speed_prev_delomega)*kdo);
    e_speed_prev_delomega=e_speed_delomega;
    e_speed_sum_delomega += e_speed_delomega;

    if(pv_speed[0]>pv_speed[1])
    {
        pwm_pulse[0]-=fabs(delomegacorrection/2);
        pwm_pulse[1]+=fabs(delomegacorrection/2);
    }
     else if((pv_speed[0]<pv_speed[1]))
     {
        pwm_pulse[0]+=fabs(delomegacorrection/2);
        pwm_pulse[1]-=fabs(delomegacorrection/2); 
     }



  for(int i=0;i<2;i++)
  {
    if (pwm_pulse[i] <255 & pwm_pulse[i] >0)
    { digitalWrite(motordir[i],HIGH);
      analogWrite(motorpwm[i],pwm_pulse[i]);  //set motor speed  
    }
    else
    {
      if (pwm_pulse[i]>255)
      {
        digitalWrite(motordir[i],HIGH);
        analogWrite(motorpwm[i],255);
      }
      else
      {
        digitalWrite(motordir[i],HIGH);
        analogWrite(motorpwm[i],0);
      }
    }

}
 
}
}
