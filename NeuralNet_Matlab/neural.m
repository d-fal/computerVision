clc
clear all
f1=fopen('ESTIMATEBP1.dat','w');
fprintf(f1,'\nThe following is the weight change and the mean square error: ');
fprintf(f1,'\n-----------------------------------------------------------\n\n');
w1=rand(5,1)/5;
w2=rand(1)/5;
bias = 4.0;
delw2 = 0.0;
mu = 0.001;
delw1 = 0;
mumentum = 0.5;
n = 5;
ITERATION = 2000;

Xpad = zeros(ITERATION + n , 1);
