"use strict";

function hidden_clear()
{
	for (let i = 0; i < timeouts.length; i++)
		clearTimeout(timeouts[i]);

	timeouts = [];
	clearInterval(my_interval);
	delete_grid();

	if (window.innerWidth > menu_width + 50)
	{
		init_css_properties_before();
		generate_grid();
		init_css_properties_after();
		visualizer_event_listeners();
	}
}

function clear()
{
	document.querySelector("#slct_2").value = "0";
	hidden_clear();
}

function menu_event_listeners()
{
	document.querySelector("#slct_2").addEventListener('change', event =>
	{
		maze_generators();
	});

	document.querySelector("#clear").addEventListener('click', event =>
	{
		let start_temp = start_pos;
		let target_temp = target_pos;
		clear();
		place_to_cell(start_pos[0], start_pos[1]).classList.remove("start");
		place_to_cell(start_temp[0], start_temp[1]).classList.add("start");
		place_to_cell(target_pos[0], target_pos[1]).classList.remove("target");
		place_to_cell(target_temp[0], target_temp[1]).classList.add("target");
		start_pos = start_temp;
		target_pos = target_temp;
	});

	document.querySelector("#play").addEventListener('click', event =>
	{
		if (generating)
			document.querySelector("#slct_2").value = "0";

		generating = false;
		clear_grid();
		maze_solvers();
	});
}
