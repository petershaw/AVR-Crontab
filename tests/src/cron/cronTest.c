//
//
//

#include <stdio.h>
#include "../../cu/cu.h"
#include "../../../src/cron/cron.h"

int number = 0;

void *dummy(void){}
void incrementNumber(void){
    ++number;
}

char nextidentifyer;

TEST(testCronInit) {
    assertTrue(NULL == crontab_ptr);
    cron_init();
    assertFalse(NULL == crontab_ptr);
}

TEST(testCronAdd) {
    cron_init();
    assertEquals(1, nextidentifyer);
    char id1 = cron_add_job(0, 0, 2, 0, dummy()); // every two minutes
    assertEquals(2, nextidentifyer);
    assertEquals(1, id1);
    char id2 = cron_add_job(0, 30, 0, 1, dummy()); // every 30 seconds afte a hour
    assertEquals(3, nextidentifyer);
    assertEquals(2, id2);
}

TEST(testCronCount){
    cron_init();
    assertEquals(0, cron_count_jobs());
    
    cron_add_job(1, 0, 0, 0, dummy());
    assertEquals(1, cron_count_jobs());

    cron_add_job(0, 0, 1, 0, dummy());
    assertEquals(2, cron_count_jobs());
    
    cron_add_job(0, 1, 0, 0, dummy());
    assertEquals(3, cron_count_jobs());

    cron_add_job(0, 1, 0, 0, dummy());
    assertEquals(4, cron_count_jobs());

    cron_add_job(0, 2, 1, 0, dummy());
    assertEquals(5, cron_count_jobs());
}

TEST(testCronRemove){
    cron_init();
    assertEquals(0, cron_count_jobs());
    
    char job1, job2, job3, job4, job5, job6, job7, job8, job9;
    
    job1 = cron_add_job(0, 0, 0, 1, dummy());
    assertEquals(1, cron_count_jobs());
    
    job2 = cron_add_job(0, 0, 0, 2, dummy());
    assertEquals(2, cron_count_jobs());

    job3 = cron_add_job(0, 0, 0, 3, dummy());
    assertEquals(3, cron_count_jobs());

    job4 = cron_add_job(0, 2, 0, 0, dummy());
    assertEquals(4, cron_count_jobs());

    job5 = cron_add_job(500, 1, 0, 0, dummy());
    assertEquals(5, cron_count_jobs());

    job6 = cron_add_job(0, 1, 0, 0, dummy());
    assertEquals(6, cron_count_jobs());
    
    job7 = cron_add_job(0, 2, 0, 0, dummy());
    assertEquals(7, cron_count_jobs());

    job8 = cron_add_job(0, 0, 0, 3, dummy());
    assertEquals(8, cron_count_jobs());

    job9 = cron_add_job(0, 0, 2, 0, dummy());
    assertEquals(9, cron_count_jobs());

    // remove a leave with rlb-sub nodes
    cron_remove_job(job4);
    assertEquals(8, cron_count_jobs());

    cron_remove_job(job8);
    assertEquals(7, cron_count_jobs());
}

TEST(testCronClear){
    cron_init();
    assertEquals(0, cron_count_jobs());
    cron_clear();
    assertEquals(0, cron_count_jobs());
    
    cron_add_job(0, 0, 0, 1, dummy());
    cron_add_job(0, 0, 0, 2, dummy());
    cron_add_job(0, 0, 0, 3, dummy());
    assertEquals(3, cron_count_jobs());
    
    cron_clear();
    assertEquals(0, cron_count_jobs());
}

TEST(testCronSorted){
    cron_init();
    cron_add_job(0, 0, 0, 1, dummy());
    cron_add_job(0, 0, 0, 2, dummy());
    cron_add_job(0, 0, 0, 3, dummy());
    cron_add_job(0, 2, 0, 0, dummy());
    cron_add_job(500, 1, 0, 0, dummy());
    cron_add_job(0, 1, 0, 0, dummy());
    cron_add_job(0, 2, 0, 0, dummy());
    cron_add_job(0, 0, 0, 3, dummy());
    cron_add_job(0, 0, 2, 0, dummy());
    
    assertEquals(9, cron_count_jobs());
    cron_joblist_t  *current;
    current         = crontab_ptr->first;
    int c, lastvalue;
    c = 0;
    lastvalue = 0;
    while (current != NULL) {
        ++c;
        printf("-> %d ", current->total_ms);
        if(current->next != NULL){
            assertTrue(current->total_ms <= current->next->total_ms);
        } else if(lastvalue != 0){
            assertTrue(current->total_ms >= lastvalue);
        }
        lastvalue = current->total_ms;
        current = current->next;
    }
    printf("\n");
}

TEST(testCronExecute){
    cron_init();
    
    char job1, job2;
    job1 = cron_add_job(3, 0, 0, 0, (void *)incrementNumber);
    assertEquals(1, cron_count_jobs());

    job2 = cron_add_job(1, 0, 0, 0, (void *)incrementNumber);
    assertEquals(2, cron_count_jobs());

    cron_joblist_t  *current;
    current         = crontab_ptr->first;
    while (current != NULL) {
        printf("-> %d ", current->total_ms);
        current = current->next;
    }
    printf("\n");
    assertEquals(0, number);
    printf("n: %d\n", number);
    
    interuptServiceRoutine();
    assertEquals(1, number);
    printf("n: %d\n", number);
    
    interuptServiceRoutine();
    assertEquals(2, number);
    printf("n: %d\n", number);
    
    interuptServiceRoutine();
    assertEquals(4, number);
    printf("n: %d\n", number);
    
    interuptServiceRoutine();
    assertEquals(5, number);
    printf("n: %d\n", number);
    
    interuptServiceRoutine();
    assertEquals(6, number);
    printf("n: %d\n", number);
    
    interuptServiceRoutine();
    assertEquals(8, number);
    printf("n: %d\n", number);
    
}

