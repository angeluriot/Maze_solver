"use strict";

function get_neighbours(cell, distance)
{
	let up = [cell[0], cell[1] - distance];
	let right = [cell[0] + distance, cell[1]];
	let down = [cell[0], cell[1] + distance];
	let left = [cell[0] - distance, cell[1]];
	return [up, right, down, left];
}

function random_int(min, max)
{
	min = Math.ceil(min);
	max = Math.floor(max);
	return Math.floor(Math.random() * (max - min)) + min;
}

function fill()
{
	for (let i = 0; i < grid.length; i++)
		for (let j = 0; j < grid[0].length; j++)
			add_wall(i, j);
}

function fill_walls()
{
	for (let i = 0; i < grid.length; i++)
		for (let j = 0; j < grid[0].length; j++)
			if (i % 2 == 0 || j % 2 == 0)
				add_wall(i, j);
}

function enclose()
{
	for (let i = 0; i < grid.length; i++)
	{
		add_wall(i, 0);
		add_wall(i, grid[0].length - 1);
	}

	for (let j = 0; j < grid[0].length; j++)
	{
		add_wall(0, j);
		add_wall(grid.length - 1, j);
	}
}

function randomized_depth_first()
{
	fill();
	let current_cell = [1, 1];
	remove_wall(current_cell[0], current_cell[1]);
	grid[current_cell[0]][current_cell[1]] = 1;
	let stack = [current_cell];

	my_interval = window.setInterval(function()
	{
		if (stack.length == 0)
		{
			clearInterval(my_interval);
			clear_grid();
			generating = false;
			return;
		}

		current_cell = stack.pop();
		let neighbours = [];
		let list = get_neighbours(current_cell, 2);

		for (let i = 0; i < list.length; i++)
			if (get_node(list[i][0], list[i][1]) == -1 || get_node(list[i][0], list[i][1]) == 0)
				neighbours.push(list[i]);

		if (neighbours.length > 0)
		{
			stack.push(current_cell);
			let chosen_cell = neighbours[random_int(0, neighbours.length)];
			remove_wall((current_cell[0] + chosen_cell[0]) / 2, (current_cell[1] + chosen_cell[1]) / 2);
			remove_wall(chosen_cell[0], chosen_cell[1]);
			grid[chosen_cell[0]][chosen_cell[1]] = 1;
			stack.push(chosen_cell);
		}

		else
		{
			remove_wall(current_cell[0], current_cell[1]);
			grid[current_cell[0]][current_cell[1]] = 2;
		}
	}, 16);
}

function kruskal_algorithm()
{
	fill_walls();
	let nb_areas = 0;
	let wall_list = [];

	for (let i = 1; i < grid.length - 1; i++)
		for (let j = 1; j < grid[0].length - 1; j++)
		{
			if (i % 2 == 1 && j % 2 == 1)
			{
				nb_areas++;
				grid[i][j] = nb_areas;
			}

			if ((i + j) % 2 == 1)
				wall_list.push([i, j]);
		}

	my_interval = window.setInterval(function()
	{
		while (true)
		{
			if (nb_areas == 1)
			{
				clearInterval(my_interval);
				clear_grid();
				generating = false;
				finish_generate();
				return;
			}

			let index = random_int(0, wall_list.length);
			let wall = wall_list[index];
			wall_list.splice(index, 1);
			let cell_pair;

			if (grid[wall[0] - 1][wall[1]] > -1)
				cell_pair = [grid[wall[0] - 1][wall[1]], grid[wall[0] + 1][wall[1]]];
			else
				cell_pair = [grid[wall[0]][wall[1] - 1], grid[wall[0]][wall[1] + 1]];

			if (cell_pair[0] != cell_pair[1])
			{
				for (let i = 1; i < grid.length - 1; i += 2)
					for (let j = 1; j < grid[0].length - 1; j += 2)
						if (grid[i][j] == cell_pair[0])
							grid[i][j] = cell_pair[1];

				remove_wall(wall[0], wall[1]);
				nb_areas--;
				return;
			}
		}
	}, 29);
}

