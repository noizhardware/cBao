#ifndef _BAOGL_H_
#define _BAOGL_H_

#define FILENAME_VERSION "2021c12-1225"

/*** TODO

*/

/*** INCLUDES */
     #include "SDL.h"
     #include <stdio.h>
     #include <stdbool.h>
     #include <math.h>
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
     /*Screen dimension constants*/
     #define SCREEN_WIDTH 2560
     #define SCREEN_HEIGHT 1440
     
     #define BAOGL_MAIN \
     int main(int argc, char* argv[]){  \
          bool quit;                    \
          SDL_Window* window;           \
          SDL_Event event;              \
          uint32_t tt;                  \
          Uint64 start;                 \
          Uint64 end;                   \
          float elapsed
          
     #define BAOGL_PRE_IMAGE  \
         (void)argc;\
         (void)argv;\
          /* Enable standard application logging */\
          SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);\
          if (SDL_Init(SDL_INIT_VIDEO) < 0) {\
               return 1;\
               printf("Initialization failed\n");\
          }\
          else{\
               SDL_Log("Initialization successful!\n");\
          }\
          window = SDL_CreateWindow("POWERCODIO!!!",\
          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,\
          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);\
          if (window == NULL) {\
               SDL_Quit();\
               return 2;\
          }\
          /* We create a renderer with hardware acceleration, we also present according with the vertical sync refresh.*/\
          rendererMain = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;\
          quit = false;\
          while (!quit) {\
               start = SDL_GetPerformanceCounter();\
               tt = SDL_GetTicks(); /* milliseconds */\
               while (SDL_PollEvent(&event)) {\
                    if (event.type == SDL_QUIT) {\
                         quit = true;\
                    }\
               }\
               SDL_SetRenderDrawColor(rendererMain, 0, 0, 0, 0xFF); /* reset background to black */\
               SDL_RenderClear(rendererMain) /* clear the screen */\
               
     #define BAOGL_END \
               SDL_RenderPresent(rendererMain);\
               end = SDL_GetPerformanceCounter();\
               elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();\
               SDL_Log("Current FPS: %.2f\n", (1.0f / elapsed));\
         }\
         SDL_DestroyWindow(window);\
         SDL_DestroyRenderer(rendererMain);\
         SDL_Quit();\
         return 0;\
     }\
     __asm__("") /* just a dummy line to allow a semicolon after the function */
    
          
/* DEFINES end. */

/*** TYPEDEFS */
     typedef struct vec3_{
          float x;
          float y;
          float z;
     } vec3;
     typedef struct vec2_{
          float x;
          float y;
     } vec2;
     
     typedef struct triangle2d_t_{
          vec2 a;
          vec2 b;
          vec2 c;
     } triangle2d_t;
     typedef struct triangle3d_t_{
          vec3 a;
          vec3 b;
          vec3 c;
     } triangle3d_t;
     
/* TYPEDEFS end. */

/*** GLOBALS */
     SDL_Renderer* rendererMain;
     vec2 res = {SCREEN_WIDTH, SCREEN_HEIGHT};
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
static __inline__ vec2 div2(vec2 in, float div);
static __inline__ vec2 mul2(vec2 in, float mul);

static __inline__ vec2 vec2make(float x, float y);
static __inline__ vec3 vec3make(float x, float y, float z);
static __inline__ void vec2init(vec2* in, float x, float y);
static __inline__ void vec3init(vec3* in, float x, float y, float z);
static __inline__ void triangle2dInit(triangle2d_t* in, vec2 a, vec2 b, vec2 c);
static __inline__ void triangle3dInit(triangle3d_t* in, vec3 a, vec3 b, vec3 c);
static __inline__ void triangle3dInitF(triangle3d_t* in, float aa, float ab, float ac, float ba, float bb, float bc, float ca, float cb, float cc);

static __inline__ void triangle3d2d(triangle3d_t* tri, triangle2d_t* tri_p, float maxDist);

static __inline__ void setColor(vec3 col);
static __inline__ void drawPoint(vec2 p, vec3 col);
static __inline__ void drawLine(vec2 a, vec2 b, vec3 col);
static __inline__ void _dla_changebrightness(vec3* colorIn, vec3* colorOut, float br);
static __inline__ void _dla_plot(vec2 point, vec3* col, float br);
static __inline__ void drawLineAA(vec2 a, vec2 b, vec3 color);
static __inline__ void drawTri2d(triangle2d_t tri, vec3 col);

