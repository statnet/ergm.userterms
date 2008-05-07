#include <string.h>
#include "model.h"

/*****************
  void ModelDestroy
******************/
void ModelDestroy(Model *m)
{  
  int i;

  for(i=0; i < m->n_terms; i++)
    free(m->dstatarray[i]);
  free(m->dstatarray);
  free(m->termarray);
  free(m->workspace); 
  free(m);
}

/*****************
 int ModelInitialize

 Allocate and initialize the ModelTerm structures, each of which contains
 all necessary information about how to compute one term in the model.
*****************/
Model* ModelInitialize (char *fnames, char *sonames, double *inputs,
			int n_terms) {
  int i, j, k, l, offset;
  ModelTerm *thisterm;
  char *fn,*sn;
  Model *m;
  
  m = (Model *) malloc(sizeof(Model));
  m->n_terms = n_terms;
  m->termarray = (ModelTerm *) malloc(sizeof(ModelTerm) * n_terms);
  m->dstatarray = (double **) malloc(sizeof(double *) * n_terms);
  m->n_stats = 0;
  for (l=0; l < n_terms; l++) {
      thisterm = m->termarray + l;

      /* fnames points to a single character string, consisting of the names
      of the selected options concatenated together and separated by spaces.
      This is passed by the calling R function.  These names are matched with
      their respective C functions that calculate the appropriate statistics. 
      Similarly, sonames points to a character string containing the names
      of the shared object files associated with the respective functions.*/
      for (; *fnames == ' ' || *fnames == 0; fnames++);
      for (i = 0; fnames[i] != ' ' && fnames[i] != 0; i++);
      fnames[i] = 0;
      for (; *sonames == ' ' || *sonames == 0; sonames++);
      for (j = 0; sonames[j] != ' ' && sonames[j] != 0; j++);
      sonames[j] = 0;
      /* Extract the required string information from the relevant sources */
      if((fn=(char *)malloc(sizeof(char)*(i+3)))==NULL){
        Rprintf("Error in ModelInitialize: Can't allocate %d bytes for fn.\n",
		sizeof(char)*(i+3));
	exit(0);
      }
      fn[0]='d';
      fn[1]='_';
      for(k=0;k<i;k++)
        fn[k+2]=fnames[k];
      fn[i+2]='\0';
      /* fn is now the string 'd_[name]', where [name] is fname */
/*      Rprintf("fn: %s\n",fn); */
      if((sn=(char *)malloc(sizeof(char)*(j+1)))==NULL){
        Rprintf("Error in ModelInitialize: Can't allocate %d bytes for sn.\n",
		sizeof(char)*(j+1));
	exit(0);
      }
      sn=strncpy(sn,sonames,j);
      sn[j]='\0';
      
      /*  Most important part of the ModelTerm:  A pointer to a
      function that will compute the change in the network statistic of 
      interest for a particular edge toggle.  This function is obtained by
      searching for symbols associated with the object file with prefix
      sn, having the name fn.  Assuming that one is found, we're golden.*/ 
      thisterm->func = 
	(void (*)(int, Vertex*, Vertex*, ModelTerm*, Network*))
	R_FindSymbol(fn,sn,NULL);
      if(thisterm->func==NULL){
        Rprintf("Error in ModelInitialize: could not find function %s in "
                "namespace for package %s.\n",fn,sn);
	exit(0);
      }      

      /*Clean up by freeing sn and fn*/
      free((void *)fn);
      free((void *)sn);

      /*  Now process the values in model$option[[optionnumber]]$inputs;
          See comments in InitErgm.r for details.    */
      offset = (int) *inputs++;  /* Set offset for attr vector */
/*      Rprintf("offsets: %f %f %f %f %f\n",inputs[0],inputs[1],inputs[2], */
/*		         inputs[3],inputs[4],inputs[5]); */
      thisterm->nstats = (int) *inputs++; /* Set # of statistics returned */
/*      Rprintf("l %d offset %d thisterm %d\n",l,offset,thisterm->nstats); */
      if (thisterm->nstats <= 0)
	{ /* Must return at least one statistic */
	  Rprintf("Error in ModelInitialize:  Option %s cannot return %d \
               statistics.\n", fnames, thisterm->nstats);
	  return NULL;
	}
      /*  Update the running total of statistics */
      m->n_stats += thisterm->nstats; 
      m->dstatarray[l] = (double *) malloc(sizeof(double) * thisterm->nstats);
      thisterm->dstats = m->dstatarray[l];  /* This line is important for
                                               eventually freeing up malloc'ed
					       memory, since thisterm->dstats
					       can be modified but 
					       m->dstatarray[l] cannot be.  */
      thisterm->ninputparams = (int) *inputs++; /* Set # of inputs */
      /* thisterm->inputparams is a ptr to inputs */
      thisterm->inputparams = (thisterm->ninputparams ==0) ? 0 : inputs; 
      
      thisterm->attrib = inputs + offset; /* Ptr to attributes */
      inputs += thisterm->ninputparams;  /* Skip to next model option */

      /*  The lines above set thisterm->inputparams to point to needed input
      parameters (or zero if none) and then increments the inputs pointer so
      that it points to the inputs for the next model option for the next pass
      through the loop. */

      fnames += i;
      sonames += j;
    }
  
  m->workspace = (double *) malloc(sizeof(double) * m->n_stats);
  for(i=0; i < m->n_stats; i++)
    m->workspace[i] = 0.0;
  return m;
}


