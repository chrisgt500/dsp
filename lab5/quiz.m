% Passband specs
maxripple = .25;     %maximum stopband ripple [dB]
startgain = 10;      %gain at beginning of stopband [dB]
endgain = 10;        %gain at end of stopband [dB]
passlow = 0.18;        %passband beginning frequency [normalized]
passhigh = 0.25;    %passband ending frequency [normalized]

% Stopband specs
minreject = -60;    %minimum rejection in stopband [dB}
stopbegin = 0.28;     %frequency stopband begins [normalized]
stopend = 0.5;     %frequency stopband ends [normalized]

% Other junk to specify
N = 8 * 1024;       %number of samples
M = 121;             %number of coefficients in filter
beta = 8;           %adjustable window parameter
hrspec = .017;       %how far Hr should extend beyond spec


figure(1); clf; hold on;
winlow = minreject-10;
winhigh = 20;
axis([0 .5 winlow winhigh]);    %set window size


%% Ellip Functions

% n - filter order
% rp - peak to peak passband ripple in dB
% rs - stopband attenuation in dB
% wp - passband edge frequency
% ftype options - 'low' 'bandpass' 'high' 'stop'(notch)
% gain - passband gain in dB

% [b,a] = ellip() returns coefficients in the form B(z)/A(z) where B(z) =
% b(1) + b(2)z^-1 + b(3)z^-2 + ... b(n+1)z^-n. A(z) follows the same format
% Using the [b,a] format can cause numerical problems due to rounding errors

% [z,p,k] = ellip() returns coefficients in the form
% (1-z(1)z^-1)(1-z(2)z^-1)...*(1-z(n)z^-1) for the numerator and does the
% same with the poles in the denominator.  The entire expression is then
% scaled by k.

n =  7;
rp = .125;
rs = 75;
wp = [.18 .25];
ftype = 'bandpass';
gain = 10^(10.125/20);

[b,a] = ellip(n, rp, rs, wp, ftype);
hold on;
freqz(gain*b,a);
b = gain*b;



