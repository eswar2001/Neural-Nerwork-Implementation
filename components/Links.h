#ifndef LINKS_H
#define LINKS_H

#include <bits/stdc++.h>
#include "./Neuron.h"

class NeuralNetwork;
class Neuron;
class Layer;

using namespace std;

/*Links Class begins*/
class Links
{
public:
    Neuron *start, *end;
    double weight;
    Links(Neuron *start, Neuron *end, double weight)
    {
        this->end = end;
        this->start = start;
        this->weight = weight;
    }
    ~Links();
    double *getWeight()
    {
        return &weight;
    }
    double getWeightval()
    {
        return weight;
    }
    void changeWeight(double x)
    {
        this->weight = x;
    }
    Neuron *getStart()
    {
        return start;
    }
    Neuron *getEnd()
    {
        return end;
    }
    void propagate(double output)
    {
        getStart()->addInputfromlinks(output * getWeightval());
    }
};

Links::~Links()
{
}

/*Links Class ends*/
#endif