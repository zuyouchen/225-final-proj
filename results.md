# Full Written Report
 
A written report. In addition to your code, your Github repository must contain a results.md file which describes:

    The output and correctness of each algorithm – You should summarize, visualize, or highlight some part of the full-scale run of each algorithm. Additionally, the report should briefly describe what tests you performed to confirm that each algorithm was working as intended.

    The answer to your leading question – You should direct address your proposed leading question. How did you answer this question? What did you discover? If your project was ultimately unsuccessful, give a brief reflection about what worked and what you would do differently as a team.

## Background and Leading Question

Elden Ring is a action RPG released in February of 2022 by studio Fromsoftware, famous for their line of Dark Souls video games as well as Sekiro and Bloodborne. Elden Ring is unique among the set of games as it is fully open world and can be traversed in almost any order. Gamers have wasted no time optimizing routes to complete the game as quickly as possible, namely in 2 categories: All Remembrances, where a player must defeat all 15 primary bosses (Godrick the Grafted, Rennala Queen of the Full Moon, Starscourge Radahn, Rykard Lord of Blasphemy, Regal Ancestor, Astel Naturalborn of the Void, Lichdragon Fortissax, Morgott the Omen King, Fire Giant, Maliketh the Black Blade, Dragonlord Placidusax, Mohg the Lord of Blood, Malenia Goddess of Rot, Godfrey the First Elden Lord, and Radagon of the Golden Order/Elden Beast), and any%, where a player must defeat 2 of the 7 demigods (Godrick, Rennala, Radahn, Rykard, Morgott, Mohg, and Malenia) and then finish the game by defeating Radagon and the Elden Beast. 

Our leading question was what is the fastest Elden Ring speedun (either an All Major Bosses route or an any% route) as constructed using a graph data structure and various graph traversal and path-finding algorithms? To answer this question, we inputted all major locations in Elden Ring as nodes, each storing a time to complete (0 if just a location to pass through, or a positive double if a boss fight) with edges between nodes representing the time it would take to go from one node to another. Using this structure, we were able to run path finding algorithms such as Dijkstra's and Floyd-Washall to find optimal routes throughout the game. 

## Output and Correctness of Each Major Algorithm

Graph Representation:

BFS:

Dijkstra's:

Floyd-Warshall:

Visualization:

## Tests Used to Check Algorithm Correctness

Graph Representation:

BFS:

Dijkstra's:

Floyd-Warshall:

Visualization:





