** 57.2 / 60 pts **

Proposal & Project submission - 10pts

Presentation, Readme & Report - 10pts

Deliverables:

For each deliverable, code was clean, readable and well documented (unless otherwise noted) so 20pts there. 20 remaining points.

BFS: 3.4 pts
- BFS testing is not sufficient. You only test the sizes of the path returned; what about the path itself?
- Runtime met

Dijkstra's: 3.2pts
- There was a mix of unordered_map and map. Recall map is O(logn) and less efficient, and introduced some extra inefficiencies (i.e. dist and prev). Complexity not impacted but inefficient
- Similar to BFS, the Dijkstra tests were not sufficient; comparison of path length does not imply a correct path, and while there is an additional test for Dijkstra's, it only checks shard bearers and the last vertex.
- Runtime met

Floyd-Warshall: 3.8pts
- The Floyd-Warshall tests run the algorithm for *every* test. You should only run the algorithm once, and make your assertions based on that result from *one* call to the algorithm, as the result is unique.
- Runtime met

Visualization: 3.8pts
- Consider removing all the comments. While this project may feeling a bit "informal", you would always want to remove blocks of comments before submitting the final product.
- Replace the lambda body with the already defined euclidean_distance method to improve readability

Misc (Graph & Execution): 3pts
- Unfortunately, the use of a vector<Node*> really impacted some performance in your implementation. nameToNode, getNodeIdx are O(|V|) each where V is your set of vertices because of the choice of a vector. These should really be O(1) (think OOP, or, alternatively, a different structure than a vector).
- Similarly, adjListToAdjMatrix is O(|V|^3) due to the use of find, and it should be O(|V|^2).
- Graph construction is not optimally efficient either because addEdge is O(|V|). This should be O(1).
- Why is the graph reconstructed for every algorithm in main? Your algorithm should not mutate the graph; all of these algorithms are effectively traversals and shouldn't mutate the graph structure itself.

Total points: 10 + 10 + 20 + 3.4 + 3.2 + 3.8 + 3.8 + 3 = 57.2pts

General notes (unrelated to grading):
- Cool project, I love the scope of it and the goal.
- I love some good enum usage.
- While Floyd-Warshall was correct, I think it would have been far more meaningful if you produced something that could recreate the paths (i.e. maybe the matrix includes previous vertices) or some paths itself. The distances don't seem very meaningful.
- How come there is not a path from Red Wolf to Godrick....? You can skip Stormveil and go to Raya Lucaria first?
- In some of your documentation you claimed runtimes such as O(n), but did not tell me what n is. What is n? Always define your variables in a formal setting!
- Fun little application of nearest neighbors (python makes it so easy..)
- Note that even though Dijkstra's is greedy, it is optimal. So even if you did a non-greedy SSSP algorithm, it would produce the same result. I think the big issue with Dijkstra's vs speed runners, as you mentioned, is the ability for speedrunners to plan accordingly. This could be accomplished, I believe, with a much more complicated graph structure and layering, though.
- I was very glad to see the update to Dijkstra's and the usage of PQ. Initially, your proposal had a worse runtime, and a naive approach to Dijkstra's. I'm very pleased to see you reconsidered.
- Always consider the underlying runtime of every data structure you use and the functions you are calling for it :)

Great work, Tarnished. Best of luck on future endeavors.