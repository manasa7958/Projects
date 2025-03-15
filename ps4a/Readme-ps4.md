# PS4: Sokoban

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 4 hours


## Description
In this project we are creating a version of the Sokoban game. The objective of the game is for the player to push the red boxes into the storage locations. The sokoban.zip file has text files with various levels in them which are recreated in this program. 

### Features
I decided to store level data as a std::vector<std::string> because it would make it easy for indexing and also when implementing my operator>>, and operator<< functions. 

I also used sf::Texture to store the images as this would eliminate the need to load each image repeatedly. 

Lastly, when trying to mimic the output from the instructions file I made sure to draw the ground texture first, and then the other objects to avoid redundant rendering. 

#### Part a
In part A of the project we have to implement the Sokoban class, which is where different levels data is stored. Each level text file had an arrangement of symbols which were the converted to their corresponding images and rendered as output. These symbols included: # (grey wall), . (ground), @ (player), A (Red box), a (storage spot).
I wrote code for the operator>>, operator<< which is meant to read and write the levels from stream accordingly. 
I also created the protected virtual void method named draw which is used to display the game.

#### Part b

### Memory
I stored level data as a std::vector<std::string>. I did not use any dynamic memory allocation so I did not haev any smart pointer (shared or unique).

### Lambdas
I used the std::find to locate the player, and the std::for_each to iterate throught the board and check for the win condition. I also used the Lambda expression std::any_of inside of my isWon() function to check if any boxes remained that were not in it's storage position yet. 

### Issues
I had issues with my Makefile. I was able to run my program on my personal terminal but the Gradescope autograder was not able to find Sokoban.a. This is because I did not write Sokoban.a in the project root and instead had it inside the build/ subdirectory. However, with a bit of trial and error I was able to fix it. 
I also had some trouble with my draw function as I struggled with the placement of the ground tiles. Initially the player did not have the ground background but when I tried fixing that I added the background to the entire screen while in the correct output the ground should not be under the gray walls. So I had to rewrite my if-else statement inside of the draw function a couple of times before I was able to render the correct output.

### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements
https://www.sfml-dev.org/documentation/3.0.0/ - referred to the documentation for SFMl when writing functions.
https://www.google.com/search?client=safari&rls=en&q=functions+in+algorithm+library+c%2B%2B&ie=UTF-8&oe=UTF-8 - used to figure out what algorithm library functions to use
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