static __inline__ float length2(vec2 a, vec2 b);

/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
static __inline__ vec2 div2(vec2 in, float div){
     vec2 out;
     out.x = in.x/div;
     out.y = in.y/div;
     return out;
}
static __inline__ vec2 mul2(vec2 in, float mul){
     vec2 out;
     out.x = in.x*mul;
     out.y = in.y*mul;
     return out;
}
static __inline__ vec2 vec2make(float x, float y){
     vec2 out;
     out.x=x;
     out.y=y;
     return out;
}
static __inline__ vec3 vec3make(float x, float y, float z){
     vec3 out;
     out.x=x;
     out.y=y;
     out.z=z;
     return out;
}
static __inline__ void vec2init(vec2* in, float x, float y){
     in->x=x;
     in->y=y;
}
static __inline__ void vec3init(vec3* in, float x, float y, float z){
     in->x=x;
     in->y=y;
     in->z=z;
}

static __inline__ void triangle2dInit(triangle2d_t* in, vec2 a, vec2 b, vec2 c){
     in->a.x=a.x;
     in->a.y=a.y;
     in->b.x=b.x;
     in->b.y=b.y;
     in->c.x=c.x;
     in->c.y=c.y;
}
static __inline__ void triangle3dInit(triangle3d_t* in, vec3 a, vec3 b, vec3 c){
     in->a.x=a.x;
     in->a.y=a.y;
     in->a.z=a.z;
     in->b.x=b.x;
     in->b.y=b.y;
     in->b.z=b.z;
     in->c.x=c.x;
     in->c.y=c.y;
     in->c.z=c.z;
}
static __inline__ void triangle3dInitF(triangle3d_t* in, float aa, float ab, float ac, float ba, float bb, float bc, float ca, float cb, float cc){ /* same, but by providing raw floats */
     triangle3dInit(in,
          vec3make(aa, ab, ac),
          vec3make(ba, bb, bc),
          vec3make(ca, cb, cc)
     );
}

static __inline__ void triangle3d2d(triangle3d_t* tri, triangle2d_t* tri_p, float maxDist){ /* projects 3d triangle into 2d */
     triangle2dInit(tri_p,
          vec2make(tri->a.x*(maxDist/tri->a.z), tri->a.y*(maxDist/tri->a.z)),
          vec2make(tri->b.x*(maxDist/tri->b.z), tri->b.y*(maxDist/tri->b.z)),
          vec2make(tri->c.x*(maxDist/tri->c.z), tri->c.y*(maxDist/tri->c.z))
     );
}

static __inline__ float length2(vec2 a, vec2 b){
     return sqrt(pow(b.x-a.x, 2)+pow(b.y-a.y, 2));
}

static __inline__ void setColor(vec3 col){
     SDL_SetRenderDrawColor(rendererMain, (int)255*col.x, (int)255*col.y, (int)255*col.z, 0xFF); /* last one is opacity */
}

static __inline__ void drawPoint(vec2 p, vec3 col){
     setColor(col);
     SDL_RenderDrawPoint(rendererMain, p.x, p.y);
}
static __inline__ void drawLine(vec2 a, vec2 b, vec3 col){
     float lenX = fabs(b.x-a.x);
          int8_t dirX = a.x<b.x ? 1 : -1;
     float lenY = fabs(b.y-a.y);
          int8_t dirY = a.y<b.y ? 1 : -1; 
     float err = (lenX>lenY ? lenX : -lenY)/2.;
     float e2;
     vec2 a1;

     vec2init(&a1, a.x, a.y);

     setColor(col);

     for(;;){
          drawPoint(a1, col);
          if (a1.x==b.x && a1.y==b.y) break;
          e2 = err;
          if (e2 > -lenX) { err -= lenY; a1.x += dirX; }
          if (e2 < lenY) { err += lenX; a1.y += dirY; }
     }
}
static __inline__ void drawTri2d(triangle2d_t tri, vec3 col){
     drawLine(tri.a, tri.b, col);
     drawLine(tri.b, tri.c, col);
     drawLine(tri.c, tri.a, col);
}

