\name{ergmuserterms-package}
\alias{ergmuserterms-package}
\alias{ergmuserterms}
\alias{InitErgmTerm.m2star}
\alias{InitErgmTerm.testme}
\alias{InitErgmTerm.absdiffme}
\alias{InitErgmTerm.wtdcensus}
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
\url{http://statnetproject.org}.
A tutorial, support newsgroup, references and links to further
resources are provided there.

When publishing results obtained using this package the original authors
are to be cited as:

Mark S. Handcock, David R. Hunter, Carter T. Butts, Steven M. Goodreau,
and Martina Morris. 2003
\emph{statnet: Software tools for the Statistical Modeling of Network Data}
\cr
\url{http://statnetproject.org}.

We have invested a lot of time and effort in creating the
\code{statnet} suite of packages for use by other researchers.
lease cite it in all papers where it is used.

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

  There are three example terms:
    \item{\code{testme}}{\emph{A clone of Edges}. 
    It is included for purposes of an example.
    This option adds one graph statistic
    equal to the number of edges in the graph.  For undirected
    graphs, \code{edges} is isomorphic to \code{kstar(1)}; for
    digraphs, \code{edges} is isomorphic to both \code{ostar(1)}
    and \code{istar(1)}.  }

    \item{\code{m2star}}{\emph{Mixed 2-stars, aka 2-paths:}
    This option can only be 
    specified with a digraph; for undirected graphs see \code{kstar(2)}. This 
    option adds one statistic to the model, equal to the 
    number of mixed-2-stars in the graph, defined as a 
    pair of edges \eqn{\{(i->j), (j->k)\}.} }
  
    \item{\code{absdiffme(attrname)}}{\emph{A clone of Absolute difference:} 
    It is included for purposes of an example.
    \code{attrname} argument is a character string giving the name of a
    quantitative attribute in the network's vertex attribute list. This term
    adds one network statistic to the model equaling the sum of
    \code{abs(attrname[i]-attrname[j])} for all edges (i,j) in the network. }

   To add a new term you need to (all file references are relative to the 
   package directory).:
     \item{1}{Download the source version of this package. For example,\\
             \code{download.packages("ergmuserterms",destdir=".",type="source", contriburl="http://csde.washington.edu/statnet")}\\
      where \code{destdir} is the directory to save the source
      (e.g., \code{ergmuserterms_2.0.tar.gz}) in.}
     \item{2}{Unpack the source into a directory
              (e.g., on LINUX or the Mac 
               \code{tar -vzxf ergmuserterms_2.0.tar.gz}).}
     \item{3}{Optionally, rename the package name from 
              \code{ergmuserterms} to some something
        more evocative of its use (e.g., \code{myergm}). 
        This can be done using a global change to the files in the 
        directory. Optionally, edit the \code{DESCRIPTION} file to reflect the 
        use of the package.}
     \item{4}{Edit \code{R/InitErgmTerm.users.R} to add 
         \R \code{InitErgmTerm} functions for the new terms.}
     \item{5}{Edit \code{src/changestats.c} to add \code{C}
         functions (like the examples in the file) to compute the 
         new change statistics.}
     \item{6}{Compile the package using the usual \R
         tools (e.g., \code{R CMD build myergm} and
                      \code{R CMD INSTALL myergm}).}
     \item{7}{Run it! It depends on \pkg{ergm} and \pkg{network}, of course.
            See the example below.}
}
\author{
Mark S. Handcock \email{handcock@stat.washington.edu},\cr
David R. Hunter \email{dhunter@stat.psu.edu},\cr
Carter T. Butts \email{buttsc@uci.edu},\cr
Steven M. Goodreau \email{goodreau@u.washington.edu}, and\cr
Martina Morris \email{morrism@u.washington.edu}

Maintainer: Mark S. Handcock \email{handcock@stat.washington.edu}
}
\references{
Admiraal R, Handcock MS (2007).
 {\pkg{networksis}: Simulate bipartite graphs with fixed
  marginals through sequential importance sampling}.
 Statnet Project, Seattle, WA.
 Version 1, \url{http://statnetproject.org}.

Bender-deMoll S, Morris M, Moody J (2008).
 {Prototype Packages for Managing and Animating Longitudinal
  Network Data: \pkg{dynamicnetwork} and \pkg{rSoNIA}.}
 {Journal of Statistical Software}, \textbf{24}(7).
 \url{http://www.jstatsoft.org/v24/i07/}.

Butts CT (2006).
 {\pkg{netperm}: Permutation Models for Relational Data}.
 Version 0.2, \url{http://erzuli.ss.uci.edu/R.stuff}.

Butts CT (2007).
 {\pkg{sna}: Tools for Social Network Analysis}.
 Version 1.5, \url{http://erzuli.ss.uci.edu/R.stuff}.

Butts CT (2008).
 {\pkg{network}: {A} Package for Managing Relational Data in \R.}
 {Journal of Statistical Software}, \textbf{24}(2).
 \url{http://www.jstatsoft.org/v24/i02/}.

Butts CT, with help~from David~Hunter, Handcock MS (2007).
 {\pkg{network}: Classes for Relational Data}.
 Version 1.2, \url{http://erzuli.ss.uci.edu/R.stuff}.

Goodreau SM, Handcock MS, Hunter DR, Butts CT, Morris M (2008a).
 {A \pkg{statnet} Tutorial.}
 {Journal of Statistical Software}, \textbf{24}(8).
 \url{http://www.jstatsoft.org/v24/i08/}.

Goodreau SM, Kitts J, Morris M (2008{{b}}).
 {Birds of a Feather, or Friend of a Friend? Using Exponential
  Random Graph Models to Investigate Adolescent Social Networks.}
 {Demography}, \textbf{45}, in press.

Handcock MS (2003{{b}}).
 {\pkg{degreenet}: Models for Skewed Count Distributions Relevant
  to Networks}.
 Statnet Project, Seattle, WA.
 Version 1.0, \url{http://statnetproject.org}.

Handcock MS, Hunter DR, Butts CT, Goodreau SM, Morris M (2003{{a}}).
 {\pkg{ergm}: {A} Package to Fit, Simulate and Diagnose
  Exponential-Family Models for Networks}.
 Statnet Project, Seattle, WA.
 Version 2, \url{http://statnetproject.org}.

Handcock MS, Hunter DR, Butts CT, Goodreau SM, Morris M (2003{{b}}).
 {\pkg{statnet}: Software Tools for the Statistical Modeling of
  Network Data}.
 Statnet Project, Seattle, WA.
 Version 2, \url{http://statnetproject.org}.

Hunter DR, Handcock MS, Butts CT, Goodreau SM, Morris M (2008{{b}}).
 {\pkg{ergm}: {A} Package to Fit, Simulate and Diagnose
  Exponential-Family Models for Networks.}
 {Journal of Statistical Software}, \textbf{24}(3).
 \url{http://www.jstatsoft.org/v24/i03/}.

Krivitsky PN, Handcock MS (2007).
 {\pkg{latentnet}: Latent position and cluster models for
  statistical networks}.
 Seattle, WA.
 Version 2, \url{http://statnetproject.org}.

Morris M, Handcock MS, Hunter DR (2008).
 {Specification of Exponential-Family Random Graph Models:
  Terms and Computational Aspects.}
 {Journal of Statistical Software}, \textbf{24}(4).
 \url{http://www.jstatsoft.org/v24/i04/}.
}
\seealso{statnet, network, ergm, ergm-terms}
\examples{
data(sampson)
fit <- ergm(samplike~m2star)
summary(fit)

fit <- ergm(samplike~m2star + testme)
summary(fit)

samplike \%v\% "ng" <- match(samplike \%v\% "group", c("Loyal","Outcasts","Turks"))
fit <- ergm(samplike~absdiffme("ng"))
summary(fit)

summary(samplike~wtdcensus(rep(1,16)))
summary(samplike~wtdcensus)
}
\keyword{ package }
\keyword{ models }
