#include "net.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector<unsigned> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);
    Net myNet(topology);
    vector<double> inputVals;
    //myNet.feedForward(inputVals);

    vector<double> targetVals;
    //myNet.feedForward(targetVals);

    vector<double> resultVals;
    //myNet.getResults(resultVals);
    cout<<"Hey there \n";
    return a.exec();
}
