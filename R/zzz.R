.onAttach <- function(lib, pkg){
  info <- packageDescription("ergm.userterms")
  packageStartupMessage(
    paste('\nergm.userterms: version ', info$Version, ', created on ', info$Date, '\n',
          'Based on "statnet" project software (statnet.org).\n',
          'For license and citation information see statnet.org/attribution\n',
          'or type citation("ergm.userterms").\n', sep="")
 )
}



