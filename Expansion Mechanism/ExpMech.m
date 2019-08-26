%LOCUS OF THE ARC 
%Intersection of 2 circles with radii (a+b)and (t)
%(x-b)^2+y^2=(a+b)^2;
%(x^2)+y^2=t^2

a = 3;
b = 9;
x=[];
y=[];
for t=1:0.1:25
x = -b/2 + ((a+b)^2-(t^2))/(2*b);
y = sqrt(((2*b+a)^2-t^2)*(t^2-a^2))/(2*b);
plot(x,y,".")
hold on
end

%Dependency of r on Theta 

theta1=linspace(0,pi,pi/20);
r=[];
%Polar Co-ordinates 
for theta=0:pi/20:pi/2
r= sqrt((a+b)^2-(b*sin(theta)^2))-(b*cos(theta));
plot(theta,r,"*");
hold on 
end








