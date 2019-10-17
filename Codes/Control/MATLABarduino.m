a = arduino('com6', 'uno');     

pwm_step = (5-0)/20;
for i = 1:20

    writePWMVoltage(a, 'D11', i*pwm_step_step);
    pause(0.1)
    analog=a.readvoltage('A0')
    plot(analog)
end
clear a