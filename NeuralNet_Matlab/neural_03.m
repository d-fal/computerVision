clc
clear all
% Neural Network
% Training using Back Propagation Method
% Written by: Davood Falahati

% According to Principles of Artificial Networks BY: Daniel Graupe
% Chapter 6.

% -----------------------------------------------------------------


x  = [0 0;
      0 1;
      1 0;
      1 1];
d  = [0;
      1;
      1;
      0];

INPUT_SIZE = size(x,1);
MAX_ITERATION = 1;
bias=-[1;1;1];
eta = .7; % Training ratio
TOPOLOGY = [2;2;1];
fprintf('PRELIMINIARIES\n-------------------------------------------------\nInput ,Desired Output:\n');
display([num2str([x d])]);
fprintf('-------------------------------------------------\n');

if(TOPOLOGY(1)~=size(x,2))
   error('input mismatch!'); 
end

w=rand(sum(TOPOLOGY));

for m=1:MAX_ITERATION %ITERATION
    for j=1:size(x,1) %INPUT SIZE
        
        for layerNo=1:length(TOPOLOGY)
            z=zeros(1,TOPOLOGY(layerNo));
            y=z;
            rowNo = sum(TOPOLOGY(1:layerNo-1));
            rowInd=rowNo+1;
            index=1;
            
            while(rowInd<=rowNo+TOPOLOGY(layerNo))
                for columnInd=rowNo+1:rowNo+TOPOLOGY(layerNo)
%              fprintf(['( ',num2str(rowInd),' , ',num2str(columnInd),' )  ']);
             if(layerNo==1)
             z(index)=z(index)+w(rowInd,columnInd)*x(j,index);
             y(index)=sigmoid(z(index));
             else
             z(index)= z(index)+w(rowInd,columnInd)*y(index);
             y(index)=sigmoid(z(index)); % y(index) is updated
             end
                end
%              fprintf('\n');
             
             index=index+1;
             rowInd=rowInd+1;
            
            end
            y_vec{layerNo}=y;

        end   
        % The above steps devoted to forward propagation
        % Computing Delta Wj
        for n=1:length(y_vec{TOPOLOGY(end)})
        PHI_k(n)= y_vec{TOPOLOGY(end)}(n)*(1-y_vec{TOPOLOGY(end)}(n))*(d(j)-y_vec{TOPOLOGY(end)}(n));
        end  % for the output
        
        for layerNo=1:length(TOPOLOGY)-1
          for nodeNo=1:TOPOLOGY(layerNo)
          tmpVal=y_vec{layerNo};
            for n=1:length(tmpVal)
          PHI_j(layerNo,nodeNo)=tmpVal(nodeNo)*(1-tmpVal(nodeNo));    
            end
          end
        end
    end               %INPUT SIZE
end                   %ITERATION

