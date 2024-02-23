#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>
#include "state_comparer.hpp"
#include "priority_queue.hpp"
using namespace std;

#define MAX_RUN_TIME 900000
#define MAX_LEN 1024

using namespace std::chrono;

enum COLOR
{
    WHITE,
    GRAY,
    BLACK
};

int64_t alreadySpentMaxRuntime(system_clock::time_point &from)
{
    int64_t curTime = duration_cast<milliseconds>(high_resolution_clock::now() - from).count();
    return curTime > MAX_RUN_TIME ? curTime : -1;
}

std::optional<state_t> ucs(state_t root)
{
    int64_t auxTime;
    int64_t totalNodes, numAtD; // counters
    state_t state, child;       // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;
    system_clock::time_point start = high_resolution_clock::now();
    std::unordered_map<state_t, COLOR> colors = {{}};
    bool printedIsGoal = false;
    char rootString[MAX_LEN];
    char outString[MAX_LEN];
    PriorityQueue<state_t> open;        // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated

    ssize_t rootOut = sprint_state(rootString,MAX_LEN,&root);

    state = root;
    state_map_add(map, &state, 0);
    open.Add(0, 0, state);
    colors[state] = COLOR::GRAY;

    d = 0;
    numAtD = 0;
    totalNodes = 0;
    while (!open.Empty())
    {
        // get current distance from goal; since operator costs are
        // non-negative this distance is monotonically increasing
        if (open.CurrentPriority() > d)
        {
            printf("");
            d = open.CurrentPriority();
            numAtD = 0;
        }

        // remove top state from priority state
        state = open.Top();
        open.Pop();
        init_fwd_iter(&iter, &state);

        if ((auxTime = alreadySpentMaxRuntime(start)) != -1)
        {
            
            printf("%s ",rootString);
            std::cout << "\t Interrumpted \t" << duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
            printf("             %" PRId64 "                     %d\n", numAtD, d);
            break;
        }

        if (is_goal(&state))
        {
            // state_to_string(&state);
            sprint_state(outString,MAX_LEN,&state);
            printf("%s ",outString);
            std::cout << "\t True " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
            printf("             %" PRId64 "                     %d\n", numAtD, d);
            printedIsGoal = true;
            return std::optional<state_t>(state);
        }

        numAtD++;
        totalNodes++;

        // look at all succesors of the state
        while ((ruleid = next_ruleid(&iter)) >= 0)
        {

            apply_fwd_rule(ruleid, &state, &child);
            const int child_d = d + get_fwd_rule_cost(ruleid);
            const int *old_child_d = state_map_get(map, &child);
            if (colors.contains(child))
            {
                if (colors[child] == COLOR::WHITE)
                {
                    colors[child] = COLOR::GRAY;
                    open.Add(child_d, child_d, child);
                }
            }
            else if ((old_child_d == NULL) || (*old_child_d > child_d))
            {
                colors[child] = COLOR::GRAY;
                open.Add(child_d, child_d, child);
            }
        }
    }

    // print last level and total states
    if (numAtD > 0 && !printedIsGoal)
    {
        printf("%s ",rootString);
        std::cout << "\t False \t" << duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
        printf("             %" PRId64 "                     %d\n", numAtD, d);
    }

    return std::nullopt;
}

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

    printf("Entrada \t\t\t              Tiempo \t    nodos abiertos       \t Distancia \t\n");
    printf("-----------------------------------------------------------------------------\n");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            counter++;
            numbersOfChars = read_state(line.c_str(), &root);
            if (numbersOfChars <= 0)
            {
                printf("Error: invalid state entered.\n");
                // continue;
            }
            ucs(root);
        }
    }

    file.close();
    return 0;
}