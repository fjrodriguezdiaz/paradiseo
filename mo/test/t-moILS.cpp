/*
<t-moILS.cpp>
Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  ue,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.
The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.

ParadisEO WebSite : http://paradiseo.gforge.inria.fr
Contact: paradiseo-help@lists.gforge.inria.fr
*/

#include <iostream>
#include <cstdlib>
#include <cassert>

#include <algo/moTS.h>
#include <algo/moILS.h>
#include "moTestClass.h"
#include <eval/oneMaxEval.h>
#include <continuator/moTrueContinuator.h>
#include <comparator/moSolNeighborComparator.h>
#include <comparator/moNeighborComparator.h>
#include <memory/moSolVectorTabuList.h>
#include <neighborhood/moDummyNeighbor.h>

class dummyMonOp: public eoMonOp<bitVector> {
public:
    bool operator()(bitVector&) {
        return false;
    }
};

int main() {

    std::cout << "[t-moILS] => START" << std::endl;

    bitNeighborhood nh(4);
    oneMaxEval<bitVector> fullEval;
    evalOneMax eval(4);

    moTS<bitNeighbor> ts(nh, fullEval, eval, 1, 7);

    dummyMonOp op;

    //basic constructor
    moILS<bitNeighbor> test1(ts, fullEval, op, 3);

    //simple constructor
    moTrueContinuator<moDummyNeighbor<bitVector> > cont;
    moILS<bitNeighbor> test2(ts, fullEval, op, cont);

    //general constructor
    moMonOpPerturb<bitNeighbor> perturb(op, fullEval);
    moAlwaysAcceptCrit<bitNeighbor> accept;
    moILS<bitNeighbor> test3(ts, fullEval, cont, perturb, accept);

    std::cout << "[t-moILS] => OK" << std::endl;

    return EXIT_SUCCESS;
}

