# Traveling Salesman Problem

Given: A finite set of "cities" C = {c0, c1, … , cm-1} and a cost function d: C x C → Unsigned-Number ∪ { ∞ }, which represents a cost for traveling between ci and cj each city for all i, j ∈ {0…m-1} and if there is no direct way to travel between two cities ci and cj, i ≠ j, let d(ci,cj) = ∞ and assume d(ci,ci) = 0 for all i ∈ {0,…,m-1}. (Note: Number can equal unsigned integer, or real number, such as float or double in many programming languages. The symbol, ∞, can be represented as the max value representation of the respective data type.)

Find least cost tour of all cities. Of all the simple paths involving all cities in C and with the starting and ending city the same (a.k.a., a Hamiltonian cycle), find the least cost Hamiltonian cycle. This is called the optimal tour.

## Algorithm Design using Dynamic Programming

Suppose that G = < V, E> is a directed graph with V = {1, 2, ..., m} and E and the cost function defined and represented by an adjacency matrix M: M[i][i] = 0, M[i][j] ≥ 0 if i ≠ j, and M[i][j] = ∞ if there is no edge between vertices i and j.

Without loss of generality assume that the tour starts vertex 1 and ends with vertex 1. Hence, that tour must go through edge (1, i) for at least one vertex i≠1 then followed by a path from i to 1 exactly once through each vertex in V – {1, i}. (The minus is the set difference operator.) If the tour is optimal (sum of weights is minimum of all such tours), then so is the path from i to 1. Thus, the principle of optimality holds. The Principle of Optimality states that in a sequence of decision points, each subsequence (sub-problem) must also be optimal.

Suppose the following are given: a set of vertices S ⊆ V – {1} and a vertex i ∈ V – S with i = 1 only if S = V – {1}. Suppose that function g(i, S) is defined as the length of the shortest path from vertex i to vertex 1 and that passes through each vertex in S one and only one time. Given this definition of g, one can represent the length of the entire optimal Hamiltonian cycle as g(1, V – {1}).

So, by the principle of optimality, we have g(1, V-{1}) = min for 2≤j≤m (M[1][j]+g(j, V-{1,j})) (1)

To generalize, consider any vertex i ≠ 1 and S ≠∅, and S≠ V – {i} and i ∉ S and define g(i, S)= minj ∈ S(M[i][j]+g(j, S-{j}) ) (2) and g(i,∅)=M[i][1], for i=2, 3,…, m

Given that we know the values of g(i,S) when S = ∅, we can then calculate g(i,S) when the size of S is 1 (|S| = 1) and with vertex 1 ∉ S. Then, we can calculate g when |S| = 2 with vertex 1 ∉ S. We continue on until we know all the values for g(j, V – {1}) for all j, such j ≠ 1, we can finally use eq. (1) to arrive at the solution.
