library(network)
m=matrix(c(
 0, 0, 1, 0, 0, 1, 0, 1,
 0, 0, 0, 0, 1, 0, 0, 0,
 0, 0, 0, 0, 0, 1, 1, 1,
 0, 1, 0, 0, 1, 0, 1, 0,
 1, 1, 1, 1, 0, 0, 0, 0,
 1, 1, 0, 0, 0, 0, 0, 1,
 0, 0, 0, 0, 0, 0, 0, 0,
 1, 0, 1, 0, 1, 0, 0, 0), 8,8, byrow=T)
mnw=network(m) 
plot(mnw,displaylabels=T,boxed.labels=F,vertex.cex=5,
 label.pos=5,label.cex=2,edge.lwd=3,arrowhead.cex=3)

lab = c(3, 6, 8, 5, 6, 7, 8, 2, 5, 7, 1, 2, 3, 4, 1, 2, 8, 0, 1, 3, 5)
el = c(1, 2, 2, 3, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12, 13, 12, 14,
       15, 16, 16, 17, 19, 21, 20, 21)
el = matrix(el, ncol=2, byrow=T)
m2nw = network(el, dir=F)

coord = matrix(c(
  1.5, 2,
  2, 4,
  2.5, 2,
  4, 4,
  5.5, 2,
  6, 4,
  6.5, 2,
  8, 4,
  8.5, 2,
  9, 0,
  10, 0,
  10.5, 2,
  11, 0,
  11, 4,
  12.5, 2,
  13, 4,
  13.5, 2,
  15, 4,
  17, 4,
  17, 0,
  17.5, 2), ncol=2, byrow=T)
plot(m2nw,displaylabels=T,boxed.labels=F,vertex.cex=5,
 label.pos=5,label.cex=2,edge.lwd=3,arrowhead.cex=3, label=lab,
 coord=coord, jitter=F, pad=0, xlim=c(5, 14), vertex.sides=20,
 vertex.col=5, ylim=c(0, 7.5))
roots = coord[coord[,2]==4, 1]
text(roots, rep(5.7, 8), paste("node ",1:8,":", sep=""), cex=2)  
text(roots, rep(5, 8), c("6,8,3", "5", "7,6,8", "2,5,7", "4,2,3,1",
                         "2,1,8", "None", "1,5,3"), cex=2)  
for(i in roots-.95) 
  polygon(c(i, i+1.9, i+1.9, i, i), c(6, 6, 3.2, 3.2, 5.5))
text(9.5,7,"Out-edge Lists", cex=2.5)


