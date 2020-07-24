#ifndef __BAOUTIL_H__
#define __BAOUTIL_H__
/* 202007241413 */

/* C90 compliant <3 */

#ifdef __cplusplus
extern "C" {
#endif

/* for 2D arrays*/
#define ARRAYELEMS(arr) sizeof(*arr)-1 /* how many elements in the array */
/* #define ARRAYELEMSIZE(arr) sizeof(arr[0]) -- size of the single elements */

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