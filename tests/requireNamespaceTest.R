#  File tests/requireNamespaceTest.R in package ergm.userterms, part of the Statnet suite
#  of packages for network analysis, http://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  http://statnet.org/attribution
#
#  Copyright 2012-2018 Statnet Commons
#######################################################################
library(network)
requireNamespace('ergm')   #load the namespace, but don't attach the package
# try loading a term from another package namespace
requireNamespace('ergm.userterms')  # NOTE: this now loads ergm normally because it id a Depends of eut
ergm::summary.statistics.formula(network.initialize(2,directed=FALSE)~mindegree(2))
ergm::summary.statistics.formula(network.initialize(2,directed=FALSE)~edges)
