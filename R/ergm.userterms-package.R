#' User-defined terms used in Exponential Family Random Graph Models
#' 
#' This non-CRAN package contains template code for user defined (change) statistics
#' that can be used with the \CRANpkg{statnet} suite of packages (and \CRANpkg{ergm} in
#' particular). To use this package the \CRANpkg{statnet} packages \CRANpkg{ergm} and
#' \CRANpkg{network} are required.
#' 
#' As background, \CRANpkg{statnet} is a suite of software packages for statistical
#' network analysis. The packages implement recent advances in network modeling
#' based on exponential-family random graph models (ERGM). The components of
#' the package provide a comprehensive framework for ERGM-based network
#' modeling: tools for model estimation, for model evaluation, for model-based
#' network simulation, and for network visualization. This broad functionality
#' is powered by a central Markov chain Monte Carlo (MCMC) algorithm. The
#' coding is optimized for speed and robustness. For detailed information on
#' how to download and install the software, go to the \code{\link[ergm]{ergm}}
#' website: \url{statnet.org}. A tutorial, support newsgroup, references and
#' links to further resources are provided there.
#' 
#' We have invested a lot of time and effort in creating the \code{statnet}
#' suite of packages for use by other researchers. Please cite it in all papers
#' where it is used.
#' 
#' For complete citation information, use\cr
#' \code{citation(package="ergm")}.
#' 
#' 
#' @section Creating User-defined terms using this package: The \CRANpkg{statnet}
#' suite of packages allows the user to explore a large number of potential
#' models for their network data. These can be seen by typing
#' \code{?ergmTerm} (once the package \CRANpkg{ergm} has
#' been installed).  For more information on the models and terms see Morris,
#' Handcock, and Hunter (2008).
#' 
#' The purpose of the package is to allow additional terms can be coded up by
#' users (you!) and be used at native speeds with \CRANpkg{statnet}. So the suite
#' of packages can be extended with minimal work by the user. In addition the
#' core packages are not altered and so the new packages benefit from
#' improvements to the core suite.
#' 
#' The process of creating new terms is explained in depth by the
#' document entitled by Hunter, Goodreau, and Handcock (2013) that is
#' found in the \file{inst/doc} directory of this package. While that
#' article is still valid, API changes in \CRANpkg{ergm} 4.0 have
#' simplified the term implementations and added new capabilities; see
#' the *Terms API* vignette in \CRANpkg{ergm}.
#' 
#' In brief, to add a new term you need to (all file references are relative to
#' the package directory):
#' 
#' 1.  Download the source version of this package, currently hosted
#' at \url{https://github.com/statnet/ergm.userterms}, e.g.,
#' \url{https://github.com/statnet/ergm.userterms/archive/refs/heads/master.zip}.
#' 
#' 2.  Unpack the source into a directory.
#' 
#' 3.  Optionally, rename the package name from \code{ergm.userterms} to some
#' something more evocative of its use (e.g., \code{myergm}).  This can be done
#' using a global change to the files in the directory. Optionally, edit the
#' \file{DESCRIPTION} file to reflect the use of the package.
#' 
#' 4.  Edit \file{R/InitErgmTerm.users.R} to add \R \code{InitErgmTerm}
#' functions for the new terms.
#' 
#' 5.  Edit \file{src/changestats.users.c} to add \code{C} functions (like the
#' example already in that file) to compute the new change statistics.
#' 
#' 6.  Compile the package using the usual \R tools (e.g., \code{R CMD build
#' myergm} and \code{R CMD INSTALL myergm}).
#' 
#' 7.  Run it! It depends on \CRANpkg{ergm} and \CRANpkg{network}, of course.  See the
#' example below.
#' @seealso [ergm-package], [network-package], [`ergmTerm`]
#' @references
#'   Hunter DR, Goodreau SM, Handcock MS (2013).  `ergm.userterms`: A
#'   Template Package for Extending `statnet`, *Journal of Statistical
#'   Software* 52(2), 1-25, \doi{10.18637/jss.v052.i02}.
#' @keywords package models
"_PACKAGE"





#' Updating \pkg{\link[ergm.userterms:ergm.userterms-package]{ergm.userterms}}
#' prior to 3.1
#' 
#' Explanation and instructions for updating custom ERGM terms developed prior
#' to the release of \code{\link[=ergm-package]{ergm}} version 3.1 (including
#' 3.0--999 preview release) to be used with versions 3.1 or later.
#' 
#' 
#' @section Explanation:
#' 
#' \pkg{\link[ergm.userterms:ergm.userterms-package]{ergm.userterms}} ---
#' Statnet's mechanism enabling users to write their own ERGM terms --- comes
#' in a form of an R package containing files for the user to put their own
#' statistics into (i.e., \file{changestats.user.h}, \file{changestats.user.c},
#' and \file{InitErgmTerm.user.R}), as well as some boilerplate to support them
#' (e.g., \file{ergm_edgetree.h}, \file{edgetree.c}, \file{ergm_changestat.h},
#' \file{changestat.c}, etc.).
#' 
#' Although the
#' \pkg{\link[ergm.userterms:ergm.userterms-package]{ergm.userterms}} API is
#' stable, recent developments in ergm have necessitated the boilerplate files
#' in \pkg{ergm.userterms} to be updated.  To reiterate, the user-written statistic
#' source code (\file{changestats.user.h}, \file{changestats.user.c}, and
#' \file{InitErgmTerm.user.R}) can be used without modification, but other
#' files that came with the package need to be changed.
#' 
#' To make things easier in the future, we have implemented a mechanism (using
#' R's LinkingTo API, in case you are wondering) that will keep things in sync
#' in releases after the upcoming one. However, for the upcoming release, we
#' need to transition to this new mechanism.
#' @section Instructions:
#' 
#' The transition entails the following steps. They only need to be done once
#' for a package. Future releases will keep up to date automatically.
#' 
#' \enumerate{
#' 
#' \item Download the up-to-date
#' \pkg{\link[ergm.userterms:ergm.userterms-package]{ergm.userterms}}
#' source \url{https://github.com/statnet/ergm.userterms}, e.g.,
#' \url{https://github.com/statnet/ergm.userterms/archive/refs/heads/master.zip}
#' and unpack it.
#' 
#' \item Copy the R and C files defining the user-written terms (usually
#' \file{changestats.user.h}, \file{changestats.user.c}, and
#' \file{InitErgmTerm.user.R}) and \emph{only} those files from the old
#' \pkg{\link[ergm.userterms:ergm.userterms-package]{ergm.userterms}} source
#' code to the new. Do \emph{not} copy the boilerplate files that you did not
#' modify.
#' 
#' \item If you have customized the package \file{DESCRIPTION} file (e.g., to
#' change the package name) or \file{zzz.R} (e.g., to change the startup
#' message), modify them as needed in the updated
#' \pkg{\link[ergm.userterms:ergm.userterms-package]{ergm.userterms}}, but do
#' \emph{not} simply overwrite them with their old versions.
#' 
#' \item Make sure that your \code{\link[=ergm-package]{ergm}} installation is
#' up to date, and rebuild
#' \pkg{\link[ergm.userterms:ergm.userterms-package]{ergm.userterms}}.
#' 
#' }
#' @name eut-upgrade
NULL
