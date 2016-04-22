numSamples = 1024;
n = 0:numSamples - 1;
sin_x = sin(linspace(0,pi,numSamples));

A0 = 25.3;
f0 = .3074;
theta0 = .1234;
x = A0*cos(2*pi*f0*n+theta0);

re = real(x);
im = imag(x);
w = kaiser(numSamples, 7)';

re = re .* sin_x;
im = im .* sin_x;
N = numSamples*64*2;
f = (0:N-1)/N;

X = fft(re + j*im, N);
dbX = 20*log10(abs(X));

plot(f(1:end/2), dbX(1:end/2))
