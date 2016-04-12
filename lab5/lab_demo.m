N = 8*1024;
f = (0:N-1)/N;
f(N/2+1+1:end) = f(N/2+1+1:end)-1; %%keeps track of negative freq too

M = 81;  %%affects filter order
beta = 8.2; %%filter shape

Hr = (abs(f) > .135 & abs(f)<.315)  ...         %real transfer using this line for pass band
    .*(10 .^ ((abs(f) - .15) * 10 / .15  /20)); 

Hd = Hr.*exp(-j*2*pi*f*(M-1)/2); %%desired tranfer

figure(2); clf;

patch ([0 .1 .1 0], [-100 -100 -70 -70], .9*[1 1 1]); %%specs
patch ( [.35 .5 .5 .35], [-100 -100 -70 -70], .9*[1 1 1]);

patch([.15 .3 .3 .15],[-1 9 11 1], .9*[1 1 1]);
hold on;

plot(f, 20*log10(abs(Hr)));  %%plots the gain of real transfer in dB
axis([ 0 .5 -80 20]);

figure(1); clf;
hd = ifft(Hd);  %%transfer function of desired impulse response
stem(0:N-1 , hd, '.');

h = hd(1:M).*kaiser(M, beta)'; %%windowed impulese
hold on;
stem(0:M-1,h,'.'); %%transfer function of 
figure(2);
plot(f, 20*log10(abs(fft(h,N))));