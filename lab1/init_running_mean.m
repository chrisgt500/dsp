function [s] = init_running_mean( M, blocksize )
%INIT_RUNNING_MEAN Summary of this function goes here
%   Detailed explanation goes here
%
%
%

s = struct('M', M, 'blocksize', blocksize, 'array', zeros(1,M-1), 'runningtotal', zeros(1,M));



end

