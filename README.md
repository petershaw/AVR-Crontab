AVR-Crontab (libavrcron.a)
==================

Description
------------------------------
A cron like library implementation for avr mikrocontroller.
**Cron** will recall a function after a time period comes up.
**Timeout** will call a function once after a time period.
**Timer** has some information about the uptime

Installation
------------------------------
Checkout this repository and go into the project directory. 
If you want to execute all tests first see _Tests_ below. The main task will execute the 
tests ass well. 

Type:

	make

to compile cron for your target. You have to specify the target device in the makefile. 
Please set *MCU* and *F_CPU*!

When cron is compiled a library file is stored in ./target/libavrcron.a

Integration
------------------------------
To use cron in your own project you have to set the cronlib into your LIBS  directive in your makefile, or direct in the cc line:

	$(CC) $(LDFLAGS) -o $(TRG) $(shell find $(OBJECTDIR) -type f -name *.o) -lm -lavrcron

If everything ist fine, you can point your console into the project root

Tests
------------------------------
The crontab is unit tested with cunit. cunit is bundled in this repository. 
In the folder ./regressions you have all outputs in separate files.

run

	make
	
and execute all tests with

	./target/tests

You should see a output like this one:

<pre>

--------------------------------------------------
|               |  failed  |  succeed  |  total  |
|------------------------------------------------|
| assertations: |       0  |       93  |     93  |
| tests:        |       0  |       15  |     15  |
| tests suites: |       0  |        3  |      3  |
==================================================
</pre>

Examples
------------------------------
// You have to set cron up at the setup phase of the uC.

	cron_init();

Will do the job for you. Just be sure to invoke it at the beginning, before you use the confab.

###  CRON ###

// execute myFunc() every 2 minutes.

	char job1 = cron_add_job(0, 0, 2, 0, myFn()); 

// and execute another function every one and a half hour.

	char job2 = cron_add_job(0, 30, 0, 1, anotherFunc()); 

Thats it! 
You can check bow many jobs the crontab has.

	cron_count_jobs()

In the example above it will return 2.
If you don't like the first one any more, than run

	cron_remove_job(job1);

It is possible to delete every job from the crontab with

	 cron_clear();

###  TIMEOUT ###

Timeout works as cron does, but the job will be executed only once. For example you want a feedback after 30 min if nothing is touched, than you can use the timer and reset it every time the device is touched.
You have to give every separate timeout task a unified name. 

	int twb_timeout_session 	= 1;
	void isTouced(){
		cron_set_timeout(twb_timeout_session, 0, 30, 0, 0, &twb75_stop_session);
	}

Call isTouced in every routine that compute a button press or any other user interaction. the timer with the name twb_timeout_session will be resettet. If isTouced() issn't called for 30 min than the function twb75_stop_session will be executed.

for all methods from Cron there is a equivalent in Timeout:

	cron_remove_timeout(char)
	cron_count_timeouts

### TIMER ###
Timer provides functions to get some information about the running time of your application

	system_millisecunds_since_startup
Will return the milliseconds since the cron_init(); was called.

	system_days_since_startup
Will return the days since the cron_init(); was called.
After 24 hours system_days_since_startup is 1

After calling:
	cron_calculate_uptime_hms

**three variables are set:**

		cron_seconds
return a integer between 0 and 60 for the current second the device is running.  

		cron_minutes
return a integer between 0 and 60 for the current minute the device is running	

		cron_hours
returns a integer between 0 and 24 for every hour the device is running. After 24 hours system_days_since_startup is incremented. cron_calculate_uptime_hms will set cron_hours, cron_minutes and cron_seconds to 0.

		 printf("UPTIME: %02d:%02d:%02d\n", cron_hours, cron_minutes, cron_seconds);


