.onAttach <- function(lib, pkg){
  sm <- statnetStartupMessage("ergm.userterms", c("statnet"), FALSE)
  if(!is.null(sm)){
    packageStartupMessage(sm)
    packageStartupMessage(paste(c(strwrap(paste("NOTE: If you use custom ERGM terms based on ",sQuote("ergm.userterms")," version prior to 3.1, you will need to perform a one-time update of the package boilerplate files (the files that you did not write or modify) from ",sQuote("ergm.userterms")," 3.1 or later. See help('eut-upgrade') for instructions.",sep="")),""),collapse="\n"))
  }
}



