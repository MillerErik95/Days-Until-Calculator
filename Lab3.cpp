#include <iostream>
#include <sys/time.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <signal.h>
#include <unistd.h>

#define MDT (-6)
using namespace std;

struct TimeLeftResult 
{
    int totalSeconds;
    int days;
    int hours;
    int minutes;
    double seconds;
};

void daysLeft(time_t target_date, const char *signame, int signum);
void sigintHandler(int signum);
void sigalrmHandler(int signum);
TimeLeftResult timeLeft(time_t target_date);
void printfTime(time_t current);
void checkSeconds(TimeLeftResult result); 

static int interruptCount = 0; /* Tracks the amount of CTRL-C interrupt count */
static int sequenceNumber = 0; /* Interval of time between sequences */

int main() 
{
    struct sigaction int_action, alrm_action;

    /* SIGINT signal handling */ 
    int_action.sa_handler = sigintHandler;
    sigemptyset(&int_action.sa_mask);
    int_action.sa_flags = 0;
    sigaction(SIGINT, &int_action, NULL);

    /* SIGALRM signal handling */
    alrm_action.sa_handler = sigalrmHandler;
    sigemptyset(&alrm_action.sa_mask);
    alrm_action.sa_flags = 0;
    sigaction(SIGALRM, &alrm_action, NULL);

    alarm(3);
    while (1) 
    {
        pause();
    }
    return 0;
}

/* Prints output to console */
void daysLeft(time_t target_date, const char *signame, int signum) 
{
    time_t current;
    time(&current);
    TimeLeftResult result = timeLeft(target_date);

    printf("%d By %s:\n", sequenceNumber++, signame);
    printfTime(current);
    printf("Until %d %s : %d days, %d hours, %d minutes, %d seconds\n",
           localtime(&target_date)->tm_year + 1900,
           (signum == SIGINT ? "Fourth of July" : "Christmas Day"),
           result.days, result.hours, result.minutes, (int)result.seconds);
    printf("Total number of seconds: %d\n\n", result.totalSeconds);
}

/* Calculates time left from current time to target date */
TimeLeftResult timeLeft(time_t target_date) 
{
  time_t current;
  time(&current);

  /* difftime calculates the difference between two times in seconds */
  double seconds = difftime(target_date, current);

  int days = seconds / (60 * 60 * 24);
  seconds -= days * (60 * 60 * 24);
  int hours = seconds / (60 * 60);
  seconds -= hours * (60 * 60);
  int minutes = seconds / 60;
  seconds -= minutes * 60;

  int totalSeconds = static_cast<int>(difftime(target_date, current));

  TimeLeftResult result = {totalSeconds, days, hours, minutes, seconds};
  return result;
}

/* Prints formatted Time */
void printfTime(time_t current) 
{
  char buffer[100];
  strftime(buffer, sizeof(buffer), "Current date and time: %Y-%m-%d %A %I:%M:%S %p, %Z\n", localtime(&current));
  cout << buffer;
}

/* SIGINT signal handler */
void sigintHandler(int signum) 
{
  time_t julyFourth;
  struct tm julyFourth_tm = {0};

  julyFourth_tm.tm_year = 2023 - 1900;
  julyFourth_tm.tm_mon = 6;
  julyFourth_tm.tm_mday = 4;
  julyFourth = mktime(&julyFourth_tm);

  /* Returns days left fourth of july */
  daysLeft(julyFourth, "SIGINT", signum);

  interruptCount++;

  /* Handles CTRL-C  */
  if (interruptCount > 2) 
  {
      exit(0);
  } else 
  {
    char answer;
    do 
    {
      printf("Do you want to quit? (y/n): ");
      scanf(" %c", &answer);
    } 
    while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');
      if (answer == 'y' || answer == 'Y') 
      {
        exit(0);
      }
  }
}

/* SIGALRM signal handler */
void sigalrmHandler(int signum) 
{
    time_t Christmas;
    struct tm Christmas_tm = {0};

    Christmas_tm.tm_year = 2023 - 1900;
    Christmas_tm.tm_mon = 11;
    Christmas_tm.tm_mday = 25;
    Christmas = mktime(&Christmas_tm);

  /* Returns days left Christmas */
  daysLeft(Christmas, "SIGALRM", signum);

  /* Alarm set based on sequence number */
  if (sequenceNumber % 2 == 0) 
  {
    alarm(8);
    } else 
  {
    alarm(3);
    }
  }

/* Verify that the total number of seconds from the question 4
   above actually converts to the answer of question 3.         */ 
void checkSeconds(TimeLeftResult result) 
{
  int totalSeconds1 = result.days * 60 * 60 * 24 + result.hours * 60 * 60 + result.minutes * 60 + result.seconds;
  if (result.totalSeconds == totalSeconds1) 
  {
         cout << "The total number of seconds.. " << result.totalSeconds << " is correctly converted." << endl;
  } else 
  {
    cout << "Error: The total number of seconds is not correctly converted." << endl;
  }
}