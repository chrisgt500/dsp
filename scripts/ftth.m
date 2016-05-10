numSamples = 1024; %% samples of x

%% Phase and Magnitude Initializations
A0 = 25.3;
f0 = .3074;
theta0 = .1234;

A1 = 0.2;
f1 = 0.33;
theta1 = .5678;

n = 0:numSamples-1;
%x = A0*cos(2*pi*f0*n+theta0) + A1*cos(2*pi*f1*n+theta1);
x = data;
%% FFT

N = 64*numSamples*2; %zero padding much much larger than numSamples
f = (0:N-1)/N; %normalized padded frequenct

w = kaiser(numSamples, 10)'; %kaiser window function
H = sum(w); %needed to find amplitude
X = fft(x.*w,N); %performs the windowed, zero-padded FFT
dBX = 20*log10(abs(X)); %converts to dB
[peaks, locations] = findpeaks(dBX(1:end/2), f(1:end/2), 'SortStr','descend'); %finds the all peaks and their locations and sorts them

figure(1); clf;
plot(f(1:end/2), dBX(1:end/2)); %plots the FFT (only half of normalized Frequency)

numPeaks = input('How many peaks do you want to detect? '); %user input for number of peaks

detectedMags = zeros(1,numPeaks); %preallocation for speed
detectedFreqs = zeros(1,numPeaks);

for i = 1:numPeaks %loops over the highest peaks and resturns the associated amplitude and frequenct
    detectedMags(i) = 10^(peaks(i)/20)*2/H; %converts from dB and then scales by window function
    detectedFreqs(i) = locations(i);
end

%outputs to the terminal
detectedMags
detectedFreqs

%% Useful plots
% FFT No zero pad, no window
%{
plot((0:numSamples-1)/numSamples, abs(fft(x)));
%}

% FFT Zero pad, no window
%{
plot((0:N-1)/N, abs(fft(x,N)));
%}

% Stem plot no zero pad, no window, no FFT, not normalized
%{
stem(0:numSamples-1, x);
%}



