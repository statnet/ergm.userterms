#ifndef CHANGESTATS_H
#define CHANGESTATS_H

#include "edgetree.h"

typedef struct ModelTermstruct {
	void (*d_func)(Edge, Vertex*, Vertex*, struct ModelTermstruct*, Network*);
  void (*s_func)(struct ModelTermstruct*, Network*);
  void (*t_func)(struct ModelTermstruct*, Network*);
	double *attrib; /* Ptr to vector of covariates (if necessary; generally unused) */
	int nstats;   /* Number of change statistics to be returned */
	double *dstats; /* ptr to change statistics returned */
	int ninputparams; /* Number of input parameters passed to function */
	double *inputparams; /* ptr to input parameters passed */
} ModelTerm;


/****************************************************
 Macros to make life easier                         *
 Note:  These things still need to be documented    */ 
/* binomial coefficient macro: */
#define CHOOSE(n,r) ((n)<(r) ? (0) : (my_choose((double)(n),(int)(r)))) 

/* macros that tell whether a particular edge exists */
#define IS_OUTEDGE(a,b) (EdgetreeSearch((a),(b),nwp->outedges)!=0?1:0)
#define IS_INEDGE(a,b) (EdgetreeSearch((a),(b),nwp->inedges)!=0?1:0)
#define IS_UNDIRECTED_EDGE(a,b) IS_OUTEDGE(MIN(a,b), MAX(a,b))

/* macros that may be used to step through all in- or out-edges of a particular
   node.  These are used by the STEP_THROUGH_OUTEDGES and STEP_THROUGH_INEDGES 
   macros. */
#define MIN_OUTEDGE(a) (EdgetreeMinimum(nwp->outedges, (a)))
#define MIN_INEDGE(a) (EdgetreeMinimum(nwp->inedges, (a)))
#define NEXT_OUTEDGE(e) (EdgetreeSuccessor(nwp->outedges,(e)))
#define NEXT_INEDGE(e) (EdgetreeSuccessor(nwp->inedges,(e)))

/* macros to list each of the out-neighbors or in-neighbors, one at a time,
   of node a.  At each iteration of the loop, the variable v equals the node 
   number of the corresponding neighbor. */
#define STEP_THROUGH_OUTEDGES(a,e,v) for((e)=MIN_OUTEDGE(a);((v)=OUTVAL(e))!=0;(e)=NEXT_OUTEDGE(e))
#define STEP_THROUGH_INEDGES(a,e,v) for((e)=MIN_INEDGE(a);((v)=INVAL(e))!=0;(e)=NEXT_INEDGE(e))

/* The OUTVAL and INVAL macros give the "other endnode" of edge e, depending
   on whether it is an in-edge or an out-edge.  Presumably the first endnode
   of the edge is already known in this context. */
#define OUTVAL(e) (nwp->outedges[(e)].value)
#define INVAL(e) (nwp->inedges[(e)].value)

/* macro for changing the status of the (a,b) edge:  Add it if absent, or 
   delete it if present. */
#define TOGGLE(a,b) (ToggleEdge((a),(b),nwp))

#define N_NODES (nwp->nnodes) /* Total number of nodes in the network */
#define OUT_DEG (nwp->outdegree) /* Vector of length N_NODES giving current outdegrees */
#define IN_DEG (nwp->indegree) /* Vector of length N_NODES giving current indegrees */
#define DIRECTED (nwp->directed_flag) /* 0 if network is undirected, 1 if directed */
#define N_EDGES (nwp->nedges) /* Total number of edges in the network currently */

/* 0 if network is not bipartite, otherwise number of first node of second type */
#define BIPARTITE (nwp->bipartite)

/* macros used for internal purposes:  assigning the next in- and out-edge when
   needed */
#define NEXT_INEDGE_NUM (nwp->next_inedge)
#define NEXT_OUTEDGE_NUM (nwp->next_outedge)

/* Vector of change statistics to be modified by the function*/
#define CHANGE_STAT (mtp->dstats)
/* Number of change statistics required by the current term */
#define N_CHANGE_STATS (mtp->nstats)

/* Vector of values passed via "inputs" from R */
#define INPUT_PARAM (mtp->inputparams)
#define N_INPUT_PARAMS (mtp->ninputparams) /* Number of inputs passed */

/* macro to set all changestats to zero at start of function */
#define ZERO_ALL_CHANGESTATS(a) for((a)=0; (a)<N_CHANGE_STATS; (a)++) CHANGE_STAT[(a)]=0.0

/* macros to cycle through all toggles proposed for the current step, then
   make the current toggle in case of more than one proposed toggle, then
   undo all of the toggles to reset the original network state.  */
#define FOR_EACH_TOGGLE(a) for((a)=0; (a)<ntoggles; (a)++)
#define TOGGLE_IF_MORE_TO_COME(a) if((a)+1<ntoggles) TOGGLE(heads[(a)],tails[(a)])
#define UNDO_PREVIOUS_TOGGLES(a) for((a)=ntoggles-2; (a)>=0; (a)--) TOGGLE(heads[(a)],tails[(a)])

/* changestat function prototype */
#define CHANGESTAT_FN(a) void (a) (int ntoggles, Vertex *heads, Vertex *tails, ModelTerm *mtp, Network *nwp)

/* Not often used */
#define INPUT_ATTRIB (mtp->attrib)



/* IMPORTANT: Add your function names here */

CHANGESTAT_FN(d_testme);
CHANGESTAT_FN(d_m2star);
              
#endif
