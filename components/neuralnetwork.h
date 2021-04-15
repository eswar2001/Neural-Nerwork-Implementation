#include <bits/stdc++.h>
#include "./Layers.h"
using namespace std;

/*NeuralNetwork Class begins*/
class NeuralNetwork
{
public:
    vector<Layer *> layers;

    NeuralNetwork();
    ~NeuralNetwork();
    void addLayer(map<string, double> properties)
    {
        layers.push_back(new Layer(layers.size() + 1, this, properties));
    }
    vector<Layer *> getLayers()
    {
        return layers;
    }
};

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::~NeuralNetwork()
{
}

/*NeuralNetwork Class ends*/