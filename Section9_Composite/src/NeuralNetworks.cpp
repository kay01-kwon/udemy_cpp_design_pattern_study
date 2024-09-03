#include <iostream>
#include <string>
#include <vector>
#include <ostream>

using std::cout;
using std::endl;

using std::string;
using std::vector;

using std::ostream;

struct Neuron;

// CRTP
template <typename Self>
struct SomeNeurons
{
    template <typename T> void connect_to(T &other)
    {
        for(Neuron &from : *static_cast<Self*>(this))
        {
            for(Neuron &to : other)
            {
                from.out_.push_back(&to);
                to.in_.push_back(&from);
            }
        }
    }
};

struct Neuron : SomeNeurons<Neuron>
{
    public:

    Neuron()
    {
        static int id_(1);
        this->id_ = id_++;
    }

    // void connect_to(Neuron &other)
    // {
    //     out_.push_back(&other);
    //     other.in_.push_back(this);
    // }

    Neuron* begin() { return this;}
    Neuron* end() { return this + 1;}

    friend ostream &operator<<(ostream &os, const Neuron &obj)
    {
        for(Neuron* n: obj.in_)
        {
            os << n->id_ << "\t --> \t[" << obj.id_ << "]" << endl;
        }

        for(Neuron* n: obj.out_)
        {
            os << "[" << obj.id_ << "] \t --> \t" << n->id_ << endl;
        }

        return os;
    }

    // private:
    vector<Neuron*> in_, out_;
    unsigned int id_;
};

struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while(count-- > 0)
            push_back(Neuron());
    }

    friend ostream &operator<<(ostream &os, const NeuronLayer &obj)
    {
        for(auto &n: obj)
            os << n;

        return os;
    }

};


int main()
{
    Neuron n1, n2;

    n1.connect_to(n2);

    cout << n1 << n2 << endl;

    NeuronLayer layer1(2), layer2(3);

    n1.connect_to(layer1);
    layer1.connect_to(layer1);
    layer2.connect_to(layer2);

    cout << layer1 << endl;

    return 0;
}