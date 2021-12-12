#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <math.h>

#include "SDL2/SDL.h"

#include "visualisation.hpp"

struct Vector {
    double x;
    double y;
    Vector() {}
    Vector(double x, double y) :x(x), y(y) {} 
};

// Random positions generator
int randxy(int plage, int centre)
{
  return centre - 0.5*plage + rand()%plage; 
}

void drawParticle(SDL_Renderer* renderer, Vector center) {
    // Center coordinates
    double xc = center.x, yc = center.y;
    double x = 0, y = 5;

    SDL_SetRenderDrawColor ( renderer, 250, 250, 250, 255 );
    SDL_RenderDrawPoint( renderer, xc+x, yc-y );

    int p = 3 - (2*5);

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


void compute_accelerations(Graph& graph, std::vector<Vector>& pos, std::vector<Vector>& acc, double l0) {
    // Get number of vertices
    u64 N = graph.N;

    // Compute the force between i and j
    for(int i=0 ; i<N ; i++) {
        acc[i].x = 0 ; acc[i].y = 0;
        for(int j=0 ; j<N ; j++) {
            if(i==j) continue;
            // Position Vector beetween i and j
            double rx = pos[j].x - pos[i].x;
            double ry = pos[j].y - pos[i].y;

            // Module of position vector
            double rMod = sqrt(rx*rx + ry*ry);

            // Forces
            double k1 = 1/l0;
            double k2 = 4 * l0*l0;
            double f1 = - k1 * (rMod - l0);  // if i and j are connected
            double f2 = k2/(rMod*rMod);      // if i and j aren't connected

            // Vector storing forces and directions
            double attX = rx * (f1/rMod)  ;  double attY = ry * (f1/rMod);
            double repX = rx * (f2/rMod)  ;  double repY = ry * (f2/rMod);

            // All vertices apply repulsive froce to each other
            acc[i].x = acc[i].x - repX;
            acc[i].y = acc[i].y - repY;

            std::cout << rMod << std::endl;

            if ( graph.areConnected(i,j) ) {
                acc[i].x = acc[i].x - attX;
                acc[i].y = acc[i].y - attY;
            }
        }
    }
}

void compute_positions(Graph& graph, std::vector<Vector>& pos, std::vector<Vector> vel, std::vector<Vector>& acc, int w, int h) {
    int limits = 20;
    for (u64 i = 0; i<graph.N ; i++) {
        double tmpX = pos[i].x;
        double tmpY = pos[i].y;

        tmpX += vel[i].x + (acc[i].x * 0.5);
        tmpY += vel[i].y + (acc[i].y * 0.5);
        if ( (tmpX <= w-limits) & (tmpX >= limits) & (tmpY <= h-limits) & (tmpY >= limits) ) {
            pos[i].x = tmpX;
            pos[i].y = tmpY;
        }
    }
}

void simulate(Graph& graph, std::vector<Vector>& pos, std::vector<Vector> vel, std::vector<Vector>& acc, double l0, int w, int h) {
    u64 N = graph.N;
    compute_accelerations(graph, pos, acc, l0);
    for(int i=0 ; i<N ; i++) {
        //vel[i].x = vel[i].x * 2;
        //vel[i].y = vel[i].y * 2;
        vel[i].x = vel[i].x + acc[i].x;
        vel[i].y = vel[i].y + acc[i].y;
    }
    compute_positions(graph, pos, vel, acc, w, h);
}

void drawGraph(Graph& graph) {
    // Initialise random seed
    srand(getpid());

    // Parameters
    int width = 800, height = 800;
    u64 timeSteps = 300;
    double l0 = 50;  // Spring size
    u64 N = graph.N;

    // Physicals variables
    std::vector<Vector> pos(N), vel(N), acc(N);

    // Initialize Random Positions and Velocities
    for(u64 i=0 ; i<N ; i++) {
        pos[i].x = randxy(200, 400);
        pos[i].y = randxy(200, 400);

        vel[i].x = 0  ;  vel[i].y = 0;
    }

    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);

    for(u64 t=0 ; t<timeSteps ; t++) {
        simulate(graph, pos, vel, acc, l0, width, height);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for(u64 i=0 ; i<N ; i++) {
            drawParticle(renderer, pos[i]);
            for(u64 j=0 ; j<N ; j++) 
                if (graph.areConnected(i,j))
                    SDL_RenderDrawLine(renderer, pos[i].x, pos[i].y, pos[j].x, pos[j].y);
        }

        SDL_RenderPresent(renderer);
    }

    while( SDL_WaitEvent(&event))
        if (event.type==SDL_QUIT) break;
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}