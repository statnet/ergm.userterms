\name{mindegree-term}
\alias{mindegree}
\alias{ergm-terms}
\alias{InitErgmTerm.mindegree}
\docType{methods}
\title{New Minimum Degree Term for the 'ergm' Package}
\description{
  This is a new term for the \code{\link{ergm}} package 
  that counts the number of nodes in the network with at least
a given degree.
}
%\usage{
%terms.ergm()
\section{The Minimum Degree Term}{
 \describe{
  \item{\code{mindegree(mindeg, by=NULL)}}{\emph{Minimum Degree:}
    The \code{mindeg} argument is an integer. This
term adds one
    network statistic to the model being the 
number of nodes in the network of at least degree \code{mindeg}.
That is, the statistic equals the number of nodes in the
network with \code{mindeg} or more edges.
The optional argument
    \code{by} is a character string giving the name of an
attribute in the
    network's vertex attribute list.
    If this is specified, 
    then degrees are calculated using the subnetwork consisting
of only
    edges whose endpoints have the same value of the \code{by}
attribute.
    This term can only be used with undirected networks.
   }
  }
}
%}
%\arguments{
%\item{\dots}{Specific to the model term.}
%}

\details{
     The function \code{\link{ergm}} is used to fit linear
exponential
  random graph models, in which
  the probability of a given network, \eqn{y}, on a set of nodes
is
  \eqn{\exp\{\theta{\cdot}g(y)\}/c(\theta)}{\exp\{\theta *
g(y)\}/c(\theta)}, where
  \eqn{g(y)} is a vector of network statistics for \eqn{y},
  \eqn{\theta} is a parameter vector of the same
  length and \eqn{c(\theta)} is the
  normalizing constant for the distribution.

  The network statistics \eqn{g(y)} are entered as terms in the
  function call to \code{\link{ergm}}.
  The \code{\link{ergm}} package contains a wide range of terms.
  For the details on the possible
  \code{<model terms>}, see \code{\link{ergm-terms}}.  

  The \code{ergm.userterms} package provides a template for
adding new terms.
  The terms can be used throughout the \code{\link{ergm}} package
  and behave identically to the supplied terms.
}
%\value{\code{\link{ergm}} returns an object of class 'ergm' that is a list.
%}
\references{
Hunter DR, Goodreau SM, Handcock MS (2013).
{\pkg{ergm.userterms}: {A} Template Package for 
Extending \pkg{statnet}}, Journal of Statistical
Software 52(2), 1-25,
URL http://www.jstatsoft.org/v52/i02/.
}
\seealso{statnet, network, ergm, ergm-terms}
\examples{
\donttest{
data(florentine)
summary(flomarriage~mindegree(3))
summary(flomarriage~mindegree(1,by="priorates"))
fit <- ergm(flomarriage~edges+mindegree(1,by="priorates"))
summary(fit)
}
}
\keyword{models}
