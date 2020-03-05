
boolean motor_start = true;
const byte pin_a = 2;   //for encoder pulse A
const byte pin_b = 3;   //for encoder pulse B

const byte motordir1 = 12; 
const byte motordir2 = 13; 


const byte motorpwm1 = 5; //for H-bridge: motor speed
const byte motorpwm2 = 6; 

int encoder = 0;
int m_direction = 0;
int sv_speed = 100;     //this value is 0~255
double pv_speed = 0;
double set_speed = 0;
double e_speed = 0; //error of speed = set_speed - pv_speed
double e_speed_pre = 0;  //last error of speed
double e_speed_sum = 0;  //sum error of speed
double pwm_pulse = 0;     //this value is 0~255
double kp = 0;
double ki = 0;
double kd = 0;
int timer1_counter; //for timer
int i=0;

void serialEvent() {
  while (Serial.available()) 
  {
    char inp = (char)Serial.read();
    Serial.println(inp)
  }

}

void setup()
 {
  pinMode(pin_a,INPUT_PULLUP);
  pinMode(pin_b,INPUT_PULLUP);
  pinMode(motordir1,OUTPUT);
  pinMode(motordir2,OUTPUT);
  pinMode(motorpwm1,OUTPUT);
  pinMode(motorpwm2,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pin_a), detect_a, RISING);
  attachInterrupt(digitalPinToInterrupt(pin_b), detect_b, RISING);
  // start serial port at 9600 bps:
  Serial.begin(9600);
  //--------------------------timer setup
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 59286;   // preload timer 65536-16MHz/256/2Hz (34286 for 0.5sec) (59286 for 0.1sec)
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
  //--------------------------timer setup
 }

 void detect_a()
 {
   encoder++;
 }
̥
 void detect_b()
 {

 }

 ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.1sec
{
  Serial.println("MUKESHHHHH")
  TCNT1 = timer1_counter;   // set timer
  pv_speed = 600.0*(encoder/200.0)/0.1;  //calculate motor speed, unit is rpm
  encoder=0;
  //print out speed
  //if (Serial.available() <= 0) {
  //Serial.print("speed");
  // Serial.println(pv_speed);         //Print speed (rpm) value to Visual Studio
 }

void loop() 

{
  //PID program
  if (motor_start){
    e_speed = set_speed - pv_speed;
    pwm_pulse = e_speed*kp + e_speed_sum*ki + (e_speed - e_speed_pre)*kd;
    e_speed_pre = e_speed;  //save last (previous) error
    e_speed_sum += e_speed; //sum of error
    if (e_speed_sum >4000) e_speed_sum = 4000;
    if (e_speed_sum <-4000) e_speed_sum = -4000;
  }
  else{
    e_speed = 0;
    e_speed_pre = 0;
    e_speed_sum = 0;
    pwm_pulse = 0;
  }
  
  //update new speed
  if (pwm_pulse <255 & pwm_pulse >0){
    analogWrite(pin_pwm,pwm_pulse);  //set motor speed  
  }
  else{
    if (pwm_pulse>255){̥
      analogWrite(pin_pwm,255);
    }
    else{
      analogWrite(pin_pwm,0);
    }
  }
  
}

