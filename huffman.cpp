//
// Created by ghost on 14.11.2020.
//

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

Huffman::Huffman() {}
void Huffman::start(int C, char **V) {
    int mode;
    mode = this->testParam(C, V);
    reader(V[2]);
    sort(alpha.begin(),alpha.end());
    createHuffTree();
    Encode(V[2],"check");
    Decode("check","decode");
}


int Huffman::testParam(int C,char **V) {
    if(C==1){
        cout<<"its Huffman Encode/Decode programm"<<endl;
        exit(0);
    }
    if(C==2){
        if(!strcmp(V[1],"-h")){
            cout<<"its help"<<endl;
            exit(0);
        }
        if(!strcmp(V[1],"--test")){
            cout<<"its test"<<endl;
            return 0;
        }
    }
    if(C==3){
        if(!strcmp(V[1],"-e")){
            return 1;
        }
        if(!strcmp(V[1],"-d")){
            return 2;
        }
        if(!strcmp(V[1],"-a")){
            return 3;
        }
    }
    cout<<"unknown command. use -h for help"<<endl;
    exit(1);
}
void Huffman::Wcounter(char ch) {
    bool Found = false;
    for(int i=0;i<alpha.size();i++){
        if(alpha[i].second==ch){
            Found = true;
            alpha[i].first = alpha[i].first+1;
            break;
        }
    }
    if(!Found){
        alpha.push_back({1,ch});
    }
}

void Huffman::Encode(char *input ,char *output){
//    ofstream out;
    FILE *in = fopen(input,"r");
//    out.open(output,ofstream::binary);
    FILE *out = fopen(output,"wb");
    if(!in){
        cout<<"file not found!!"<<endl;
        exit(3);
    }
    char ch;
    string gcode;
    while((ch=fgetc(in)) != EOF){
        gcode = findGammaCode(ch);
        if(gcode==""){
            cout<<"error, not found in gamma";
            exit(4);
        }
//        out<<gcode;
        fwrite(gcode.c_str(),sizeof(string),gcode.length(),out);
    }
//    out.close();
    fclose(out);
    fclose(in);
}

void Huffman::Decode(char *input, char *output) {
    FILE *in = fopen(input,"r");
    ofstream out;
    out.open(output);
    if(!in){
        cout<<"file not found!!"<<endl;
        exit(5);
    }
    string code="";
    char ch;
    while((ch=fgetc(in)) != EOF){
        if(ch=='3'){
            cout<<"error"<<endl;
            exit(6);
        }
        code += ch;
//        cout<<"check: "<<code<<endl;
        if(code[0]=='0' && code.length()==1){
            code = findGammaChar(code);
//            cout<<"code: "<<code<<endl;
            out<<code;
            code = "";
        }else{
            if(ch=='1' && code.length()>=2){
                code = findGammaChar(code);
//                cout<<"code: "<<code<<endl;
                out<<code;
                code = "";
            }
        }
    }
    out.close();
    fclose(in);
}

void Huffman::createHuffTree() {
    string code="1";
    for(int i=alpha.size()-1;i>=0;i--){
        if(i==alpha.size()-1){
            gamma.push_back({alpha[i].second, "0"});
        }else if(i>0){
            gamma.push_back({alpha[i].second, (code + "1")});
            code+=(0+'0');
        }else{
            gamma.push_back({alpha[i].second, (code + "1")});
        }
    }
    for(int i =0;i<gamma.size();i++){
        cout<<gamma[i].first<<"  "<<gamma[i].second<<endl;
    }
}

string Huffman::findGammaCode(char ch) {
    for(int i=0;i<gamma.size();i++){
        if(ch == gamma[i].first){
            return gamma[i].second;
        }
    }
    return "";
}

char Huffman::findGammaChar(string code) {
    for(int i=0;i<gamma.size();i++){
        if(code == gamma[i].second){
            return gamma[i].first;
        }
    }
    return '3';
}

void Huffman::reader(char *name) {
    FILE *f = fopen(name,"r");
    if(f==NULL){
        cout<<"file not found!"<<endl;
        exit(2);
    }
    char ch;
    while((ch=fgetc(f)) != EOF){
        Wcounter(ch);
    }
    fclose(f);
}
void Huffman::viewAlpha(){
    for(int i = 0; i<alpha.size();i++){
        cout<<alpha[i].first<<"  "<<alpha[i].second<<endl;
    }
};


int main(int argc, char **argv){
    Huffman a;
    a.start(argc, argv);
    return 0;
}