/***********************
 DegreeBound* DegreeBoundInitialize
************************/
DegreeBound* DegreeBoundInitialize(int *attribs, int *maxout, int *maxin,
	          	   int *minout, 
			   int *minin, int condAllDegExact,  int attriblength,
			   Network *nwp)
{
  int i,j;
  DegreeBound *bd;
  

  bd = (DegreeBound *) malloc(sizeof(DegreeBound));

  bd->fBoundDegByAttr = 0;
  bd->attrcount = condAllDegExact ? 1 : attriblength / nwp->nnodes;
  bd->attribs = (int *) malloc(sizeof(int) * attriblength);
  bd->maxout  = (int *) malloc(sizeof(int) * attriblength);
  bd->maxin   = (int *) malloc(sizeof(int) * attriblength);
  bd->minout  = (int *) malloc(sizeof(int) * attriblength);
  bd->minin   = (int *) malloc(sizeof(int) * attriblength);
  
  /* bound by degree by attribute per node */
  if (bd->attrcount)
    {
      /* flag that we have data here */
      bd->fBoundDegByAttr = 1;
      
      if (!condAllDegExact)
	{
	  for (i=1; i <= nwp->nnodes; i++)
	    for (j=0; j < bd->attrcount; j++)
	      {
		bd->attribs[i-1 + j*nwp->nnodes] = 
		  attribs[(i - 1 + j*nwp->nnodes)];
		bd->maxout[i-1 + j*nwp->nnodes] =  
		  maxout[(i - 1 + j*nwp->nnodes)];
		bd->maxin[i-1 + j*nwp->nnodes] =  
		  maxin[(i - 1 + j*nwp->nnodes)];
		bd->minout[i-1 + j*nwp->nnodes] =  
		  minout[(i - 1 + j*nwp->nnodes)];
		bd->minin[i-1 + j*nwp->nnodes] =   
		  minin[(i - 1 + j*nwp->nnodes)];
	      }
	}
      else  /* condAllDegExact == TRUE */
	{
	  /* all ego columns get values of current in and out degrees;
	   max and min ego columns for (each of in and out) get same value; */
	  for (i=1;i<=nwp->nnodes;i++)
	    bd->maxout[i-1] = bd->minout[i-1] = nwp->outdegree[i];
	  
	  for (i=1;i<=nwp->nnodes;i++)
	    bd->maxin[i-1] = bd->minin[i-1] = nwp->indegree[i];
	}
    }
  return bd;
}


/*****************
  void DegreeBoundDestroy
******************/
void DegreeBoundDestroy(DegreeBound *bd)
{  
  free(bd->attribs); 
  free(bd->maxout); 
  free(bd->minout); 
  free(bd->maxin); 
  free(bd->minin); 
  free(bd);
}

