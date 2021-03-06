M = 110;        %Number of filter coefficients: Adjust to meet spec
passgain = 12; % passband gain in dB
passripple = .25; %+- ripple in dB
attenuation = -70; %attenuation in dB
corner_frequencies = [ 0 0.125 .15 .25 .28 .5]; %corner of pass/stop bands

%% Behind the scenes magic stuff
%Desired response: Spec three separate bands by giving the corner
%frequencies and gains at the corner frequencies. Frequencies are 
%normalized by Fs/2. Gains are absolute values (not dB)
A1 = 10^(passgain/20);        %passband gain
F = corner_frequencies/0.5;       %corner freq
A = [0 0 A1 A1 0 0];             %corner freq gains

%weight each vector designed so that each band has its own tolerance
d1 = 10^(passgain/20)-10^((passgain-passripple)/20);      %max passband error
d2 = 10^(attenuation/20);                   %max stopband error
W  = [1/d2 1/d1 1/d2];           %weight per specified band

%filter design and some really ugly plot code intermixed

stop = 20*log10(d2);
passh = 20*log10(A1+d1);
passl = 20*log10(A1-d1);

figure(1); clf;
hold on;
patch([F(1)*.5 F(2)*.5 F(2)*.5 F(1)*.5],[stop stop stop-20 stop-20], .9*[1 1 1]);
patch([F(3)*.5 F(4)*.5 F(4)*.5 F(3)*.5], [passh passh passl passl], .9*[1 1 1]);
patch([F(5)*.5 F(6)*.5 F(6)*.5 F(5)*.5], [stop stop stop-20 stop-20], .9*[1 1 1]);


h = firpm(M-1, F, A, W);        %this is the filter creation
N = 8 * 1024;
f = (0:N-1)/N;
f(N/2+1+1:end) = f(N/2+1+1:end)-1;
f(N/2+1) = NaN;
plot(f, 20*log10(abs(fft(h,N))));

axis([0 .5 -90 20]);