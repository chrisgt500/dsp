%Passband: Gain 12dB+/- .25 dB, .15 < f < .25
% Stopbands : 70 min attenuation, f < .125, or .28 <f < .5

M = 120;

%Desired response: Spec three separate bands by giving the corner
%frequencies and gains at the corner frequencies. Frequencies are
%normalized by Fs/2

A1 = 10^(12/20);
F = [0 0.125 0.15 0.25 0.28 0.5] /.5;
A = [0 0   A1   A1   0  0];

%weight vector designed so that each band has its own toelernce
d1 = 10^(12/20) - 10^(11.75/20);
d2 = 10^(-70/20);
W = [1/d2 1/d1 1/d2];

% Filter design
h = firpm(M-1, F, A, W);



