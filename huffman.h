#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
class Huffman{
public:
    Huffman();
    void start(int C,char **V);
private:
    vector<pair<int,char>> alpha;
    vector<pair<char,string>> gamma;
protected:
    int testParam(int C,char **V);
    void Wcounter(char ch);
    void reader(char *name);
    void viewAlpha();
    void createHuffTree();
    void Encode(char *input,char *output);
    void Decode(char *input,char *output);
    string findGammaCode(char ch);
    char findGammaChar(string code);
};