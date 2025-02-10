/*  File src/changestats.users.c in package ergm.userterms, part of the Statnet suite
 *  of packages for network analysis, https://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  https://statnet.org/attribution
 *
 *  Copyright 2012-2019 Statnet Commons
 */
#include "ergm_changestat.h"

C_CHANGESTAT_FN(c_mindegree) {
  Rboolean attrflag = IINPUT_PARAM[0];
  Vertex mindeg = IINPUT_PARAM[1];
  if(attrflag==0){
    Vertex tdeg = IN_DEG[tail]+OUT_DEG[tail];
    Vertex hdeg = IN_DEG[head]+OUT_DEG[head];
    CHANGE_STAT[0] += edgestate ?
      - (tdeg==mindeg) - (hdeg==mindeg) :
      (tdeg==mindeg-1) + (hdeg==mindeg-1);
  }else{
    unsigned int t_nodecov = IINPUT_PARAM[tail+1];
    unsigned int h_nodecov = IINPUT_PARAM[head+1];
    if (t_nodecov == h_nodecov) {
      Vertex tdeg = 0;
      EXEC_THROUGH_EDGES(tail, e, node3, { /* step through edges of tail */
          if(IINPUT_PARAM[node3+1]==t_nodecov) tdeg++;
        });
      Vertex hdeg = 0;
      EXEC_THROUGH_EDGES(head, e, node3, { /* step through edges of head */
          if(IINPUT_PARAM[node3+1]==h_nodecov) hdeg++;
        });
      CHANGE_STAT[0] += edgestate ?
        - (tdeg==mindeg) - (hdeg==mindeg) :
        (tdeg==mindeg-1) + (hdeg==mindeg-1);
    }else{
      CHANGE_STAT[0] = 0;
    }
  }
}

