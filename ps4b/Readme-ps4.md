# PS4: Sokoban

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 12 hours


## Description
In this project we are creating a version of the Sokoban game. The objective of the game is for the player to push the red boxes into the storage locations. The sokoban.zip file has text files with various levels in them which are recreated in this program.  The second part of the project is geared towards implementing the movements in the Sokoban Game. We are required to build a working move function, reset funtion, and check for victory.

### Features
I decided to store level data as a grid vector because it would make it easy for indexing and also when implementing my operator>>, and operator<< functions.  I also used a loadTexture function to load all textures at once when it is called so that my program does not have to be load the textures repeatedly. In part because of the project we have to implement the movePlayer(), reset(), and isWon() function.

#### Part a
In part A of the project we have to implement the Sokoban class, which is where different levels data is stored. Each level text file had an arrangement of symbols which were the converted to their corresponding images and rendered as output. These symbols included: # (grey wall), . (ground), @ (player), A (Red box), a (storage spot).  I wrote code for the operator>>, operator<< which is meant to read and write the levels from stream accordingly.  I also created the protected virtual void method named draw as mentione din the instructions to display the game.

#### Part b
In part because of the project we have to implement the movePlayer(), reset(), and isWon() function. The reset function should allow the user to reset (and restart) the game by pressing 'R'. The movePlayer() is the base/fundamental function responsible for programming the movement of the player and boxes. I used the Direction enum and translated it into a 2D vector to handle movement in different directions. 

In terms of handling collisionsLastly, the isWon() function is used to declare victory. Many things need to taken into consideration when declaring victory because in the case that the number of targets or boxes are greater than the other, we still need to be able to recognize victory. 

### Memory
I stored level data as a std::vector<std::string>. I did not use any dynamic memory allocation so I did not haev any smart pointer (shared or unique).

### Lambdas
I used the Lambda expressions to count boxesOnTargets, totalBoxes, and totalTargets. Then I utilized these lambda expressions as parameters to the std::count_if function from the algorithm library for my isWon() function. The use of lambdas and the algorithm function makes the code concise and reduces the chance of off-by-one errors in my code. Previously I was creating loops inside of the isWon() function which made the fucntion a lot more lengthy and harder to read. 

### Issues
I had issues with my Makefile. I was able to run my program on my personal terminal but the Gradescope autograder was not able to find Sokoban.a. This is because I did not write Sokoban.a in the project root and instead had it inside the build/ subdirectory. However, with a bit of trial and error I was able to fix it.  I also had some trouble with my draw function as I struggled with the placement of the ground tiles. Initially the player did not have the ground background but when I tried fixing that I added the background to the entire screen while in the correct output the ground should not be under the gray walls. So I had to rewrite my if-else statement inside of the draw function a couple of times before I was able to render the correct output.

In part B I particularly struggled with creating the Missing Symbol Test. In addition to problems with the test, I also had memory allocation problems that caused all new tests in the actual Sokoban assignment to fail. In order to fix this I had to change the memory allocation and access. I initially had the board stored as a vector string which was most likely the reason memory was violated inside of the isWon() funtion and the reset() function. In order to rectify this problem I changed the vecyor string to use the grid vector instead.

### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements
https://www.sfml-dev.org/documentation/3.0.0/ - referred to the documentation for SFMl when writing functions.
https://www.google.com/search?client=safari&rls=en&q=functions+in+algorithm+library+c%2B%2B&ie=UTF-8&oe=UTF-8 - used to figure out what algorithm library functions to use
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
