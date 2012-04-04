#include "Path.h"
#include "TSSParser.h"
#include "Scanner.h"
#include <cstring>
#include <map>
#include <string>
#include <iostream>
using namespace std;

TSSParser::TSSParser() {
    childCounter = 0;
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

        //store curent head in vector
        Node * myHead = new Node;
        copy(myHead, head);
        nodes.push_back(myHead);
        head = NULL;
        childCounter = 0;
    } else if (str.compare("[];") == 0) {
        //this means that previous node that we built
        //is list. Set the list flag
        //cout << "It is [];\n";
        current->isList = true;
        Node * myHead = new Node;
        copy(myHead, head);
        nodes.push_back(myHead);
        head = NULL;
        childCounter = 0;
    } else {
        //There are 2 cases here.
        //case 1 and 4
        if (str.at(0) == '[') {
            //first this means that current object is list object
            current->isList = true;
            //extract pointer name
            string::iterator iter;
            string temp = "";
            for (iter = str.begin(); iter < str.end(); iter++) {
                if (*iter == '[' || *iter == ']' || *iter == '(' || *iter == '*')
                    continue;
                if (*iter == ')')
                    break;
                temp += *iter;
            }

            //got the name, now create new node for it
            current = new Node();
            if (head->no_of_children == 0) {
                head->child = current;
                current->parent = head;
                current->pos = childCounter;
                current->name = temp;
                current->objectType = "RO";
                ++childCounter;
                ++head->no_of_children;
            } else {
                Node * tempN = head->child;
                while (tempN->next != NULL)
                    tempN = tempN->next;

                current->name = temp;
                current->objectType = "RO";
                current->pos = childCounter;
                current->parent = head;

                tempN->next = current;
                ++head->no_of_children;
                ++childCounter;
            }

            //check if last value of string is ;
            if (str.at(str.size() - 1) == ';') {
                //we are done building current tree. 
                Node * myHead = new Node;
                copy(myHead, head);
                nodes.push_back(myHead);
                head = NULL;
                childCounter = 0;
            }
            //nodes.push_back(head);
        } else {
            if (head == NULL) {
                head = new Node();
                head->no_of_children = 0;
                current = head;
            } else {
                //create new child node
                current = new Node();
                if (head->no_of_children == 0) {
                    //only create 1 pointer to first child
                    head->child = current;
                    current->parent = head;
                    current->pos = childCounter;
                    ++head->no_of_children;
                    ++childCounter;
                } else {
                    //link child with its sibling
                    Node * temp = head->child;
                    while (temp->next != NULL)
                        temp = temp->next;
                    temp->next = current;
                    current->parent = head;
                    current->pos = childCounter;
                    ++head->no_of_children;
                    ++childCounter;
                }
            }

            //extract name and type from the given string
            string temp = "";
            string::iterator iter;
            for (iter = str.begin(); iter < str.end(); iter++) {
                if (*iter == ':') {
                    //this is our name
                    current->name = temp;
                    temp = "";
                    ++iter;
                }
                temp += *iter;
            }

            //this is our type
            current->objectType = temp;
            //set appropriate flag
            if ((temp.compare("SO")) == 0)
                current->isSO = true;
            else if ((temp.compare("RO")) == 0)
                current->isRO = true;
            else current->isBO = true;

        }
    }
}

void TSSParser::print() {
    while (!nodes.empty()) {
        head = nodes.front();
        cout << "(Head): " << head->name << " (Type): " << head->objectType
                << " (Children): " << head->no_of_children;
        if (head->isBO) cout << " (BO) ";
        else if (head->isRO) cout << " (RO) ";
        else if (head->isSO) cout << " (SO) ";
        if (head->isList) cout << " (List) ";
        cout << endl;
        current = head->child;
                     
        do {
            cout << "\t(Child " << current->pos << "): " << current->name << " (Type): " << current->objectType;
            if (current->isBO) cout << " (BO) ";
            else if (current->isRO) cout << " (RO) ";
            else if (current->isSO) cout << " (SO) ";
            if (current->isList) cout << " (List) ";
            cout << endl;
            current = current->next;
        } while (current != NULL);
        nodes.pop_front();
    }
}

void TSSParser::copy(Node *a, Node *b) {
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
    a->isBO = b->isBO;
    a->isList = b->isList;
    a->isRO = b->isRO;
    a->isSO = b->isSO;
}
