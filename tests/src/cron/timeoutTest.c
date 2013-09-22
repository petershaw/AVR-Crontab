//
//
//

#include <stdio.h>
#include "../../cu/cu.h"
#include "../../../src/cron/cron.h"

int timeoutInvoked = 0;

void timeout(void){
    ++timeoutInvoked;
}

TEST(testCronTimeoutAdd){
    cron_init();
    assertEquals(0, cron_count_timeouts());
    
    cron_set_timeout(1, 60, 0, 0, 0, (void *)timeout);
    assertEquals(1, cron_count_timeouts());
    
    cron_set_timeout(2, 0, 5, 0, 0, (void *)timeout);
    assertEquals(2, cron_count_timeouts());
    
    cron_set_timeout(1, 70, 0, 0, 0, (void *)timeout);
    assertEquals(2, cron_count_timeouts());
}

TEST(testCronTimeoutRemove){
    cron_init();
    assertEquals(0, cron_count_timeouts());
    
    cron_set_timeout(1, 60, 0, 0, 0, (void *)timeout);
    cron_set_timeout(2, 0, 5, 0, 0, (void *)timeout);
    cron_set_timeout(3, 0, 0, 10, 1, (void *)timeout);
    assertEquals(3, cron_count_timeouts());
    
    cron_remove_timeout(2);
    assertEquals(2, cron_count_timeouts());
}

TEST(testCronTimeoutExecute){
    cron_init();
    timeoutInvoked = 0;
    
    cron_set_timeout(1, 4, 0, 0, 0, (void *)timeout);
    assertEquals(0, timeoutInvoked);
    
    interuptServiceRoutine();
    interuptServiceRoutine();
    interuptServiceRoutine();
    assertEquals(0, timeoutInvoked);
    
    interuptServiceRoutine();
    assertEquals(1, timeoutInvoked);
    
    interuptServiceRoutine();
    interuptServiceRoutine();
    interuptServiceRoutine();
    interuptServiceRoutine();
    assertEquals(1, timeoutInvoked);

}
