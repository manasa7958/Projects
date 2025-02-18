# PS2: Triangle Fractal

## Contact
Name: Manasa Praveen

Section: 202

Partner Name: Ponita Ty

Partner Section: 202

Time to Complete: ~8 hours


## Description
In this project, we are tasked with creating a variation on the Sierpinski triangle. We use SFML to display the triangle fractal and are tasked with writing a recursive function that calculates and places the "child" triangles at the vertices of the relative "parent" triangle. The program allows the user to specify the size of the largest triangle and the depth being the number of iterations. One of the main objectives of this project is to ensure that the window in which the triangle fractal is being displayed changes dynamically so that the triangle fractal is never too small or spilling over. 

### Features
Describe what your major decisions were and why you did things that way.  How did you represent fractal elements and how did you compute their positions?
When creating this project some of the major decisions we needed to make concerned the rendering, scaling, and recursion. As can be seen from our code(triangle.hpp) we decided to sf::ConvexShape to build our triangle. We reviewed the SFML website to better understand how it worked. We represented fractal elements in a vector, as we realized this would make it easier to draw and iterate.
Additionally, when it came to building our triangle fractal we were having some trouble so instead of creating a recursive function at first we made an iterative function that could only go up to a depth of 2, this helped the user better understand the logic behind the calculations before we scaled up to do numerous recursions.
We also had to carefully choose the positioning of the "child" triangles. We started by first calculating the height of the triangle and then we used (x - L/2, y - h) for the top left, (x + L/2, y - h) for the top right, and (x - L/2, y - h) for the bottom.
Lastly, scaling was another feature that had us stumped before we decided to go with the calculation implemented in the program. Before that, both of us attempted several methods and even tried using margins.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
We struggled with dynamically scaling the triangle fractal and were stuck in it for a while. We ended up assigning a default windowWidth and windowHeight, which we then used to scale depending on the triangleHeight. We were stuck on the numbers involved in the scaling for a bit but with some trial and error, we were able to figure out a formula that worked for us. 
Additionally, we were also struggling with the mathematical calculations for a bit as both of us found it easier to draw the traditional Sierpinski triangle than the variation that we needed to submit for this project. 
Also, initially while building this program we were hardcoding the depth and not using user input but once we were able to get the other mathematical calculations we were able to change the program so that it uses the depth indicated by the user. 

### Extra Credit
We added color to the program so that it changes based on the depth of the fractal. We created a color array that stores four different colors (magenta, blue, yellow, and green) and then employed modulo 4 to assign specific colors based on depth.

## Pair Programming
How did working with a partner affect your work?
I think working with a partner helped both of us. I think when we struggled with different things we were able to brainstorm and form ideas a lot more quickly because we were working with one another. It also definitely helped lessen the workload, since the PS2 project is notorious for being time-consuming working with a partner helped make the project feel less overwhelming. 

## Acknowledgements
https://www.sfml-dev.org/tutorials/3.0/graphics/shape/#regular-polygons
https://bjc.edc.org/bjc-r/cur/programming/3-lists/1-abstraction/2-fractal-art.html
https://bjc.edc.org/bjc-r/cur/programming/3-lists/old/2-sorting/1-recursion.html