function prim_algorithm()
{
	fill();
	let first_cell = [1, 1];
	remove_wall(first_cell[0], first_cell[1]);
	grid[first_cell[0]][first_cell[1]] = 1;
	let wall_list = [];
	let list = get_neighbours(first_cell, 1);

	for (let i = 0; i < list.length; i++)
		if (list[i][0] > 0 && list[i][0] < grid.length - 1 && list[i][1] > 0 && list[i][1] < grid[0].length - 1)
			wall_list.push(list[i]);

	my_interval = window.setInterval(function()
	{
		while (true)
		{
			if (wall_list.length == 0)
			{
				clearInterval(my_interval);
				clear_grid();
				generating = false;
				finish_generate();
				return;
			}

			let index = random_int(0, wall_list.length);
			let wall = wall_list[index];
			wall_list.splice(index, 1);
			let cell_pair;

			if (wall[0] % 2 == 0)
				cell_pair = [[wall[0] - 1, wall[1]], [wall[0] + 1, wall[1]]];
			else
				cell_pair = [[wall[0], wall[1] - 1], [wall[0], wall[1] + 1]];

			let new_cell;
			let valid = false;

			if (grid[cell_pair[0][0]][cell_pair[0][1]] < 1)
			{
				new_cell = cell_pair[0];
				valid = true;
			}

			else if (grid[cell_pair[1][0]][cell_pair[1][1]] < 1)
			{
				new_cell = cell_pair[1];
				valid = true;
			}

			if (valid)
			{
				remove_wall(wall[0], wall[1]);
				remove_wall(new_cell[0], new_cell[1]);
				grid[new_cell[0]][new_cell[1]] = 1;
				let list = get_neighbours(new_cell, 1);

				for (let i = 0; i < list.length; i++)
					if (list[i][0] > 0 && list[i][0] < grid.length - 1 && list[i][1] > 0 && list[i][1] < grid[0].length - 1)
						wall_list.push(list[i]);

				return;
			}
		}
	}, 28);
}

function wilson_algorithm()
{
	fill();
	let cell_list = [];

	for (let i = 1; i < grid.length - 1; i += 2)
		for (let j = 1; j < grid[0].length - 1; j += 2)
			cell_list.push([i, j]);

	let first_cell = cell_list[0];
	cell_list.splice(0, 1);
	grid[first_cell[0]][first_cell[1]] = 10;
	let current_cell = cell_list[random_int(0, cell_list.length)];
	let random_walk = true;
	let first_step = current_cell;
	let new_way_list = [];

	my_interval = window.setInterval(function()
	{
		if (cell_list.length == 0)
		{
			clearInterval(my_interval);
			clear_grid();
			generating = false;
			finish_generate();
			return;
		}

		if (random_walk)
			while (true)
			{
				let list = get_neighbours(current_cell, 2);
				let index;
				let chosen_cell;

				do
				{
					index = random_int(0, list.length);
					chosen_cell = list[index];
				}
				while (get_node(chosen_cell[0], chosen_cell[1]) == -2)

				grid[current_cell[0]][current_cell[1]] = -(index + 3);

				if (grid[chosen_cell[0]][chosen_cell[1]] == 10)
				{
					random_walk = false;
					current_cell = first_step;
					return;
				}

				else
					current_cell = chosen_cell;
			}

		else
		{
			if (grid[current_cell[0]][current_cell[1]] == 10)
			{
				current_cell = cell_list[random_int(0, cell_list.length)];
				random_walk = true;
				first_step = current_cell;

				new_way_list = [];
			}

			else
			{
				let index = -grid[current_cell[0]][current_cell[1]] - 3;
				let next_cell = get_neighbours(current_cell, 2)[index];
				let wall = [(current_cell[0] + next_cell[0]) / 2, (current_cell[1] + next_cell[1]) / 2];
				new_way_list.push(current_cell);
				new_way_list.push(wall);
				remove_wall(current_cell[0], current_cell[1]);
				remove_wall(wall[0], wall[1]);
				grid[current_cell[0]][current_cell[1]] = 10;

				for (let i = 0; i < cell_list.length; i++)
					if (cell_list[i][0] == current_cell[0] && cell_list[i][1] == current_cell[1])
					{
						cell_list.splice(i, 1);
						break;
					}

				current_cell = next_cell;
			}
		}
	}, 18);
}

