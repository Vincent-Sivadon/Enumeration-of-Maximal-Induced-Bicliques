#include<iostream>
#include<vector>

#include<algorithm>


typedef struct  edgeMin // structure dont les champs stockent le sommet de degré minimal et ledit degré
{
    int degree;
    int vertex;
}edgeMin;

/************ Fonction permettant de connaitre Le degre de chaque sommet*****/
std::vector<int> Find_degrees(std::vector<int> graph[],int Nb_vertices)
{
    std::vector<int> edgesDegree(Nb_vertices); 

    for(int i = 0; i < Nb_vertices; i++)
       edgesDegree[i] = graph[i].size(); // Pour chaque sommet donc entré de la liste d'adjacence, compter le nombre de
                                          // sommet voisins.

    return edgesDegree;
}


/********* Fonction utilitaire permettant d'afficher le tableau des degrés *******************/
void PrintVercticesDeg(std::vector<int> Vertices)
{
    for(int i = 0; i < Vertices.size(); i++)
    {
        std::cout << "Sommet " << i << ": " << Vertices[i] <<"\n";
    }
}

/******** Fonction utilitaire permettant d'afficher le graphe ***********************************/

void printGraph(std::vector<int> graph[], int N)
{
    for (int i = 0; i < N; i++){
        std::cout << "\n voisins de : " << i 
                  << "\n";
        for(auto x : graph[i])
            std::cout << "->" << x;
            printf("\n");}
}

/************* Fonction permettant d'ajouter des arretes a un graphe modeliser par une liste d'adjacence */

void addEdge(std::vector<int> graph[], int a, int b)
{
    graph[a].push_back(b);
    graph[b].push_back(a);
}


/************* fonction permettant de trouver les sommets de degrés minimum ainsi que le degré minimal d'un graphe passé en argument *****************************/





edgeMin FindVertexDegMin(std::vector<int> graph[],int N)
{
    edgeMin s;
    std::vector<int>EdgeDeg = Find_degrees(graph,N);            // Trouver les degrés de chaque sommet du graphe passé en argument et les stocker dans un tableau
    int vertexWithDegMin = 0;                                   // On commence par initialisé le sommet de degré minimal comme le premier sommet de la liste d'adjacence
    int minEdgeDeg     = EdgeDeg[vertexWithDegMin];             // On commence également par initialisé le degré minimial par le degré du premier sommet
   
    for(int i = 0; i < N ; i++ )                                 // Parcourir le tableau des degrés à la recherche du sommet de degré minimal
    {
        if (EdgeDeg[i] < minEdgeDeg)
        {
            minEdgeDeg     = EdgeDeg[i];                         // Mettre à jour le degré minimal
            vertexWithDegMin = i;                               // Mettre à jour le sommet de degré minimal
        }
    }
    s.degree = minEdgeDeg;
    s.vertex = vertexWithDegMin;

    return s;

}

/* Fonction utilitaire pour afficher le degrée d'un minimal et le sommet du graphe ayant ce degré*****************/
void printMinVertex(edgeMin s)
{
    std::cout << " Vertex with minimum degree :" << s.vertex <<"\n";
    std::cout << " Minimal degree : " << s.degree << "\n";
}

void delNode(std::vector<int>graph[], int N, int node) {
    for(int i = 0; i< N; i++){
        auto finded = std::find(graph[i].begin(), graph[i].end(), node);
        if(finded != graph[i].end())
            graph[i].erase(graph[i].begin(), finded);
    }
}

/* Fonction pour supprimer les sommets d'un graphe ****/

void delVertices(std::vector<int>graph[], int N, int vertex)
{
    for(int i = 0; i< N; i++)
    {
        for(auto& i : graph[i])
            std::cout << i << " ";
        std::cout << std::endl;
    }

    for(int i = 0; i< N; i++)
    {
        if(i == vertex)
        {
            int n = graph[i].size();
            std::cout << "n : " << n << " delete : " << vertex << "\n";
            for(auto& i : graph[i])
                std::cout << i << " ";
            std::cout << std::endl;
            /*for(int j= 0; j<n; j++)
            {
                
                std::vector<int>::iterator it1;
                std::vector<int>::iterator it2;
                it1 = std::find(graph[i].begin(),graph[i].end(),j);
                it2 = std::find(graph[j].begin(),graph[j].end(),i);
                std::cout << j <<":"<<*it2;
                if(it1 == graph[i].end())
                    std::cout << "not found" << std::endl;
                graph[i].erase(it1);
                //graph[j].erase(it2);
                
            }*/
        }
    }
}
/*

vector <int> edges;                 // ce tableau permet de stocker les sommets du graphes
vector <int> degree_tab;            // ce tableau permet de stocker le degré minimal à chaque étape de l'algorithme

int N ;                             // Nombre de sommets initiale dans le graphe

/******************* Début de la boucle en N afin  de trouver l'ordre de dégénérescence du graphe******************/
/* 
for (int i= 0; i<N; i++)
{

}

 */

int main()
{
    int N = 5;
    // Graph
    std::vector<int> graph[N];
    /*for (unsigned i=0; i<5; i++)
        graph.emplace_back();*/

    // Ajout des arêtes
    addEdge(graph,0,1);
    addEdge(graph,0,4);
    addEdge(graph,1,4);
    addEdge(graph,1,3);
    addEdge(graph,1,2);
    addEdge(graph,2,3);
    addEdge(graph,3,4);
    //

    printGraph(graph,N);

/*    
    std::vector<int> VertDeg = Find_degrees(graph,N);

    PrintVercticesDeg(VertDeg); 

    edgeMin s = FindVertexDegMin(graph,N);
    printf("\n");
    printMinVertex(s);

    printf("\n"); */
    delVertices(graph,N,2);
    //printGraph(graph,N);
    return 0;
}