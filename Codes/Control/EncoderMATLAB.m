clc;
clear all;
a = arduino('COM4','Uno','Libraries','rotaryEncoder');
chna1='D2'; %interrupt 1
chnb1='D3'; %interrupt 2
encoder = rotaryEncoder(a,'D2','D3',810);
%MOTOR DRIVER PINS INITIALISED

pwm='D5';
direction='D7';
kp=0.09;
ki=0.09;
kd=0;
error=0;
current_val=0;
error_prev=0;
dt=0;
setpoint=6000;
prevtime=0;
scale=100;
iscale=1;
risetime=0;
settime=0;
figure
h=animatedline;
ylabel("Response");
ylim([0,8500]);

while(1)
    [current_val,time]=readCount(encoder);
    if(current_val==0.9*setpoint)
        risetime=time;
    end
    
    if(current_val>=0.80*setpoint & current_val <= 1.8*setpoint)
        settime=time;
    end
    dt=time-prevtime;
    error=setpoint-current_val;
    error_sum=(error_prev+error)*dt;
    error_diff=(error-error_prev)/dt;
    pid=error*kp+error_diff*kd+(error_sum*ki/iscale);
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
    xlim([time-50,time+50]);
    drawnow;
    
end

    
    
    
    