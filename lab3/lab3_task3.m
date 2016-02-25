function [] = lab3_task3(sos, g)
%LAB3_TASK3 Summary of this function goes here
%   Detailed explanation goes here

fprintf('float g = %f;\n',g);
fprintf('int sections = %d;\n', size(sos,1));
fprintf('float coefs[%d] = {\n',5*size(sos,1));
for i = 1:size(sos,1);
    for j = [1 2 3 5 6]
        fprintf('%f, ',sos(i,j)); 
    end
    fprintf('\n');
end
fprintf('\b\b\b\n};\n');

