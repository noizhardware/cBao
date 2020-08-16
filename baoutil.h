#ifndef __BAOUTIL_H__
#define __BAOUTIL_H__
/* 202008152305 */

/* C90 compliant <3 */

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NIL ((void*)0)

static __inline__ char* boolToString(bool in){
  return in ? "true" : "false";}

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
// And can be used like
// int values[] = { 1, 2, 3 };
// foreach(int *v, values) {
//     printf("value: %d\n", *v);}
THIS ONE I THINK IS NOT C90 compliant :( */

#define forever for(;;) /* use: forever{ my_code_here; } - use break to exit the forever loop*/

#define elif else if

#ifdef __cplusplus
}
#endif

#endif /* __BAOUTIL_H__ */
