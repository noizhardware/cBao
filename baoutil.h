#ifndef _BAOUTIL_H_
#define _BAOUTIL_H_
/* 2021c13-0053 */

/* ANSI C compliant <3 */

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*#define NIL ((void*)0)*/

#define PORCODIO \
     printf("______ ___________ _____ ___________ _____ _____\n"); \
     printf("| ___ |  _  | ___ /  __ |  _  |  _  |_   _|  _  |\n"); \
     printf("| |_/ | | | | |_/ | /  \\| | | | | | | | | | | | |\n"); \
     printf("|  __/| | | |    /| |   | | | | | | | | | | | | |\n"); \
     printf("| |   \\ \\_/ | |\\ \\| \\__/\\ \\_/ | |/ / _| |_\\ \\_/ /\n"); \
     printf("\\_|    \\___/\\_| \\_|\\____/\\___/|___/  \\___/ \\___/\n") \

/*static __inline__ char* boolToString(bool in){
  return in ? "true" : "false";}*/

/* for 2D arrays*/
/*#define ARRAYELEMS(arr) sizeof arr / sizeof arr[0]*/ /* how many elements in the array */
#define ARRAYELEMS(arr) (&arr)[1] - arr /* how many elements in the array */

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)
      /*
And can be used like
int v = 0;
int values[] = { 1, 2, 3 };
foreach(&v, values) {
    printf("value: %d\n", *v);}
*/
#define forever for(;;) /* use: forever{ my_code_here; } - use break to exit the forever loop*/

#define elif else if

#define DUMMY __asm__("nop") /* dummy line, might be used to allow a semicolon after a function closing bracket '}' */

#ifdef __cplusplus
}
#endif

#endif /* _BAOUTIL_H_ */
