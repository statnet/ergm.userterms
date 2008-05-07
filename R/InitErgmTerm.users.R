#################################################################
#
# !!USERS: READ THIS FIRST!!
#
# This is a file of examples. You can either add all functions to the bottom
# of this file or have them in separate files (with the extension .R).
# There are identical from "statnet"'s perspective.
#
# Each term must have its own InitErgmTerm function. This file contains
# eample functions.
#################################################################
#
# InitErgmTerm functions
#
# INPUT:
# Each InitErgmTerm function takes two arguments, nw and arglist,
# which are automatically supplied by ergm.getmodel.  There may be
# other arguments passed by ergm.getmodel, so each InitErgmTerm
# function must also include the ... argument in its list.
#
# OUTPUT:
# Each InitErgmTerm function should return a list.  
#    REQUIRED LIST ITEMS:
#          name: Name of the C function that produces the change
#                statistics.  (Note:  The name will have "d_" 
#                prepended.  For example, the C function for the
#                absdiff change statistics is called "d_absdiff"
#                even though InitErgmTerm.absdiff only returns
#                names = "absdiff")
#    coef.names: Vector of names for the coefficients (parameters)
#                as they will be reported in the output.
#
#    OPTIONAL LIST ITEMS:
#        inputs: Vector of inputs (of type double) that the
#                d_xxx function will require.  Default is NULL.
#        soname: This is the (text) name of the package containing the C function
#                called d_[name].  Default is "ergm"
#    dependence: Logical variable telling whether addition of this term to
#                the model makes the model into a dyadic dependence model.
#                If none of the terms sets dependence==TRUE, then the model
#                is assumed to be a dyadic independence model, which means
#                that the pseudolikelihood estimate coincides with the
#                maximum likelihood estimate.  Default value:  TRUE
#  emptynwstats: Vector of values (if nonzero) for the statistics evaluated
#                on the empty network.  If all are zero for this term, this
#                argument may be omitted.  Example:  If the degree0 term is
#                among the statistics, this argument is necessary because
#                degree0 = number of nodes for the empty network.
#        params: For curved exponential family model terms only: This argument 
#                is a list:  Each item in the list should be named with the
#                corresponding parameter name (one or more of these will
#                probably coincide with the coef.names used when
#                initialfit=TRUE; the initial values of such parameter values
#                will be set by MPLE, so their values in params are ignored.)
#                Any parameter not having its initial value set by MPLE
#                should be given its initial value in this params list.
#           map: For curved exponential family model terms only: A function 
#                that gives the map from theta (the canonical
#                parameters associated with the statistics for this term)
#                to eta (the corresponding curved parameters).  The length
#                of eta is the same as the length of the params list above.
#                This function takes two args:  theta and length(eta).
#      gradient: For curved exponential family model terms only: A function 
#                that gives the gradient of the eta map above.
#                If theta has length p and eta has length q, then gradient
#                should return a p by q matrix.
#                This function takes two args:  theta and length(eta).

#
# A simple example
# This is identical to the "edges" term already in "statnet"
#
InitErgmTerm.testme <- function(nw, arglist, ...) {
  # Construct the output list
  list(name="testme",             #name: required
       coef.names = "testme",     #coef.names: required
       inputs = NULL,             #There are no extra inputs for this term
       soname = "ergmuserterms",  # So "ergm" knows where to find it!
       dependence = FALSE # So we don't use MCMC if not necessary
       )
}
#
# A longer example 
# This is identical to the 2-star term already in "ergm"
InitErgmTerm.m2star <- function(nw, arglist, ...) {
#
  # Check the network and arguments to make sure they are appropriate.
  # make sure that the network is directed
  a <- check.ErgmTerm(nw, arglist, directed=TRUE, bipartite=NULL,
                      varnames = NULL,
                      vartypes = NULL,
                      defaultvalues = list(),
                      required = NULL)
  # Construct the output list
  list(name="m2star",             #name: required
       coef.names = "m2star",     #coef.names: required
       inputs = NULL,             #There are no extra inputs for this term
       soname = "ergmuserterms",  # So "ergm" knows where to find it!
       dependence = TRUE # So we need to use MCMC 
       )
}

#
# An example with covariates
# This is identical to the "absdiff" term already in "statnet"
#

InitErgmTerm.absdiffme <- function(nw, arglist, ...) {
  # Check the network and arguments to make sure they are appropriate.
  a <- check.ErgmTerm(nw, arglist, directed=NULL, bipartite=NULL,
                          varnames = c("attrname"),
                          vartypes = c("character"),
                          defaultvalues = list(NULL),
                          required = c(TRUE))  
  assignvariables(a) # create local variables from names in 'varnames'
  # Process the arguments
  nodecov <- get.node.attr(nw, attrname)
  ### Construct the list to return
  list(name="absdiffme",                                     #name: required
       coef.names = paste("absdiffme", attrname, sep="."), #coef.names: required
       inputs = nodecov,  # We need to include the nodal covariate for this term
       dependence = FALSE # So we don't use MCMC if not necessary
       )
}

#########################################################
InitErgmTerm.wtdcensus<-function (nw, arglist, ...) {
  a=check.ErgmTerm(nw, arglist, directed=NULL, bipartite=NULL,
    varnames = c("w","name"),
    vartypes = c("numeric","character"),
    defaultvalues = list(rep(1,16),""),
    required = c(FALSE,FALSE))
  w<-a$w
  if(length(w)!=16 || !is.numeric(w)){
    stop ("Weights argument to wtdcensus() has needs to be of length 16.", call.=FALSE)
  }

  if(a$name==""){
   coef.names<-"wtdcensus"
  }else{
   coef.names<-paste("wtdcensus",a$name,sep=".")
  }

  # Construct the output list
  list(name="wtdcensus",        #name: required
       coef.names = coef.names, #coef.names: required
       inputs = w,  # We need to include the nodal covariate for this term
       soname = "ergmuserterms", # So "ergm" knows where to find it!
       dependence = TRUE # So we don't use MCMC if not necessary
       )
}
