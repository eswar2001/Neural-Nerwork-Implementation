#ifndef NEURALNETWORKS_H
#define NEURALNETWORKS_H

#include "Layers.h"
#include "Neuron.h"

class Neuron;
class Layer;
class NeuralNetwork;

#include <bits/stdc++.h>
using namespace std;

#define RANDOM_MAX_WT 10

/*NeuralNetwork Class begins*/
class NeuralNetwork
{
public:
    vector<Layer *> layers;
    NeuralNetwork();
    ~NeuralNetwork();
    void setInput(vector<double> in)
    {
        for (int i = 0; i < in.size(); i++)
        {
            layers[0]->neuron[i]->setInputfromlinks(in[i]);
        }
    }
    void addLayer(map<string, double> properties)
    {
        layers.push_back(new Layer(layers.size() + 1, this, properties));
    }
    vector<Layer *> getLayers()
    {
        return layers;
    }
    void trigger()
    {
        for (Layer *x : layers)
        {
            x->trigger();
        }
    }
    vector<double> getOutput()
    {
        return (layers.back())->getOutput();
    }
    void getConnections()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i]->getConnections(layers[i + 1]);
        }
    }
    vector<Layer *> getLayers()
    {
        return layers;
    }
    void changeWeights(vector<vector<vector<double>>> &weights)
    {

        for (int i = layers.size() - 1; i >= 0; i--)
        {
            if (weights[i].size() != 0)
                layers[i]->changeWeights(weights[i]);
        }
    }
    vector<vector<vector<double *>>> getWeights()
    {
        vector<vector<vector<double *>>> w;
        w.reserve(layers.size() - 1);
        for (Layer *x : layers)
        {
            w.push_back(x->getWeights());
        }
        return move(w);
    }
    vector<vector<vector<Links *>>> getLinks()
    {
        vector<vector<vector<Links *>>> w;
        w.reserve(layers.size() - 1);
        for (Layer *x : layers)
        {
            w.push_back(x->getLinks());
        }
        return move(w);
    }
    void setRandomWeights()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i]->setRandomWeights(RANDOM_MAX_WT);
        }
    }
    vector<double> predict(vector<double> &in)
    {
        setInput(in);
        trigger();
        return getOutput();
    }
};

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::~NeuralNetwork()
{
}

/*NeuralNetwork Class ends*/
#endif