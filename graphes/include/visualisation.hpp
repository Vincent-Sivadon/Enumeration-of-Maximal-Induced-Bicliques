/*
    - Contient l'implémentation de la fonction Graph::draw()
      et toutes les fonctions intermédiaires à celle-ci
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <math.h>

#include <SDL2/SDL.h>


typedef unsigned long long u64;



// Structures permettant la représentation des positions, vitesses, et accélérations de chaque sommet
struct Vector {
    double x;
    double y;
    Vector() {}
    Vector(double x, double y) :x(x), y(y) {} 
};

// Génère un nombre aléatoire dans [centre - plage/2 , centre + plage/2]
u64 randxy(u64 plage, u64 centre)
{
  return centre - 0.5*plage + rand()%plage; 
}

// Détermine quel pixel font parti d'un disque de rayon 5 et les dessine
void drawParticle(SDL_Renderer* renderer, Vector center) {
    // Coordonnées du centre du disque
    double xc = center.x, yc = center.y;
    double x = 0, y = 5;

    SDL_SetRenderDrawColor ( renderer, 250, 250, 250, 255 );
    SDL_RenderDrawPoint( renderer, xc+x, yc-y );

    u64 p = 3 - (2*5);
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

// Met à jour l'accélération que subit un sommet en fonction des autres sommets
template <typename T>
void compute_accelerations(Graph<T>& graph, std::vector<Vector>& pos, std::vector<Vector>& acc, double l0) {
    // Nombre de sommets
    u64 N = graph.N;

    // Calcul la force entre i et j
    for(u64 i=0 ; i<N ; i++) {
        // Remet à zéro l'accélération du sommet i
        acc[i].x = 0 ; acc[i].y = 0;

        // Parcourt tout les autres sommets
        for(u64 j=0 ; j<N ; j++) {
            // un sommet n'exerce pas de force sur lui-même
            if(i==j) continue;

            // Coordonées du vector position de i vers j
            double rx = pos[j].x - pos[i].x;
            double ry = pos[j].y - pos[i].y;

            // Taille du vecteur position
            double rMod = sqrt(rx*rx + ry*ry);

            // Force entre les sommets i et j en fonction de s'ils sont liés ou pas
            double k1 = 1/l0;
            double k2 = 4 * l0*l0;
            double f1 = - k1 * (rMod - l0);  // force attractive (si i et j liés)
            double f2 = k2/(rMod*rMod);      // force répulsive (dans tout les cas)

            // Construction des vecteurs correspondants à ces forces
            double attX = rx * (f1/rMod)  ;  double attY = ry * (f1/rMod);
            double repX = rx * (f2/rMod)  ;  double repY = ry * (f2/rMod);

            // Tout les sommets se repoussent entre eux
            acc[i].x = acc[i].x - repX;
            acc[i].y = acc[i].y - repY;

            // Mais seuls les sommets connectés s'attirent
            if ( graph.areConnected(i,j) ) {
                acc[i].x = acc[i].x - attX;
                acc[i].y = acc[i].y - attY;
            }
        }
    }
}

// Met à jour les positions des sommets sur le dessins en fonction de l'accélération calculée
template <typename T>
void compute_positions(Graph<T>& graph, std::vector<Vector>& pos, std::vector<Vector> vel, std::vector<Vector>& acc, u64 w, u64 h) {
    // Pour pas qu'un sommet soit dessiné exactement au bord de la fenêtre
    u64 limits = 20;

    // Pour chaque sommet
    for (u64 i = 0; i<graph.N ; i++) {
        // Vecteur position du sommet i
        double tmpX = pos[i].x;
        double tmpY = pos[i].y;

        // Calcul de sa nouvelle position en fonction de sa vitesse et de son accélération
        tmpX += vel[i].x + (acc[i].x * 0.5);
        tmpY += vel[i].y + (acc[i].y * 0.5);

        // Mise à jour de la position seulement s'il ne sort pas de la fenêtre (à limits près)
        if ( (tmpX <= w-limits) & (tmpX >= limits) & (tmpY <= h-limits) & (tmpY >= limits) ) {
            pos[i].x = tmpX;
            pos[i].y = tmpY;
        }
    }
}

// Fonction principale de mise à jour des positions des sommets
template <typename T>
void simulate(Graph<T>& graph, std::vector<Vector>& pos, std::vector<Vector> vel, std::vector<Vector>& acc, double l0, u64 w, u64 h) {
    // Nombre de sommets
    u64 N = graph.N;

    // Met à jour les accélérations
    compute_accelerations(graph, pos, acc, l0);

    // Met à jour les vitesses
    for(u64 i=0 ; i<N ; i++) {
        vel[i].x = vel[i].x + acc[i].x;
        vel[i].y = vel[i].y + acc[i].y;
    }

    // Met à jour les positions
    compute_positions(graph, pos, vel, acc, w, h);
}


// Dessine le graph à l'écran
template <typename T>
void Graph<T>::draw() {
    // Initialise random seed
    srand(getpid());

    // Parameters
    u64 width = 800, height = 800;  // dimensions de la fenêtre
    u64 timeSteps = 300;            // nombre de pas de temps de la simulation
    double l0 = 50;                 // Taille du "ressort" qui représente les forces attractives entre sommets liés

    // Variables de positions, vitesses et accélérations pour chaque sommet
    std::vector<Vector> pos(N), vel(N), acc(N);

    // Initialisation des positions et des vitesses pour chaque sommet
    for(u64 i=0 ; i<N ; i++) {
        pos[i].x = randxy(200, 400);
        pos[i].y = randxy(200, 400);

        vel[i].x = 0;
        vel[i].y = 0;
    }

    // SDL initialisation (bibliothèque graphique 2D)
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);

    // Boucle de la simulation
    for(u64 t=0 ; t<timeSteps ; t++) {
        // Met à jour les positions des sommets sur le dessin
        simulate<T>(*this, pos, vel, acc, l0, width, height);

        // Efface le contenu graphique de la fenêter
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessine chaque sommets et chaque liens s'ils existent
        for(u64 i=0 ; i<N ; i++) {
            drawParticle(renderer, pos[i]);
            for(u64 j=0 ; j<N ; j++) 
                if (areConnected(i,j))
                    SDL_RenderDrawLine(renderer, pos[i].x, pos[i].y, pos[j].x, pos[j].y);
        }

        // Actualisation graphique de la fenêtre
        SDL_RenderPresent(renderer);
    }

    // Met tout le code en pause tant que l'utilisation ne quitte pas la fenêtre
    while( SDL_WaitEvent(&event))
        if (event.type==SDL_QUIT) break;
    
    // Nettoie la mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
