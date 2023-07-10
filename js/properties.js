"use strict";

const initial_max_grid_size = 47;
const menu_width = 323;


const grid_size_x = 21;
const grid_size_y = 21;
const cell_size = 40;

/*  Generator algorithms
*
*   1 - Randomized depth first
*   2 - Krusal algorithm
*   3 - Prim algorithm
*   4 - Wilson algorithm
*   5 - Aldous Broder algorithm
*   6 - Recursive division
*/
const selectedGenAlgorithm = 2;

/*  Solver algorithms
*
*   1 - Breadth first
*   2 - Bidirectional breath first
*   3 - Greedy best first
*   4 - Dijkstra
*   5 - A Star
*/

const selectedSolveAlgorithm = 1;


let grid;
let clicking = false;
let moving_start = false;
let moving_target = false;
let start_pos;
let target_pos;
let grid_clean = true;
let my_interval;

let node_list;
let node_list_index;
let path_list;
let path_list_index;
let found = false;
let path = false;

let generating = false;
let timeouts = [];
