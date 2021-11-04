"use strict";

function distance(point_1, point_2)
{
	return Math.sqrt(Math.pow(point_2[0] - point_1[0], 2) + Math.pow(point_2[1] - point_1[1], 2));
}

function maze_solvers_interval()
{
	my_interval = window.setInterval(function()
	{
		if (!path)
		{
			place_to_cell(node_list[node_list_index][0], node_list[node_list_index][1]).classList.add("cell_algo");
			node_list_index++;

			if (node_list_index == node_list.length)
			{
				if (!found)
					clearInterval(my_interval);

				else
				{
					path = true;
					place_to_cell(start_pos[0], start_pos[1]).classList.add("cell_path");
				}
			}
		}

		else
		{
			if (path_list_index == path_list.length)
			{
				place_to_cell(target_pos[0], target_pos[1]).classList.add("cell_path");
				clearInterval(my_interval);
				return;
			}

			place_to_cell(path_list[path_list_index][0], path_list[path_list_index][1]).classList.remove("cell_algo");
			place_to_cell(path_list[path_list_index][0], path_list[path_list_index][1]).classList.add("cell_path");
			path_list_index++;
		}
	}, 10);
}

function breadth_first()
{
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let frontier = [start_pos];
	grid[start_pos[0]][start_pos[1]] = 1;

	do
	{
		let list = get_neighbours(frontier[0], 1);
		frontier.splice(0, 1);

		for (let i = 0; i < list.length; i++)
			if (get_node(list[i][0], list[i][1]) == 0)
			{
				frontier.push(list[i]);
				grid[list[i][0]][list[i][1]] = i + 1;

				if (list[i][0] == target_pos[0] && list[i][1] == target_pos[1])
				{
					found = true;
					break;
				}

				node_list.push(list[i]);
			}
	}
	while (frontier.length > 0 && !found)

	if (found)
	{
		let current_node = target_pos;

		while (current_node[0] != start_pos[0] || current_node[1] != start_pos[1])
		{
			switch (grid[current_node[0]][current_node[1]])
			{
				case 1: current_node = [current_node[0], current_node[1] + 1]; break;
				case 2: current_node = [current_node[0] - 1, current_node[1]]; break;
				case 3: current_node = [current_node[0], current_node[1] - 1]; break;
				case 4: current_node = [current_node[0] + 1, current_node[1]]; break;
				default: break;
			}

			path_list.push(current_node);
		}

		path_list.pop();
		path_list.reverse();
	}

	maze_solvers_interval();
}

function bidirectional_breadth_first()
{
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let current_cell;
	let start_end;
	let target_end;
	let frontier = [start_pos, target_pos];
	grid[target_pos[0]][target_pos[1]] = 1;
	grid[start_pos[0]][start_pos[1]] = 11;

	do
	{
		current_cell = frontier[0];
		let list = get_neighbours(current_cell, 1);
		frontier.splice(0, 1);

		for (let i = 0; i < list.length; i++)
		{
			if (get_node(list[i][0], list[i][1]) == 0)
			{
				frontier.push(list[i]);

				if (grid[current_cell[0]][current_cell[1]] < 10)
					grid[list[i][0]][list[i][1]] = i + 1;
				else
					grid[list[i][0]][list[i][1]] = 11 + i;

				node_list.push(list[i]);
			}

			else if (get_node(list[i][0], list[i][1]) > 0)
			{
				if (grid[current_cell[0]][current_cell[1]] < 10 && get_node(list[i][0], list[i][1]) > 10)
				{
					start_end = current_cell;
					target_end = list[i];
					found = true;
					break;
				}

				else if (grid[current_cell[0]][current_cell[1]] > 10 && get_node(list[i][0], list[i][1]) < 10)
				{
					start_end = list[i];
					target_end = current_cell;
					found = true;
					break;
				}
			}
		}
	}
	while (frontier.length > 0 && !found)

	if (found)
	{
		let targets = [target_pos, start_pos];
		let starts = [start_end, target_end];

		for (let i = 0; i < starts.length; i++)
		{
			let current_node = starts[i];

			while (current_node[0] != targets[i][0] || current_node[1] != targets[i][1])
			{
				path_list.push(current_node);

				switch (grid[current_node[0]][current_node[1]] - (i * 10))
				{
					case 1: current_node = [current_node[0], current_node[1] + 1]; break;
					case 2: current_node = [current_node[0] - 1, current_node[1]]; break;
					case 3: current_node = [current_node[0], current_node[1] - 1]; break;
					case 4: current_node = [current_node[0] + 1, current_node[1]]; break;
					default: break;
				}
			}

			if (i == 0)
				path_list.reverse();
		}

		path_list.reverse();
	}

	maze_solvers_interval();
}

