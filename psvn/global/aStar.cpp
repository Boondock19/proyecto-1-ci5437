#include <vector>
#include "priority_queue.hpp"
#include <stdbool.h>
#include <fstream>
#include <string>
#include <time.h>
#include <sstream>
#include <iterator>
#include <cmath>
#include <ctime>
#define  MAX_LINE_LENGTH 999
using namespace std;
int64_t nodes;


// Funcion que verifica si el estado tiene solucion
bool has_solution(std::vector<int> state) {
    int invertions = 0;
    int blank_arrow = 0;
    int size = sqrt(state.size());

    //El blanco siempre esta en la primera posicion
    blank_arrow = 1;

    for (int i = 0; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            if (state[j] != 0 && state[j] < state[i]) {
                invertions++;
            }
        }
    }

    if (size % 2 == 0) {
        if (blank_arrow % 2 == 0) {
            return invertions % 2 != 0;
        } else {
            return invertions % 2 == 0;
        }
    } 
    return invertions % 2 == 0;   
}



int aStar(state_t *root)
{
    /**
     * Declaracion de variables con sus tipos
    */
    PriorityQueue<state_t> queueP;
    state_map_t *distance = new_state_map();
    state_t state, children; 
    int g, ruleid;
    ruleid_iterator_t iter;

    /**
     * Inicializamos la busqueda de la solucion con
     * el estado inicial
    */
    state_map_add( distance, root, 0 );
    queueP.Add(0, 0, *root );
    
    //Inicializacion del tiempo de interrumpcion
    std::clock_t initInterrumption = std::clock();

    // Loop de busqueda de A estrella
    while(!queueP.Empty()) {
        // Interrumpir la busqueda si el tiempo excede 5 minutos
        double interrumptionTime = (std::clock() - initInterrumption) / (double) CLOCKS_PER_SEC;
        if (interrumptionTime > 150.0) {
            return -2;
        }


        g = queueP.CurrentPriority();
        state = queueP.Top();
        queueP.Pop();

        int *oldDistance = state_map_get(distance, &state);
        // contador de nodes expandidos / estados abiertos
        ++nodes;



        if ((oldDistance == NULL) || (g < *oldDistance) || (!compare_states(&state, root))) {
            state_map_add( distance, &state, g );
            // Si llegamos a la meta lo retornamos
            if (is_goal(&state)) {
                return g;
            }

            // Iterador de look ahead
            init_fwd_iter( &iter, &state );

            // Generamos la proxima regla/operacion disponible para el estado
            // Si es valida la aplicamos y generamos el nuevo estado
            while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
                apply_fwd_rule( ruleid, &state, &children );
                int children_g = g + get_fwd_rule_cost( ruleid );
                int children_h = heuristica(children);
                int children_f = children_g + children_h;
                if (children_h < INT_MAX) {
                    queueP.Add( children_f, children_g, children );

                }
            }
        }
    }
    return -1;
}



int main(int argc, char const *argv[]){
    char str[MAX_LINE_LENGTH + 1];
    string line;
    int result;
    ssize_t numbersOfChars;
    float runTime;
    state_t root;
    ifstream file;
    clock_t init, end, duration;


     cargarPDBs();


    printf("Por favor ingrese un txt de prueba: ");
    if (fgets(str, sizeof str, stdin) == NULL) {
        printf("Ocurrio un error al leer el input del usuario.\n");
        return 0;
    }


    str[strlen(str)-1] = '\0';

    file.open(str);

    if (!file.is_open()) {
        printf("El nombre del archivo no es correcto, por favor ingrese el nombre adecuadamente: %s\n", str);
        return -1;
    }

    printf("Entrada \t\t\t Tiempo \t   nodos abiertos       Distancia\t\n");
    printf("-----------------------------------------------------------------------------\n");
    
    while (getline(file, line)) {
        
        //printf("line: %s\n", line.c_str());

        //Verificar num de inversiones
        std::string line_copy = line;
        std::replace(line_copy.begin(), line_copy.end(), 'b', '0');
        std::istringstream iss(line_copy);
        std::vector<int> state((std::istream_iterator<int>(iss)), std::istream_iterator<int>());

        if (!has_solution(state)) {
            printf("%s \t False \t 0 \t\t 0\n", line.c_str());
        }
        
        numbersOfChars = read_state(line.c_str(), &root);
        if (numbersOfChars <= 0) {
            printf("Error: invalid state entered.\n");
            //continue;
        }

        

        init = clock();
        nodes = 0; 
        result = aStar(&root);
        end = clock();

        duration = end - init;

        runTime = duration / (double) CLOCKS_PER_SEC;

        if (result == -2) {
            printf("%s \t Interrumption \t %f \t %ld \t\t\n", line.c_str(), runTime, nodes);
        }

        if (result == -1) {
            printf("%s \t False \t %f \t %ld \t\t %d\n", line.c_str(), runTime, nodes, result);
        } else {
            printf("%s \t True \t %f \t %ld \t\t %d\n", line.c_str(), runTime, nodes, result);
        } 

        
    }

    file.close();
    return 0;
}