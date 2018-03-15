# lem-in
RAKING IN ANTS

1. Document all your code
2. Focus on modular functions with purity
3. Detail your approach to solve the problem

A few lessons learned in this project.
-------------------------------------
1. Fully form your ideas about what to do before doing it. You had a massive issue with how to set the "successful path" because you didn't have the insight that as long as any one of a vertex's edges leads to the end, it's a "successful path" node. 
2. Don't take shortcuts-- understand why something is happening. This is why you had so many errors when setting an array of struct pointers.
3. Have defined error messages-- don't just randomly use 1 and 0 as you wish. DEFINE abstractions.
4. Think about time/space complexity from now on. You used a linked list because the input is dynamic-- but an array of structs would have allowed you to access the graph far quicker. In O(1) time.

Problem Approach
----------------
1. Parse input and create necessary data structures to hold data, while simultaneously handling error checking in this stage.
2. Pre-set the map with necessary steps to reach goal and whether the path leads to the goal or not.
3. Move ants according to a simple algorithm of, "if not occupied, if successful path, if less steps".

Data Structures Used
--------------------
1. A struct to hold "farm", the "graph", and some misc. information. Super struct that contains everything to be freed.
2. The graph data structure itself. A linked list of linked lists. Each node in the linked list represents a vertex and holds misc. information, a pointer to a struct called "link" that handles all the edges of said vertex (data is also held in a linked list format), and a pointer to the next vertex. [Linked list of linked lists]
3. All of the ants are held in an array of structure pointers. [Array]
