//
// Created by ghost on 14.11.2020.
//

#include "huffman.h"


Huffman::Huffman() {
    this->opener();
}

void Huffman::opener() {
    cout<<endl;
    cout<<"\t__    __      ______ "<<endl;
    cout<<"\t| |  / /   / /______\\ \\   | | \\  / | |   | |"<<endl;
    cout<<"\t| | / /    | |      | |   | |\\ \\/ /| |   | |"<<endl;
    cout<<"\t| |/ /     | |      | |   | |  --  | |   | |"<<endl;
    cout<<"\t| |\\ \\     | |      | |   | |      | |   | |"<<endl;
    cout<<"\t| | \\ \\    | |      | |   | |      | |   | |"<<endl;
    cout<<"\t| |  \\ \\   | |______| \\   | |      | |   | |"<<endl;
    cout<<"\t| |   \\ \\  \\ \\______| \\\\  | |      | |   | |"<<endl;
    cout<<"\n\nK@mi soft\ngithub.com:kamighost1\n"<<endl;
}

void Huffman::start(int C, char **V) {
    int mode;
    mode = this->testParam(C, V);
    tree = new tree;
    reader(V[2]);
    sort(alpha.begin(),alpha.end());
    createHuffTree();
    viewAlpha();
    viewGamma();
//    Encode(V[2],"check");
//    Decode("check","decode");
    cout<<"weight: "<<weight/8<<endl;
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
    FILE *in = fopen(input,"r");
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
        this->writeBits(out,gcode);
    }
    fclose(out);
    fclose(in);
}

void Huffman::Decode(char *input, char *output) {
    FILE *in = fopen(input,"rb");
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
        if(code[0]=='0' && code.length()==1){
            code = findGammaChar(code);
            out<<code;
            code = "";
        }else{
            if(ch=='1' && code.length()>=2){
                code = findGammaChar(code);
                out<<code;
                code = "";
            }
        }
    }
    out.close();
    fclose(in);
}

void Huffman::createHuffTree() {
    bool right = 0;
    string code="1";
    for(int i=alpha.size()-1;i>=0;i--){
        if(right){
            addRightBranch(alpha[i].second);
            right = 0;
        }else{
            addLeftBranch(alpha[i].second);
            right = 1;
        }
    }
}

void Huffman::addLeftBranch(char sym) {
    Tree *node;
    string code = "0";
    node = tree;
    if(node->left){
        while(node->left || node->right){
            node = node->left;
            code += "0"; //011110 01110 0110 010 0 11 101 1001 10001
        }
    }

}
void Huffman::addRightBranch(char sym) {
    cout<<"l"<<endl;
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
    cout<<"count simbols:"<<endl;
    for(int i = 0; i<alpha.size();i++){
        cout<<alpha[i].first<<"  '"<<alpha[i].second<<"'"<<endl;
    }
    cout<<endl;
};

void Huffman::viewGamma(){
    cout<<"Gamma alphabet:"<<endl;
    for(int i =0;i<gamma.size();i++){
        cout<<gamma[i].first<<"  '"<<gamma[i].second<<"'"<<endl;
    }
    cout<<endl;
};

void Huffman::writeBits(FILE *out, string msg){
    char buf;
    for(int i =0;i<msg.length();i++){
        buf=msg[i];
        fwrite(&buf,1,1,out);
        weight++;
    }
}
