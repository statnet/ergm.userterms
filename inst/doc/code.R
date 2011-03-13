library(ergm.userterms)
set.seed(123)
ntwk <- network(10, directed = FALSE)
lab <- letters[rep(1:2, 5)]
ntwk %v% "labels" <- lab
plot(ntwk, label = lab, label.pos = 5, vertex.cex = 2.5) 
summary(ntwk ~ mindegree(2) + mindegree(2, by = "labels"))

