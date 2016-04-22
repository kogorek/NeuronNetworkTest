#include "neuron.h"


neuron::neuron(char iname):name(iname)
{
    std::ifstream fin;
    std::stringstream sstm;
    sstm << "./XP/" << name << ".exp";
    fin.open(sstm.str().c_str());
    if(fin.fail())
    {
        for(int x = 0; x < 30; x++)
            for(int y = 0; y < 30; y++)
                memory[x][y] = 255;
    }
    else
    {
        for(int x = 0; x < 30; x++)
            for(int y = 0; y < 30; y++)
                fin >> memory[x][y];
    }
    output = 0;
    weight = 50;

}

neuron::~neuron()
{
    std::ofstream fout;
    //std::string path = "./XP/" + name;
    std::stringstream sstm;
    sstm << "./XP/"  << name << ".exp";
    fout.open(sstm.str().c_str());
    for(int x = 0; x < 30; x++)
    {
        for(int y = 0; y < 30; y++)
        {
            fout << memory[x][y] << std::endl;
        }
    }
    fout.close();
}
