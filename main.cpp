#include <bits/stdc++.h>
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
};

Links::~Links()
{
}

/*Links Class ends*/

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
};

Neuron::~Neuron()
{
}

/*Neuron Class ends*/

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
    }
    ~Layer();
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
        w.reserve(neuron.size());
        for (Neuron *x : neuron)
        {
            w.push_back(x->getLinks());
        }
        return w;
    }
    vector<vector<double *>> getWeights()
    {
        vector<vector<double *>> w;
        w.reserve(neuron.size());
        for (Neuron *x : neuron)
        {
            w.push_back(x->getWeights());
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
};
Layer::~Layer()
{
}

/*Layer Class ends*/

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