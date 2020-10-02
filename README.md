# anywhrChallenge


Problem -

We are given a task to mark hypothetical hexagons as hotspots of COVID disease. Multiple hexagons make a cluster. 
There are 3 actions that we can do - 
1. Query the neighbors of a particular hexagon.
2. Add a hexagon to a cluster by mentioning its neighbor that is already present in the cluster and the border it will share with it.
3. Remove a hexagon from a cluster as long as it does not seperate 2 hotspots.

My approach towards this problem -

First let us talk about how I represent a hexagon. Let us assume that these hexagons are laid out in 2 dimensional coordinate system. I have taken the topmost left point of the hexagon as my head vertex. So if I know the coordinates of head vertex of a hexagon I can find out the others. Let us say the coordinates of the head vertex is (X,Y), then the coordinates of the rest of the vertices of that hexagon in clockwise order will be -
(X+1,Y)
(X+2,Y-1)
(X+1,Y-2)
(X,Y-2)
(X-1,Y-1)
So I created a class called Hexagon and stored its name and the coordinates of the head vertex of the hexagon as member variables.
The Cluster class contains a set of Hexagons as its member variable.

Now let me tell you how I solved each of the above actions

1. To query the neighbors of a particular hexagon, I first got the coordinates of that hexagon and calculated the coordinates of the neighboring hexagon, then searched it my set.
This will take O(N + 6logN) which is O(N) where N is the total number of hexagons. The O(N) part is finding the hexagon with that name. I found this later, we can maintain a map to handle this and that will lead to O(logN) complexity.
2. Adding a hexagon just means adding it to our set which will take O(logN) time.
3. To remove a hexagon, I first erased it from my cluster (set) and then did a customised DFS search to find whether all the hexagons are connected. If they are not I just simply add that hexagon back to our cluster. To travel from one hexagon to other in my case means to find the coordinate of the neighbor ( O(1) time comp ) and do search of these coordinates on my set (6logN cause there can be 6 neighbors), therefore the total time complexity for this action is O(NlogN).

You can use my program interactively. I have attached sample input file and output file for the test cases provided in the problem document. My output matches with the expected output as per my calculations.

I have written my solution in c++ and i think with some more effort i can write this in java and python too. I opted c++ as I am most comfortable with it. I think I may need more than 1 day to write the frontend part of the code as I have comparitively much less experience in that area.
