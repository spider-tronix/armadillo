w(50)=0
ia(50)=0
r(50)=0
dt=0.001
a=36
b=72
theta(50)=0;
factor(50)=0;
idisk=202464;
ispoke=15.44;
R=100
v(50)=0
ra=50
ka=100
la=1
f=0.5
thetaref=0.7
k3=35.5
k2=35.6
k1=35.7
thetamax=pi/2;
clc()
theta(2)=0.5;
for i= 2:10000
    if(thetaref<theta(2))
        theraref=pi-thetaref;
    end
    while(theta(i)<thetamax)
        theta(i+1)=theta(i)+(w(i)*dt);
        ia(i+1)=ia(i)-(ra*ia(i)*dt/la)-(ka*w(i)*dt/la)+(v(i)*dt/la);
        r(i+1)=sqrt(((a+b)^2)-(b*sin(theta(i+1)))^2)-(b*cos(theta(i+1)));
        factor(i)=(ispoke/idisk)*(cos(theta(i))+f*sin(theta(i)))*r(i)*(r(i+1)+r(i-1)-2*r(i))*8/((f*R^2)*(1-(f*sin(theta(i)))-cos(theta(i)))*dt);
        w(i+1)=w(i)+(ka*ia(i)*dt/idisk)-factor(i);
        wref(i)=-k1*(theta(i)-thetaref);
        dertheta(i)=(theta(i+1)-theta(i))/dt;
        derwref(i)=-k1*dertheta(i);
        iaref(i)=(idisk/ka)*(derwref(i)-(k2*(w(i)-wref(i)))+(factor(i)/dt));
        deriref(i)=(iaref(i)-iaref(i-1))/dt;
        v(i+1)=la*((ra*ia(i-1)/la)+(ka*w(i-1)/la)-(k3*(ia(i)-iaref(i)))+deriref(i)); 
        plot(i,theta(i),".")
        hold on
    end
    while(theta(i)>thetamax)
         theta(i+1)=(2*thetamax)-theta(i);
         thetaref=(2*thetamax)-thetaref;
         theta(i+1)=theta(i+1);
         ia(i+1)=ia(i)-(ra*ia(i)*dt/la)-(ka*w(i)*dt/la)+(v(i)*dt/la);
         r(i+1)=sqrt(((a+b)^2)-(b*sin(theta(i+1)))^2)-(b*cos(theta(i+1)));
         factor(i)=(ispoke/idisk)*(cos(theta(i))+f*sin(theta(i)))*r(i)*(r(i+1)+r(i-1)-2*r(i))*8/((f*R^2)*(1-(f*sin(theta(i)))-cos(theta(i)))*dt);
         w(i+1)=w(i)+(ka*ia(i)*dt/idisk)-factor(i);
         wref(i)=-k1*(theta(i)-thetaref);
         dertheta(i)=(theta(i+1)-theta(i))/dt;
         derwref(i)=-k1*dertheta(i);
         iaref(i)=(idisk/ka)*(derwref(i)-(k2*(w(i)-wref(i)))+(factor(i)/dt));
         deriref(i)=(iaref(i)-iaref(i-1))/dt;
         v(i+1)=la*((ra*ia(i-1)/la)+(ka*w(i-1)/la)-(k3*(ia(i)-iaref(i)))+deriref(i)); 
         plot(i,theta(i),".")
         hold on
    end
end
        
    

    
             
        
    
 