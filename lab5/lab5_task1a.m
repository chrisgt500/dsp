%% FIR filter design
% Authors: Colin Leary, Forrest Smith, Sean Turner

% Specs: less than .1dB ripple in passband, 0 > |f| > 0.07
%       more than 80dB rejection in stopband, .11 < |f| < 0.5

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
M = 170;             %number of coefficients in filter
beta = 8;           %adjustable window parameter
hrspec = .01;       %how far Hr should extend beyond spec


% Important junk to calculate from above info
f = (0:N-1)/N;      %specify normalized frequencies
f(N/2+1+1:end) = f(N/2+1+1:end)-1; %keep track of negative frequencies

stem_logical = 0;

%% Plot filter response
% Generate stop and pass bands
figure(1); clf; hold on;
winlow = minreject-10;
winhigh = 20;
axis([0 .5 winlow winhigh]);    %set window size

%plot passband
patch([passlow passhigh passhigh passlow], ...
          [(maxripple+startgain) (maxripple+endgain) ...
          (-maxripple+endgain) (-maxripple+startgain)], ...
          .9*[1 1 1]); 

if (passlow == 0) || (passhigh == .5)  %check type of filter
    %if not bandpass, plot accordingly
    patch([stopbegin stopend stopend stopbegin], ...
          [minreject minreject winlow winlow], ...
          .9*[1 1 1]);
      
else
    %if bandpass, plot two stopbands
    patch([0 .15 .15 0], ...
          [minreject minreject winlow winlow], ...
          .9*[1 1 1]);
    patch([stopbegin .5 .5 stopbegin], ...
          [minreject minreject winlow winlow], ...
          .9*[1 1 1]);
end

%% Calculate real and desired transfer functions
m = (endgain-startgain)/(passhigh-passlow);     %slope of Hr

%Calculate entire line (point-slope formula) and convert from dB
%Then limit the line to within hrspec
Hr =  ((abs(f) > (passlow-hrspec)) & (abs(f) < (passhigh+hrspec))) .* ...
        10 .^ (((abs(f) .* m) - (m*passlow) + startgain)/20);

%plot the desired Hr for visualization
plot(f, 20*log10(abs(Hr)));

%From the real transfer function, obtain the complete desired transfer function
Hd = Hr.*exp(-j*2*pi*f*(M-1)/2);

%% Calculate impulse responses and window
%Perform inverse FFT to obtain impulse response
hd = ifft(Hd);

%window impulse response to obtain filter response
h = hd(1:M).*kaiser(M, beta)';

%% Plot results
%plot FFT of resulting, windowed filter response
plot(f, 20*log10(abs(fft(h,N))));

%optionally plot a stem plot of the windowed and non windowed impulse responses
if(stem_logical)
    figure(2); clf;
    stem(0:N-1 , hd, '.');
    hold on;
    stem(0:M-1,h,'.'); %%transfer function of 
end
%}