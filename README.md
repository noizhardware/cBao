# cBao
## a collection of C headers

- non-branching where possible (still a work-in-progress)
  + `#define BRANCH` or use `-DBRANCH` with **gcc** to use the branching version of the functions, where available.
- as a rule of thumb, compile with `-O3` to maximize performance with branchless functions.
