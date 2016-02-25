%% Lab 3 - Task 2

%This function is designed to take pole and zeros in the z-plane and create
%a filter based on those poles.  Our specific filter was required to
%attenuate -40dB at frequencies below f = .1 and -50dB at frequencies above
%f = .35.  In the .15 < f < .25 band, there is a pass band which must fit
%the graph given in the lab manual.

N = 1024;
f = linspace(0,1,N);
w = 2*pi*f;
z = exp(j*w);




iir_poles =[
    .9 * exp(j*2*pi*.14*[1 -1]), ...
    .93 * exp(j*2*pi*.15*[1 -1]), ...
    .615 * exp(j*2*pi*.2*[1 -1]), ...
    .92 * exp(j*2*pi*.25*[1 -1]), ...
    .001 * exp(j*2*pi* 0*[1 -1]), ...
    .001 * exp(j*2*pi* 0 *[1 -1])
    
    
];

iir_zeros =[
   	1, ...
    -1, ...
    exp(j*2*pi*.05*[1 -1]), ...
    exp(j*2*pi*.07*[1 -1]), ...
    exp(j*2*pi*.1*[1 -1]), ...
    exp(j*2*pi*.35*[1 -1]), ...
    exp(j*2*pi*.43*[1 -1])
];

num = poly(iir_zeros);
den = poly(iir_poles);
hold on;
plot(iir_poles, 'x');
plot(iir_zeros, 'o');
rectangle('Position',[-1 -1 2 2],'Curvature',[1 1]);
grid;
axis square;

k = 1/(max(abs(polyval(num,z)./polyval(den,z))));

H = 20*log10(k*abs(polyval(num,z)./polyval(den,z)));

figure;
plot(f,H);
hold on;
grid on;
xlim([0 .5]);
ylim([-60, 5]);

%% Geometric Limits for Gain
plot([0 .1 .1 0 0],[-40 -40 -60 -60 -40])
plot([.35 .5 .5 .35 .35],[-50 -50 -60 -60 -50])

plot([.15 .2 .2 .15 .15],[1 -4 -6 -1 1])
plot([.2 .25 .25 .2 .2],[-4 1 -1 -6 -4]);

[sos,g] = zp2sos(num,den,k,'up','inf'); %need inf? yes

lab3_task3(sos,g);

