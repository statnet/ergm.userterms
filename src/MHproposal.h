#ifndef MHproposal_H
#define MHproposal_H

#include "edgetree.h"
#include "R_ext/Rdynload.h"

typedef struct DegreeBoundstruct {
  int attrcount;
  int fBoundDegByAttr;
  int *attribs;
  int *maxout;
  int *minout;
  int *maxin;
  int *minin;
} DegreeBound;

DegreeBound* DegreeBoundInitialize(int *attribs, int *maxout, int *maxin, 
			   int *minout, int *minin, int condAllDegExact, 
			   int attriblength, Network *nwp);

void DegreeBoundDestroy(DegreeBound *bd);


#define NO_EDGE       0x00 /*these four used in realocateWithReplacement */
#define OLD_EDGE      0x01 
#define NEW_EDGE      0x02 
#define CAN_IGNORE    (OLD_EDGE | NEW_EDGE)  

/* Maximum tries (up to an MH-specific constant). */
#define MAX_TRIES 5000

/* MH_* proposal failed codes. */
/* Tails: */
#define MH_FAILED 0
/* Heads: */
#define MH_UNRECOVERABLE 0
#define MH_IMPOSSIBLE 1
#define MH_UNSUCCESSFUL 2

/* "Quit" threshold for unsuccessful proposals as a fraction of steps. */
#define MH_QUIT_UNSUCCESSFUL 0.05


/* Macros to test for logical inequality (XOR) and logical equality (XNOR). */
#define XOR(a,b) (((a)==0) != ((b)==0))
#define XNOR(a,b) (((a)==0) == ((b)==0))

/*  Notes on MHproposal type:
   An MH proposal function must take two arguments:  a pointer to an 
   MHproposal structure, which holds all the information regarding the
   MH proposal; and a pointer to an array of Network structures, which 
   contain the network(s).  
   
   Each MH proposal function should check to see whether ntoggles==0
   upon being called.  If so, the MH proposal function should change
   the value of ntoggles to be the largest possible number of toggles
   required, so that this amount of memory can be allocated.
*/


/* *** don't forget tail-> head */

typedef struct MHproposalstruct {
  void (*func)(struct MHproposalstruct*, Network*);
  Edge ntoggles;
  Vertex *toggletail;
  Vertex *togglehead;
  double logratio;
  int status;
  DegreeBound *bd;
  Network **discord;
  double *inputs; /* may be used if needed, ignored if not. */
  /* int multiplicity; Is this needed? I removed all references to
       'multiplicity' everywhere */
} MHproposal;


void MH_init(MHproposal *MHp, 
	     char *MHproposaltype, char *MHproposalpackage, 
	     double *inputs,
	     int fVerbose,
	     Network *nwp, 
	     int *attribs, int *maxout, int *maxin, 
	     int *minout, int *minin, int condAllDegExact, 
	     int attriblength);

void MH_free(MHproposal *MHp);

int CheckTogglesValid(MHproposal *MHp, Network *nwp);
int CheckConstrainedTogglesValid(MHproposal *MHp, Network *nwp);
unsigned int dEdgeListSearch(Vertex tail, Vertex head, double *el);
#endif 



