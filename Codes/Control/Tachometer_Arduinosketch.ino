volatile long enca=0,encb=0;
float dt= 1000.0; //sampling time 
int speed=125;
int rpm=0,rpm1=0;
float time1=0,timeprev=0;;
void setup()
{
    pinMode(6,OUTPUT); //PWM pin2
    pinMode(5,OUTPUT); //PWM pin1
    Serial.begin(9600);
    analogWrite(6,speed);
    analogWrite(5, 0);  
    pinMode(2, INPUT_PULLUP);  // Using internal pullup
    pinMode(3, INPUT_PULLUP);  // using internal pullup
    attachInterrupt(digitalPinToInterrupt(2), encodera, RISING);
    attachInterrupt(digitalPinToInterrupt(3), encoderb, RISING);
    timeprev=millis();
}
float calcspeed()
{
    rpm=(enca*60/203);
    enca=0;
    return rpm;
}

void encodera()
{
    enca++;
}

void encoderb()
{
    encb++;
}

void loop()
{
    time1=millis();
    if(time1-timeprev>=dt)
    {   
        timeprev=time1;
        rpm=calcspeed();
        Serial.print("RPM : ");
        Serial.println(rpm);
    }
    
}
