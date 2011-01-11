/*
* <node.h>
* Copyright (C) DOLPHIN Project-Team, INRIA Futurs, 2006-2008
* (C) OPAC Team, LIFL, 2002-2008
*
* Sebastien Cahon, Alexandru-Adrian Tantar, Clive Canape
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

#ifndef __node_h
#define __node_h

#include <string>
#include <cassert>

#include "../../core/runner.h"

typedef int RANK_ID;

struct Node
  {

    RANK_ID rk; /* Rank */
    std :: string name; /* Host name */
    unsigned num_workers; /* Number of parallel workers */
    int rk_sched; /* rank of the scheduler */
    std :: vector <RUNNER_ID> id_run; /* List of runner def. IDs */
    std :: vector <RUNNER_ID> execution_id_run; /* List of runtime execution runner IDs */
  };

extern Node * my_node;

extern bool isScheduleNode ();

extern int getNodeRank (); /* It gives the rank of the calling process */

extern RANK_ID getRankOfRunner (RUNNER_ID __key);

extern int getNumberOfNodes (); /* It gives the size of the environment (Total number of nodes) */

extern void collectiveCountOfRunners ( unsigned int* num_local_exec_runners, unsigned int* num_exec_runners );

extern int iCollectiveCountOfRunners ( unsigned int* num_local_exec_runners, unsigned int* num_exec_runners );

extern int getRankFromName (const std :: string & __name); /* It gives the rank of the process
							      expressed by its name */

extern void initNode (int * __argc, char * * * __argv);

#endif