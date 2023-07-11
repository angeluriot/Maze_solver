export const grid_size_x: number = 21;
export const grid_size_y: number = 21;

/*  Generator algorithms
*
*   1 - Randomized depth first
*   2 - Krusal algorithm
*   3 - Prim algorithm
*   4 - Wilson algorithm
*   5 - Aldous Broder algorithm
*   6 - Recursive division
*/
export const selectedGenAlgorithm: number = 2;

/*  Solver algorithms
*
*   1 - Breadth first
*   2 - Bidirectional breath first
*   3 - Greedy best first
*   4 - Dijkstra
*   5 - A Star
*/

export const selectedSolveAlgorithm: number = 1;

export const mazeProperties = {
    grid: undefined,
    start_pos: undefined,
    target_pos: undefined,
    grid_clean: true,
    my_interval: undefined,
    generating: false,
    timeouts: []
}
