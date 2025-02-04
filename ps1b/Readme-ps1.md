# PS1: LFSR / PhotoMagic

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 5 hours


## Description
Part a: The purpose of this project is to procude psedo-random bits by simulating a linear feedback shift register (LFSR). In part a of the project we need to define necessary functions like the generate and step functions. Our code is then tested to ensure that the appropriate results are obtained (in this project we use tap positions at 13, 12, and 10).
Part b: The purpose of this project is to encode and decode the cat.jpg image using the base code that we had for part a. In this part we also use PhotoMagic and sfml to load the photo and encode messages inside of the image.

### Features
I had to brainstorm what kind of tests I want to implement, I made an LFSROutput test, noThrow test, wrongInsert test and modified the GeneratInstr test. I particularly struggled with the wringInsert test and had to resubmit my project multiple times to the autograder.

#### Part a
I made an LFSROutput test, noThrow test, wrongInsert test and modified the GeneratInstr test. In the second part of the project I defined necessary function and modfied the private class in the hpp file. I had to write code for the generate and step functions mainly. I did have to rework my step function multiple times because i had been trying to declare my tap positions instead if using their indexes. This had caused quite a bit of errors but then I chose to directly use the indexes and that made my program compile correctly.

#### Part b


### Issues
As of now there are no issues. My program is compiling correctly and my linting all seems to right as well. 

### Tests
There are a couple of major things that are being tested, as outlined by the requirements on gradescope. One of the first tests in my test.cpp file ensure that the step function that I defined in the FibLFSR.cpp file works correctl, the next test ensures that the genrate function defined works correctly. The third test make sure that the operator<< correctly prints the LFSR state. The fourth test looks to make sure the seeds that are being declared are valid, like they are the correct length (16-bit) and dont have any invalid characters. The last test is just looking to make sure the insertion is being correctly performed as it tests the shift.

### Extra Credit
Anything special you did. This is required to earn bonus points.

## Acknowledgements
Part a:
https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c  - I used this to figure how to store the seed in integer format
https://stackoverflow.com/questions/13865842/does-static-constexpr-variable-inside-a-function-make-sense - I was using this initially when I was trying to declare the tap psotions in my cpp instead of using the index
https://cplusplus.com/reference/algorithm/ - had a faint idea of the functions but this helped
Part b:

### Credits
The cat.jpg file provided in class was used for this project
