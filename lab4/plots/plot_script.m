%% bell202_timing
%d{
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
xlabel('Time [s]');s
ylabel('Output voltage [V]');
grid;
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
grid;
%}