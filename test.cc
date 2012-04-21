/*
 * Test.cc
 *
 *  Created on: Mar 7, 2012
 *      Author: Archesh
 */

#include "TSSParser.h"
#include <iostream>
using namespace std;

int main() {


    TSSParser parser("<StructureObject:SO> -= <Object1:SO>(*object1Ref) <Object2:SO>[](*Object2Ref) <Object2Ref:RO>[];"
            "<Object1:SO> -= <Object1Base:DA>[] <Object1Structure:SO>(*object1StructRef);"
            "<Object2:SO> -= <Object2Base:S>;"
            "<Object1Structure:SO> -= <Object1StructureBase:IA>[];"
             , false);

    if (parser.validateGrammar()) {
        vector<PathComponent> vect;
        if (parser.storeAccessCode("StructureObject.Object1.Object1Structure.Object1StructureBase[5]", vect)) {
            //print the vector
            cout << "Path: ";
            for (int i = 0; i < vect.size(); i++) {
                cout << vect.at(i).label;
                if (i != vect.size() - 1)
                    cout << "->";
            }

            cout << "\nAccess codes: ";
            for (int i = 0; i < vect.size(); i++) {
                cout << vect.at(i).accessCode;
                if (i != vect.size() - 1)
                    cout << ":";
            }
            cout << endl;
        }
        
        Path * p = new Path(vect);
        cout << "Is BO? " << parser.isBO(p) << endl;
        cout << "Is SO? " << parser.isSO(p) << endl;
        cout << "Is List? " << parser.isList(p) << endl;
        cout << "Is RO? " << parser.isRef(p) << endl;
        cout << "Type: " << parser.getBOType(p) << endl;
        delete p;
    }

    return 0;
}
