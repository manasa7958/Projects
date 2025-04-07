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
One of the earliest struggles in this project was when we were creating our tests, we struggled with cut ends tests for a while and after some back and forth of trying different variations we were finally able to get our test to pass. We ended up making our cut ends test more robust making sure it explicitly tests for head and tail mismatches. We also made sure not only check for line count, but also make sure that expected charcter pairing were found. Nevertheless, this was a test we struggled on an went back and forth for a while before being able succesfully pass the autograder. 
Also, the both of us own Mac's and neither of our laptops support valgrind which is why we had to search for other ways to measure the memory used. We tried to install valgrind in homebrew but our latops did not support it so we had to research and find other ways to record the memory being used. We ended up using the acitivity monitor which is an in-built utility. In there we were able to see the memory used for each run in KB which we then converted to MB by dividing the KB by 1024. 


## Analysis

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Please list:
 - a copy of the test case input
   Input 1: TGCA
   Input 2: ACGT
 - the expected test case output
   Edit distance = 4
   T A 1
   G C 1
   C G 1
   A T 1
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
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of your program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b. Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
 - a = 3.7359e-8
 - b = 2.0757
 - largest N = 905,171
I used the doubling method to calculate the constant b. In the doubling method we use pairs of input with them being N and 2N. Once we repeated this process pf calculting b for pairs (ecoli2500, ecoli5000), (ecoli5000, ecoli10000), and so on we then averaged the answer to find our general value for the constant b. Once we solved for the constant b, we were able to substitute it into the formula while plugging a known point and love for constant a as well. Lastly, in order to estimate the largest N, we used 86400 (# of seconds in a day) as the time, while using the constants a and b we previously calculated to find N. We were also able to ensure our data works because the constant b we calculated is very close to 2, therefore closely modeling a quadratic formula and confirming our implementation works as expected.

### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.
 - a = 3.8147e-6
 - b = 2
 - largest N = 46,340

The code uses a @D dynamic programming table of size (N + 1)^2 integers. Since each of these integers use 4 bytes, so the toal memory being utilized is 4(N^2). To convert this into MB we divided by 1024^2. I was then able to effectively solve for the constants a and b. All we had to do then was subsitute the constant values, as well as set 8GB (8192 MB) as the memory limit and solve for N accordingly.

### Valgrind
Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

| data file     | Calculated (mb) | Measured (mb) | Difference (%) |
|---------------|-----------------|---------------|----------------|
|ecoli2500.txt  |  23.86          |  32.29        |  35.33         |
|ecoli5000.txt  |  95.41          |  105.25       |  10.32         |
|ecoli10000.txt |  381.55         |  522.92       |  37.05         |
|ecoli20000.txt |  1526.03        |  9.84         |  99.36         |
|ecoli50000.txt |  9537.12        |  12.03        |  99.87         |
|ecoli100000.txt|  38147.74       |  11.85        |  99.97         |

Valgrind is not supported on either of our laptops so finding valrgind errors is not possible for us. 
As can be seen by the calculated percentage differences in the case of the large files starting from ecoli20000.txt the measured and calculated memory usage is drastically different. This is because the optDistance() and alignment() functions in our EDistance.cpp file doesn't build the enture table in the case the strings are longer than 10,000. Instead 1D arrays are used, which are a lot more space efficient and hence drop the memory usage drastically as well.

## Pair Programming
If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?
I think working with a partner helped both of us. I think when we struggled with different things we were able to brainstorm and form ideas a lot more quickly because we were working with one another. It also definitely helped lessen the workload and helped make the project feel less overwhelming. We switched a couple of different times, with one of us getting started on the testing first after which the other started building the base of the program. 


## Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
