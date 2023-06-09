# Full Written Report

## Background, Leading Question, and Caveats

Elden Ring is a action RPG released in February of 2022 by studio Fromsoftware, famous for their line of Dark Souls video games as well as Sekiro and Bloodborne. Elden Ring is unique among the set of games as it is fully open world and can be traversed in almost any order. Gamers have wasted no time optimizing routes to complete the game as quickly as possible, namely in 2 categories: All Remembrances, where a player must defeat all 15 primary bosses (Godrick the Grafted, Rennala Queen of the Full Moon, Starscourge Radahn, Rykard Lord of Blasphemy, Regal Ancestor, Astel Naturalborn of the Void, Lichdragon Fortissax, Morgott the Omen King, Fire Giant, Maliketh the Black Blade, Dragonlord Placidusax, Mohg the Lord of Blood, Malenia Goddess of Rot, Godfrey the First Elden Lord, and Radagon of the Golden Order/Elden Beast), and any%, where a player must defeat 2 of the 7 demigods (Godrick, Rennala, Radahn, Rykard, Morgott, Mohg, and Malenia) and then finish the game by defeating Radagon and the Elden Beast. Both routes are quite different and require different locations to be visited and as we can see by analyzing runs posted to speedrun.com, runners take many different routes to finish their runs and there is no set route that is the clear best (as of May 2023 at least).

But if we had a computer try to speedrun Elden Ring, what route would it take? This was our leading question for the Elden Ring Speedrun Optimizer project. To answer this question, we inputted all major locations in Elden Ring as nodes, each storing a time to complete (0 if it’s just a location to pass through, or a positive double if it’s a boss fight) with edges between nodes representing the time it would take to go from one node to another. Using this structure, we were able to run path finding algorithms such as Dijkstra's and Floyd-Washall to find optimal routes throughout the game.

By running these algorithms, we resulted in an any% route of 59.9167 minutes (compared to the current any% glitchless world record of 57.45 minutes) and an All Remembrances route of 2.25806 hours (compared to the current All Remembrances glitchless world record of about 1.85 hours). 
Roughly speaking, our any% route follows the following path: start to Godrick to Rennala to Draconic Tree Sentinel to Morgott to Fire Giant to Maliketh to Elden Beast. The current world record speedrun, performed by user blanxz, gathers numerous items and first fights the Draconic Tree Sentinel, then Radahn, then Godrick, then Morgott and the rest of the run is about the same. Other routes I’ve watched, such as one performed by user LilAggy, choose to fight Rykard instead of Radahn. There is a ton of variation in routing, so ours is just another possibility added to the pile of possible routes. Since Elden Ring is so new, no route has been confirmed to be the singular best yet. Our time is similar enough to world records that the route we have produced is no doubt viable in actual speedrunning.

Once again speaking roughly, our All Remembrances route starts and heads to Godrick, then Rennala, Radahn, Regal Ancestor, Morgott, Fortissax, Astel, Rykard, Fire Giant, Mohg, Malenia, Maliketh, Placidusax, Godfrey, and Elden Beast. The current world record for All Remembrances glitchless performed by user Forsa goes from start to Rykard, then Radahn, Morgott, Mohg, Regal Ancestor, Rennala, Godrick, Fire Giant, Astel, Placidusax, Fortissax, Malenia, Maliketh, Godfrey, and Elden Beast. 

There are a few caveats to our algorithm. Elden Ring is far too expansive to account for all possible weapons and upgrades, so ours generally assumes an early-acquired weapon being used for the entire run, and that extra items are never picked up. Furthermore, Dijkstra’s algorithm is greedy and does not plan ahead, so we generally visit closer nodes before farther ones, not being able to decide if farther away nodes may actually yield shorter times in the long run. So our moderate increase in time in our All Remembrances route makes sense given this consideration.

While the route we have outputted is interesting and exciting, the inability to plan ahead does make the route slower than current world records and we do not know of any way to account for this without making the algorithm vastly more complex. Nonetheless, it was fun to see the algorithm decide, for example, to fight Rennala rather than Radahn in any%, and visit Rykard so late in All Remembrances, and other choices like that. It was also extremely satisfying to observe our route drawn out in the visualization function, giving us a tangible look at what we had created. 

## Output and Correctness of Each Major Algorithm

Graph Representation: Our graph representation begins with a CSV of nodes and a CSV of prerequisites. The node CSV’s lines begin with a node and its time to complete (often 0 if it’s just a location or a number if it’s a boss to fight), and all nodes following it are related nodes, with their subsequent number being the time it takes to travel between the current line’s node and the related node. 

Example of a line in the nodes CSV: firstStep,70,gatefront,80,dectusHaight,120,

