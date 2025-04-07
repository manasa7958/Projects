# PS5: DNA Alignment

## Contact
Name: Ponita Ty
Section: 202

Partner: Manasa Praveen
Partner Section: 202

Time to Complete: 6 hours

## Description
Explain what the project does
The PS5 is meant to create a DNA sequence alignment tool using edit distance. The edit distance calculates the minmum cost of aligning two different DNA strings by assigning different cost values for different operations. In the case of insertion or deletion the cost is 2, for subsitution the cost varies between 1 and 0 depending on whether or not the characters differ or matcht. The program then also reconstructs the optimal alignment path and reports the time it had taken to do so.

### Features
Explain how you did the actual alignment including the data structures used.
We needed to implement the Hirschberg's Algorithm as indicated in the instructions to create an efficient algorithm that computer the DNA sequence alignments in linear space. We used the std::vector for scoring the matrices and linear space-array, as well as the std::ostringstream for efficienct string building. 

### Testing
Describe what the unit tests you wrote check for and why you picked them.
Our unit tests checked to make sure our min3 function works optimally by making sure the distance is calculated properly. We also tested edge/unusual cases like empty string, strings of unequal length, head/tail deletions, reversed strings, and cut ends. We also created a no throw test to make sure that an error is not thrown in the case that a valid input is being run.
These tests should ensure the correctness of our functions from the EDistance.cpp file by catching off-by-one bugs and ensuring the algorithm handles simple and tricky strings without crashing.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.


## Analysis

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Please list:
 - a copy of the test case input
 - the expected test case output
 - whether your program ran correctly on it or not
 - optionally, any other remarks

### Specs
Your Computer
Memory: 8 GB, 2133 MHz, LPDDR3
Processors: 1.4 GHz Quad-Core Intel Core i5

Partner's Computer
Memory: 8 GB, unified memory
Processors: Apple M2 (8-core CPU, 2022 MacBook Air)

### Runs
Fill in the table with the results of running your code on both your and your partner's computers.

| data file     | distance | memory (mb) | time (seconds) | partner time |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  | 118      |             | 0.87279        |  0.422032    |
|ecoli5000.txt  | 160      |             | 3.56677        |  1.68111     |
|ecoli10000.txt | 223      |             | 14.1065        |  6.70453     |
|ecoli20000.txt | 3135     |             | 70.7839        |  33.4179     |
|ecoli50000.txt | 19485    |             | 443.296        |  211.453     |
|ecoli100000.txt| 24166    |             | 1788.53        |  843.177     |

Here is an example from another computer for some of the files.

| data file    | distance | time (s) |
|--------------|----------|----------|
|ecoli2500.txt |      118 |    0.171 |
|ecoli5000.txt |      160 |    0.529 |
|ecoli7000.txt |      194 |    0.990 |
|ecoli10000.txt|      223 |    1.972 |
|ecoli20000.txt|     3135 |    7.730 |

### Time
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of youu program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b. Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
 - a = 
 - b = 
 - largest N = 

### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.
 - a = 
 - b = 
 - largest N = 

### Valgrind
Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

| data file     | Calculated (mb) | Measured (mb) | Difference (%) |
|---------------|-----------------|---------------|----------------|
|ecoli2500.txt  |                 |  32.29        |                |
|ecoli5000.txt  |                 |  105.25       |                |
|ecoli10000.txt |                 |  522.92       |                |
|ecoli20000.txt |                 |  9.84         |                |
|ecoli50000.txt |                 |  12.03        |                |
|ecoli100000.txt|                 |  11.85        |                |

## Pair Programming
If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?

## Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
