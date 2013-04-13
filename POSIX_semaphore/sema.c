#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

sem_t * sem_id;

/**
 * Signal Handler for CTRL^C
 */
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

	// Register signal and signal handler
	signal(SIGINT, signal_callback_handler);

	/**
	 * Semaphore open
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
