"use strict";


function generate_grid()
{
	grid = new Array(grid_size_x).fill(0).map(() => new Array(grid_size_y).fill(0));

	start_pos = [1, grid_size_y - 2];
	target_pos = [grid_size_x - 2, 1];
}

function add_wall(x, y)
{
	grid[x][y] = -1;
}

function remove_wall(x, y)
{
	grid[x][y] = 0;
}

function clear_grid()
{
	if (!grid_clean)
	{
		for (let i = 0; i < timeouts.length; i++)
			clearTimeout(timeouts[i]);

		timeouts = [];
		clearInterval(my_interval);

		for (let i = 0; i < grid.length; i++)
			for (let j = 0; j < grid[0].length; j++)
			{
				if (grid[i][j] > -1)
				{
					remove_wall(i, j);
				}

				else if (grid[i][j] < -1)
					add_wall(i, j);

			}

		grid_clean = true;
	}
}

function get_node(x, y)
{
	if (x >= 0 && x < grid.length && y >= 0 && y < grid[0].length)
		return grid[x][y];

	return -2;
}
