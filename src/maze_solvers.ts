import { clear_grid, get_neighbours, get_node } from "./common";
import { mazeProperties, selectedSolveAlgorithm } from './properties';

let node_list;
let node_list_index;
let path_list;
let path_list_index;
let found = false;
let path = false;

export function maze_solvers(): void {
	console.log("Starting maze solving");
	clear_grid();
	mazeProperties.grid_clean = false;
	clear_grid();

	switch(selectedSolveAlgorithm) {
		case 1:
			breadth_first();
			break;
		case 2:
			bidirectional_breadth_first();
			break;
		case 3:
			greedy_best_first();
			break;
		case 4:
			dijkstra();
			break;
		case 5:
			a_star();
			break;
		default:
			dijkstra();
			break;
	}
}


function distance(point_1, point_2)
{
	return Math.sqrt(Math.pow(point_2[0] - point_1[0], 2) + Math.pow(point_2[1] - point_1[1], 2));
}

function maze_solvers_interval(): void {
	mazeProperties.my_interval = window.setInterval(function()
	{
		if (!path)
		{
			node_list_index++;

			if (node_list_index == node_list.length)
			{
				if (!found)
					clearInterval(mazeProperties.my_interval);

				else
				{
					path = true;
				}
			}
		}

		else
		{
			if (path_list_index == path_list.length)
			{
				clearInterval(mazeProperties.my_interval);
				console.log(path_list);
				return;
			}

			path_list_index++;
		}
	}, 10);
}

function breadth_first(): void {
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let frontier = [mazeProperties.start_pos];
	mazeProperties.grid[mazeProperties.start_pos[0]][mazeProperties.start_pos[1]] = 1;

	do
	{
		let list = get_neighbours(frontier[0], 1);
		frontier.splice(0, 1);

		for (let i = 0; i < list.length; i++)
			if (get_node(list[i][0], list[i][1]) == 0)
			{
				frontier.push(list[i]);
				mazeProperties.grid[list[i][0]][list[i][1]] = i + 1;

				if (list[i][0] == mazeProperties.target_pos[0] && list[i][1] == mazeProperties.target_pos[1])
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
		let current_node = mazeProperties.target_pos;

		while (current_node[0] != mazeProperties.start_pos[0] || current_node[1] != mazeProperties.start_pos[1])
		{
			switch (mazeProperties.grid[current_node[0]][current_node[1]])
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

function bidirectional_breadth_first(): void {
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let current_cell;
	let start_end;
	let target_end;
	let frontier = [mazeProperties.start_pos, mazeProperties.target_pos];
	mazeProperties.grid[mazeProperties.target_pos[0]][mazeProperties.target_pos[1]] = 1;
	mazeProperties.grid[mazeProperties.start_pos[0]][mazeProperties.start_pos[1]] = 11;

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

				if (mazeProperties.grid[current_cell[0]][current_cell[1]] < 10)
					mazeProperties.grid[list[i][0]][list[i][1]] = i + 1;
				else
					mazeProperties.grid[list[i][0]][list[i][1]] = 11 + i;

				node_list.push(list[i]);
			}

			else if (get_node(list[i][0], list[i][1]) > 0)
			{
				if (mazeProperties.grid[current_cell[0]][current_cell[1]] < 10 && get_node(list[i][0], list[i][1]) > 10)
				{
					start_end = current_cell;
					target_end = list[i];
					found = true;
					break;
				}

				else if (mazeProperties.grid[current_cell[0]][current_cell[1]] > 10 && get_node(list[i][0], list[i][1]) < 10)
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
		let targets = [mazeProperties.target_pos, mazeProperties.start_pos];
		let starts = [start_end, target_end];

		for (let i = 0; i < starts.length; i++)
		{
			let current_node = starts[i];

			while (current_node[0] != targets[i][0] || current_node[1] != targets[i][1])
			{
				path_list.push(current_node);

				switch (mazeProperties.grid[current_node[0]][current_node[1]] - (i * 10))
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

function greedy_best_first(): void {
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let frontier = [mazeProperties.start_pos];
	mazeProperties.grid[mazeProperties.start_pos[0]][mazeProperties.start_pos[1]] = 1;

	do
	{
		frontier.sort(function(a, b)
		{
			return distance(a, mazeProperties.target_pos) - distance(b, mazeProperties.target_pos);
		});

		let list = get_neighbours(frontier[0], 1);
		frontier.splice(0, 1);

		for (let i = 0; i < list.length; i++)
			if (get_node(list[i][0], list[i][1]) == 0)
			{
				frontier.push(list[i]);
				mazeProperties.grid[list[i][0]][list[i][1]] = i + 1;

				if (list[i][0] == mazeProperties.target_pos[0] && list[i][1] == mazeProperties.target_pos[1])
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
		let current_node = mazeProperties.target_pos;

		while (current_node[0] != mazeProperties.start_pos[0] || current_node[1] != mazeProperties.start_pos[1])
		{
			switch (mazeProperties.grid[current_node[0]][current_node[1]])
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

function dijkstra(): void {
	breadth_first();
}

function a_star(): void {
	node_list = [];
	node_list_index = 0;
	path_list = [];
	path_list_index = 0;
	found = false;
	path = false;
	let frontier = [mazeProperties.start_pos];
	let cost_grid = new Array(mazeProperties.grid.length).fill(0).map(() => new Array(mazeProperties.grid[0].length).fill(0));
	mazeProperties.grid[mazeProperties.start_pos[0]][mazeProperties.start_pos[1]] = 1;

	do
	{
		frontier.sort(function(a, b)
		{
			let a_value = cost_grid[a[0]][a[1]] + distance(a, mazeProperties.target_pos) * Math.sqrt(2);
			let b_value = cost_grid[b[0]][b[1]] + distance(b, mazeProperties.target_pos) * Math.sqrt(2);
			return a_value - b_value;
		});

		let current_cell = frontier[0];
		let list = get_neighbours(current_cell, 1);
		frontier.splice(0, 1);

		for (let i = 0; i < list.length; i++)
			if (get_node(list[i][0], list[i][1]) == 0)
			{
				frontier.push(list[i]);
				mazeProperties.grid[list[i][0]][list[i][1]] = i + 1;
				cost_grid[list[i][0]][list[i][1]] = cost_grid[current_cell[0]][current_cell[1]] + 1;

				if (list[i][0] == mazeProperties.target_pos[0] && list[i][1] == mazeProperties.target_pos[1])
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
		let current_node = mazeProperties.target_pos;

		while (current_node[0] != mazeProperties.start_pos[0] || current_node[1] != mazeProperties.start_pos[1])
		{
			switch (mazeProperties.grid[current_node[0]][current_node[1]])
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