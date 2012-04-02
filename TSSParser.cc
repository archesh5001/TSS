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
        tokens = strtok (grammarC, "<>-=");
        while(tokens != NULL) {
            stok = new string (tokens);
            cout << *stok << endl;
            tokens = strtok(NULL, "<>-=");
            //buildTree(*stok);
            delete stok;
        }
    }
    return true;
    
}


void TSSParser :: buildTree(string &str) {
    //There are 4 possible strings that come in here
    //1. onjectName : objectType
    //2. ;
    //3. [];
    //4. [](*pointerName);
    
    //type 1
    if(str.compare(";") == 0) {
        //find the next child in map
        return;
    } else if(str.compare("[];") == 0) {
        //this means that previous node that we built
        //is list. Set the list flag
        cout << "It is [];\n";
    }else {
        bool isHead = false;
        if(str.at(0) != '[') {
            //we have type 1
            string :: iterator iter;
            string temp ("");
            for(iter = str.begin(); iter < str.end(); iter++){
                if(*iter == ':') {
                    //store objectName and start extracting flag type
                    if(grammarTree == NULL) {
                        isHead = true;
                         grammarTree = new Node();
                        grammarTree->name = temp;
                    }else {
                        current = grammarTree->child;
                        while(current->next != NULL)
                            current = current->next;
                        current = new Node();
                        current->name = temp;
                    }
                    temp = "";
                    iter++;
                } 
                
                temp += *iter;
            }
            if(isHead)
                 grammarTree->objectType = temp;
            else
                current->objectType = temp;
        }
    }
}



