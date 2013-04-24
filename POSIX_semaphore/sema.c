#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

/*http://www.freepascal.org/docs-html/rtl/unixtype/sem_t.html
Semaphore declaration*/
sem_t * sem_id;

/**
 * Signal Handler for CTRL^C
 * We need this signal handler because some times when 
 * manully kill the process by pressing CTRL+C, that time 
 * semaphore should also Closed and unlinked. If not Next time 
 * when you run the same program, it will use same semaphore 
 * and will not work as expected.
**/
void signal_callback_handler(int signum)
{
	/**
	 * Semaphore Close: Close a named semaphore
	 */
	if ( sem_close(sem_id) < 0 )
	{
		perror("sem_close");
	}

	/**
	 * Semaphore unlink: Remove a named semaphore  from the system.
	 */
	if ( sem_unlink("/mysem") < 0 )
	{
		perror("sem_unlink");
	}

   // Terminate program
   exit(signum);
}

int main()
{

	/*Register signal and signal handler*/
	signal(SIGINT, signal_callback_handler);

	/**
	 * Semaphore open, http://linux.die.net/man/3/sem_open
	 * Semaphore Name: "/mysem"
	 * oflag: O_CREAT the semaphore is created if it does not already exist.
	 * mode: Both Read & Write.
	 * Semphore Value: Semaphore initialized to 1.
	 */
	sem_id=sem_open("/mysem", O_CREAT, S_IRUSR | S_IWUSR, 1);

	printf("About to wait\n");

	/**
	 * Semaphore wait. It will decrease the semaphore value. Now 0.
	 */
	if (sem_wait(sem_id) < 0)
	{
		perror("sem_wait");
	}

	printf("About to sleep\n");
	sleep(5);
	printf("About to post\n");

	/**
	 * Semaphore post. It will Increase the semaphore value. Now 1.
	 */
	if ( sem_post(sem_id) < 0 )
	{
		perror("sem_post");
	}

	printf("Finished task \n");

	/**
	 * Semaphore Close: Close a named semaphore
	 */
	if ( sem_close(sem_id) < 0 )
	{
		perror("sem_close");
	}

	/**
	 * Semaphore unlink: Remove a named semaphore  from the system.
	 */
	if ( sem_unlink("/mysem") < 0 )
	{
		perror("sem_unlink");
	}


	return 0;
}
