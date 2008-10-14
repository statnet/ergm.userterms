#include "changestats.h"

/*  !!USERS : READ ME!! */
/*  Just add your change statistics to the bottom of this file */

/*  Here are some examples */
/*  Be sure to read the comments in changestats.h */


/* This routine is here as a test -- its functionality is equivalent */
/* to d_edges. */
CHANGESTAT_FN(d_testme) {
  int edgeflag, i;
  Vertex h, t;
  
  CHANGE_STAT[0] = 0.0;
  for (i=0; i < ntoggles; i++)
    {
      edgeflag = IS_OUTEDGE(h = heads[i], t = tails[i]);
      CHANGE_STAT[0] += edgeflag ? - 1 : 1;
      TOGGLE_IF_MORE_TO_COME(i);
    }
  UNDO_PREVIOUS_TOGGLES(i);
}


/* This routine is here as a test -- its functionality is equivalent */
/* to d_m2star in "ergm". */

CHANGESTAT_FN(d_m2star) {
  Vertex h, t;
  int hid, tod, change;
  int i, edgeflag, backedgeflag;
    
  CHANGE_STAT[0] = 0.0;

  for (i=0; i < ntoggles; i++)
    {
      /*  edgeflag is 1 if the edge from heads[i] to tails[i]  */
      /*   exists and will disappear */
      /*  edgeflag is 0 if the edge does not exist */
      edgeflag = IS_OUTEDGE(h = heads[i], t = tails[i]);
      backedgeflag = (EdgetreeSearch(t, h, nwp->outedges) != 0);

      hid = IN_DEG[h]; 
      tod = OUT_DEG[t];
      change = hid + tod - 2*backedgeflag; 
      CHANGE_STAT[0] += (edgeflag ? -change : change); 

      TOGGLE_IF_MORE_TO_COME(i);
    }
  UNDO_PREVIOUS_TOGGLES(i);
}


/*****************                       
 changestat: d_absdiffme
*****************/

CHANGESTAT_FN(d_absdiffme) { 
  double change;
  Vertex h, t;
  int i;

  CHANGE_STAT[0] = 0.0;
  FOR_EACH_TOGGLE(i) {
    h = heads[i]; 
    t = tails[i];
    change = fabs(INPUT_ATTRIB[h-1] - INPUT_ATTRIB[t-1]);
    CHANGE_STAT[0] += IS_OUTEDGE(h,t) ? -change : change;
    TOGGLE_IF_MORE_TO_COME(i); /* Needed in case of multiple toggles */
  }
  UNDO_PREVIOUS_TOGGLES(i); /* Needed on exit in case of multiple toggles */
}


