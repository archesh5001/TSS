#include "Path.h"

Path :: Path() {
    
}

Path :: ~Path() {
    
}

Path :: Path(vector <PathComponent> vector) {
    for(int i = 0; i < vector.size(); i++)
        vPath.push_back(vector.at(i));
}
