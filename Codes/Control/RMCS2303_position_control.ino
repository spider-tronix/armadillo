/*
Connections of Drive and Arduino
Serial Port 0 is not used to connect to drive because its connected to USB-Serial and used to show information on console.

For Arduino Uno Software serial needs to be used as there is only one hardware serial port and its connected to USB-Serial. 
   Drive to Arduino UNO/Nano connections
   GND         -      GND
   RXD         -      D3
   TXD         -      D2

*/


#include<RMCS2303drive.h>
#include<math.h>

RMCS2303 rmcs;                      //object for class RMCS2303

SoftwareSerial myserial(2,3);     //Software Serial port For Arduino Uno. Comment out if using Mega.

//Parameter Settings "Refer datasheet for details" - 
byte slave_id=7;                    //Choose the slave id of connected drive.
int INP_CONTROL_MODE=513;           //IMPORTANT: refer datasheet and set value(integer) according to application 
int PP_gain=32;
int PI_gain=16;
int VF_gain=32;
int LPR=810/4;
int acceleration=5000;
int speed=8000;
float radius,a= b= ;
double current_theta=0;
const double PI =3.141592653589793238463;
long int Current_position;
float theta,r;

void setup()
{
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //set baudrate for usb serial to monitor data on serial monitor
   rmcs.begin(&myserial,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.
   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,speed);    //Uncomment to write parameters to drive. Comment to ignore.

}

void loop()
{
   theta=acos((a^2+(2*a*b)-(r^2))/(2*r*b));               //Multiply by Gear Ratio to obtain the exact angle rotated by shafts
   rmcs.Absolute_position(slave_id,(theta*LPR)/(2*PI));   //enter position count with direction (CW:+ve,CCW:-ve) 
   
   while(1)                                   //Keep reading positions. Exit when reached.
   {
      Current_position=rmcs.Position_Feedback(slave_id); //Read current encoder position
      Current_theta=(2*PI*Current_position)/LPR;         //MULTIPLY by gear ratio to obtain the angle rotated
      Serial.print("Position Feedback :\t");
      Serial.print(Current_position);
      radius=sqrt((a+b)^2-(b*sin(current_theta))^2)-(b*cos(current_theta));
      //Serial.println(radius);  Use it for plotting radius   
      delay(100);
      if(radius==r)
      {
         Serial.println("Radius reached ");
      }
   }
   delay(200);
}
 