function [y,s] = calc_running_mean(x,s)
%CALC_RUNNING_MEAN Summary of this function goes here
%   Detailed explanation goes here
% M : how many to average over
% X : data 
% structure { M, blocksize, array}

%%% Calculating average;
s.runningtotal(1:  %%init runningtotal with values    


for i = 1:length(x):
    s.runningtotal = circshift(s.runningtotal, [0,1]);   %%mean of vector, shift by 1, mean ...
  


%%% Setting array

s.array = circshift(s.array,[0,min(s.M-1,s.blocksize)]);
s.array(1:min(s.M-1,s.blocksize)) = x(end-min(s.M-1,s.blocksize)+1:end);


end

