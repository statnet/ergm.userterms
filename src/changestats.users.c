/*  File src/changestats.users.c in package ergm.userterms, part of the Statnet suite
 *  of packages for network analysis, https://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  https://statnet.org/attribution
 *
 *  Copyright 2012-2019 Statnet Commons
 */
#include "ergm_changestat.h" // change statistics API and helper functions
#include "ergm_storage.h" // storage API and helper functions

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


/*****************
 Square root of triangles: The private storage approach.
*****************/

/* Initializer: store the number of triangles in its private storage. */
I_CHANGESTAT_FN(i_sqrt_triangle) {
  ALLOC_STORAGE(1, double, ntri); /* Allocate private storage for 1 number to store the current number of triangles. */

  /* NB: In an undirected network, tail < head. */
  EXEC_THROUGH_NET_EDGES(tail, head, e1, { /* For each edge (tail < head) in the network... */
      EXEC_THROUGH_FOUTEDGES(head, e, node3, { /* and each edge (head < node3)... */
          *ntri += IS_OUTEDGE(tail, node3); /* a triangle is formed if an edge exists between node3 and tail. */
      });
    });

  /* *ntri now contains the number of triangles in the network. */
}

/* Updater: will be called when toggling (tail, head) with state edgestate is imminent. */
U_CHANGESTAT_FN(u_sqrt_triangle) {
  GET_STORAGE(double, ntri); /* Obtain a pointer to private storage and cast it to the correct type. */
  double change = 0;

  EXEC_THROUGH_EDGES(head, e, node3, { /* For each edge of head... */
      change += IS_UNDIRECTED_EDGE(node3, tail); /* A shared neighbor between tail and head exists if an edge exists between node3 and tail. */
    });

  /* Thus the toggle of (tail, head) will change the triangle statistic. */
  *ntri += edgestate ? -change : change;
}

/* Cleanup; done automatically when STORAGE != NULL, so not needed in this case. */
/* F_CHANGESTAT_FN(f_sqrt_triangle) { */
/*   Free(STORAGE); */
/* } */

/* Change statistic: can refer to its storage. */
C_CHANGESTAT_FN(c_sqrt_triangle) {
  GET_STORAGE(double, ntri); /* Obtain a pointer to private storage and cast it to the correct type. */
  double change = 0;

  EXEC_THROUGH_EDGES(head, e, node3, { /* For each edge of head... */
      change += IS_UNDIRECTED_EDGE(node3, tail); /* A shared neighbor between tail and head exists if an edge exists between node3 and tail. */
    });

  /* Now, we add the new value of the statistic and subtract the old. */
  CHANGE_STAT[0] += sqrt(*ntri + (edgestate ? -change : change)) - sqrt(*ntri);
}


/*****************
 Square root of triangles: The auxiliary approach.
*****************/

/*****
 This is an auxiliary term .triangle which exports the number of
 triangles that other change statistics can use. Notice that it
 doesn't have a c_ or a d_ function.
 *****/

/* Initializer: store the number of triangles in its private storage. */
I_CHANGESTAT_FN(i__triangle) {
  ALLOC_AUX_STORAGE(1, double, ntri); /* Allocate public storage for 1 number to store the current number of triangles. */

  /* NB: In an undirected network, tail < head. */
  EXEC_THROUGH_NET_EDGES(tail, head, e1, { /* For each edge (tail < head) in the network... */
      EXEC_THROUGH_FOUTEDGES(head, e, node3, { /* and each edge (head < node3)... */
          *ntri += IS_OUTEDGE(tail, node3); /* a triangle is formed if an edge exists between node3 and tail. */
      });
    });

  /* *ntri now contains the number of triangles in the network. */
}

/* Updater: will be called when toggling (tail, head) with state edgestate is imminent. */
U_CHANGESTAT_FN(u__triangle) {
  GET_AUX_STORAGE(double, ntri); /* Obtain a pointer to its public storage and cast it to the correct type. */
  double change = 0;

  EXEC_THROUGH_EDGES(head, e, node3, { /* For each edge of head... */
      change += IS_UNDIRECTED_EDGE(node3, tail); /* A shared neighbor between tail and head exists if an edge exists between node3 and tail. */
    });

  /* Thus the toggle of (tail, head) will change the triangle statistic. */
  *ntri += edgestate ? -change : change;
}

/* Cleanup; done automatically when STORAGE != NULL, so not needed in this case. */
/* F_CHANGESTAT_FN(f__triangle) { */
/*   Free(STORAGE); */
/* } */

/*****
 This is a change statistic that expects a the number of triangles in its public storage.
 *****/

C_CHANGESTAT_FN(c_sqrt_triangle_aux) {
  GET_AUX_STORAGE(double, ntri); /* Obtain a pointer to public storage and cast it to the correct type. */
  double change = 0;

  EXEC_THROUGH_EDGES(head, e, node3, { /* For each edge of head... */
      change += IS_UNDIRECTED_EDGE(node3, tail); /* A shared neighbor between tail and head exists if an edge exists between node3 and tail. */
    });

  /* Now, we add the new value of the statistic and subtract the old. */
  CHANGE_STAT[0] += sqrt(*ntri + (edgestate ? -change : change)) - sqrt(*ntri);
}
