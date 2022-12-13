#include "Graph.h"
#include "Ant.h"
#include "../lib/CTPL/ctpl.h"

#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>


Graph graphInstance;
double bestSolutionCost = -1;
std::vector<int> bestSolutionTabuList;
std::mutex solutionMutex;


void antSolve(int ithread) {
    // Note that int parameter "ithread" is need for CTPL thread pool

    // Creates ant object
    Ant ant(&graphInstance);

    // traverses graph
    ant.traverseGraph();

    // Retrieves values from graph traversal
    auto cost = (float) ant.getCost();
    //std::vector<int> tabuList = ant.getTabuList(); //TODO - remove?

    // Checks if no solution has been set or if new solution is best
    solutionMutex.lock();
    if (bestSolutionCost == -1 || cost < bestSolutionCost ) {
        bestSolutionCost = cost;
        bestSolutionTabuList = ant.getTabuList();
    }
    solutionMutex.unlock();

    //Updates Partial Pheromone
    ant.updatePartialPheromone( (1 / cost) );
}

int solve(const std::string& filePath, int ants, float evapRate, int evaluations, double alpha, double beta, int threads) {
    //Generating graph
    std::cout << "Generating Graph...                       ";
    Graph graph(filePath, alpha, beta);
    graphInstance = graph;
    std::cout << "Done\n";

    std::cout << "Running simulations...                    ";

    // Timer
    auto start = std::chrono::steady_clock::now();

    // Creates [threads] number of threads
    ctpl::thread_pool p( threads );

    // Runs single evaluations till max evaluations have been reached
    for (int evaluation = 0; evaluation < evaluations; ++evaluation) {

        // Assigns antSolve function to CTPL thread pool queue
        for (int i = 0; i < ants; i++){
            p.push(antSolve);
        }

        // Wait for threads to complete work
        p.stop(true);

        // The next two function calls have not been integrated into the ant traversal (which may be more efficient) to make it easy to change the update rule from:
        // t_i_j(t+1) <- (1-p)*t_i_j(t) + delta(t_i_j(t)) [from lecture notes]
        // to:
        // t_i_j(t+1) <- (1-p)*(t_i_j(t) + delta(t_i_j(t))) [from CA specification] - default
        // to change to the first equation, change the order of the next two function calls

        // Add partial pheromone to total pheromone
        graph.addPheromone();

        // Evaporate pheromone
        graph.evaporatePheromone(evapRate);

    }

    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = stop - start;

    //std::vector<int> bestPath = graphInstance.getBestPath(); //TODO - remove

    // If bestSolutionCost is near initial limit value
    if ( bestSolutionCost == -1 ) {
        std::cout << "\n Error, no best path found.";
        return 1;
    }

    std::cout << "Done\n";
    std::cout << "\nIn "<< evaluations << " evaluations found optimal path of cost " << (bestSolutionCost) << " in ";
    std::cout <<  diff.count() << "s\n";
    std::cout << "Best solution ([value] facility at [index] location):\n";
    std::cout << "[ ";
    for (int i : bestSolutionTabuList) {
        std::cout << i << ", ";
    }
    std::cout << bestSolutionTabuList[bestSolutionTabuList.size()] <<" ]\n";

    return 0;
}

int main(int argc, char **argv) {
    // Default Arguments
    std::string filePath = "../../res/dataSet.txt";
    int ants = 100;
    float evapRate = 0.9;
    int evaluations = 10000;
    double alpha = 2.0;
    double beta = 1.0;
    int threads = 1;

    // Reading in arguments from command line
    if (argc == 0) {
        return solve(filePath, ants, evapRate, evaluations, alpha, beta, threads);
    }
    std::string arg0 = argv[0];
    if (arg0 == "--help") {
        std::cout << "\n\n Help info \n\n"; //TODO implement help function
        return 0;
    }
    for (int i = 0; i < argc-1; i = i+2) {
        std::string argument = argv[i];
        std::string value = argv[i+1];
        if (argument == "-ants") {
            ants = std::stoi( value );
        } else if (argument == "-evapRate") {
            evapRate = std::stof( value );
        } else if (argument == "-evaluations") {
            evaluations = std::stoi( value );
        } else if (argument == "-alpha") {
            alpha = std::stod( value );
        } else if (argument == "-beta") {
            beta = std::stod( value );
        } else if (argument == "-threads") {
            threads = std::stoi( value );
        } else {
            std::cout << "\nError - Invalid arguments";
            return 1;
        }
    }
    return solve(filePath, ants, evapRate, evaluations, alpha, beta, threads);
}
