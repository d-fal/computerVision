#include "net.h"

Net::Net(const std::vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    for(unsigned layerNum=0;layerNum<numLayers;++layerNum){
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size()-1 ? 0 : topology[layerNum+1];
        for(unsigned neuronNum=0;neuronNum<=topology[layerNum];++neuronNum){
        m_layers.back().push_back(Neuron(numOutputs,neuronNum));
        std::cout<<"made a neuron! \n";
        }
        m_layers.back().back().setOutputVal(1.0);
    }
}


Neuron::Neuron(unsigned numOutput, unsigned myIndex){

    for(unsigned c=0;c<numOutput;++c){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight= randomWeight();


    }
m_myIndex = myIndex;
}


double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;
double Neuron::randomWeight(){
    return rand()/RAND_MAX;

}

void Neuron::setOutputVal(double val){
    m_outputVal=val;
}
double Neuron::getOutputVal(){
    return m_outputVal;
}

void Neuron::feedForward(const Layer &prevLayer){
    double 0.0;

    for(unsigned n=0;n<prevLayer.size();++n){
        sum+=prevLayer[n].getOutputVal()* prevLayer[n]*m_outputWeights[m_myIndex].weight;

    }
m_outputVal = Neuron::transferFunction(sum);
}

void Net::feedForward(const std::vector<double> &inputVals){

assert(inputVals.size() == m_layers[0].size()-1);

for( unsigned i=0; i<inputVals.size();++i){
m_layers[0][i].setOutputVal(inputVals[i]);
}
// Forward propagate


}

void Net::backProp(const std::vector<double> &targetVals){
Layer &outputLayer = m_layers.back();
m_error = 0.0;

for (unsigned n=0; n<outputLayer.size()-1;++n){
    double delta = targetVals[n]-outputLayer[n].getOutputVal();
    m_error+=delta*delta;
}

m_error/=outputLayer.size()-1;
m_error=sqrt(m_error);

m_recentAvergeError = (m_recentAvergeError*m_recentAverageSmoothingFactor + m_error)/(m_recentAverageSmoothingFactor + 1.0);

//
for (unsigned n=0 ; n< outputLayer.size() - 1; ++n){
outputLayer[n].calculateGradients(targetVals[n]);
}

for ( unsigned layerNum = m_layers.size() - 2; layerNum>0 ; --layerNum){
    Layer &hiddenLayer = m_layers[layerNum];
    Layer &nextLayer   = m_layers[layerNum+1];

    for (unsigned n=0; n<hiddenLayer.size();++n){
        hiddenLayer[n]=outputLayer[n].calcHiddenGradients(nextLayer);
    }
}

for (unsigned layerNum =m_layers.size()-1; layerNum > 0 ;--layerNum ){
Layer &layer = m_layers[layerNum];
Layer &prevLayer = m_layers[layerNum-1];

for(unsigned n=0;n<layer.size()-1;++n){
    layer[n].updateInputWeights(prevLayer);
}
}

}


double Neuron::transferFunction(double x){
return tanh(x);

}

double Neuron::transferFunctionDerivative(double x){
    return 1.0 - x*x;

}

double Neuron::sumDOW(const Layer &nextLayer) const{
double sum = 0.0;

for (unsigned n =0 ; n<nextLayer.size()-1;++n){
sum+=m_outputWeights[n].weight  * nextLayer[n].m_gradient;
}
return sum;
}
void Neuron::updateInputWeights(Layer &prevLayer){
for(unsigned n = 0; n<prevLayer.size(); ++n){
   Neuron &neuron = prevLayer[n];
   double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;
   double newDeltaWeight =
           eta
           * neuron.getOutputVal()
           * m_gradient
           + alpha
           * oldDeltaWeight;

   neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
   neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
}

}

void Neuron::calcOutputGradients(double targetVal){
    double delta = targetVal - m_outputVal;
    m_gradient = delta* Neuron::transferFunctionDerivative(m_outputVal);

}

void Neuron::calcHiddenGradients(const Layer &nextLayer){

double dow = sumDOW(nextLayer);
m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}


void Net::getResults(std::vector<double> &resultVals) const{

resultVals.clear();

for (unsigned n = 0 ; n< m_layers.back().size()-1;++n){
resultVals.push_back()[n].getOutputVal();
}
}
