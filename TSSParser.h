/* 
 * File:   TSSParser.h
 * Author: Archesh
 *
 * Created on March 29, 2012, 3:28 PM
 */

#ifndef TSSPARSER_H
#define	TSSPARSER_H



#endif	/* TSSPARSER_H */

#include "Path.h"
#include "Scanner.h"
#include <cstring>
#include <map>
#include <string>

using namespace std;

enum Type {Int, IntAR, Double, DoubleAR, String, Byte};
class TSSParser
{
    private:
        
       struct Node
        {
            string name;                // Name of the node
            string objectType;
            Type type;                  // Data type iif isBO
            int no_of_children;         // No. of chilren
            bool visited;               // Track if SO node has been visited
            int pos;                    // Position in the list of children
            map <string, Node *> children; //pointers to children
            Node * parent;
            Node * child;
            Node * next;
        };

        Node *grammarTree;      // Actual data structure to store the grammar
        Node * current;
        string * grammar;
        
        Node * getParentNode();
       
        void buildTree(string &);


    public:

        TSSParser(); //default constructor
        TSSParser(string grammar, bool isFile); // grammar is a file name if 
                                                // isFile == true
        ~TSSParser();
         bool validateGrammar();   // Validate the given grammar
        
        
        int* genAccessCode(Path p);           // Generate access code

        bool isBO(Path p);
        bool isSO(Path p);
        bool isList(Path p);
        bool isRef(Path p);

        Type getBOType(Path p);
        bool validatePath(Node *, string Name); // Validate a given path
};
