clc;
clear all;
a = arduino('COM4','Uno','Libraries','rotaryEncoder');
chna1='D2'; %interrupt 1
chnb1='D3'; %interrupt 2
encoder = rotaryEncoder(a,'D2','D3',810);
%MOTOR DRIVER PINS INITIALISED

pwm='D5';
direction='D7';
kp=0.009;
ki=0.09;
kd=0;
error=0;
current_val=0;
error_prev=0;
dt=0;
thetaref=0;
setpoint=45;
prevtime=0;
scale=10;
iscale=1;
risetime=0;
settime=0;
figure
h=animatedline;
h1=animatedline('Color','r');
h2=animatedline('Color','b');

ylabel("Response");
current_count=0;
flag=0;
flag1=0;
tic;
delay=5;
while(1)
    [current_count,time]=readCount(encoder);
    current_val=(current_count*360)/9840;
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
    t=toc;
    if (t>delay)
        setpoint=setpoint+10;
        if(setpoint<100)
            tic;
        else
            setpoint=setpoint-52;
            tic;
        end
    end
    addpoints(h1,time,setpoint);
    addpoints(h2,time,setpoint-current_val);
    addpoints(h,time,current_val);
    xlim([time-50,time+50]);
    drawnow;
    
end

    
    
    
    