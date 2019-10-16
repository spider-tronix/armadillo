int enca=0,encb=0;
float dt= 100; //sampling time 
int speed=125;
float rpm=0,rpm1=0;
unsigned long time1=0;
void setup()
{
    pinMode(6,OUTPUT); //PWM pin2
    pinMode(5,OUTPUT); //PWM pin1
    Serial.begin(9600);
    analogWrite(6,speed);
    analogWrite(5, 0);

    attachInterrupt(digitalPinToInterrupt(2), encodera, RISING);
    attachInterrupt(digitalPinToInterrupt(3), encoderb, RISING);


}
float calcspeed()
{
    rpm=(enca*60)/(5*dt);
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
    if(millis()-time1>=dt)
    {
        rpm=calcspeed();
        Serial.print("RPM : ");
        Serial.println(rpm);
    }
}
