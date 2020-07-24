int mu(int in,  int (*fn1)(int), int (*fn2)(int)){
  return fn2(fn1(in));}
/* pipeline operator, usage:
int doppel(x){return x*2;}
int trippel(x){return x*3;}
int num = 2;
printf("%d\n", mu(num, doppel, trippel));
*/
