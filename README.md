# OS-Lab4
## The task
The task for the lab is to find critical path and critical time in an oriented, weighted, acyclic process graph.
To get everything clear:
> __Critical path__ is the longest path from a given vertice to the END vertice.   
     
At the same time,     
> __Critical time__ is the time it takes to travel the critical path from the given vertice.
## The algorithm briefly
To determine the critical path the first thing to do would be to determine the critical times of the nodes. In order to do that
we start from the end node, 1-by-1 walking through all of his predeccessors and check the critical time of those nodes. Repeated until the start node's children are all set and good to be proceeded into finding the critical path.   
The path finding is really simple: starting with the Start node, move to the node with the highest critical time among all children available. Stop when the End node achieved.
## The main functions of the program
+ ```void CalculateVerticeCriticalTime(int v)``` function - the function that goes from the End vertice to the Start vertice, basically, calculating all the critical times via the algorithm described above.     
+ ```void PrintGraph()``` function - prints the details of each graph node with it's weight, critical time and the list of it's children with their critical time.    
+ ```void PrintCriticalPath()``` function - prints the critical path in a from 'nodeStart -> node2 -> ... -> nodeEnd' via the algorithm described above.
## The algorithm demonstration
First of all, I drew an an oriented, weighted, acyclic process graph:
![The unsolved version of the graph](/images/example_unsolved.jpg "The unsolved version of the graph")
The numbers in brackets show the weight of the node, while the numbers in the circles are the number of the nodes.
After executing the program we can see the next result:
![The program execution result](/images/example_result.jpg "The program execution result")
Solving it on paper, the next result appears:
![The resolved version of the graph](/images/example_resolved.jpg "The resolved version of the graph")
As you might've guessed, the paths are completely the same.
