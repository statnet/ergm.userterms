#################################################################
#
# !!USERS: READ THIS FIRST!!
#
# This is a file of examples. You can either add all functions to the bottom
# of this file or have them in separate files (with the extension .R).
# There are identical from "statnet"'s perspective.
#
# Each term must have its own InitErgmTerm function. This file contains
# sample functions.
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
#        inputs: Vector of (double-precision numeric) inputs that the 
#                changestat function called d_<name> will require
#                (see WHAT THE C CHANGESTAT FUNCTION RECEIVES below).
#                The default is NULL; no inputs are required.  But it MUST
#                be a vector!  Thus, if some of the inputs are, say, matrices,
#                they must be "flattened" to vectors; if some are categorical
#                character-valued variables, they must be converted to numbers.
#                Optionally, the inputs vector may have an attribute named 
#                "ParamsBeforeCov", which is the
#                number that used to be the old Element 1 (number of input
#                parameters BEFORE the beginning of the covariate vector)                                                         
#                when using the old InitErgm specification; see the comment
#                at the top of the InitErgm.R file for details.  This 
#                ParamsBeforeCov value is only necessary for compatibility 
#                with some of the existing d_xxx changestatistic functions.
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
# WHAT THE C CHANGESTAT FUNCTION RECEIVES:
#                The changestat function, written in C and called d_<name>,
#                where <name> is the character string passed as the required
#                output item called "name" (see above), will have access to
#                the vector of double-precision values created by the 
#                InitErgmTerm function as the optional output item called
#                "inputs".  This array will be called INPUT_PARAMS in the C
#                code and its entries may accessed as INPUT_PARAMS[0],
#                INPUT_PARAMS[1], and so on.  The size of the INPUT_PARAMS 
#                array is equal to N_INPUT_PARAMS, a value which is 
#                automatically set for you and which is available inside the
#                C function.  Thus INPUT_PARAMS[N_INPUT_PARAMS-1] is the last
#                element in the vector. Note in particular that it is NOT 
#                necessary to add the number of inputs to the "inputs" vector
#                since this is done automatically.

#
# A simple example
# This is identical to the "edges" term already in "ergm"
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
# This is identical to the "absdiff" term already in "ergm"
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

# See R/InitErgmTerm.R in the source distribution of the "ergm" 
# package for more examples.

