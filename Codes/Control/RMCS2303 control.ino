
#include<RMCS2303drive.h>

RMCS2303 rmcs;                    //object for class RMCS2303

SoftwareSerial myserial(2,3);     //Software Serial port For Arduino Uno. Comment out if using Mega.


byte slave_id=7;                  // Should be changed when 2 drivers are used for MODBUS protocol
int INP_CONTROL_MODE=203;           
int PP_gain=32;
int PI_gain=16;
int VF_gain=32;
int LPR=334;
int acceleration=5000;
int speed=100;


long int Current_position;
long int Current_Speed;

void setup()
{
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //Set baudrate for usb serial to monitor data on serial monitor
   rmcs.begin(&myserial,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.
   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,speed);    //Uncomment to write parameters to drive. Comment to ignore.
   //rmcs.READ_PARAMETER(slave_id);//DEBUG function
   
}

void loop()
{
  
   rmcs.Speed(slave_id,100);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
   rmcs.Enable_Digital_Mode(slave_id,0);       //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 

   delay(3000);
   Current_Speed=rmcs.Speed_Feedback(slave_id); 
   Serial.print("Current Speed feedback : ");
   Serial.println(Current_Speed);

   delay(5000);
   Serial.println("Break Motor");
   rmcs.Brake_Motor(slave_id,0);                 //Brake motor. 0-fwd,1-reverse direction. 

   delay(2000);
   Serial.println("Changing direction");
   rmcs.Enable_Digital_Mode(slave_id,1);           //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 

   delay(3000);
   Current_Speed=rmcs.Speed_Feedback(slave_id); 
   Serial.print("Current Speed feedback : ");
   Serial.println(Current_Speed);

   
   delay(3000);
   Serial.println("Disable Motor");
   rmcs.Disable_Digital_Mode(slave_id,1);        //Disable motor in digital speed control mode. 0-fwd,1-reverse direction. 
   delay(3000);
}