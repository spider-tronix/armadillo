clc;
clear all;
a = arduino('COM4','Uno','Libraries','rotaryEncoder');
chna1='D2'; %interrupt 1
chnb1='D3'; %interrupt 2
encoder = rotaryEncoder(a,'D2','D3',810);
%MOTOR DRIVER PINS INITIALISED

pwm='D5';
direction='D7';
kp=0.04;
ki=0.09;
kd=0;
error=0;
current_val=0;
error_prev=0;
dt=0;
thetaref=0;
setpoint=(thetaref*9840)/360;
prevtime=0;
scale=200;
iscale=1;
risetime=0;
settime=0;
figure
h=animatedline;
ylabel("Response");
ylim([0,150]);
current_theta=0;
flag=0;
flag1=0;

while(1)
    [current_val,time]=readCount(encoder);
    current_theta=(current_val*360)/9840;
    if(current_val==0.9*setpoint & flag1==0)
        risetime=time;
        flag1=1;
    end
    
    if(current_val>=0.80*setpoint & current_val <= 1.8*setpoint & flag==0)
        settime=time;
        flag=1;
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
    
    addpoints(h,time,current_theta);
    xlim([time-50,time+50]);
    drawnow;
    
end

    
    
    
    