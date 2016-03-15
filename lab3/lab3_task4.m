%% Lab 3 - Task 4
%
%
%
Fs = 50E3;

N = 1024;
f = linspace(0,1,N);
w = 2*pi*f;
z = exp(j*w);

limits = true;



iir_poles =[
    .972 * exp(j*2*pi*.142*[1 -1]), ...
    .91 * exp(j*2*pi*.157*[1 -1]), ...
    .665 * exp(j*2*pi*.197*[1 -1]), ...
    .94 * exp(j*2*pi*.25*[1 -1]), ...
    .68 * exp(j*2*pi*.225*[1 -1]) 
];

iir_zeros =[
    exp(j*2*pi*.05*[1 -1]), ...
    exp(j*2*pi*.07*[1 -1]), ...
    exp(j*2*pi*.1*[1 -1]), ...
    exp(j*2*pi*.35*[1 -1]), ...
    exp(j*2*pi*.43*[1 -1])
];

num = poly(iir_zeros);
den = poly(iir_poles);

plot(iir_poles, 'x');
hold on;
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
if(limits)
    plot([0 .1 .1 0 0],[-40 -40 -60 -60 -40]);
    plot([.35 .5 .5 .35 .35],[-50 -50 -60 -60 -50]);

    plot([.15 .2 .2 .15 .15],[1 -4 -6 -1 1]);
    plot([.2 .25 .25 .2 .2],[-4 1 -1 -6 -4]);
end
%% Actual Filter Data

data = csvread('DSP_Lab3_Task4.csv',1,0);

freq = data(:,1);
filter_gain = data(:,3);

plot(freq/Fs,filter_gain,'--');

legend('Calculated','Actual');
