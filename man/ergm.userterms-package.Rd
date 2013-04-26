\name{ergm.userterms-package}
\alias{ergm.userterms-package}
\alias{ergm.userterms}
\docType{package}
\title{
User-defined terms used in Exponential Family Random Graph Models
}
\description{
This package contains template code for
user defined (change) statistics that can be used with the
\pkg{statnet} suite of packages (and \pkg{ergm} in particular).
To use this package the \pkg{statnet} 
packages \pkg{ergm} and \pkg{network} are required.

As background, 
\pkg{statnet} is a suite of software packages for statistical network analysis.
The packages implement recent advances in network modeling based on
exponential-family random graph models (ERGM). The components of the package
provide a comprehensive framework for ERGM-based network modeling: tools for
model estimation, for model evaluation, for model-based network simulation, and
for network visualization. This broad functionality is powered by a central
Markov chain Monte Carlo (MCMC) algorithm. The coding is optimized for speed
and robustness.
For detailed information on how to download and install the software,
go to the \code{\link[ergm]{ergm}} website:
\url{statnet.org}.
A tutorial, support newsgroup, references and links to further
resources are provided there.

When publishing results obtained using this package the original authors
are to be cited as:

Mark S. Handcock, David R. Hunter, Carter T. Butts, Steven M. Goodreau,
and Martina Morris. 2003
\emph{statnet: Software tools for the Statistical Modeling of Network Data}
\cr
\url{statnet.org}.

We have invested a lot of time and effort in creating the
\code{statnet} suite of packages for use by other researchers.
Please cite it in all papers where it is used.

For complete citation information, use\cr
\code{citation(package="statnet")}.
}
\section{Creating User-defined terms using this package}{
  The \pkg{statnet} suite of packages allows the
  user to explore a large number of potential models
  for their network data. These can be seen by typing
  \code{help("ergm-terms",package="ergm")} (once the package
  \pkg{ergm} has been installed).  For more information on
  the models and terms see Morris, Handcock, and Hunter (2008).

  The purpose of the package is to allow additional terms can
  be coded up by users (you!) and be used at native speeds with
  \pkg{statnet}. So the suite of packages can be extended with
  minimal work by the user. In addition the core packages are
  not altered and so the new packages benefit from improvements
  to the core suite.
  
  The process of creating new terms is explained in depth by the 
  document entitled 
  by Hunter, Goodreau, and Handcock (2010) that is 
  found in the inst/doc directory of this package.

   In brief, to add a new term you need to (all file references are relative to the 
   package directory).:

   1.  Download the source version of this package. For example, in R use
   
             \code{download.packages("ergm.userterms", destdir=".", type="source")}
             
      where \code{destdir} is the directory to save the source
      (e.g., \code{ergm.userterms_3.0.tar.gz}) in.

     2.  Unpack the source into a directory
              (e.g., on Linux or the Mac 
               \code{tar -vzxf ergm.userterms_3.0.tar.gz}).

     3.  Optionally, rename the package name from 
              \code{ergm.userterms} to some something
        more evocative of its use (e.g., \code{myergm}). 
        This can be done using a global change to the files in the 
        directory. Optionally, edit the \code{DESCRIPTION} file to reflect the 
        use of the package.

     4.  Edit \code{R/InitErgmTerm.users.R} to add 
         \R \code{InitErgmTerm} functions for the new terms.

     5.  Edit \code{src/changestats.users.c} to add \code{C}
         functions (like the example already in that file) to compute the 
         new change statistics.

     6.  Compile the package using the usual \R
         tools (e.g., \code{R CMD build myergm} and
                      \code{R CMD INSTALL myergm}).

     7.  Run it! It depends on \pkg{ergm} and \pkg{network}, of course.
            See the example below.
}
\references{
Hunter DR, Goodreau SM, Handcock MS (2013).
{\pkg{ergm.userterms}: {A} Template Package for 
Extending \pkg{statnet}}, Journal of Statistical
Software 52(2), 1-25,
URL http://www.jstatsoft.org/v52/i02/.
}
\seealso{statnet, network, ergm, ergm-terms}
\examples{
data(faux.mesa.high)
summary(faux.mesa.high~mindegree(2))
fit <- ergm(faux.mesa.high~mindegree(2), estimate="MPLE")
summary(fit)
}
\keyword{ package }
\keyword{ models }