function greedy_best_first()
{
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let frontier = [start_pos];
	grid[start_pos[0]][start_pos[1]] = 1;

	do
	{
		frontier.sort(function(a, b)
		{
			return distance(a, target_pos) - distance(b, target_pos);
		});

		let list = get_neighbours(frontier[0], 1);
		frontier.splice(0, 1);

		for (let i = 0; i < list.length; i++)
			if (get_node(list[i][0], list[i][1]) == 0)
			{
				frontier.push(list[i]);
				grid[list[i][0]][list[i][1]] = i + 1;

				if (list[i][0] == target_pos[0] && list[i][1] == target_pos[1])
				{
					found = true;
					break;
				}

				node_list.push(list[i]);
			}
	}
	while (frontier.length > 0 && !found)

	if (found)
	{
		let current_node = target_pos;

		while (current_node[0] != start_pos[0] || current_node[1] != start_pos[1])
		{
			switch (grid[current_node[0]][current_node[1]])
			{
				case 1: current_node = [current_node[0], current_node[1] + 1]; break;
				case 2: current_node = [current_node[0] - 1, current_node[1]]; break;
				case 3: current_node = [current_node[0], current_node[1] - 1]; break;
				case 4: current_node = [current_node[0] + 1, current_node[1]]; break;
				default: break;
			}

			path_list.push(current_node);
		}

		path_list.pop();
		path_list.reverse();
	}

	maze_solvers_interval();
}

function dijkstra()
{
	breadth_first();
}

function a_star()
{
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let frontier = [start_pos];
	let cost_grid = new Array(grid.length).fill(0).map(() => new Array(grid[0].length).fill(0));
	grid[start_pos[0]][start_pos[1]] = 1;

	do
	{
		frontier.sort(function(a, b)
		{
			let a_value = cost_grid[a[0]][a[1]] + distance(a, target_pos) * Math.sqrt(2);
			let b_value = cost_grid[b[0]][b[1]] + distance(b, target_pos) * Math.sqrt(2);
			return a_value - b_value;
		});

		let current_cell = frontier[0];
		let list = get_neighbours(current_cell, 1);
		frontier.splice(0, 1);

		for (let i = 0; i < list.length; i++)
			if (get_node(list[i][0], list[i][1]) == 0)
			{
				frontier.push(list[i]);
				grid[list[i][0]][list[i][1]] = i + 1;
				cost_grid[list[i][0]][list[i][1]] = cost_grid[current_cell[0]][current_cell[1]] + 1;

				if (list[i][0] == target_pos[0] && list[i][1] == target_pos[1])
				{
					found = true;
					break;
				}

				node_list.push(list[i]);
			}
	}
	while (frontier.length > 0 && !found)

	if (found)
	{
		let current_node = target_pos;

		while (current_node[0] != start_pos[0] || current_node[1] != start_pos[1])
		{
			switch (grid[current_node[0]][current_node[1]])
			{
				case 1: current_node = [current_node[0], current_node[1] + 1]; break;
				case 2: current_node = [current_node[0] - 1, current_node[1]]; break;
				case 3: current_node = [current_node[0], current_node[1] - 1]; break;
				case 4: current_node = [current_node[0] + 1, current_node[1]]; break;
				default: break;
			}

			path_list.push(current_node);
		}

		path_list.pop();
		path_list.reverse();
	}

	maze_solvers_interval();
}

function maze_solvers()
{
	clear_grid();
	grid_clean = false;

	if ((Math.abs(start_pos[0] - target_pos[0]) == 0 && Math.abs(start_pos[1] - target_pos[1]) == 1) ||
		(Math.abs(start_pos[0] - target_pos[0]) == 1 && Math.abs(start_pos[1] - target_pos[1]) == 0))
		{
			place_to_cell(start_pos[0], start_pos[1]).classList.add("cell_path");
			place_to_cell(target_pos[0], target_pos[1]).classList.add("cell_path");
		}

	else if (document.querySelector("#slct_1").value == "1")
		breadth_first();

	else if (document.querySelector("#slct_1").value == "2")
		bidirectional_breadth_first();

	else if (document.querySelector("#slct_1").value == "3")
		greedy_best_first();

	else if (document.querySelector("#slct_1").value == "4")
		dijkstra();

	else if (document.querySelector("#slct_1").value == "5")
		a_star();
}
