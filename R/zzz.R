.onAttach <- function(lib, pkg){
  sm <- statnetStartupMessage("ergm.userterms", c("statnet"), FALSE)
  if(!is.null(sm)) packageStartupMessage(sm)
}



