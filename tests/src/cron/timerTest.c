//
//
//

#include <stdio.h>
#include "../../cu/cu.h"
#include "../../../src/cron/cron.h"

TEST(testTimerInit){
    cron_init();
    assertEquals(0, system_millisecunds_since_startup);
    assertEquals(0, system_days_since_startup);
    assertEquals(0, cron_seconds);
    assertEquals(0, cron_minutes);
    assertEquals(0, cron_hours);
}

TEST(testTimerTick){
    cron_init();
    assertEquals(0, system_millisecunds_since_startup);
    assertEquals(0, system_days_since_startup);
    
    cron_increment_clock();
    assertEquals(1, system_millisecunds_since_startup);
    assertEquals(0, system_days_since_startup);

    cron_increment_clock();
    assertEquals(2, system_millisecunds_since_startup);
    assertEquals(0, system_days_since_startup);

    int i;
    for(i=0; i<1000; ++i){
            cron_increment_clock();
    }
    assertEquals(1002, system_millisecunds_since_startup);
    assertEquals(0, system_days_since_startup);
}

TEST(testTimerOverclock){
    cron_init();
    assertEquals(0, system_millisecunds_since_startup);
    assertEquals(0, system_days_since_startup);
    
    int i;
    for(i=0; i<86400000; ++i){
        cron_increment_clock();
    }
    assertEquals(0, system_millisecunds_since_startup);
    assertEquals(1, system_days_since_startup);

    cron_increment_clock();
    assertEquals(1, system_millisecunds_since_startup);
    assertEquals(1, system_days_since_startup);

}

TEST(testTimerGetTime){
    cron_init();
    assertEquals(0, cron_seconds);
    assertEquals(0, cron_minutes);
    assertEquals(0, cron_hours);
    
    cron_calculate_uptime_hms();
    printf("TIME: %02d:%02d:%02d\n", cron_hours, cron_minutes, cron_seconds);
    assertEquals(0, cron_seconds);
    assertEquals(0, cron_minutes);
    assertEquals(0, cron_hours);
    
    int i;
    for(i=0; i<43200000; ++i){
        cron_increment_clock();
    }
    cron_calculate_uptime_hms();
    printf("TIME: %02d:%02d:%02d\n", cron_hours, cron_minutes, cron_seconds);
    assertEquals(0, cron_seconds);
    assertEquals(0, cron_minutes);
    assertEquals(12, cron_hours);
    
    for(i=0; i<(60000 *3)+ (1000*30); ++i){
        cron_increment_clock();
    }
    cron_calculate_uptime_hms();
    printf("TIME: %02d:%02d:%02d\n", cron_hours, cron_minutes, cron_seconds);
    assertEquals(30, cron_seconds);
    assertEquals(3, cron_minutes);
    assertEquals(12, cron_hours);
}

TEST(testTimerSecondsNotOver){
    cron_init();
    int i;
    int biggest_sec = 0;
    int biggest_min = 0;
    int biggest_hour = 0;
    int lastSec = 0;
    for(i=0; i<86400000 *3; ++i){ // 3 Tage
        cron_increment_clock();
        cron_calculate_uptime_hms();
        if(cron_seconds > biggest_sec){
            biggest_sec = cron_seconds;
        }
        if(cron_minutes > biggest_min){
            biggest_min = cron_minutes;
        }
        if(cron_hours > biggest_hour){
            biggest_hour = cron_hours;
        }
        if(lastSec != cron_seconds){
            printf("uptime: %02d:%02d:%02d\n", cron_hours, cron_minutes, cron_seconds);

            lastSec = cron_seconds;
        }
    }
    assertTrue(biggest_sec == 59);
    assertTrue(biggest_min == 59);
    assertTrue(biggest_hour == 23);
}