/*** antialias line - from https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm#Algorithm */
static __inline__ void _dla_changebrightness(vec3* colorIn, vec3* colorOut, float br){
     if ( br > 1.0 ){
          br = 1.0;
     }
     /* linear... Maybe something more complex could give better look */
     colorOut->x = br * colorIn->x;
     colorOut->y = br * colorIn->y;
     colorOut->z = br * colorIn->z;
}
#define plot_(P,D) do{ vec3 f_;				\
  f_.x = color.x; f_.y = color.y; f_.z = color.z;			\
  _dla_plot((P), &f_, (D)) ; }while(0)
static __inline__ void _dla_plot(vec2 point, vec3* col, float br){
     vec3 oc;
     _dla_changebrightness(col, &oc, br);
     drawPoint(point, oc);
}
#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X))+0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))
#define swap_(a, b) do{ __typeof__(a) tmp;  tmp = a; a = b; b = tmp; }while(0)
static __inline__ void drawLineAA(vec2 a, vec2 b, vec3 color){ /* AA AntiAlias */
     double dx = (double)b.x - (double)a.x;
     double dy = (double)b.y - (double)a.y;
     if ( fabs(dx) > fabs(dy) ) {
          double gradient = dy / dx;
          double xend = round_(a.x);
          double yend = a.y + gradient*(xend - a.x);
          double xgap = rfpart_(a.x + 0.5);
          vec2 pxl1;
               /*int xpxl1 = xend;
               int ypxl1 = ipart_(yend);*/
          double intery;
          vec2 pxl2;
               /*int xpxl2;
               int ypxl2;*/
          int x;
          
          vec2init(&pxl1, xend, ipart_(yend));
          
          if ( b.x < a.x ) {
               swap_(a.x, b.x);
               swap_(a.y, b.y);
          }
          plot_(pxl1, rfpart_(yend)*xgap);
          plot_(vec2make(pxl1.x, pxl1.y+1), fpart_(yend)*xgap);
          intery = yend + gradient;

          xend = round_(b.x);
          yend = b.y + gradient*(xend - b.x);
          xgap = fpart_(b.x+0.5);
          pxl2.x = xend;
          pxl2.y = ipart_(yend);
          plot_(pxl2, rfpart_(yend) * xgap);
          plot_(vec2make(pxl2.x, pxl2.y+1), fpart_(yend) * xgap);

          for(x=pxl1.x+1; x < pxl2.x; x++) {
               plot_(vec2make(x, ipart_(intery)), rfpart_(intery));
               plot_(vec2make(x, ipart_(intery) + 1), fpart_(intery));
               intery += gradient;
          }
     }
     else{
          double gradient = dx / dy;
          double yend = round_(a.y);
          double xend = a.x + gradient*(yend - a.y);
          double ygap = rfpart_(a.y + 0.5);
          vec2 pxl1;
               /*int ypxl1 = yend;
               int xpxl1 = ipart_(xend);*/
          double interx;
          vec2 pxl2;
               /*int ypxl2;
               int xpxl2;*/
          int y;
          
          vec2init(&pxl1, yend, ipart_(xend));
          
          if ( b.y < a.y ) {
               swap_(a.x, b.x);
               swap_(a.y, b.y);
          }
          
          plot_(pxl1, rfpart_(xend)*ygap);
          plot_(vec2make(pxl1.x+1, pxl1.y), fpart_(xend)*ygap);
          interx = xend + gradient;

          yend = round_(b.y);
          xend = b.x + gradient*(yend - b.y);
          ygap = fpart_(b.y+0.5);
          pxl2.y = yend;
          pxl2.x = ipart_(xend);
          plot_(pxl2, rfpart_(xend) * ygap);
          plot_(vec2make(pxl2.x+1, pxl2.y), fpart_(xend) * ygap);

          for(y=pxl1.y+1; y < pxl2.y; y++) {
               plot_(vec2make(ipart_(interx), y), rfpart_(interx));
               plot_(vec2make(ipart_(interx) + 1, y), fpart_(interx));
               interx += gradient;
          }
     }
}
#undef swap_
#undef plot_
#undef ipart_
#undef fpart_
#undef round_
#undef rfpart_
/* antialias line end */

/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
     }
#endif
#endif /* _BAOGL_H_ */