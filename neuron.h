#ifndef NEURON_H
#define NEURON_H


class neuron
{
public:
    char name;
    int weight;
    int output;
    int input[30][30];
    int memory[30][30];
    neuron(char iname);
    ~neuron();
};

#endif // NEURON_H
