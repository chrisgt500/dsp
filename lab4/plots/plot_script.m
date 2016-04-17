%% bell202_timing
%{
data = csvread('bell202_timing.csv', 6, 0);
t = data(:,1);
v = data(:,2);

figure;
plot(t,v);
title('Time to execute demodulation');
xlabel('Time [s]');
ylabel('Pin voltage [V]');
grid;
%}

%% bell202_output
%d{
data = csvread('bell202_output.csv', 6, 0);
t = data(:,1);
v = data(:,2);

figure;
plot(t,v);
title('Demodulated Bell 202 signal');
xlabel('Time [s]');
ylabel('Output voltage [V]');
grid;
figure;
%}

%% bell202_timing
%d{
data = csvread('bell202_timing.csv', 6, 0);
t = data(:,1);
v = data(:,2);

plot(t,v);
title('Time to execute demodulation');
xlabel('Time [s]');
ylabel('Pin voltage [V]');
xlim([-.001 .002]);
grid;
figure;
%}
%% Filter Responses
sos1 = csvread('filter1_sos.csv',0,0);
g = 0.000916;
sos1(1,1:3) = sos1(1,1:3)*g;
freqz(sos1);
figure;

sos2 = csvread('filter2_sos.csv',0,0);
g = 0.002097;
sos2(1,1:3) = sos2(1,1:3)*g;
freqz(sos2);

