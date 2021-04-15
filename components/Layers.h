#ifndef LAYERS_H
#define LAYERS_H

#include <bits/stdc++.h>
#include "./Neuron.h"
class NeuralNetwork;
class Neuron;
class Layer;

using namespace std;

/*Layer Class begins*/

class Layer
{
public:
    int layer_id;
    NeuralNetwork *network;
    vector<Neuron *> neuron;
    map<string, double> properties;
    Layer() {}
    Layer(int layer_id, NeuralNetwork *network, map<string, double> properties)
    {
        this->layer_id = layer_id;
        this->network = network;
        this->properties = properties;

        initLayer();
    }
    ~Layer();
    void initLayer()
    {
        neuron.clear();
        for (int i = 0; i < properties["size"]; i++)
        {
            neuron.push_back(new Neuron(i + 1, this, properties["has_bias"]));
        }
    }
    int getLayerID()
    {
        return layer_id;
    }
    void setRandomWeights(double range)
    {
        for (Neuron *x : neuron)
        {
            x->setRandomWeights(range);
        }
    }
    vector<vector<Links *>> getLinks()
    {
        vector<vector<Links *>> w;
        // w.reserve(neuron.size());
        for (Neuron *x : neuron)
        {
            w.emplace_back(x->getLinks());
        }
        return w;
    }
    vector<vector<double *>> getWeights()
    {
        vector<vector<double *>> w;
        w.reserve(neuron.size());
        for (Neuron *x : neuron)
        {
            w.emplace_back(x->getWeights());
        }
        return w;
    }
    vector<Neuron *> getNeurons()
    {
        return neuron;
    }
    void changeWeights(vector<vector<double>> &weights)
    {
        int cnt = 0;
        for (Neuron *x : neuron)
        {
            x->changeWeights(weights[cnt++]);
        }
    }
    void trigger()
    {
        for (Neuron *x : neuron)
        {
            x->trigger();
        }
    }
    void getConnections(Layer *next)
    {
        for (Neuron *x : neuron)
        {
            for (Neuron *y : next->neuron)
            {
                if (!y->getBias())
                    x->addOutLink(y);
            }
        }
    }
    vector<double> getOutput()
    {
        vector<double> m;
        m.reserve(neuron.size());
        for (Neuron *x : neuron)
        {
            m.push_back(x->getOutput());
        }
        return m;
    }
    vector<Neuron *> getNeurons()
    {
        return neuron;
    }
};
Layer::~Layer()
{
}

/*Layer Class ends*/
#endif