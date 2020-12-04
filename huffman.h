#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>


typedef struct Tree{
    char symbol;
    char code[20];
    Tree *left;
    Tree *right;
} Tree;

using namespace std;
class Huffman{
public:
    Huffman();
    void start(int C,char **V);
private:
    vector<pair<int,char>> alpha;
    vector<pair<char,string>> gamma;
    float weight=0;
    Tree *tree;
protected:
    void opener();
    int testParam(int C,char **V);
    void Wcounter(char ch);
    void reader(char *name);
    void viewAlpha();
    void viewGamma();
    void createHuffTree();
    void addLeftBranch(char sym);
    void addRightBranch(char sym);
    void Encode(char *input,char *output);
    void Decode(char *input,char *output);
    string findGammaCode(char ch);
    char findGammaChar(string code);
    void writeBits(FILE *out, string msg);
};
