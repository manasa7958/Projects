# PS7: Kronos Log Parsing

## Contact
Name: Manasa Praveen
Section: 202
Time to Complete: 7 hours


## Description
PS7 parses intouch log files to identify and report boot events. Each log file contains entries that track when a device starts and completes the booting process recording the total time in milliseconds. The program then will generate a report showing each boot event, and other such data.

### Features
For this project I set up a BootState structure that keeps all of the current boot's state making it easy to manage, before I was using variables that makes it harder to manage. I also made my error handling a lot more robust which helped when building my code in the first place. I used boost::regex_search for boot start entries and boost::regex_match for end entries to allow for partial or dull matching depending on what is appropriate and necessary in each situation. I had to put in a lot of thought into this because a lot of my submission kept timing out on Autograder. I also build a lambda expression builTimestamp() for my timestamp parsing that handles errors efficiently and prevent any malformed lines. 

### Approach
I used a BootState object to keep trach of all the current Boot states and then each time a start was found I marked it and then looked throught to find the matching end. If I did find the end pair then I would record the time duration. If in between this process another start boot is noted then the previous one was marked as incomplete. I used a single-pass approach and it helped with memory usage and simplified my matching logic significantly. 

### Regex
My boot start pattern: 
R"((\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2}): \(log\.c\.166\) server started)"
This pattern matches log entries indicating the start of the boot pattern. It extracts the year, month, day, hour, minutes, and second. 
My boot end pattern:
R"((\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2})\.(\d{3}):INFO:oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080)"
This pattern matches the log entries indication the end of the boot pattern. It captures the date and time along with the milliseconds data as well.

### Issues
In terms of linting I was initally using the namespace directives so I needed to change that and only use the boost declrations now. I was able to successfully implement lambda expression to improve speed and readability of my code. I also had a lot of trouble with the amount of time my program was taking to run and had to make choices and understand how to code more efficiently. One of the choices I made to address that was use boost::regex_match and boost::regex_search depending on what is needed in different cases. 

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
I did refer to all of the notes on regex provided and blackboard.

