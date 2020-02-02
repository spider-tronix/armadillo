clc;
clear all;
a = arduino('COM4','Uno','Libraries','rotaryEncoder');
chna1='D2'; %interrupt 1
chnb1='D3'; %interrupt 2
encoder = rotaryEncoder(a,'D2','D3',810);
%MOTOR DRIVER PINS INITIALISED

pwm='D5';
direction='D7';
kp=0.7;
ki=0.3;
kd=0.01;
error=0;
current_val=0;
error_prev=0;
dt=0;
setpoint=15000;
prevtime=0;
scale=100;

figure
h=animatedline;
ylabel("Response");

while(1)
    [current_val,time]=readCount(encoder);
    dt=time-prevtime;
    error=setpoint-current_val;
    error_sum=(error_prev+error)*dt;
    error_diff=(error-error_prev)/dt;
    pid=error*kp+error_diff*kd+error_sum*ki;
    pid=pid/scale;
    prevtime=time;
    error_prev=error;
    if(pid>0)
        if(pid>5)
            pid=5;
        end
        writeDigitalPin(a,direction,1);
        writePWMVoltage(a,pwm,pid);
    elseif(pid<0)
        if(pid<-5)
            pid=-5;
        end
        writeDigitalPin(a,direction,0);
        writePWMVoltage(a,pwm,-pid);
    end 
    
    addpoints(h,time,current_val);
    xlim([time-10,time+10]);
    drawnow;
    
end

    
    
    
    