#  File R/InitErgmTerm.users.R in package ergm.userterms, part of the Statnet suite
#  of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution
#
#  Copyright 2012-2019 Statnet Commons
#######################################################################
######################################################################
#
# !! USERS: READ THIS FIRST!!
#
# Each term must have its own InitErgmTerm function. You can either
# add all functions to the bottom of this file or have them in 
# separate files (with the extension .R).
#
# See the Terms API vignette in the 'ergm' package for the latest API.
#
######################################################################


#  ------------------------------------------------------------------------- 
#  Sample InitErgmTerm function(s) and annotated documentation
#  --------------------------------------------------------------------------

### Define the name of the term in R; this will be used by
### ergmTerm-general Roxygen2 template to construct the Rd file name
### and other information:
###
#' @templateVar name mindegree
#'
### Provide a title and brief description:
###
#' @title Minimum Degree
#'
#' @description This term adds one network statistic to the model
#'   being the number of nodes in the network of at least degree
#'   `mindeg`. That is, the statistic equals the number of nodes
#'   in the network with `mindeg` or more edges.  This term can
#'   only be used with undirected networks.
#'
### Note the:
###
### * "#" in front of the name; this is to keep R CMD check from
###    parsing the term.
###
### * "binary:" tag specifying that this is a binary version as
###   opposed to a "valued:' one.
###
#' @usage
#' # binary: mindegree(mindeg, by=NULL)
#'
### Parameters, using the same syntax as function documentation.
###
#' @param mindeg an integer giving the 
#'
#' @param by an optional argument specifying a vertex attribute (see
#'   Specifying Vertex attributes and Levels (`?nodal_attributes`) for
#'   details). If this is specified, then degrees are calculated using
#'   the subnetwork consisting of only edges whose endpoints have the
#'   same value of the `by` attribute.
#'
### Import the standard ergmTerm documentation template so that it
### gets indexed in ?ergmTerm.
###
#' @template ergmTerm-general
#'
### Other items, e.g., more details, examples, see also, references.
###
#' @details This `InitErgmTerm` function is for the mindegree term
#'   described by
#'
#'   Hunter DR, Goodreau SM, Handcock MS (2013).  `ergm.userterms`: A
#'   Template Package for Extending `statnet`, *Journal of Statistical
#'   Software* 52(2), 1-25, \doi{10.18637/jss.v052.i02}.
#'
#'   It has been further updated to use the latest \CRANpkg{ergm} APIs
#'   and conventions.
###
### Specify term keywords; see ?ergmKeyword
###
#' @concept undirected
#' @concept categorical nodal attribute
#' @concept frequently-used
###
### No @export!
InitErgmTerm.mindegree <- function(nw, arglist, ...) {
  a <- check.ErgmTerm(nw, arglist, directed=FALSE, bipartite=FALSE,
      varnames = c("mindeg", "by"),
      vartypes = c("numeric", ERGM_VATTR_SPEC),
      required = c(TRUE, FALSE),
      defaultvalues = list(NULL, NULL))
  if(length(a$mindeg) > 1)
    stop("The argument mindeg to mindegree expected a vector of length ",
         "1, but received a vector of length ",length(a$mindeg))
  if (is.null(a$by)) {
    attrflag <- 0
    nodecov <- NULL
    coef.names <- paste("mindegree", a$mindeg, sep="")
  } else {
    attrflag <- 1
    nodecov <- ergm_get_vattr(a$by, nw)
    attrname <- attr(nodecov, "name")
    coef.names <- paste("mindegree.", attrname, a$mindeg, sep="")
    u <- sort(unique(nodecov))
    nodecov <- match(nodecov,u)
  }
  list(name = "mindegree",
      coef.names = coef.names,
      pkgname = "ergm.userterms", # Optional: usually autodetected.
      iinputs = c(attrflag, a$mindeg, nodecov), # Integer inputs
      # inputs =  Numeric (double) inputs (unused)
      dependence = TRUE,
      emptynwstats = (a$mindeg == 0) * network.size(nw)
  )
}