(the node itself is firstStep and it takes 70 seconds to pass through; it is related to gatefront with a travel time of 80 seconds and dectusHaight with a travel time of 120 seconds).

These times were recorded through analyses of existing speedruns as well as personal testing in-game. The prerequisite CSV contains a node followed by its prerequisite, or a node that must be visited before entering the node itself. The only unique one here is that Godfrey (Golden Shade) must be visited after two demigods/shard bearers are defeated, which is handled separately in the read-in function.

Example of a line in the prerequisite CSV: ainselMain, liurniaTower,

(we must visit liurniaTower before visiting ainselMain)

Another example (the only unique one): godfreyGoldenShade, two_shard_bearers,

(to fight godfreyGoldenShade, we must have defeated 2 shard bearers, and this total is incremented each time we do and thus is handled in code almost the same way). 

When calling the Graph constructor and passing in strings to identity the node CSV and the prereq CSV, our algorithm parses through them and feeds the information into a node struct which contains all the important information for each node. Due to the caveat of needing to assign names, times, related nodes, and prerequisites, our algorithm runs at O(n^3). Our primary means of testing this algorithm was printing out the result and verifying that it correctly read in the CSV; each node had the correct related nodes and prerequisites. 

BFS: Our breadth-first search algorithm begins at a start node (always called “firstStep,” the location that the player begins the game at). Our algorithm is almost a traditional BFS save for one consideration: we must account for prerequisite nodes. To do this, we check if we’ve visited the prerequisite nodes, and while we haven’t, we remove the node and add it onto the end of the queue. Since this is a nested loop within our overarching loop, this pushes our algorithm up to a worst case O(n^2) runtime. To test this algorithm, we assert that it hits every possible node, and we inputted our resulting vector path into the visualization and verified that it followed a breadth-first nature. 

Dijkstra's: Our Dijkstra’s algorithm is similar to BFS in that it is similar to a traditional implementation of Dijkstra’s save for the fact that it must also account for prerequisites. To handle this, we once again create a loop to remove all nodes from the front of the queue that have unvisited prerequisites and add them onto the back of the queue later. Due to this additional loop, we add additional n worth of time onto the algorithm, bringing its final runtime to O(n^2 * logn). To test this algorithm in the case of it being an All Remembrances route by asserting that it visits every node and then visualizing it to make sure it follows a sensible structure. To test that it properly handles prerequisites and doesn't visit any needless nodes in the any% route, we assert these aforementioned facts as well as once again inputting it into the visualization and checking if it makes sense.

Floyd-Warshall: In contrast to Dijkstra's algorithm that finds the shortest path between a single vertex and all other vertices, the Floyd-Warshall algorithm solves the all-pairs shortest-path problem, which we used to find the shortest distances between every pair of location vertices in our given graph. This works by estimating the shortest path between two vertices and further improving upon this estimate until the optimal time is reached. As we followed the traditional approach of implementing Floyd-Warshall in testing up to n^2 edge combinations, this algorithm has a time complexity of O(n^3), where n is the number of locations in the graph. 

We consider the two cases regarding every pair of source and destination vertices and the intermediary node not yet considered as a valid intermediate vertex:
* intermediate location of interest is not an intermediate vertex in the shortest path, in which case we maintain the current optimal distance
* intermediate location of interest is an intermediate vertex in the shortest path, in which the current optimal distance is updated.

Since some nodes can be entered but not left, the path from A to B may exist while from B to A may not. 
In adapting our current implementations, we also convert the adjacency list representation of our map into an adjacency matrix for use in our algorithm. We also implement an additional helper function taking two parameters of starting and ending target node strings respectfully to retrieve the distance data calculated from this algorithm.


Visualization: The visualization ended up being the last step in the compilation process. Creating the visualization involved:

* coordinating with the members of the team that was responsible for putting the output of BFS/Dijkstra's into a CSV
* creating some expectations about a standard format that these outputs should follow
* reading this output into the program  

We then thoroughly researched the different visualization libraries available to us to visualize data in Python and settled on the `matplotlib` library. The visualization then takes O(n^2) time to read in the CSV since we had to loop through each row in the CSV, split a row into a list, and then loop through said list; it then takes essentially O(n) time to complete the rest of the computation, with the only other two parts of heavy computation being: having to loop through the outputted BFS/Dijkstra's path linearly and having to write a lambda that runs in O(n) time that computes the point in the stored dictionary of points provided in the CSV that's closest to the user's mouse. As a quick last note, we couldn't write any formal test cases for this part of the project since testing essentially just involved visually observing whether or not the visualization was correct at each iteration of the development process.
