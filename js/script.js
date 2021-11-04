"use strict";

function init_css_properties_before()
{
	document.querySelector("#menu").style.width = menu_width.toString(10) + "px";
	document.querySelector("#visualizer").style.width = (window.innerWidth - menu_width).toString(10) + "px";
	document.querySelector("#visualizer").style.left = menu_width.toString(10) + "px";
}

function init_css_properties_after()
{
	document.querySelector("#grid").style.width = (cell_size * grid_size_x).toString(10) + "px";
	document.querySelector("#grid").style.height = (cell_size * grid_size_y).toString(10) + "px";
}

window.onload = function()
{
	init_css_properties_before();
	generate_grid();
	init_css_properties_after();

	window.addEventListener('resize', () =>
	{
		clear();
	});

	visualizer_event_listeners();
	menu_event_listeners();

	document.querySelector("#hider").style.visibility= "hidden";
}
