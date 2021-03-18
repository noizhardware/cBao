#ifndef _BAOGL_H_
#define _BAOGL_H_

#define BAOGL_VERSION "2021c16-1901"

/*** TODO

*/

/*** INCLUDES */
     #include "SDL.h"
     #include <stdio.h>
     #include <stdbool.h>
     #include <math.h>
     #include "baoutil.h"
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
     /*Screen dimension constants*/
     #if defined SCREEN_8K || defined SCREEN_4320P
          #define SCREEN_WIDTH 7680
          #define SCREEN_HEIGHT 4320
     #elif defined SCREEN_4K || defined SCREEN_2160P
          #define SCREEN_WIDTH 4096
          #define SCREEN_HEIGHT 2160
     #elif defined SCREEN_QHD || defined SCREEN_1440P
          #define SCREEN_WIDTH 2560
          #define SCREEN_HEIGHT 1440
     #elif defined SCREEN_FULLHD || defined SCREEN_1080P
          #define SCREEN_WIDTH 1920
          #define SCREEN_HEIGHT 1080
     #elif defined SCREEN_HD || SCREEN_HDREADY || defined SCREEN_720P
          #define SCREEN_WIDTH 1280
          #define SCREEN_HEIGHT 720
     #elif defined SCREEN_SD
          #define SCREEN_WIDTH 720
          #define SCREEN_HEIGHT 576
     #elif defined SCREEN_480P
          #define SCREEN_WIDTH 852
          #define SCREEN_HEIGHT 480
     #elif defined SCREEN_360P
          #define SCREEN_WIDTH 480
          #define SCREEN_HEIGHT 360
     #elif defined SCREEN_240P || defined SCREEN_NTSC
          #define SCREEN_WIDTH 426
          #define SCREEN_HEIGHT 240
     #elif defined SCREEN_144P
          #define SCREEN_WIDTH 256
          #define SCREEN_HEIGHT 144
     #endif
     /*Screen dimension constants END. */
     
     #define aspectRatio (res.x<res.y?res.x/res.y:res.y/res.x)
     
/* DEFINES end. */

/*** FUNCTION BLOCK DEFINES */
     #ifdef LOG_FPS
          #define FPS_END \
               ;end = SDL_GetPerformanceCounter();\
               elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();\
               SDL_Log("Current FPS: %.2f\n", (1.0f / elapsed));
          #define FPS_START \
                    start = SDL_GetPerformanceCounter();
          #define FPS_DECL \
               Uint64 start;                 \
               Uint64 end;                   \
               float elapsed
     #else
          #define FPS_END
          #define FPS_START
          #define FPS_DECL
     #endif /* LOG_FPS */

     #define BAOGL_MAIN \
     int main(int argc, char* argv[]){  \
          bool quit;                    \
          SDL_Window* window;           \
          SDL_Event event              \
          FPS_DECL
     
     
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
               FPS_START;\
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
               FPS_END; \
         }\
         SDL_DestroyWindow(window);\
         SDL_DestroyRenderer(rendererMain);\
         SDL_Quit();\
         return 0;\
     }\
     DUMMY
/* FUNCTION BLOCK DEFINES end. */     

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
     uint32_t tt;
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
static __inline__ vec2 div2(vec2 in, float div);
static __inline__ vec2 mul2(vec2 in, float mul);

static __inline__ vec2 vec2make(float x, float y);
static __inline__ vec3 vec3make(float x, float y, float z);
static __inline__ void vec2init(vec2* in, float x, float y);
static __inline__ void vec3init(vec3* in, float x, float y, float z);
static __inline__ void triangle2dInit(triangle2d_t* in, vec2 a, vec2 b, vec2 c);
static __inline__ triangle2d_t triangle2dMake(vec2 a, vec2 b, vec2 c);
static __inline__ void triangle3dInit(triangle3d_t* in, vec3 a, vec3 b, vec3 c);
static __inline__ void triangle3dInitF(triangle3d_t* in, float aa, float ab, float ac, float ba, float bb, float bc, float ca, float cb, float cc);

static __inline__ void setColor(vec3 col);
static __inline__ void drawPoint(vec2 p, vec3 col); /* [-1..1] coordinates */
static __inline__ void drawPoint_(vec2 p, vec3 col); /* absolute coordinates */
static __inline__ void drawLine(vec2 a, vec2 b, vec3 col); /* [-1..1] coordinates */
static __inline__ void drawLine_(vec2 a, vec2 b, vec3 col); /* absolute coordinates */
static __inline__ void _dla_changebrightness(vec3* colorIn, vec3* colorOut, float br);
static __inline__ void _dla_plot(vec2 point, vec3* col, float br);
static __inline__ void drawLineAA(vec2 a, vec2 b, vec3 color);
static __inline__ void drawTri2d(triangle2d_t tri, vec3 col);
static __inline__ void drawTri2dAA(triangle2d_t tri, vec3 col);
static __inline__ void drawCircle(vec2 pos, float r, vec3 col);

static __inline__ vec3 vec3translate(vec3 in, vec3 trans);

static __inline__ vec2 uvToAbs(vec2 uv);
static __inline__ triangle2d_t uvTri2d(triangle2d_t tri);


static __inline__ float length2d(vec2 a, vec2 b);
static __inline__ float length3d(vec3 a, vec3 b);

static __inline__ vec3 norm3d(vec3 in);

/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */

