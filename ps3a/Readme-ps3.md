# PS3: N-Body Simulation

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 9 hours


## Description
Explain what the project does.

### Features
Describe what your major decisions were and why you did things that way.

### Memory
Describe how you managed the lifetimes of your objects, including if you used smart pointers.
I did use smart pointers in this project as it was suggested by the rubric. I had to look up how to use smart pointers and understand them because I was not very confident in using them. 

### Issues
I had a lot of trouble with generating the planets into my window because for some reason the planets were not being diaplyed correctly. So then I had to debug my files to figure out if there was an issue with the files being read correctly, or if the drawable function was being called appropriately. I also had to check if positioning was the problem. In the end the scaling was indeed one of the biggest concerns which was why the planets were not being displayed correctly on my end. 
As of now from my understanding my code should work correctly.
I also did have trouble with my formatting test. When working on the test.cpp I did a dummy submission on Gradescope to figure out the criterias that were being testsed and then wrote my tests accordingly. I did not have too much trouble with my emptyUniverse testing nor the flipped values testing but my formatting testing had me stuck for a while. I had to rewrite parts of it mutliple times and then tried comparing the expected and actual strings which lead to errors. In the end I tried getting the output's string to be reassigned to another variable and then tried checking that way. 

### Extra Credit
I added a background image to the SFML window. I also made sure to dynamically scale the background. I downloaded a jpg image from the internet that I thought would be appropriate as a background for the planets and then wrote the code for it in my Universe.cpp file. Most of the code remained rather basic I just had to put in effort into scaling of the photo because initially it only covered a bit of the window.

## Acknowledgements
https://www.istockphoto.com/photos/galaxy-sky - background image

https://www.geeksforgeeks.org/iomanip-in-cpp/ - to learn about iomanip

https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/ - learning about smart pointers
