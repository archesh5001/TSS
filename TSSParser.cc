#include "Path.h"
#include "TSSParser.h"
#include "Scanner.h"
#include <cstring>
#include <map>
#include <string>
#include <iostream>
using namespace std;


TSSParser :: TSSParser() {}
TSSParser :: TSSParser(string grammar, bool isFile) {
    //will take care of file input later
      this->grammar = new string(grammar);
}

TSSParser :: ~TSSParser() {
    //delete all the nodes in grammar tree
    delete grammar;
}

bool TSSParser :: validateGrammar() {
    //first check if syntax is correct
    Scanner scanner(*grammar);
    if(!scanner.scan())  {
        cout << "Grammar has syntax errors\n";
        return false;;
    }else {
        
        //check semantics while building tree
        char * grammarC =new char[grammar->size()+1];
        grammarC[grammar->size()]=0;
        memcpy(grammarC,grammar->c_str(),grammar->size()); 
        
        char * tokens;
        string * stok;
        tokens = strtok (grammarC, " <>;=");
        while(tokens != NULL) {
            stok = new string (tokens);
            cout << *stok << endl;
            tokens = strtok(NULL, "<>-=");
            //break;
            delete stok;
        }
    }
    return true;
    
}