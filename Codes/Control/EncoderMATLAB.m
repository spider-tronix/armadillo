clc;
clear all;
clean all;
a = arduino('COM4','Uno','Libraries','rotaryEncoder');
chna1='D2'; %interrupt 1
chnb1='D3'; %interrupt 2
encoder = rotaryEncoder(a,'D2','D3',810);
motorpos='D5';
motorneg='D6';
kp=1;
ki=2;
kd=1;
error=0;
current_val=0;
error_prev=0;
dt=0;
setpoint=90;
prevtime=0;

while(1)
    [current_val,time]=readCount(encoder);
    dt=time-prevtime;
    error=setpoint-current_val;
    error_sum=(error_prev+error)*dt;
    error_diff=(error-error_prev)/dt;
    pid=error*kp+error_diff*kd+error_sum*ki;
    prevtime=time;
    error_prev=error;
    
    if(pid>5)
        pid=5;
    elseif(pid<-5)
        pid=-5;
    end
    
    
    if(pid>0)
        writePWMVoltage(a,motorpos,pid);
    elseif
        writePWMVoltage(a,motorneg,pid);
    end 
    
    
    plot(time,setpoint,"*");
    hold on;
    plot(time,current_val,"#");
    hold on;
    xlabel('time');
    ylabel('response');
    
end

    
    
    
    