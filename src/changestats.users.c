#include "changestats.h"

CHANGESTAT_FN(d_mindegree) {
	Vertex h, t, node3;
	int i, mindeg, hdeg, tdeg;
	Edge e;
	int attrflag;
	double h_nodecov, t_nodecov;

	ZERO_ALL_CHANGESTATS(i);
	FOR_EACH_TOGGLE(i) {
		h = heads[i]; t = tails[i];
		attrflag = INPUT_PARAM[0];
		mindeg = INPUT_PARAM[1];
		if(attrflag==0){
			hdeg = IN_DEG[h]+OUT_DEG[h];
			tdeg = IN_DEG[t]+OUT_DEG[t];
			CHANGE_STAT[0] += IS_OUTEDGE(h,t) ? 
				- (hdeg==mindeg) - (tdeg==mindeg) :
				(hdeg==mindeg-1) + (tdeg==mindeg-1);
		}else{
			h_nodecov = INPUT_PARAM[h+1];
			t_nodecov = INPUT_PARAM[t+1];
			if (h_nodecov == t_nodecov) {
				hdeg = 0;
				STEP_THROUGH_OUTEDGES(h, e, node3) { /* step through outedges of head */
					if(INPUT_PARAM[node3+1]==h_nodecov){++hdeg;}
				}

				STEP_THROUGH_INEDGES(h, e, node3) { /* step through inedges of head */
					if(INPUT_PARAM[node3+1]==h_nodecov){++hdeg;}
				}
				tdeg = 0;
				STEP_THROUGH_OUTEDGES(t, e, node3) { /* step through outedges of tail */
					if(INPUT_PARAM[node3+1]==t_nodecov){++tdeg;}
				}
				STEP_THROUGH_INEDGES(t, e, node3) { /* step through inedges of tail */
					if(INPUT_PARAM[node3+1]==t_nodecov){++tdeg;}
				}
				CHANGE_STAT[0] += IS_OUTEDGE(h,t) ? 
					- (hdeg==mindeg) - (tdeg==mindeg) :
					(hdeg==mindeg-1) + (tdeg==mindeg-1);
			}else{
				CHANGE_STAT[0] = 0;
			}
		}
		TOGGLE_IF_MORE_TO_COME(i); /* Needed in case of multiple toggles */
	}
	UNDO_PREVIOUS_TOGGLES(i); /* Needed on exit in case of multiple toggles */
}