function aldous_broder_algorithm()
{
	fill();
	let cells_nb = ((grid.length - 1) / 2) * ((grid[0].length - 1) / 2);
	let current_cell = [1, 1];
	remove_wall(current_cell[0], current_cell[1]);
	grid[current_cell[0]][current_cell[1]] = 1;
	cells_nb--;

	my_interval = window.setInterval(function()
	{
		if (cells_nb == 0)
		{
			clearInterval(my_interval);
			clear_grid();
			generating = false;
			finish_generate();
			return;
		}

		while (true)
		{
			let neighbours = [];
			let list = get_neighbours(current_cell, 2);

			for (let i = 0; i < list.length; i++)
				if (get_node(list[i][0], list[i][1]) != -2)
					neighbours.push(list[i]);

			let chosen_cell = neighbours[random_int(0, neighbours.length)];

			if (grid[chosen_cell[0]][chosen_cell[1]] != 1)
			{
				let wall = [(current_cell[0] + chosen_cell[0]) / 2, (current_cell[1] + chosen_cell[1]) / 2];
				remove_wall(wall[0], wall[1]);
				remove_wall(chosen_cell[0], chosen_cell[1]);
				grid[chosen_cell[0]][chosen_cell[1]] = 1;
				cells_nb--;
				current_cell = chosen_cell;
				return;
			}

			current_cell = chosen_cell;
		}
	}, 28);
}

function recursive_division()
{
	enclose();
	let time = 0;
	let step = 17;
	timeouts = [];

	function sub_recursive_division(x_min, y_min, x_max, y_max)
	{
		if (y_max - y_min > x_max - x_min)
		{
			let x = random_int(x_min + 1, x_max);
			let y = random_int(y_min + 2, y_max - 1);

			if ((x - x_min) % 2 == 0)
				x += (random_int(0, 2) == 0 ? 1 : -1);

			if ((y - y_min) % 2 == 1)
				y += (random_int(0, 2) == 0 ? 1 : -1);

			for (let i = x_min + 1; i < x_max; i++)
				if (i != x)
				{
					time += step;
					timeouts.push(setTimeout(function() { add_wall(i, y); }, time));
				}

			if (y - y_min > 2)
				sub_recursive_division(x_min, y_min, x_max, y);

			if (y_max - y > 2)
				sub_recursive_division(x_min, y, x_max, y_max);
		}

		else
		{
			let x = random_int(x_min + 2, x_max - 1);
			let y = random_int(y_min + 1, y_max);

			if ((x - x_min) % 2 == 1)
				x += (random_int(0, 2) == 0 ? 1 : -1);

			if ((y - y_min) % 2 == 0)
				y += (random_int(0, 2) == 0 ? 1 : -1);

			for (let i = y_min + 1; i < y_max; i++)
				if (i != y)
				{
					time += step;
					timeouts.push(setTimeout(function() { add_wall(x, i); }, time));
				}

			if (x - x_min > 2)
				sub_recursive_division(x_min, y_min, x, y_max);

			if (x_max - x > 2)
				sub_recursive_division(x, y_min, x_max, y_max);
		}
	}

	sub_recursive_division(0, 0, grid.length - 1, grid[0].length - 1);
	timeouts.push(setTimeout(function() { generating = false; timeouts = [] }, time));
}

function maze_generators()
{
	generating = true;

	grid_clean = false;

	console.info("Starting maze generation")
	switch(selectedGenAlgorithm) {
		case 1: 
			randomized_depth_first();
			break;
		case 2:
			kruskal_algorithm();
			break;
		case 3:
			prim_algorithm();
			break;
		case 4:
			wilson_algorithm();
			break;
		case 5:
			aldous_broder_algorithm();
			break;
		case 6:
			recursive_division();
			break;
		default:
			kruskal_algorithm();
			break;
	}
}

function finish_generate() {
	grid[start_pos[1]][start_pos[0]] = 2;
	console.log(grid);
	console.log(start_pos);
	console.log(target_pos);
	setTimeout(() => {
		maze_solvers();
	}, 1000)
}
