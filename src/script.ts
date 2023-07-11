import { maze_generators } from "./maze_generators";
import { grid_size_x, grid_size_y, mazeProperties } from "./properties";

window.onload = function()
{
	generate_grid();
	maze_generators();
}

function generate_grid(): void {
	mazeProperties.grid = new Array(grid_size_x).fill(0).map(() => new Array(grid_size_y).fill(0));

	mazeProperties.start_pos = [1, grid_size_y - 2];
	mazeProperties.target_pos = [grid_size_x - 2, 1];
}


