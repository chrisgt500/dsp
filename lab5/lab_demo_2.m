A0 = 25.3;
f0 = .3074;
theta0 = .1234;

A1 = 0.2;
f1 = 0.33;
theta1 = .5678;

N1 = 512; %% samples
n = 0:N1-1;
x = A0*cos(2*pi*f0*n+theta0) + A1*cos(2*pi*f1*n+theta1);

figure(1);clf;
stem(n,x);

X = fft(x);
f = (0:N1-1)/N1;
figure(2); clf;

stem(f,abs(X),'.');

N2 = 64*1024;
X2 = fft(x, N2);
f2 = (0:N2-1)/N2;
hold on;
plot(f2,abs(X2));

figure(3); clf;
w = kaiser(512, 8)';
H = sum(w);
X3 = fft(x.*w,N2);
plot(f2, 20*log10(abs(X3)));

%%use rectangle window, height is 512(A/2)

[x,b] = max(abs(X2));
estimated_theta = f2(b);
