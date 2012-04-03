#include "Path.h"
#include "TSSParser.h"
#include "Scanner.h"
#include <cstring>
#include <map>
#include <string>
#include <iostream>
using namespace std;

TSSParser::TSSParser() {
}

TSSParser::TSSParser(string grammar, bool isFile) {
    //will take care of file input later
    this->grammar = new string(grammar);
}

TSSParser::~TSSParser() {
    //delete all the nodes in grammar tree
    delete grammar;
}

bool TSSParser::validateGrammar() {
    //first check if syntax is correct
    Scanner scanner(*grammar);
    if (!scanner.scan()) {
        cout << "Grammar has syntax errors\n";
        return false;
        ;
    } else {

        //check semantics while building tree
        char * grammarC = new char[grammar->size() + 1];
        grammarC[grammar->size()] = 0;
        memcpy(grammarC, grammar->c_str(), grammar->size());

        char * tokens;
        string * stok;
        tokens = strtok(grammarC, "<>-=");
        while (tokens != NULL) {
            stok = new string(tokens);
            cout << *stok << endl;
            tokens = strtok(NULL, "<>-=");
            buildTree(*stok);
            delete stok;
        }
        delete grammarC;
    }
    cout << "vector size: " << nodes.size() << endl;
    print();
    return true;

}

void TSSParser::buildTree(string &str) {
    //There are 4 possible strings that come in here
    //1. onjectName : objectType
    //2. ;
    //3. [];
    //4. [](*pointerName);


    //type 1
    if (str.compare(";") == 0) {
        Node * temp = head;
        cout << "Headt: " << temp->name << endl;
        temp = head->child;
        do{
            cout << "Childt: " << temp->name << endl;
            temp = temp->next;
        }while(temp != NULL);
        
        //store curent head in vector
        Node * myHead = new Node;
        copy (myHead, head);
        nodes.push_back(myHead);
        head = NULL;

    } else if (str.compare("[];") == 0) {
        //this means that previous node that we built
        //is list. Set the list flag
        //cout << "It is [];\n";
        Node * myHead = new Node;
        copy (myHead, head);
        nodes.push_back(myHead);
        head = NULL;
       // nodes.push_back(head);
    } else {
        //There are 2 cases here.
        //case 1 and 4
        if (str.at(0) == '[') {
            //cout << "Ignoring " << str << " for now\n";
            Node * myHead = new Node;
            copy (myHead, head);
            nodes.push_back(myHead);
            head = NULL;
            //nodes.push_back(head);
        } else {
            if (head == NULL) {
                cout << "creating head\n";
                head = new Node();
                head->no_of_children = 0;
                current = head;
            } else {
                //create new child node
                current = new Node();
                if (head->no_of_children == 0) {
                    cout << "creating first child\n";
                    //only create 1 pointer to first child
                    head->child = current;
                    current->parent = head;
                    current->next = NULL;
                    ++head->no_of_children;
                } else {
                    cout << "Creating > 1 child\n";
                    //link child with its sibling
                    Node * temp = head->child;
                    while (temp->next != NULL)
                        temp = temp->next;
                    temp->next = current;
                    current->parent = head;
                    ++head->no_of_children;
                }
            }
            //extract name and type from the given string
            string temp;
            string::iterator iter;
            for (iter = str.begin(); iter < str.end(); iter++) {
                if (*iter == ':') {
                    //this is our name
                    current->name = temp;
                    cout << "Current name is: " << current->name << endl;
                    temp = "";
                    ++iter;
                }
                temp += *iter;
            }

            //this is our type
            current->objectType = temp;
            cout << "Current type is: " << current->objectType << endl;
        }
    }
}

void TSSParser::print() {
    while(!nodes.empty()) {
        head = nodes.front();
        cout << "Head: " << head->name << " Type: " << head->objectType 
                << " Children: " << head->no_of_children << endl;
        current = head->child;
        do {
            cout << "Child: " << current->name << " Type: " << current->objectType << endl; 
            current = current->next;  
        }while(current != NULL);
        nodes.pop_front();
    }
}

void TSSParser :: copy(Node *a, Node *b) {
    a->child = b->child;
    a->children = b->children;
    a->name = b->name;
    a->next = b->next;
    a->no_of_children = b->no_of_children;
    a->objectType = b->objectType;
    a->parent = b->parent;
    a->pos = b->pos;
    a->type = b->type;
    a->visited = b->visited;
}
