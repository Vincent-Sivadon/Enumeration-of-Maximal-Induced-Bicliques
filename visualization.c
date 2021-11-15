#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "adjlst.h"



/* COMPILATION
        gcc molecule.c -o molecule `sdl2-config --cflags --libs` -lm
*/

typedef struct {
    double x,y;
} Vector;
Vector addV(Vector a, Vector b)
{
    Vector c = { a.x + b.x, a.y + b.y};
    return c;
}
Vector subV(Vector a, Vector b)
{
    Vector c = { a.x - b.x, a.y - b.y};
    return c;
}
Vector mulV(double b, Vector a)
{
    Vector c = { b * a.x, b * a.y};
    return c;
}
double mod(Vector a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}



typedef struct {
    int radius;
    Vector acc;
    Vector vel;
    Vector pos;
} Atom;



typedef struct {
    double k;
    double l0;
} Spring;


// Random positions generator
int randxy(int plage, int centre)
{
  return centre - 0.5*plage + rand()%plage; 
}


// GLOBAL VARIABLES
int N;      // Number of molecule
int w,h;    // Window dimension
int timeSteps;

//
Spring spring;
Atom* molecule;
int* edges;



//
void read_edges(const char* filename)
{
    // Open file
    FILE *fp = fopen(filename, "rb");
    if(!fp)
      printf("Error : can't open '%s'\n", filename);
    
    // Get numbers vertices
    fscanf(fp, "%d\n", &N);

    // Allocation
    edges = malloc(N * N * sizeof(int));

    // Fill step by step
    int d = 0;
    for(int i=0 ; i<N*N ; i++){
      fscanf(fp, "%d ", &d);
      edges[i] = d;
    }
    
    fclose(fp);
}

void init_system(const char* filename)
{
    // Parameters
    w = h = 800;
    timeSteps = 1000;
    spring.k = 1;
    spring.l0 = 50;

    // Get Edges
    read_edges(filename);

    // Allocate molecules
    molecule   = malloc(N * sizeof(Atom));


    // Determine number of edges
    int maxEdges = N * (N-1) / 2;
    int nEdges = maxEdges / 5   ;

    for(int i=0 ; i<N ; i++){
        molecule[i].radius = 5;

        // Random positions
        molecule[i].pos.x = randxy(200, 400);
        molecule[i].pos.y = randxy(200, 400);
        
        //
        molecule[i].vel.x = 0;
        molecule[i].vel.y = 0;
    }
}


void drawAtom ( SDL_Renderer * renderer, Atom atom)
{
    // Center coordinates
    int xc = atom.pos.x, yc = atom.pos.y;
    int x = 0, y = atom.radius;

    SDL_SetRenderDrawColor ( renderer, 250, 250, 250, 255 );
    SDL_RenderDrawPoint( renderer, xc+x, yc-y );

    int p = 3 - (2*atom.radius);

    for ( x=0 ; x<=y ; x++ )
    {
        if ( p<0 )
        {
            p = ( p + (4*x) + 6 );
        }
        else
        {
            y -= 1;
            p += ( ( 4*(x-y) + 10) );
        }
        SDL_RenderDrawLine ( renderer, xc+x, yc-y, xc-x, yc-y);
        SDL_RenderDrawLine ( renderer, xc+x, yc+y, xc-x, yc+y);
        SDL_RenderDrawLine( renderer, xc+y, yc-x, xc-y, yc-x);
        SDL_RenderDrawLine ( renderer, xc+y, yc+x, xc-y, yc+x);
    }
}



void compute_accelerations()
{
  // Reset accelerations at each new time
  for (int i = 0; i < N; i++) {molecule[i].acc.x = 0 ; molecule[i].acc.y = 0;}


  // Compute the force between i and j
  for (int i = 0; i < N; i++)
    {     
      for(int j = i+1; j < N; j++){
        // Position Vector between i and j
        Vector r = subV( molecule[j].pos, molecule[i].pos);

        // Forces
        double k1 = 1/(spring.l0);
        double k2 = 4 * spring.l0*spring.l0;
        double f1 = - k1 * (mod(r) - spring.l0);     // if i and j are connected
        double f2 = k2/(mod(r) * mod(r));           // if i and j aren't connected 

        // Vector storing forces and directions
        Vector attractive = mulV(f1 / mod(r), r);
        Vector repulsive  = mulV(f2 / mod(r), r);

        // All vertices apply repulsive for to each other
        molecule[i].acc = subV(molecule[i].acc, repulsive);
        molecule[j].acc = addV(molecule[j].acc, repulsive);

        // Attractive forces between i and j only if they are connected
        if ( edges[i*N + j] ){
          molecule[i].acc = subV(molecule[i].acc, attractive);
          molecule[j].acc = addV(molecule[j].acc, attractive);

        }

      }
    }
}


//
void compute_velocities()
{  
  for (int i = 0; i < N; i++)
    molecule[i].vel = addV(molecule[i].vel, molecule[i].vel);
}

//
void compute_positions()
{
    int limits = 20;
  for (int i = 0; i < N; i++){
    Vector tmp;
    tmp = molecule[i].pos;
    tmp = addV(tmp, addV(molecule[i].vel, mulV(0.5, molecule[i].acc)));
    if ( (tmp.x <= w-limits) & (tmp.x >= limits) & (tmp.y <= h-limits) & (tmp.y >= limits) ) molecule[i].pos = tmp;
  }
}

void simulate()
{
    compute_accelerations();
    compute_velocities();
    compute_positions();
    // resolve_collision
}


int main(int argc, char **argv)
{
  if(argc < 2)
    return printf("Usage : %s [filename]\n", argv[0]), 1;
  char* filename = argv[1];

  // SDL Parameters
  int quit = 0;
  SDL_Event event;
  SDL_Window *window;
  SDL_Renderer *renderer;

  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);

  // Seed Generation
  srand(getpid());

  // Initialize System
  init_system(filename);

  for (int i=0 ; !quit && i<timeSteps ; i++)
  {
    simulate();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i=0 ; i<N ; i++)
    {
      drawAtom(renderer, molecule[i]);
      for (int j=0 ; j<N ; j++){
        if ( edges[i*N + j] )
          SDL_RenderDrawLine(renderer, molecule[i].pos.x, molecule[i].pos.y, molecule[j].pos.x, molecule[j].pos.y);
      }
    }

    //
    SDL_RenderPresent(renderer);
    SDL_Delay(5);


    while (SDL_PollEvent(&event))
      if (event.type == SDL_QUIT)
        quit = 1;
      else
        if (event.type == SDL_KEYDOWN)
          if (event.key.keysym.sym == SDLK_q)
            quit = 1;
  }

  while ( !quit ){
    while (SDL_PollEvent(&event))
      if (event.type == SDL_QUIT)
        quit = 1;
      else
        if (event.type == SDL_KEYDOWN)
          if (event.key.keysym.sym == SDLK_q)
            quit = 1;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}