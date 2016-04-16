%{
    Jacob Turcotte
    Lab 5 Briefing code
    By: Don Hummels
    Part 1
%}


N = 8*1024;
f = (0:N-1)/N;
f(N/2+1+1:end) = f(N/2+1+1:end) - 1;

M = 81;
beta = 8.2;

Hr = (abs(f)>.135 & abs(f)<.315).*(10.^( (abs(f)-.15)*10/.15 /20) );
Hd = Hr.*exp(-i*2*pi*f*(M-1)/2);

% clf == clear current figure. Makes sure you have a clean slate. 
figure(2);
clf;

% Patch is used to make the shaded areas. Pretty useful.
patch([0 .1 .1 0],[-100 -100 -70 -70], 0.9*[1 1 1]);
patch([.35 .5 .5 .35],[-100 -100 -70 -70], 0.9*[1 1 1]);
patch([.15 .3 .3 .15],[-1 9 11 1], 0.9*[1 1 1]);

hold on;

% 20 * log10() is used for Decibel representation
plot(f,20*log10(abs(Hr)));
axis([0 .5 -80 20]);

hd = ifft(Hd);
hr = ifft(Hr);

figure(1);
clf;

stem(0:N-1, hd, '.');

% Another function instead of kaiser students apparently like is
% chebwin()
h = hd(1:M).*kaiser(M, beta)';
hold on;
stem(0:M-1, h, '.');
figure(2);
plot(f, 20*log10(abs(fft(h,N))));