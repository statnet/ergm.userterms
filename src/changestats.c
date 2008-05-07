#include "changestats.h"

/*  !!USERS : READ ME!! */
/*  Just add your change statistics to the bottom of this file */

/*  Here are some examples */

/* This routine is here as a test -- it's functionality is equivalent */
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


/* This routine is here as a test -- it's functionality is equivalent */
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

/*****************                       
 changestat: d_triadcensus
*****************/

CHANGESTAT_FN(d_wtdcensus) { 
  double change;
  int i, j, edgeflag, a, b, c, d, e, edgecount, t300, 
  t210, t120C, t120U, t120D, t201, t030C, t030T, t111U, 
  t111D, t021C, t021U, t021D, t102, t012, t003;
  Vertex triadtype, node3, h, t;

  ZERO_ALL_CHANGESTATS(i);
  if (DIRECTED) {
/* directed version */
   FOR_EACH_TOGGLE(i) 
    {      
      edgeflag = IS_OUTEDGE(h = heads[i], t = tails[i]);
      t300 = 0;
      t210 = 0;
      t120C = 0;  t120U = 0;   t120D = 0;  t201 = 0;
      t030C = 0;  t030T = 0;   t111U = 0;  t111D = 0;
      t021C = 0;  t021U = 0;   t021D = 0;  t102 = 0;
      t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= N_NODES; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(t, h, nwp->outedges) != 0); 
               b = (EdgetreeSearch(t, node3, nwp->outedges) != 0);
               c = (EdgetreeSearch(node3, t, nwp->outedges) != 0);
               d = (EdgetreeSearch(node3, h, nwp->outedges) != 0);
               e = (EdgetreeSearch(h, node3, nwp->outedges) != 0);
               edgecount = (a + b + c + d + e);

               switch(edgecount)
               {  
               case 0:   /* 012 */
                 ++t012;

               case 1:   /* 021C, 021U, 021D, 102 */
                 {
                     if ((b == 1) || (d == 1))
                       ++t021C;
                     if (c == 1)
                       ++t021U;
                     if (e == 1)
                       ++t021D;
                     if (a == 1)
                       ++t102;
                 }
                 break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
                 {
                     if ((b + d) == 2)       
                       ++t030C;
                     if (((b + e) == 2) || ((c + d) == 2) || ((c + e) == 2))
                       ++t030T;
                     if (((a + b) == 2) || ((a + e) == 2) || ((d + e) == 2))
                       ++t111U;
                     if (((a + c) == 2) || ((a + d) == 2) || ((b + c) == 2))
                       ++t111D;
                 }
                 break;
            
               case 3:   /* 120C, 120U, 120D, 201 */
                 {
                     if (a == 1)
                         {
                            if (((b + d) == 2) || ((c + e) == 2))
                              ++t120C;
                            if ((b + e) == 2)
                              ++t120U;
                            if ((c + d) == 2)
                              ++t120D;
                            if (((b + c) == 2) || ((d + e) == 2))
                              ++t201;
                         }
                     else 
                         {
                            if (b == 1)
                                {
                                    if (((c + d) == 2) || ((d + e) == 2))
                                      ++t120C;
                                    if ((c + e) == 2)
                                      ++t120D;
                                } 
                            else 
                                {
                                    ++t120U;
                                }
                         } 
                 }
                 break;
             
               case 4:   /* 210 */
                 ++t210;
                 break;
             
               case 5:   /* 300 */            
                 ++t300;
                 break;
               }

               switch(edgecount)
               {  
               case 1:   /* 102, 021D, 021U, 021C */
                 --t012;
                 break;
           
               case 2:   /* 030C, 030T, 111U, 111D */ 
                 {
                     if (((a + c) == 2) || ((a + e) == 2) || ((b + d) == 2) || 
                        ((c + e) == 2)) 
                       --t021C;
                     if (((a + d) == 2) || ((b + e) == 2))
                       --t021U;
                     if (((a + b) == 2) || ((c + d) == 2))
                       --t021D;
                     if (((b + c) == 2) || ((d + e) == 2))
                       --t102;
                 } 
                 break;

               case 3:   /* 201, 120D, 120U, 120C */
                 {
                     if (a == 1)
	    	           {
	    	           if ((c + e) == 2)       
                             --t030C;
                           if (((c + d) == 2) || ((b + e) == 2) || ((b + d) == 2))
                             --t030T;
                           if ((b + c) == 2)
                             --t111U;
                           if ((d + e) == 2)
	                      --t111D;
	 	               }
 		             else
 		               {
 		                   if (b == 1)
 		 	                 {
 		 	                   if ((c + d) == 2)
 			                     --t111U;
 			                   if (((c + e) == 2) || ((d + e) == 2))
			                     --t111D;
 		 	                 }
    	    	                   else
		    	                 --t111U;
    		               }
                   }
                   break;
          
               case 4:   /* 210 */
                 {
                     if (a == 1)
                         {
                            if (((b + c + e) == 3) || ((c + d + e) == 3))
                              --t120C;
                            if ((b + c + d) == 3)
                              --t120U;
                            if ((b + d + e) == 3)
                              --t120D;
                         }
                     else 
                         {
                            if ((b + c + d + e) == 4)
                              --t201;
                         } 
                 }
                 break;
              
               case 5:   /* 300 */            
                 --t210;
                 break;
               }
               }
             }    /* ******  move to next node3 ******** */
        }
        else 
          t012 = t012 + (N_NODES - 2);  

          t003 = (t300+t210+t120C+t120U+t120D+t201+t030C+t030T);
	  t003 = t003+(t111U+t111D+t021C+t021U+t021D+t102+t012);

	  change = INPUT_PARAM[0]*t003+INPUT_PARAM[1]*t012; // WARNING incomplete
  	  CHANGE_STAT[0] += edgeflag ? -change : change;
      TOGGLE_IF_MORE_TO_COME(i);
    }
    }else{
/*  undirected */
    FOR_EACH_TOGGLE(i) 
     {      
      edgeflag = IS_OUTEDGE(h = heads[i], t = tails[i]);
      t300 = 0; t201 = 0; t102 = 0; t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= N_NODES; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(MIN(node3,t), MAX(node3,t), nwp->outedges) != 0);
               b = (EdgetreeSearch(MIN(node3,h), MAX(node3,h), nwp->outedges) != 0);
               edgecount = (a + b);

               switch(edgecount)
               {  
               case 0:   /* 012 */
		{
                 ++t102;
                 --t012;
		}
                break;

               case 1:   /* 021C, 021U, 021D, 102 */
		{
                 ++t201;
                 --t102;
		}
                break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
		{
                 ++t300;
                 --t201;
		}
                break;
            
               }
	       }

             }    /* ******  move to next node3 ******** */
        }
        else 
          t102 = t102 + (N_NODES - 2);  

      for(j = 0; j < N_CHANGE_STATS; j++)
        { 
	    triadtype = (Vertex)INPUT_PARAM[j]; 

            switch(triadtype)
            {
                case 1:  t003 = (t102+t201+t300);
 	                 CHANGE_STAT[j] += edgeflag ? -(double)t003 : (double)t003;
		      break;
 	        case 2:  CHANGE_STAT[j] += edgeflag ? -(double)t102 : (double)t102;
		      break;
	        case 3:  CHANGE_STAT[j] += edgeflag ? -(double)t201 : (double)t201;
                      break;
	        case 4:  CHANGE_STAT[j] += edgeflag ? -(double)t300 : (double)t300;
                      break;
            }
        }
     TOGGLE_IF_MORE_TO_COME(i);
     } /* i loop */
    }
    
  UNDO_PREVIOUS_TOGGLES(i);
}
