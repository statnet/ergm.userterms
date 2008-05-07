#ifndef EDGETREE_H
#define EDGETREE_H

#include <math.h>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

#define MAXEDGES 1000000 /* eventually use of MAXEDGES will be phased out */
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)<(b) ? (b) : (a))

/*typedef unsigned int Vertex;
typedef unsigned int Edge; */
typedef int Vertex;
typedef int Edge;



/*  TreeNode is a binary tree structure, which is how the edgelists 
    are stored.  The root of the tree for vertex i will be inedges[i]
    or outedges[i].  inedges[0] and outedges[0] are unused, since the
    index 0 will indicate no link.  Indices are long unsigned integers,
    which means networks can contain 2^32-1= 4294967295 edges (enough to
    hold all edges in a 92682-vertex undirected network or a 65536-vertex
    directed network, assuming no multiple edges or loops), though for this
    MAXEDGES must be adjusted accordingly.
*/
typedef struct TreeNodestruct {
  Vertex value;      /*  the vertex at the other end of this edge  */
  Edge parent;   /*  parent of this node in the tree (0 for root) */
  Edge left;     /*  left child (0 if none)  */
  Edge right;    /*  right child (0 if none) */
} TreeNode;

/* Dur_Inf is a structure containing information about durations of
edges in a network structure.
*/ 
typedef struct Dur_Infstruct {
  int MCMCtimer;
  int *lasttoggle;
/*  double mean_edge_duration; This is probably not a good idea */
} Dur_Inf;



/* Network is a structure containing all essential elements
   of a given network; it is a slightly rewritten version of the old Gptr,
   with some changes of awkard things, deletion of unnecessary things, and
   a new name more reflective of what it does!

   Some of the fields in a Network structure are:
   inedges and outedges are arrays of TreeNode that are used to 
     store all of the incoming and outgoing edges, respectively. 
   directed_flag is 1 or 0, depending on whether or not the 
     network is directed. 
   next_inedge and next_outedge are continually updated to give
     the smallest index of an edge object not being used.  
   outdegree[] and indegree[] are continually updated to give
     the appropriate degree values for each vertex.  These should
     point to Vertex-vectors of length nnodes.  
   value:  optional value(s) associated with this network 
*/
typedef struct Networkstruct {
  TreeNode *inedges;
  TreeNode *outedges;
  int directed_flag;
  Vertex bipartite;  
  Vertex nnodes;
  Edge nedges;
  Edge next_inedge;
  Edge next_outedge;
  Vertex *indegree;
  Vertex *outdegree;
  double *value;  
  Dur_Inf duration_info;
  Edge maxedges;
} Network;

Network NetworkInitialize(Vertex *heads, Vertex *tails, Edge nedges,
        Edge maxedges,
			  Vertex nnodes, int directed_flag, Vertex bipartite,
			  int lasttoggle_flag);
Network NetworkInitializeD(double *heads, double *tails, Edge nedges,
         Edge maxedges,
			   Vertex nnodes, int directed_flag, Vertex bipartite,
			   int lasttoggle_flag);
void NetworkDestroy(Network *nwp);
Edge EdgetreeSearch (Vertex a, Vertex b, TreeNode *edges);
Edge EdgetreeSuccessor (TreeNode *edges, Edge x);
Edge EdgetreeMinimum (TreeNode *edges, Edge x);
int ToggleEdge (Vertex head, Vertex tail, Network *nwp);
int ToggleEdgeWithTimestamp (Vertex head, Vertex tail, Network *nwp);
int AddEdgeToTrees(Vertex head, Vertex tail, Network *nwp);
void AddHalfedgeToTree (Vertex a, Vertex b, TreeNode *edges, Edge next_edge);
void UpdateNextedge (TreeNode *edges, Edge *nextedge, Network *nwp);
int DeleteEdgeFromTrees(Vertex head, Vertex tail, Network *nwp);
int DeleteHalfedgeFromTree(Vertex a, Vertex b, TreeNode *edges,
		     Edge *next_edge);
int FindithEdge (Vertex *head, Vertex *tail, Edge i, Network *nwp);
void printedge(Edge e, TreeNode *edges);
void InOrderTreeWalk(TreeNode *edges, Edge x);
void NetworkEdgeList(Network *nwp);
Edge EdgeTree2EdgeList(Vertex *heads, Vertex *tails, Network *nwp, Edge nmax);
Edge DesignMissing (Vertex a, Vertex b, Network *mnwp);

#endif









