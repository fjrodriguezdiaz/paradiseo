/*
* <t-moRandImprSelect.cpp>
* Copyright (C) DOLPHIN Project-Team, INRIA Futurs, 2006-2007
* (C) OPAC Team, LIFL, 2002-2008
*
* Sébastien Cahon, Jean-Charles Boisson (Jean-Charles.Boisson@lifl.fr)
*
* This software is governed by the CeCILL license under French law and
* abiding by the rules of distribution of free software.  You can  use,
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info".
*
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited liability.
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or
* data to be ensured and,  more generally, to use and operate it in the
* same conditions as regards security.
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*
* ParadisEO WebSite : http://paradiseo.gforge.inria.fr
* Contact: paradiseo-help@lists.gforge.inria.fr
*
*/
//-----------------------------------------------------------------------------
// t-moRandImprSelect.cpp
//-----------------------------------------------------------------------------

#include <eo>  // EO
#include <mo>  // MO

using std::cout;
using std::endl;

//-----------------------------------------------------------------------------

typedef EO<unsigned int> solution;

class testMove : public moMove <solution>
{
public :
  void operator () (solution & _solution)
  {
    _solution=_solution;
  }
} ;

//-----------------------------------------------------------------------------

int
main()
{
  std::string test_result, test_1, test_2, test_3;
  int value_1, value_2, value_3, return_value;
  
  unsigned int i;

  moRandImprSelect<testMove> selection;

  solution solution;
  
  testMove move;

  cout << "[ moRandImprSelect             ] ==> ";

  selection.init(0);

  test_1="KO";
  
  i=0;

  try
    {
      selection(move, i);
    }
  catch(std::runtime_error e)
    {
      test_1="OK";
    }
  
  value_1=((test_1.compare("KO")==0)?EXIT_FAILURE:EXIT_SUCCESS);

  move(solution);

  test_2=((!selection.update(move, i))?"KO":"OK");
  value_2=((test_2.compare("KO")==0)?EXIT_FAILURE:EXIT_SUCCESS);
  
  selection(move, i);

  i++;

  test_3=((!selection.update(move, i))?"KO":"OK");
  value_3=((test_3.compare("KO")==0)?EXIT_FAILURE:EXIT_SUCCESS);

  selection(move, i);

  test_result=(((test_1.compare("OK")==0)&&(test_2.compare("OK")==0)&&(test_3.compare("OK")==0))?"OK":"KO");
  return_value=(((value_1==EXIT_SUCCESS)&&(value_2==EXIT_SUCCESS)&&(value_3==EXIT_SUCCESS))?EXIT_SUCCESS:EXIT_FAILURE);
  
  cout << test_result << endl;
  return return_value;
}

//-----------------------------------------------------------------------------