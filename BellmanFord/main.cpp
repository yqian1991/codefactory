#include <climits>
#include <iostream>

#define INFINITY 999999999

 typedef struct {
        int source, destination, weight;
 } Edge;

 void BellmanFord(Edge edges[], int edgenum, int nodes, int source)
 {
     int distance[32];
     if (distance == NULL) {
		 std::cout <<"Failed, exit program \n";
       return 0;
     }//end if

     for (int i=0; i < nodes; ++i)
       distance[i] = INFINITY;

     distance[source] = 0;

     for (int i=0; i < nodes; ++i){
         for (int j=0; j < edgenum; ++j){
             if (distance[edges[j].source] != INFINITY)
             {
                if (distance[edges[j].source] + edges[j].weight < distance[edges[j].destination])
                {
                    int dummy = distance[edges[j].source] + edges[j].weight;
                    //if (dummy < distance[edges[j].destination])
                    distance[edges[j].destination] = dummy;
                }//end if
             }//end if
         }//end for
     }//end for

     for (int i=0; i < edgenum; ++i) {
         if (distance[edges[i].destination] > distance[edges[i].source] + edges[i].weight) {
             std::cout<<"Negative edge weight cycles detected!\n";
             free(distance);
             break;
         }//end if
     }//end for

     for (int i=0; i < nodes; ++i) {
         std::cout<<"The shortest distance between nodes " <<source<< " and " <<i<< " is " <<distance[i] <<"\n";
     }//end for
     free(distance);
 }
