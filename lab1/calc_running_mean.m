function [y,s] = calc_running_mean(x,s)
%CALC_RUNNING_MEAN Summary of this function goes here
%   Detailed explanation goes here
% M : how many to average over
% X : data 
% structure { M, blocksize, array}

%%% Preallocation for speed;
y = zeros(1,length(x));

for i = 1:length(x)
    s.runningtotal = circshift(s.runningtotal, [0,1]);   %shifts 1 value of x into the runningtotal vector and calculates the mean
    s.runningtotal(1) = x(i);
    y(i) = mean(s.runningtotal);
end

