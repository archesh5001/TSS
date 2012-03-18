/*
 * Test.cc
 *
 *  Created on: Mar 7, 2012
 *      Author: Archesh
 */

#include "Scanner.h"
#include <iostream.h>

int main () {
	
	Scanner scan (
        "<Region1:SO> := <regionLabel:S><face:SO><index:SO>;"
        "<face:SO> := <faceLabel:S><outerCycle:SO><holeCycle:SO>[];"
        "<index:SO> := <indexLabel:S><SegmentIndex:RO>[];"
        "<outerCycle:SO> := <segment:DA> [] (*segmentIndex);"
        "<holeCycle:SO> := <segment:B>[];");
        if(!scan.scan())
            cout << "Parse Failed\n";
        else
            cout << "Grammar is valid!\n";
	return 0;
}
