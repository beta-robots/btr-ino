//smooth DC motor start-up, from 0 to wmax in te seconds

//inputs Maxon RE40-148867 + Gearbox GP52C-223112
wmax = 30*%pi/180;   
te = 0.5; //start-up ramp duration
dt = 0.01; //time step for control (and plotting)
kwv = 317; //motor rotation rate constant [rpm/V]
gearbox = 936; //gearbox reduction
vmin = 6; //[V] TBC
vcc = 24; //[V]
pwm_max_value = 255; //pwm levels at analog write

//expression
//th(t) = a0 + a1t + a2t^2 + a3t^3 + a4t^4

//constraints
a0 = 0; //th(0)=0 , arbitrary
a1 = 0; //th_dot(0) = 0
a2 = 0; //th_dot2(0) = 0 
//th_dot(te) = wmax -> 3a3te^2 + 4a4te^3 = wmax
//th_dot2(te) = 0 -> 6a3te + 12a4te^2= 0

//build the system
HH = [  3*te^2 4*te^3; 
        6*te 12*te^2];
bb = [wmax;0]; 
aa = HH\(bb);
a3 = aa(1); a4 = aa(2);

//plot equations
nn = te/dt; 
th = [];
th_dot = [];
th_dot2 = [];
for ii=0:nn
    tt = ii*dt; 
    th = [th (a0 + a1*tt + a2*tt^2 + a3*tt^3 + a4*tt^4)];    
    th_dot = [th_dot (a1 + 2*a2*tt + 3*a3*tt^2 + 4*a4*tt^3)];    
    th_dot2 = [th_dot2 (2*a2 + 6*a3*tt + 12*a4*tt^2)];        
end
voltage = vmin + (60 .*th_dot./(2*%pi))./(kwv/gearbox)
pwm_ratio = voltage./vcc; 
pwm_value = int(pwm_max_value.*voltage./vcc); 

fh1=figure();
fh1.background = color("white");
subplot(311);
plot((0:dt:te), 180*th/%pi, 'red');
subplot(312);
plot((0:dt:te), 180*th_dot/%pi, 'green');
subplot(313);
plot((0:dt:te), 180*th_dot2/%pi, 'blue');

fh2=figure();
fh2.background = color("white");
subplot(311);
plot((0:dt:te), voltage, 'black');
subplot(312);
plot((0:dt:te), pwm_ratio, 'black');
subplot(313);
plot((0:dt:te), pwm_value, 'black');

