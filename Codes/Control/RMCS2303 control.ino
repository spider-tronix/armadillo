
#include<RMCS2303drive.h>

RMCS2303 rmcs;                    //object for class RMCS2303

SoftwareSerial myserial(2,3);     //Software Serial port For Arduino Uno. Comment out if using Mega.

// MODBUS protocol for 2 slave - 1 master communication 
//MOTOR 1 PARAMETERS
byte slave_id=7; 
int INP_CONTROL_MODE=203;           
int PP_gain=32;
int PI_gain=16;
int VF_gain=32;
//MOTOR 2 PARAMETERS
byte slave_id1=6;                // Should be changed when 2 drivers are used for MODBUS protocol
int PP_gain1=32;
int PI_gain1=16;
int VF_gain1=32;
int LPR=810/4;
int acceleration=5000;
int speed=100;


long int Current_position,Current_position1;
long int Current_Speed,Current_Speed1;

void setup()
{
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //Set baudrate for usb serial to monitor data on serial monitor
   rmcs.begin(&myserial,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.
   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,speed);    //Uncomment to write parameters to drive. Comment to ignore.
   rmcs.WRITE_PARAMETER(slave_id1,INP_CONTROL_MODE,PP_gain1,PI_gain1,VF_gain1,LPR,acceleration,speed);
   //rmcs.READ_PARAMETER(slave_id);//DEBUG function
   
}

void loop()
{
  
   rmcs.Speed(slave_id,100);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
   rmcs.Enable_Digital_Mode(slave_id,0);       //To enable motor in digital speed control mode. 0-fwd,1-reverse direction.
   rmcs.Speed(slave_id1,100); 
   rmcs.Enable_Digital_Mode(slave_id1,0);       //To enable motor in digital speed control mode. 0-fwd,1-reverse direction.
   delay(100);
   Current_Speed=rmcs.Speed_Feedback(slave_id); 
   Current_Speed1=rmcs.Speed_Feedback(slave_id1);
   Serial.print("Current Speed feedback : ");
   Serial.println(Current_Speed);
   Serial.print("Current Speed feedback1 : ");
   Serial.println(Current_Speed1);

}