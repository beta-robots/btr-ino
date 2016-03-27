
//inputs
th_0 = 20*%pi/180; 
th_e = 61*%pi/180;
wmax = 90*%pi/180;   
te = 1; //duration
dt = 0.01; //time step for plotting

//expression
//th(t) = a0 + a1t + a2t^2 + a3t^3 + a4t^4 + a5t^5 + a6t^6

//constraints
a0 = th_0; //th(0)=th_0
a1 = 0; //th_dot(0) = 0
a2 = 0; //th_dot2(0) = 0 
//th(te) = th_e -> a0 + a3te^3 + a4te^4 + a5te^5 + a6te^6 = th_e
//th_dot(te) = 0 -> 3a3te^2 + 4a4te^3 + 5a5te^4 + 6*a6te^5 = 0
//th_dot(te/2) = wmax -> 3a3(te/2)^2 + 4a4(te/2)^3 + 5a5(te/2)^4 + 6*a6(te/2)^5 = wmax
//th_dot2(te) = 0 -> 6a3te + 12a4te^2 + 20a5te^3 + 30*a6te^4= 0

//build the system
HH = [  te^3 te^4 te^5 te^6; 
        3*te^2 4*te^3 5*te^4 6*te^5; 
        3*(te/2)^2 4*(te/2)^3 5*(te/2)^4 6*(te/2)^5; 
        6*te 12*te^2 20*te^3 30*te^4 ];
bb = [th_e-th_0;0;wmax;0]; 
aa = HH\(bb);
a3 = aa(1); a4 = aa(2); a5 = aa(3); a6 = aa(4);

//plot equations
nn = te/dt; 
th = [];
th_dot = [];
th_dot2 = [];
for ii=0:nn
    tt = ii*dt; 
    th = [th (a0 + a1*tt + a2*tt^2 + a3*tt^3 + a4*tt^4 + a5*tt^5 + a6*tt^6)];    
    th_dot = [th_dot (a1 + 2*a2*tt + 3*a3*tt^2 + 4*a4*tt^3 + 5*a5*tt^4 + 6*a6*tt^5)];    
    th_dot2 = [th_dot2 (2*a2 + 6*a3*tt + 12*a4*tt^2 + 20*a5*tt^3 + 30*a6*tt^4)];        
end

fh1=figure();
fh1.background = color("white");
subplot(311);
plot((0:dt:te), 180*th/%pi, 'red');

subplot(312);
plot((0:dt:te), 180*th_dot/%pi, 'green');

subplot(313);
plot((0:dt:te), 180*th_dot2/%pi, 'blue');

