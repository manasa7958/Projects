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
n designing and implementing the recursive Sierpiński Triangle fractal, I made several key decisions regarding structure, rendering, scaling, and recursion. These decisions were influenced by the requirements of the project, the need for proper visualization, and the constraints of SFML.
Instead of using raw pixel drawing, I chose sf::ConvexShape (a built-in SFML class for polygons).
Each triangle is represented as a three-point polygon.
This allows easy manipulation, color control, and rendering with anti-aliasing support.



### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
We really struggled with dynamically scaling the triangle fractal and were stuck in it for a while honestly. (NEED HOW WE FIXED THIS). Additionally, we were also struggling with the mathematical calculations for a bit as the both of us found it easier to draw the traditional Sierpinski triangle than the variation that we needed to submit for this project. 
Also, initially while building this program we were hardcoding the depth and not using user input but once we were able to get the other mathematical calculations we were able to change the program so that it uses the depth indicated by the user. 

### Extra Credit
We added color to the program, so that it changes based on the depth of the fractal. I used four different colors and then employed modulo 4 to assign specific color based on the number of the level.

## Pair Programming
How did working with a partner affect your work?

I think working with a partner helped both of us. I think when we struggled with different things we were able to brainstorm and form ideas a lot more quickly because we were working with one another. It also definitely helped lessen the workload, since the PS2 project is notorious for being time-consuming working with a partner helped make the project feel less overwhelming. 

## Acknowledgements
https://bjc.edc.org/bjc-r/cur/programming/3-lists/1-abstraction/2-fractal-art.html
https://bjc.edc.org/bjc-r/cur/programming/3-lists/old/2-sorting/1-recursion.html
