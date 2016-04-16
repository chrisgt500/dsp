numPeaks = 2;

%Phase and Magnitude Initializations
A0 = 25.3;
f0 = .3074;
theta0 = .1234;

A1 = 0.2;
f1 = 0.33;
theta1 = .5678;

N1 = 512; %% samples
n = 0:N1-1;
x = A0*cos(2*pi*f0*n+theta0) + A1*cos(2*pi*f1*n+theta1);

%figure(1);clf;
%stem(n,x);


X = fft(x);
f = (0:N1-1)/N1;
figure(2); clf;


%stem(f,abs(X),'.');

N2 = 64*1024;
X2 = fft(x, N2);
f2 = (0:N2-1)/N2;
hold on;
plot(f2,abs(X2));

figure(3); clf;
w = kaiser(512, 8)';
H = sum(w);
X3 = fft(x.*w,N2);
%plot(f2,abs(X3));
dBX3 = 20*log10(abs(X3));
[peaks, locations] = findpeaks(dBX3(1:end/2), f2(1:end/2), 'SortStr','descend');


plot(f2(1:end/2), dBX3(1:end/2));

detectedMags = zeros(1,numPeaks);
detectedFreqs = zeros(1,numPeaks);

for i = 1:numPeaks
    detectedMags(i) = 10^(peaks(i)/20)*2/H;
    detectedFreqs(i) = locations(i);
end