static __inline__ vec2 uvToAbs(vec2 uv){ /* input uv[-1..+1], output actual coordinates */
     return(
          vec2make(
               /*(uv.x/(res.x/res.y)+1)*.5*res.x,
               res.y-((uv.y+1)*.5*res.y)*/
               
               /*      (uv.x*(res.x<res.y?res.x:res.y)+res.x)/2.,
               res.y-(uv.y*(res.x<res.y?res.x:res.y)+res.y)/2.*/
               
               /* Normalized pixel coordinates (from 0 to 1) */
               #ifdef ASPECT_RATIO_CORRECTION
                    res.x*(aspectRatio*uv.x+1.)/2.,
               #else
                    res.x*(uv.x+1.)/2.,
               #endif
               res.y-res.y*(uv.y+1.)/2.
          )
     );
}
static __inline__ triangle2d_t uvTri2d(triangle2d_t tri){
     return(
          triangle2dMake(
               uvToAbs(tri.a),
               uvToAbs(tri.b),
               uvToAbs(tri.c)
          )
     );
}

static __inline__ vec3 vec3translate(vec3 in, vec3 trans){
     return(
          vec3make(
               in.x+trans.x,
               in.y+trans.y,
               in.z+trans.z
          )
     );
}

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
static __inline__ triangle2d_t triangle2dMake(vec2 a, vec2 b, vec2 c){
     triangle2d_t out;
     triangle2dInit(&out, a, b, c);
     return out;
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

static __inline__ float length2d(vec2 a, vec2 b){
     return sqrt(pow(b.x-a.x, 2)+pow(b.y-a.y, 2));
}
static __inline__ float length3d(vec3 a, vec3 b){
     return sqrt(pow(b.x-a.x, 2)+pow(b.y-a.y, 2)+pow(b.z-a.z, 2));
}

static __inline__ vec3 norm3d(vec3 in){
     float len = length3d(vec3make(.0, .0, .0), in);
     return(vec3make(in.x/len, in.y/len, in.z/len));
}

static __inline__ void setColor(vec3 col){
     SDL_SetRenderDrawColor(rendererMain, (int)255*col.x, (int)255*col.y, (int)255*col.z, 0xFF); /* last one is opacity */
}

static __inline__ void drawPoint_(vec2 p, vec3 col){
     setColor(col);
     SDL_RenderDrawPoint(rendererMain, p.x, p.y);
}
static __inline__ void drawPoint(vec2 p, vec3 col){
     setColor(col);
     SDL_RenderDrawPoint(rendererMain, uvToAbs(p).x, uvToAbs(p).y);
}

static __inline__ void drawLine(vec2 a, vec2 b, vec3 col){
     vec2 aAbs = uvToAbs(a);
     vec2 bAbs = uvToAbs(b);
     setColor(col);
     SDL_RenderDrawLine(rendererMain, aAbs.x, aAbs.y, bAbs.x, bAbs.y);
}
/*static __inline__ void drawLine(vec2 a, vec2 b, vec3 col){
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
}*/
static __inline__ void drawLine_(vec2 a, vec2 b, vec3 col){
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
          drawPoint_(a1, col);
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
static __inline__ void drawTri2dAA(triangle2d_t tri, vec3 col){
     drawLineAA(tri.a, tri.b, col);
     drawLineAA(tri.b, tri.c, col);
     drawLineAA(tri.c, tri.a, col);
}

static __inline__ void drawCircle(vec2 pos, float r, vec3 col){
     const int32_t diameter = (r * res.x * 2);
     int32_t x = (r * res.x - 1);
     int32_t y = 0;
     int32_t tx = 1;
     int32_t ty = 1;
     int32_t error = (tx - diameter);
     vec2 posAbs = uvToAbs(pos);

     setColor(col);
     while (x >= y){
          /*Each of the following renders an octant of the circle*/
          SDL_RenderDrawPoint(rendererMain, posAbs.x + x, posAbs.y - y);
          SDL_RenderDrawPoint(rendererMain, posAbs.x + x, posAbs.y + y);
          SDL_RenderDrawPoint(rendererMain, posAbs.x - x, posAbs.y - y);
          SDL_RenderDrawPoint(rendererMain, posAbs.x - x, posAbs.y + y);
          SDL_RenderDrawPoint(rendererMain, posAbs.x + y, posAbs.y - x);
          SDL_RenderDrawPoint(rendererMain, posAbs.x + y, posAbs.y + x);
          SDL_RenderDrawPoint(rendererMain, posAbs.x - y, posAbs.y - x);
          SDL_RenderDrawPoint(rendererMain, posAbs.x - y, posAbs.y + x);

          if (error <= 0){
               ++y;
               error += ty;
               ty += 2;
          }
          if (error > 0){
               --x;
               tx += 2;
               error += (tx - diameter);
          }
     }
}
void drawCircleFill(vec2 pos, float r, vec3 col){
     vec2 center = uvToAbs(pos);
     int radius = r*res.x;
     int w, h, dx, dy;
     
     setColor(col);
     for (w = 0; w < radius * 2; w++){
          for (h = 0; h < radius * 2; h++){
               dx = radius - w; /* horizontal offset */
               dy = radius - h; /* vertical offset */
               if ((dx*dx + dy*dy) <= (radius * radius)){
                    SDL_RenderDrawPoint(rendererMain, center.x + dx, center.y + dy);
               }
          }
     }
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