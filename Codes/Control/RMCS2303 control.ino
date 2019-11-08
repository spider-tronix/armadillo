
#include<RMCS2303drive.h>

RMCS2303 rmcs;                    //object for class RMCS2303

SoftwareSerial myserial(2,3);     //Software Serial port For Arduino Uno. Comment out if using Mega.

// MODBUS protocol for 2 slave - 1 master communication 
//MOTOR 1 PARAMETERS
byte slave_id=7; 
int INP_CONTROL_MODE=257;           
int PP_gain=30;
int PI_gain=30;
int VF_gain=32;
//MOTOR 2 PARAMETERS
byte slave_id1=3;                // Should be changed when 2 drivers are used for MODBUS protocol
int PP_gain1=30;
int PI_gain1=30;
int VF_gain1=32;
int LPR=2460;
int acceleration=100;
int speed0=10;
int speedmax=30;
char c;

long int Current_position,Current_position1;
long int Current_Speed,Current_Speed1;
unsigned long time;

void setup()
{
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //Set baudrate for usb serial to monitor data on serial monitor
   rmcs.begin(&myserial,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.

   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,0);    //Uncomment to write parameters to drive. Comment to ignore.
  // rmcs.WRITE_PARAMETER(slave_id1,INP_CONTROL_MODE,PP_gain1,PI_gain1,VF_gain1,LPR,acceleration,speed1);
  //rmcs.READ_PARAMETER(slave_id);//DEBUG function
  delay(1000);
   
}

void loop()
{
   while (Serial.available()) 
   {
     c = Serial.read();
   }
   if(c=='w')
   {
   rmcs.Enable_Digital_Mode(slave_id,0);       //To enable motor in digital speed control mode. 0-fwd,1-reverse direction.
   rmcs.Speed(slave_id,speed0);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
   //rmcs.Speed(slave_id1,speed1); 
   //rmcs.Enable_Digital_Mode(slave_id1,0);       //To enable motor in digital speed control mode. 0-fwd,1-reverse direction.
    delay(100);
    Current_Speed=rmcs.Speed_Feedback(slave_id);
    Serial.print("Current Speed feedback : ");
    Serial.println(Current_Speed);
    delay(10);
   }
   else if(c=='s')
   {
   rmcs.Enable_Digital_Mode(slave_id,1);       //To enable motor in digital speed control mode. 0-fwd,1-reverse direction.
   rmcs.Speed(slave_id,speed0);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
   //rmcs.Speed(slave_id1,speed1); 
   //rmcs.Enable_Digital_Mode(slave_id1,0);       //To enable motor in digital speed control mode. 0-fwd,1-reverse direction.
   Current_Speed=rmcs.Speed_Feedback(slave_id);
    Serial.print("Current Speed feedback : ");
    Serial.println(Current_Speed);
    delay(10);

   }
   else if(c=='e')
   {
    rmcs.Brake_Motor(slave_id,0); 
   }
   else if(c=='d')
   {
    rmcs.Brake_Motor(slave_id,1);
   }
      else if(c=='u')
   {
    speed0+=5;
    if(speed0>speedmax)
    speed0=speedmax;
   }
   else if(c=='j')
   {
    speed0-=5;
    if(speed0<0)
    speed0=0;
   }


}
