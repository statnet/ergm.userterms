library(network)
requireNamespace('ergm')   #load the namespace, but don't attach the package
# try loading a term from another package namespace
requireNamespace('ergm.userterms')  # NOTE: this now loads ergm normally because it id a Depends of eut
ergm::summary.statistics.formula(network.initialize(2,directed=FALSE)~mindegree(2))
ergm::summary.statistics.formula(network.initialize(2,directed=FALSE)~edges)
