# Maze solver

![Release](https://img.shields.io/badge/Release-v4.0-blueviolet)
![Language](https://img.shields.io/badge/Language-JavaScript-ffcc14)
![Size](https://img.shields.io/badge/Size-346Ko-f12222)
![Open Source](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)

<br/>

This repository contains the source code of a web page that can generate and solve mazes using several algorithms. You can also move the start and the finish or draw your own walls.

The web page is online at the address : **[angeluriot.com/maze_solver](https://angeluriot.com/maze_solver/)**.

<br/>

<p align="center">
	<img src="https://i.imgur.com/iSW6t5e.png" width="700">
</p>

<br/>

# Summary

* **[Summary](#summary)**
* **[Features](#features)**
* **[Tests](#tests)**
	* [Maze generation algorithms](#maze-generation-algorithms)
	* [Pathfinding algorithms](#pathfinding-algorithms)
* **[Credits](#credits)**

<br/>

# Features

* You can choose the pathfinding algorithm of the maze solver :

<p align="center">
	<img src="https://i.imgur.com/D09nORf.png" width="250">
</p>

* You can move the start and the finish :

<p align="center">
	<img src="https://i.imgur.com/g40S4LH.png" width="500">
</p>

* You can also add and remove walls on the grid :

<p align="center">
	<img src="https://i.imgur.com/q7ZHJY5.png" width="500">
</p>

* But the program is also able to generate a maze and you can choose the algorithm :

<p align="center">
	<img src="https://i.imgur.com/GPM7rNP.png" width="250">
</p>

* The `Clear` button allows you to clear the grid and the `Start` button runs the pathfinding algorithm

<br/>

# Tests

### Maze generation algorithms

* **Randomized Depth-First :**

<p align="center">
	<img src="https://i.imgur.com/QOOM5Fc.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/bprV2tG.png" width="45%">
</p>

* **Kruskal's Algorithm :**

<p align="center">
	<img src="https://i.imgur.com/c3n5hgD.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/56vkvMf.png" width="45%">
</p>

* **Prim's Algorithm :**

<p align="center">
	<img src="https://i.imgur.com/zSNwWtw.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/JhGrzpK.png" width="45%">
</p>

* **Wilson's Algorithm** *(unbiased)* **:**

<p align="center">
	<img src="https://i.imgur.com/WofYqen.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/Wz3ovhz.png" width="45%">
</p>

* **Aldous-Broder Algorithm** *(unbiased)* **:**

<p align="center">
	<img src="https://i.imgur.com/Haur1ls.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/GPJqEE5.png" width="45%">
</p>

* **Recursive Division :**

<p align="center">
	<img src="https://i.imgur.com/mUXuKQ7.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/cc08aQT.png" width="45%">
</p>

<br/>

### Pathfinding algorithms

* **Breadth-First** *(Slow but gives the shortest path)* **:**

<p align="center">
	<img src="https://i.imgur.com/Sb6UDvx.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/V0aXTsQ.png" width="45%">
</p>

* **Bidirectional Breadth-First** *(A little less slow and gives the shortest path)* **:**

<p align="center">
	<img src="https://i.imgur.com/gSX6FH7.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/eK4Ddj9.png" width="45%">
</p>

* **Greedy Best-First** *(Very fast but does not always give the shortest path)* **:**

<p align="center">
	<img src="https://i.imgur.com/nXbSHOQ.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/yv3DlFy.png" width="45%">
</p>

* **Dijkstra** *(Slow but gives the shortest path)* **:**

<p align="center">
	<img src="https://i.imgur.com/Sb6UDvx.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/V0aXTsQ.png" width="45%">
</p>

* **A\*** *(Fast and gives the shortest path)* **:**

<p align="center">
	<img src="https://i.imgur.com/7sII5LX.png" width="45%">
	<span>&nbsp;&nbsp;&nbsp;</span>
	<img src="https://i.imgur.com/IChJALl.png" width="45%">
</p>

<br/>

# Credits

* [**Angel Uriot**](https://github.com/angeluriot) : Creator of the project.
