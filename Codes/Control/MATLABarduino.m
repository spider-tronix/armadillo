%ENCODER LIBRARY INITIALISATION
clear;
a=arduino('COM6','Due','Libraries','RotaryEncoder');
chna1='D2';
chnb1='D3';
chna2='D7';
chnb2='D8';
encoder1=rotaryEncoder(a,chna1,chnb1,810); %pulse/rev = 810 
encoder2=rotaryEncoder(a,chna2,chnb2,810);
pwm_volt1=2.5;
pwm_volt2=2.5;
% MOTOR OUTPUT PINS
mout1a='D5';
mout1b='D6';
mout2a='10'
mout2b='11'
direction1=0;  %clockwise
direction2=0;  %clockwise
writeDigitalPin(a,mout1a,direction1);
writePWMVoltage(a,mout1b,pwm_volt1);
writeDigitalPin(a,mout2a,direction2);
writePWMVoltage(a,mout2b,pwm_volt2);
pause(3);
executiontime=5;
period=0.1;
while 1
    rpm1=readSpeed(encoder1);
    rpm2=readSpeed(encoder2);
    fprint('current motor speed 1 is : %.2f\n',rpm1);
    fprint('current motor speed 2 is : %.2f\n',rpm2);
    pause(period);
end

