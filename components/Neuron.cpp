#include <bits/stdc++.h>
#include "Layers.cpp"
using namespace std;

/*Neuron Class begins*/
class Neuron
{
public:
    int neuron_id;
    bool has_bias = false;
    Layer *layer;
    vector<Links *> in, out;
    double when_to_activate = 0.0;
    double input_from_links = 0.0;

    Neuron(int id, Layer *layer, bool has_bias)
    {
        this->has_bias = has_bias;
        this->neuron_id = id;
        this->layer = layer;
    }
    ~Neuron();
    double getOutput()
    {
        if (has_bias)
            return 1;
        return inputs();
    }
    int getNeuronID()
    {
        return neuron_id;
    }
    bool getBias()
    {
        return has_bias;
    }
    double inputs()
    {
        return input_from_links;
    }
    void setInputfromlinks(double input_from_links)
    {
        this->input_from_links = input_from_links;
    }
    void addInputfromlinks(double input_from_links)
    {
        this->input_from_links += input_from_links;
    }
    void addOutLink(Neuron *neuron)
    {
        double weight = rand() % 5;
        out.push_back(new Links(this, neuron, weight));
        neuron->addInLink(out.back());
    }
    void addInLink(Links *links)
    {
        in.push_back(links);
    }
    void setRandomWeights(double range)
    {
        for (Links *x : out)
        {
            x->changeWeight((double(rand()) / double(RAND_MAX) * (range - (-range))) + (-range));
        }
    }
    vector<Links *> getLinks()
    {
        return out;
    }
    vector<double *> getWeights()
    {
        vector<double *> w;
        w.reserve(out.size());
        for (int i = 0; i < out.size(); i++)
        {
            w.push_back(out[i]->getWeight());
        }
        return move(w);
    }
    void changeWeights(vector<double> &weights)
    {
        int cnt = 0;
        for (Links *x : out)
        {
            x->changeWeight(weights[cnt++]);
        }
    }
    void trigger()
    {
        for (Links *x : out)
        {
            x->propagate(getOutput());
        }
    }
};

Neuron::~Neuron()
{
}

/*Neuron Class ends*/