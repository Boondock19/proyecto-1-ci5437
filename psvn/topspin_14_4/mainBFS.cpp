#include <iostream>
#include <fstream>
#include <string>
#include "BFS.hpp"
using namespace std;
//#include "aux.hpp"

int main(int argc, char const *argv[])
{

    ssize_t numbersOfChars;
    state_t root;
    int counter = 0;
    
    string line;
    ifstream file(argv[1]);
    
    if (argc != 2)
        return 1;

    cout << argv[1] << endl;

    printf("Instancia \t\t\t\t\t Solucion \t Tiempo de solucion \t   Nodos expandidos  \t  Distancia\t\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
   

    if (file.is_open()) {
        while (getline(file, line)) {
            numbersOfChars = read_state(line.c_str(), &root);
            if (numbersOfChars <= 0) {
                printf("Error: invalid state entered.\n");
            }

            do_bfs(root);
            printf("---------------------------------------------------------------------------------------------------------------\n");
            printf("con poda: \n");
            do_bfs_prunning(root);
            
            
        }
       
    }
    
        file.close();
        return 0;
        
    
}