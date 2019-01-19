//@orig_author ntwong0 
//@orig_date 2019-01-18

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/* Practice with pthreads
 *
 * The following program executes two threads
 * 1. fcn_countToFive() increments global_val from 0 to 5
 * 2. fcn_printUntilFive() prints a message once each time global_val updates, until global_val exceeds 6
 *
 * Known issue:
 *  fcn_printUntilFive() sometimes prints one additional message, due to the race condition between the two threads: 
 *      if fcn_printUntilFive() has re-enters the while-loop before fcn_countToFive() increments global_val from 5 to 6, 
 *      but does not reach the if-comparison until after global_val is incremented to 6, then an additional message will print.
 *  
 *  /TODO Use a binary semaphore to lock global_val
 */

int global_val = 0;

void *fcn_countToFive(void *ptr);
void *fcn_printUntilFive(void *ptr);

int main()
{
    // printf("Hello world\n");
    // sleep(5);
    // printf("How are you?\n");
    pthread_t thread1, thread2;
    int iret1, iret2;
    char *msg1, *msg2;

    iret1 = pthread_create( &thread1, NULL, fcn_countToFive, (void*) msg1);
    iret2 = pthread_create( &thread2, NULL, fcn_printUntilFive, (void*) msg2);
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

    return 0;
}

void *fcn_countToFive(void *ptr)
{
    while(global_val < 6)
    {
        sleep(1);
        global_val++;
    }
}

void *fcn_printUntilFive(void *ptr)
{
    int local_val = -1;
    while(global_val < 6)
    {
        if(local_val == global_val);
        else
        {
            local_val = global_val;
            printf("Print this message %d more times.\n", 5 - global_val);
        }
    }
}
