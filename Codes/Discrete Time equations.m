%System Dynamics
dt=10^-3

theta[i+1]=theta[i]+w[i]*dt

r[i]=sqrt((a+b)^2-(b*sin(theta[i]))^2)-b*cos(theta[i])

w[i+1]=w[i]+(ka/Idisk*Ia[i]*dt)-(Ispoke/Idisk)*cos(theta[i]+f*sin(theta[i])*r[i]*(r[i+1]+r[i-1]-2*r[i]*8)/(f*R^2*(1-f*sin(theta[i]-cos(theta[i])*dt)))

Ia[i+1]=Ia[i]+((-ra/Idisk)*Ia[i]*dt-ka/la*w[i]+vin/la))*dt


%control design
error=theta[i]-thetaref
Dertheta[i]=-K1(error)
wref[i]=-k1(error)