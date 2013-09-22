//
//  cron.h
//  AnalyserDude & other reference implementations
//
//  v.1.1.0
//	
//  A tiny crontab and timeout (at) implementation for the avr. Resolution is in secondes.
//  The crontab use the TIMER0 of an avr! You can not use them for any other purpose in 
//  your project, but try to work with the timeout and crontab methods to realize timer 
//  based solutions.
//
//

#ifndef AnalyserDude_cron_h
#define AnalyserDude_cron_h
#include <stdint.h>

#ifdef IGNOREINTESTS
void interuptServiceRoutine(void);
#endif

// 
// JOB DEFINITIONS
// ---------------------------------------------
typedef struct cron_joblist {
    char identifyer;
    uint32_t total_ms;                          	// total time in ms
    void (*fn)(void);                           	// function to execute at timeout
    struct cron_joblist *next;               		// next element
} cron_joblist_t;

// PROVIDE THE GLOBAL CRONTAB
// ---------------------------------------------
cron_joblist_t *crontab;

// TIMEOUT DEFINITION - THE TASKS TO EXECUTE
// AFTER THE TIME IS UP
// ---------------------------------------------
typedef struct cron_timeoutlist {
    char identifyer;
    uint32_t ms_left;
    void (*fn)(void);
    struct cron_timeoutlist *next;               	// next element
} cron_timeoutlist_t;

// PROVIDE THE GLOBAL TIMEOUT LIST
// ---------------------------------------------
cron_timeoutlist_t *cron_timeoutlist;

// CRONJOBS WILL BE ORDERD IN A LINKED LIST 
// WITH A DEFINED START- AND ENDPOINT
// ---------------------------------------------
typedef struct cron_borders {
    cron_joblist_t *first;
    cron_joblist_t *last;
} cron_borders_t;

// PROVIDE THE SART AND END POINTER TO THE 
// JOBLIST
// ---------------------------------------------
cron_borders_t *crontab_ptr;

// POINTERS TO THE FIRST AND THE LAST TIMEOUT
// ---------------------------------------------
typedef struct cron_timeoutborders {
    cron_timeoutlist_t *first;
    cron_timeoutlist_t *last;
} cron_timeoutborders_t;

// PROVIDE THE SART AND END POINTER TO THE 
// TIMEOUTLIST
// ---------------------------------------------
cron_timeoutborders_t *timeout_ptr;

// GLOBAL TIMER
// ---------------------------------------------
volatile uint32_t       system_millisecunds_since_startup;
volatile uint32_t       cron_ms_for_execution_timer;
volatile uint8_t        system_days_since_startup;
volatile unsigned int   cron_seconds;
volatile unsigned int   cron_minutes;
volatile unsigned int   cron_hours;

// FUNCTIONS
// ---------------------------------------------
/**
 * inittialize the crontab and the timers
 */
void cron_init(void);

/**
 * calculate the timer in h m s
 */
void cron_calculate_uptime_hms(void);

/**
 * Add a new job to the crontab
 * A job that should called ever 1,5h can be written as:
 * char ident = cron_add_job(0, 0, 30, 1, fn_doSomething());
 * The retruned ident is the unique identifyer of the job.
 */
char cron_add_job(int ms, int sec, int min, int hous, void *fn);

/**
 * Set or Reset a timeout function (fn) that executes
 * after the time is up.
 */
void cron_set_timeout(char id, int ms, int sec, int min, int hours, void *fn);

/**
 * Removes a job with a specific identifyer from the queue
 */
void cron_remove_job(char);

/**
 * Removes a running timeout with a specific identifyer from the queue
 */
void cron_remove_timeout(char);

/**
 * Clear the whole job definition table
 */
void cron_clear(void);

/**
 * Count the number of jobs in the table
 */
int cron_count_jobs(void);

/**
 * Count the number of timeouts in the table
 */
int cron_count_timeouts(void);

#ifdef IGNOREINTESTS
/** 
 *	The System has to increase the clock every millisecond!
 *	This is a private method, but needed in tests.
 */
void cron_increment_clock(void);
#endif

#endif
