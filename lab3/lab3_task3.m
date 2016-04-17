function [] = lab3_task3(sos, g)
%This script combines an arbitrary collection of poles and zeros and a
%desired gain constant into second order sections, and provides the
%coefficients in a suitable form for the filter functions that are
%implemented in C.


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



