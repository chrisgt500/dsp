%% Lab 3 - Task 2

%This function is designed to take pole and zeros in the z-plane and create
%a filter based on those poles.  Our specific filter was required to
%attenuate -40dB at frequencies below f = .1 and -50dB at frequencies above
%f = .35.  In the .15 < f < .25 band, there is a pass band which must fit
%the graph given in the lab manual.

N = 1024;
w = 2*pi*f;
f = linspace(0,1,N);
z = exp(j*w);




iir_poles =[
    .4 * exp(j*2*pi*.15*[1 -1]), ...
    .3 * exp(j*2*pi*.2*[1 -1]), ...
    .4 * exp(j*2*pi*.25*[1 -1])
    
    
];

iir_zeros =[
   	exp(j*2*pi*0*[1 -1]), ...
    exp(j*2*pi*.1*[1 -1]), ...
    exp(j*2*pi*.05*[1 -1]), ...
    exp(j*2*pi*.35*[1 -1]), ...
    exp(j*2*pi*.45*[1 -1]), ...
];

num = poly(iir_zeros);
den = poly(iir_poles);
hold on;
plot(iir_poles, 'x');
plot(iir_zeros, 'o');
rectangle('Position',[-1 -1 2 2],'Curvature',[1 1]);
grid;
axis square;

H = 20*log10(abs(polyval(num,z)./polyval(den,z)));
figure;
plot(f,H);
xlim([0 .5]);


