#include <QCoreApplication>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#ifndef NET_H
#define NET_H
using namespace std;
class Neuron;
typedef std::vector<Neuron> Layer;
struct Connection{
double weight;
double deltaWeight;
};
class Neuron{
public:
Neuron(unsigned numOutput, unsigned myIndex);
static double randomWeight(void);
void setOutputVal(double val);
double getOutputVal(void);
void feedForward(const Layer &prevLayer);
void calcOutputGradients(double targetVal);
void calcHiddenGradients(const Layer &nextLayer);
void updateInputWeights( Layer &prevLayer);
private:
   static double eta;
   static double alpha;
   double m_outputVal;
   vector<Connection> m_outputWeights;
   unsigned m_myIndex;
   static double transferFunction(double x);
   static double transferFunctionDerivative(double x);
   double m_gradient;
   double sumDOW(const Layer &nextLayer) const;
};

class Net
{
public:
    Net(const std::vector<unsigned> &topology);
    void feedForward(const std::vector<double> &inputVals);
    void backProp(const std::vector<double> &targetVals);
    void getResults(std::vector<double> &resultVals) const;
private:
    std::vector<Layer> m_layers;
    double m_error;
    double m_recentAvergeError;
    double m_recentAverageSmoothingFactor;
};

#endif // NET_H
