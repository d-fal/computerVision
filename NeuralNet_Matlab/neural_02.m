clc
clear all
% Neural Network
% Training using Back Propagation Method
% Written by: Davood Falahati

% According to Principles of Artificial Networks BY: Daniel Graupe
% Chapter 6.

% -----------------------------------------------------------------

weights = -1 +2.*rand(3,3);
x  = [0 0;
      0 1;
      1 0;
      1 1];
d  = [0;
      1;
      1;
      0];
INPUT_SIZE = size(x,1);
MAX_ITERATION = 1000;
bias=-[1;1;1];
eta = .7; % Training ratio
for iteration=1:MAX_ITERATION
    for i=1:INPUT_SIZE
    z(1)=bias(1)*weights(1,1)+x(i,1)*weights(1,2)+x(i,2)*weights(1,3);
    z(2)=bias(2)*weights(2,1)+x(i,1)*weights(2,2)+x(i,2)*weights(2,3);
    y(1)=sigma(z(1)); % y1(p-1)
    y(2)=sigma(z(2)); % y2(p-1)
    
    zp=bias(3)*weights(3,1)+y(1)*weights(3,2)+y(2)*weights(3,3);
    
    yp=sigma(zp); % y(p)
    output(i)=yp;
    
    PHI_k      = yp*(1-yp)*(d(i)-yp);
    PHI_j(1)   = y(1)*(1-y(1))*PHI_k*weights(3,2);
    PHI_j(2)   = y(2)*(1-y(2))*PHI_k*weights(3,3);
    Delta_wp   = eta * PHI_k ;
    Delta_w(1) = eta * PHI_j(1);
    Delta_w(2) = eta * PHI_j(2); 
    % Updating ...
    for j=1:size(weights,1)
        if (j==1)
            weights(1,j)=weights(1,j)+bias(1)*Delta_w(1);
            weights(2,j)=weights(2,j)+bias(2)*Delta_w(2);
            weights(3,j)=weights(3,j)+bias(3)*Delta_wp;
        else
            weights(1,j)=weights(1,j)+x(i,1)*Delta_w(1);
            weights(2,j)=weights(2,j)+x(i,2)*Delta_w(2);
            weights(3,j)=weights(3,j)+y(j-1)*Delta_wp;
        end
        
    end
    end % INPUT_SIZE
end
  weights
  [output' d]
 