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

limits = true;  %plot with spec given for task 2

iir_poles =[    %values are expressed in polar form and as conjugate pairs
    .972 * exp(j*2*pi*.142*[1 -1]), ...
    .91 * exp(j*2*pi*.157*[1 -1]), ...
    .665 * exp(j*2*pi*.197*[1 -1]), ...
    .94 * exp(j*2*pi*.25*[1 -1]), ...
    .68 * exp(j*2*pi*.225*[1 -1])
];

iir_zeros =[    %values are expressed in polar form and as conjugate pairs
    exp(j*2*pi*.05*[1 -1]), ...
    exp(j*2*pi*.07*[1 -1]), ...
    exp(j*2*pi*.1*[1 -1]), ...
    exp(j*2*pi*.35*[1 -1]), ...
    exp(j*2*pi*.43*[1 -1])
];

num = poly(iir_zeros);  %creates polynomial with the zeros, which will be the numerator of the filter
den = poly(iir_poles);  %creates a polynomial with the polars, which will be the denominator of the filter
hold on;
%zero-pole zplane plot
plot(iir_poles, 'x');
plot(iir_zeros, 'o');
rectangle('Position',[-1 -1 2 2],'Curvature',[1 1]);
grid;
axis square;

k = 1/(max(abs(polyval(num,z)./polyval(den,z))));   %scaling factor to make max gain 0dB

H = 20*log10(k*abs(polyval(num,z)./polyval(den,z)));

figure;
%plot of gain versus frequncy
plot(f,H);
hold on;
grid on;
xlim([0 .5]);
ylim([-60, 5]);

%% Geometric Limits for Gain
%Gives the specification for task 2 on the graph
if(limits)
    plot([0 .1 .1 0 0],[-40 -40 -60 -60 -40]);
    plot([.35 .5 .5 .35 .35],[-50 -50 -60 -60 -50]);

    plot([.15 .2 .2 .15 .15],[1 -4 -6 -1 1]);
    plot([.2 .25 .25 .2 .2],[-4 1 -1 -6 -4]);
end


%% Creates second order sections and calls the Task 3 script
[sos,g] = zp2sos(iir_zeros,iir_poles,k,'up','inf');


lab3_task3(sos,g);



