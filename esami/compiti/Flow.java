
/*
 * Copyright (c) 2012 Alberto Montresor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/**
 * Compute the max-flow using the Ford-Fulkerson algorithm.
 */
public class Flow
{

/**
 * Creates the graph contained in the written exam of 31/05/12
 * and run the max-flow algorithm over it, printing the value
 * of the max-flow.
 */
public static void main(String[] args)
{
	
	// Create a graph with 6 nodes, represented through a matrix
  	int n=6;
	int[][] C = new int[n][];
	for (int i=0; i < n; i++) {
		C[i] = new int[n];
	}

	// Read the "numero di matricola"
	int[] x = new int[6];
	for (int i=0; i < 6; i++) {
		x[i] = Integer.parseInt(args[0].substring(i,i+1));
	}
  
	// Adds capacities to edges
	C[0][1] = 35;
	C[0][2] = 25;
	C[1][3] = 5+x[2];
	C[1][2] = 8+x[1];
	C[1][4] = 11+x[0];
	C[2][3] = 7+x[3];
	C[2][4] = 6+x[4];
	C[4][5] = 5+x[5];
	C[3][5] = 25;
	C[4][5] = 35;

	// Run the flow algorithm
	int[][] F = flow(C,0,5);

	// Compute the total flow going out from the source and print it
	int tot = 0;
	for (int i=0; i < n; i++) {
		tot += F[0][i];
	}
	System.out.println(tot);
}

/**
 * Compute the max-flow using the Ford-Fulkerson algorithm
 * @param C the capacity matrix
 * @param s the source node
 * @param t the sink node
 * @return the flow matrix 
 */
private static int[][] flow(int[][] C, int s, int t)
{	
	// Create an empty flow
	int[][] F = new int[n][];
	for (int i=0; i < n; i++) {
		F[i] = new int[n];
	}
	
  // Visited array to perform DFS, initially empty
	boolean[] visited = new boolean[C.length];

	// Repeat until there is no path	
	while (dfs(C,F,s,t, visited, Integer.MAX_VALUE)>0) {
		for (int i=0; i < C.length; i++) 
			visited[i] = false;
	}
	
}

/*
 * Performs a DFS starting from node i and trying to reach node t. Nodes already visited are
 * stored in the boolean vector visited.
 *  
 * @param C the capacity matrix; if capacity[x][y]>0, there is a directed edge between x and y
 * @param F the flow matrix to be computed
 * @param i the current node
 * @param t the sink node
 * @param visited the boolean set containing the nodes that have been visited
 * @param the smallest capacity found so far.
 * @returns the value of the additional flow found during this DFS, or 0 if there the sink
 * is not reachable from the source.
 */
private static int dfs(int[][] C, int[][] F, int i, int t, boolean[] visited, int min)
{
	// If sink has been reached, terminate
	if (i==t) {
		return min;
	}
	
	visited[i] = true;
	for (int j=0; j < C.length; j++) {
		if (C[i][j] > 0 && !visited[j]) {
			// For each adjacent node j that has not been visited...
			
			// Recursively perform the DFS, using the capacity of edge [i,j] if smaller than the
			// min found so far.
			int v = dfs(C, F, j, t, visited, Math.min(min, C[i][j]));
			
			// If v>0, we have found the sink, and v is the maximum value of the flow along the
			// path connecting the source and sink. We update both the capacities and the flow
			// accordingly.
			if (v > 0) {
				C[i][j] = C[i][j]-v;
				F[i][j] = F[i][j]+v;
				C[j][i] = C[j][i]+v;
				F[j][i] = F[j][i]-v;
				return v;
			}
		}
	}	
	// The sink has not been found.
	return 0;
}

}