/*****************
 int ModelTermHamming
*****************/
int ModelTermHamming (char *fnames, int n_terms) {
  int i, k, l;
  char *fn;
  
  for (l=0; l < n_terms; l++) {
      /* fnames points to a single character string, consisting of the names
      of the selected options concatenated together and separated by spaces.
      This is passed by the calling R function.  These names are matched with
      their respective C functions that calculate the appropriate statistics. 
      Similarly, sonames points to a character string containing the names
      of the shared object files associated with the respective functions.*/
      for (; *fnames == ' ' || *fnames == 0; fnames++);
      for (i = 0; fnames[i] != ' ' && fnames[i] != 0; i++);
      fnames[i] = 0;
      /* Extract the required string information from the relevant sources */
      if((fn=(char *)malloc(sizeof(char)*(i+1)))==NULL){
        Rprintf("Error in ModelInitialize: Can't allocate %d bytes for fn.\n",
		sizeof(char)*(i+3));
	exit(0);
      }
      for(k=0;k<i;k++){
        fn[k]=fnames[k];
      }
      fn[i]='\0';
      /* fn is now the string '[name]', where [name] is fname */

/*      Rprintf("l=%d ",l); */
/*        Rprintf("%s",fn); */
/*      for(k=0;k<=i;k++){ */
/*        Rprintf("%s",fn[k]); */
/*      } */
/*      Rprintf("\n"); */

      if(strncmp(fn,"hamming",7)==0){return(l+1);}
      /*Clean up by freeing sn and fn*/
      free((void *)fn);

      /*  The lines above set thisterm->inputparams to point to needed input
      parameters (or zero if none) and then increments the inputs pointer so
      that it points to the inputs for the next model option for the next pass
      through the loop. */

      fnames += i;
    }
  
  return(0);
}

/*****************
 int ModelTermFormation
*****************/
int ModelTermFormation (char *fnames, int n_terms) {
  int i, k, l;
  char *fn;
  
  for (l=0; l < n_terms; l++) {
      /* fnames points to a single character string, consisting of the names
      of the selected options concatenated together and separated by spaces.
      This is passed by the calling R function.  These names are matched with
      their respective C functions that calculate the appropriate statistics. 
      Similarly, sonames points to a character string containing the names
      of the shared object files associated with the respective functions.*/
      for (; *fnames == ' ' || *fnames == 0; fnames++);
      for (i = 0; fnames[i] != ' ' && fnames[i] != 0; i++);
      fnames[i] = 0;
      /* Extract the required string information from the relevant sources */
      if((fn=(char *)malloc(sizeof(char)*(i+1)))==NULL){
        Rprintf("Error in ModelInitialize: Can't allocate %d bytes for fn.\n",
		sizeof(char)*(i+3));
	exit(0);
      }
      for(k=0;k<i;k++){
        fn[k]=fnames[k];
      }
      fn[i]='\0';
      /* fn is now the string '[name]', where [name] is fname */

/*      Rprintf("l=%d ",l); */
/*        Rprintf("%s",fn); */
/*      for(k=0;k<=i;k++){ */
/*        Rprintf("%s",fn[k]); */
/*      } */
/*      Rprintf("\n"); */

      if(strncmp(fn,"formation",9)==0){return(l+1);}
      /*Clean up by freeing sn and fn*/
      free((void *)fn);

      /*  The lines above set thisterm->inputparams to point to needed input
      parameters (or zero if none) and then increments the inputs pointer so
      that it points to the inputs for the next model option for the next pass
      through the loop. */

      fnames += i;
    }
  
  return(0);
}
/*****************
 int ModelTermDissolve
*****************/
int ModelTermDissolve (char *fnames, int n_terms) {
  int i, k, l;
  char *fn;
  
  for (l=0; l < n_terms; l++) {
      /* fnames points to a single character string, consisting of the names
      of the selected options concatenated together and separated by spaces.
      This is passed by the calling R function.  These names are matched with
      their respective C functions that calculate the appropriate statistics. 
      Similarly, sonames points to a character string containing the names
      of the shared object files associated with the respective functions.*/
      for (; *fnames == ' ' || *fnames == 0; fnames++);
      for (i = 0; fnames[i] != ' ' && fnames[i] != 0; i++);
      fnames[i] = 0;
      /* Extract the required string information from the relevant sources */
      if((fn=(char *)malloc(sizeof(char)*(i+1)))==NULL){
        Rprintf("Error in ModelInitialize: Can't allocate %d bytes for fn.\n",
		sizeof(char)*(i+3));
	exit(0);
      }
      for(k=0;k<i;k++){
        fn[k]=fnames[k];
      }
      fn[i]='\0';
      /* fn is now the string '[name]', where [name] is fname */

/*      Rprintf("l=%d ",l); */
/*        Rprintf("%s",fn); */
/*      for(k=0;k<=i;k++){ */
/*        Rprintf("%s",fn[k]); */
/*      } */
/*      Rprintf("\n"); */

      if(strncmp(fn,"dissolve",9)==0){return(l+1);}
      /*Clean up by freeing sn and fn*/
      free((void *)fn);

      /*  The lines above set thisterm->inputparams to point to needed input
      parameters (or zero if none) and then increments the inputs pointer so
      that it points to the inputs for the next model option for the next pass
      through the loop. */

      fnames += i;
    }
  
  return(0);
}
