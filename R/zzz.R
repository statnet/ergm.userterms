.onAttach <- function(lib, pkg){
  sm <- statnetStartupMessage("ergm.userterms", FALSE, FALSE)
  if(!is.null(sm)) packageStartupMessage(sm)
}



