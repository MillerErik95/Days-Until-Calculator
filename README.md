Time Left Calculator with Signal Handling

Summary:
This C++ program is designed to handle two types of signals (SIGINT and SIGALRM) to calculate and display the time left until specific dates, namely the Fourth of July and Christmas Day in 2023. The program demonstrates the use of signal handling to manage asynchronous events and provides an interactive way to handle interruptions.

Key Features:
Signal Handling:

SIGINT (Ctrl+C): Triggers the calculation of time left until the Fourth of July. After three interrupts, it prompts the user to decide whether to quit.
SIGALRM: Triggers the calculation of time left until Christmas Day. The alarm interval alternates between 3 and 8 seconds based on the sequence number.
Time Calculation:

Calculates the number of days, hours, minutes, and seconds remaining from the current time to the specified target date (Fourth of July or Christmas Day).
Formatted Output:

Prints the current date and time in a formatted string.
Displays the calculated time left until the target date in a user-friendly format, including the total number of seconds.
User Interaction:

After three SIGINT signals, the program prompts the user with an option to quit or continue.
Error Handling:

Ensures proper signal handling and user input processing to avoid crashes and undefined behavior.
Usage:
Running the Program:
Compile the program and run it in a Unix-like environment.
The program sets an initial alarm to go off in 3 seconds and enters an infinite loop, waiting for signals.
Interacting with the Program:
Press Ctrl+C to trigger the SIGINT signal and calculate the time left until the Fourth of July.
The program will alternately trigger the SIGALRM signal to calculate the time left until Christmas Day.
Example Output:
Upon receiving a SIGINT:
yaml
Copy code
0 By SIGINT:
Current date and time: 2024-06-21 Friday 01:23:45 PM, PDT
Until 2023 Fourth of July: 13 days, 10 hours, 36 minutes, 15 seconds
Total number of seconds: 1164815
Upon receiving a SIGALRM:
yaml
Copy code
1 By SIGALRM:
Current date and time: 2024-06-21 Friday 01:23:48 PM, PDT
Until 2023 Christmas Day: 187 days, 12 hours, 36 minutes, 12 seconds
Total number of seconds: 16229772
This program serves as a practical example of using signals to handle asynchronous events in a Unix-like operating system, making it a useful tool for learning about system calls, time calculations, and user interaction in C++.
