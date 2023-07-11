import { mazeProperties } from "./properties";

export function add_wall(x, y): void {
	mazeProperties.grid[x][y] = -1;
}

export function remove_wall(x, y): void {
	mazeProperties.grid[x][y] = 0;
}

export function clear_grid(): void {
	if (!mazeProperties.grid_clean)
	{
		for (let i = 0; i < mazeProperties.timeouts.length; i++)
			clearTimeout(mazeProperties.timeouts[i]);

            mazeProperties.timeouts = [];
		clearInterval(mazeProperties.my_interval);

		for (let i = 0; i < mazeProperties.grid.length; i++)
			for (let j = 0; j < mazeProperties.grid[0].length; j++)
			{
				if (mazeProperties.grid[i][j] > -1)
				{
					remove_wall(i, j);
				}

				else if (mazeProperties.grid[i][j] < -1)
					add_wall(i, j);

			}

            mazeProperties.grid_clean = true;
	}
}

export function get_node(x, y): number {
	if (x >= 0 && x < mazeProperties.grid.length && y >= 0 && y < mazeProperties.grid[0].length)
		return mazeProperties.grid[x][y];

	return -2;
}

export function get_neighbours(cell, distance): number[][] {
	let up = [cell[0], cell[1] - distance];
	let right = [cell[0] + distance, cell[1]];
	let down = [cell[0], cell[1] + distance];
	let left = [cell[0] - distance, cell[1]];
	return [up, right, down, left];
}