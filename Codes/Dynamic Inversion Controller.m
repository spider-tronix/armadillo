theta(50)=0;
thetar(50)=0;
iaref(50)=0
w(50)=0
ia(50)=0
r(50)=0
dt=0.000001
a=36
b=72
factor(50)=0;
idisk=202464;
ispoke=15.44;
R=100
v(50)=0
ra=50
ka=100
la=1
f=0.3
thetaref=0.6;
k3=25.5
k2=25.6
k1=25.7
clc()
theta(2)=0.01;
for i= 2:10000
    if(thetaref<theta(2))
        thetaref=pi-thetaref;
    end
    theta(i+1)=theta(i)+(w(i)*dt);
    if(theta(i)>pi/2)
        thetar(i+1)=pi-theta(i+1);
    else
        thetar(i+1)=theta(i+1);
    end
    ia(i+1)=ia(i)-(ra*ia(i)*dt/la)-(ka*w(i)*dt/la)+(v(i)*dt/la);
    r(i+1)=sqrt(((a+b)^2)-(b*sin(thetar(i+1)))^2)-(b*cos(thetar(i+1)));
    factor(i)=(ispoke/idisk)*(cos(theta(i))+f*sin(theta(i)))*r(i)*(r(i+1)+r(i-1)-2*r(i))*8/((f*R^2)*(1-(f*sin(theta(i)))-cos(theta(i)))*dt);
    w(i+1)=w(i)+(ka*ia(i)*dt/idisk)-factor(i);
    wref(i)=-k1*(theta(i)-thetaref);
    dertheta(i)=(theta(i+1)-theta(i))/dt;
    derwref(i)=-k1*dertheta(i);
    iaref(i)=(idisk/ka)*(derwref(i)-(k2*(w(i)-wref(i)))+(factor(i)/dt));
    deriref(i)=(iaref(i)-iaref(i-1))/dt;
    v(i+1)=la*((ra*ia(i-1)/la)+(ka*w(i-1)/la)-(k3*(ia(i)-iaref(i)))+deriref(i)); 
    plot(i,theta(i),'.')
    hold on
end

    
 