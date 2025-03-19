# PS3: N-Body Simulation

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 15 hours


## Description
In this project we are trying to make a static universe using SFML. In this project files are read, so in the example scrrenshot we had to include in the project the program reads planet.txt and then generates a window with planets (bodies) in the corresponding positions. Each planet has data correspnding to their position, velocity, mass, and an image as well. In part A of the project the main focus is on rendering the images in their respective positions. In part B the main objective of the project is to simulate the movement of the planets around the sun by calculating accelaration and force. 

### Features
Part a: I think having CelestBody and Universe hpp files already set up it was easier to build based on that. The CelestialBody files mainly focus on individual bodies or planets. It includes methods to read, write and draw the planets, as well as scale them. The Universe files focuses on the project as a whole including making the window, reading planet data, and drawing the background. Deciding when to use smart pointers and where to use was something I had to figure out. I decided to make std::shared_ptr<CelestialBody> as a shared smart pointer for both the CelestialBody and Universe files. This helps prevent memory leaks and also the efficiency of coding. The scaling was also another feature that I had to spend quite some time on and used a lot of guessing and checking to get the proportions right. 

Part b: In part b we had to implement the draw function, as well as the shared pointers. I had to write code for the step funciton in Universe.cpp file, which was the base function that ran the UAM equatiosn essential to program. I decided to make shared pointers for the Texture for the project. I had to pay close attention to the scaling of the planets as well as making sure my equations were correct. This was something I struggled with initially and was not able to fix until the redo. 

### Memory
Describe how you managed the lifetimes of your objects, including if you used smart pointers.
I did use smart pointers in this project as it was suggested by the rubric. I had to look up how to use smart pointers and understand them because I was not very confident in using them. Using shared pointers helps with deletion, because this makes it so that manual deletion is not really needed. It also helps with the prevention of memory leaks, and makes it a lot easier to code because I don't have to create two of the same pointer for the files and instead can share them. 
In this project I initially planned on using a shared pointer for the ClestialBody but then ended up shared pointer for Texture ans Sprite because I was able to realize that the CelestiaBodies do NOT need to be smart pointers but the texture and sprite which is accesed by both Universe adn well CelestialBody should be a shared pointer. This really helped with my approach to coding for part B when I was working on the PSXa. 

### Issues
Part a: I had a lot of trouble with generating the planets into my window because for some reason the planets were not being diaplyed correctly. So then I had to debug my files to figure out if there was an issue with the files being read correctly, or if the drawable function was being called appropriately. I also had to check if positioning was the problem. In the end the scaling was indeed one of the biggest concerns which was why the planets were not being displayed correctly on my end. 
As of now from my understanding my code should work correctly.
I also did have trouble with my formatting test. When working on the test.cpp I did a dummy submission on Gradescope to figure out the criterias that were being testsed and then wrote my tests accordingly. I did not have too much trouble with my emptyUniverse testing nor the flipped values testing but my formatting testing had me stuck for a while. I had to rewrite parts of it mutliple times and then tried comparing the expected and actual strings which lead to errors. In the end I tried getting the output's string to be reassigned to another variable and then tried checking that way. 

Part b:
I have recurring problems with my tests, I keep failing the noaccelration, antigravity, and inverted tests. I am certain that the tests are failing because of faulty code in my step function but I am unable to fix it.

### Extra Credit
Part a: I added a background image to the SFML window. I also made sure to dynamically scale the background. I downloaded a jpg image from the internet that I thought would be appropriate as a background for the planets and then wrote the code for it in my Universe.cpp file. Most of the code remained rather basic I just had to put in effort into scaling of the photo because initially it only covered a bit of the window.

### Changes
When redoing my ps3b project I worked on step function within the Universe file. I ended up scrapping all of my code and trying to rebuild it from scratch because none of the changes I made to the code seemed to be working. Most of my edits in Universe files included the created of a shared pointer for Sprites. This radically changed my code and made it a lot more efficient. I also edited my step and draw functions within the Universe file to correctly calculate the movement. Earlier despite being able to score well on the autograder I was not able to actually simulate movement on the window but now my planets revolve around the sun in the correct manner. I had to create several different versions of the step function before I finally succeeded I had a lot of trouble calculating the force and ensuring that the planets move counterclockwise.

In addition to changes in the code, I also edited my Readme file, as I had previously not added explanation for part b of my project during my submission.

## Acknowledgements
https://www.istockphoto.com/photos/galaxy-sky - background image

https://www.geeksforgeeks.org/iomanip-in-cpp/ - to learn about iomanip

https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/ - learning about smart pointers
