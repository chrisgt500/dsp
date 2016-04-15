%% Lab 5 Task 2

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

n = 20;
rp = .2;
rs = 70.2;
wp = [12000/48000 15000/48000];
ftype = 'bandpass';
gain = 10^(10.1/20);

[b,a] = ellip(n, rp, rs, wp, ftype);
[z,p,k] = ellip(n, rp, rs, wp, ftype);
sos = zp2sos(z, p, gain*k);

fvtool(b,a,sos);

%% Chebyshev Type I and Type II

% n - filter order
% rp - peak to peak passband ripple in dB
% wp - passband edge frequency
% ftype options - 'low' 'bandpass' 'high' 'stop'(notch)
% gain - passband gain in dB

% [b,a] = cheby1(n,Rp,Wp,ftype) designs a lowpass, highpass, bandpass, or 
% bandstop Chebyshev Type I filter, depending on the value of ftype and the 
% number of elements of Wp. The resulting bandpass and bandstop designs are 
% of order 2n.

% [z,p,k] = cheby1(___) designs a lowpass, highpass, bandpass, or bandstop 
% digital Chebyshev Type I filter and returns its zeros, poles, and gain. 
% This syntax can include any of the input arguments in previous syntaxes.

n1 = 6;
rp1 = .2;
wp1 = [12000/48000 15000/48000];
ftype1 = 'bandpass';
gain2 = 10^(10.1/20);

[b1,a1] = cheby1(n1,rp1,wp1,ftype1);
%freqz(gain2*b1,a1);

% [b,a] = cheby2(n,Rs,Ws,ftype) designs a lowpass, highpass, bandpass, or 
% bandstop Chebyshev Type II filter, depending on the value of ftype and the 
% number of elements of Ws. The resulting bandpass and bandstop designs are 
% of order 2n.

% [z,p,k] = cheby2(___) designs a lowpass, highpass, bandpass, or bandstop 
% digital Chebyshev Type II filter and returns its zeros, poles, and gain. 
% This syntax can include any of the input arguments in previous syntaxes.

n2 = 10;
rp2 = 70.2;
wp2 = [12000/48000 15000/48000];
ftype2 = 'bandpass';

[b2,a2] = cheby2(n2,rp2,wp2,ftype2);
%freqz(gain2*b2,a2);
%[z2,p2,k2] = cheby2(n2,rp2,wp2,ftype2);
%sos2 = zp2sos(z2,p2,k2*gain2);
%fvtool(sos2);

%% Butterworth

% [b,a] = butter(n,Wn,ftype) designs a lowpass, highpass, bandpass, or 
% bandstop Butterworth filter, depending on the value of ftype and the 
% number of elements of Wn. The resulting bandpass and bandstop designs are 
% of order 2n.

% [z,p,k] = butter(___) designs a lowpass, highpass, bandpass, or bandstop 
% digital Butterworth filter and returns its zeros, poles, and gain. This 
% syntax can include any of the input arguments in previous syntaxes.

% n - filter order
% wp - passband edge frequency
% ftype options - 'low' 'bandpass' 'high' 'stop'(notch)
% gain - passband gain in dB

n3 = 10;
wp3 = [12000/48000 15000/48000];
ftype3 = 'bandpass';
gain3 = 10^(10.1/20);

[b3,a3] = butter(n3, wp3, ftype3);
freqz(gain3*b3, a3);

