# PS1: LFSR / PhotoMagic

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 3 hours


## Description
The purpose of this project is to procude psedo-random bits by simulating a linear feedback shift register (LFSR). The project has been split into parts a and b, the first part requires us to create different tests that are implemented by the Boost.Test. In the second part of the project we need to define necessary functions like the generate and step functions. Our code is then tested to ensure that the appropriate results are obtained (in this project we use tap positions at 13, 12, and 10).

### Features
I had to brainstorm what kind of tests I want to implement, I made an LFSROutput test, noThrow test, wrongInsert test and modified the GeneratInstr test. I particularly struggled with the wringInsert test and had to resubmit my project multiple times to the autograder.

#### Part a
I made an LFSROutput test, noThrow test, wrongInsert test and modified the GeneratInstr test.

My LFSR is represented using a 16-bit string because this makes the indexing of the tap positions a lot more simpler. I specifically store it as an std::string so I do not need to worry about using bitwise operations or bitmasking. I think this benefitted my code implmentation allowing for it to be easier to utilize when validating inputs and tracking changes over time. 
The way I stored my LFSR also made debugging a lot more simpler, because I previously tried storing it as integers but soon realized that would be make it a lot more complicated.

#### Part b
In the second part of the project I defined necessary function and modfied the private class in the hpp file. I had to write code for the generate and step functions mainly. I did have to rework my step function multiple times because i had been trying to declare my tap positions instead if using their indexes. This had caused quite a bit of errors but then I chose to directly use the indexes and that made my program compile correctly.

### Issues
As of now there are no issues. My program is compiling correctly and my linting all seems to right as well. 

### Tests
There are a couple of major things that are being tested, as outlined by the requirements on gradescope. One of the first tests in my test.cpp file ensure that the step function that I defined in the FibLFSR.cpp file works correctl, the next test ensures that the genrate function defined works correctly. The third test make sure that the operator<< correctly prints the LFSR state. The fourth test looks to make sure the seeds that are being declared are valid, like they are the correct length (16-bit) and dont have any invalid characters. The last test is just looking to make sure the insertion is being correctly performed as it tests the shift.

### Extra Credit
Anything special you did. This is required to earn bonus points.

### Changes
I added an explnation on how my LFSR was represented in this code and the reasoning behing the choices I made. This change is added in the Part A section of the Readme file.

## Acknowledgements
https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c  - I used this to figure how to store the seed in integer format
https://stackoverflow.com/questions/13865842/does-static-constexpr-variable-inside-a-function-make-sense - I was using this initially when I was trying to declare the tap psotions in my cpp instead of using the index
https://cplusplus.com/reference/algorithm/ - had a faint idea of the functions but this helped
### Credits
NO images or audio used in this project
