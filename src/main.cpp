#include "Graph.h"
#include "Ant.h"
#include "../lib/CTPL/ctpl.h"

#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>


Graph graphInstance;
double bestSolutionInverseCost = 0;
std::vector<int> bestSolutionTabuList;
std::mutex solutionMutex;


void antSolve(int ithread) {
    std::cout << "In main::antSolve ";

    // Creates ant object
    Ant ant(&graphInstance);

    // traverses graph
    ant.traverseGraph();



    // Retrives values from graph traversal
    float inverseCost = ant.calculateInverseCost();
    std::vector<int> tabuList = ant.getTabuList();

    std::cout << "\ninverse cost of tabu list: " << inverseCost << "\n";

    // checks if solution is best
    // TODO - put outside thread?
    solutionMutex.lock();
    if (bestSolutionInverseCost < inverseCost) {
        bestSolutionTabuList = tabuList;
        bestSolutionInverseCost = inverseCost;
    }
    solutionMutex.unlock();

    std::cout << "\n new best inverse cost: " << bestSolutionInverseCost << "\n";

    //Updates Pheromone
    ant.updatePheromone(inverseCost);
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

        // Assigns ant work to CTPL thread pool
        for (int i = 0; i < ants; i++){
            p.push(antSolve);
        }

        // Wait for threads to complete
        p.stop(true);

        // Evaporate pheromone
        graph.evaporatePheromone(evapRate);

        try {
            // Add partial pheromone to total pheromone
            graph.addPheromone(graph.getPartialPheromone()); //TODO - this line breaks everything
        } catch (std::out_of_range e) {
            std::cout << "\nWarning: \n";
            std::cout << e.what();
        }
    }

    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = stop - start;

    std::cout << "Done\n";
    std::cout << "\nFound an optimal path of cost " << (bestSolutionInverseCost/1) << " in ";
    std::cout <<  diff.count() << "s\n";
    std::cout << "Best solution ([value] facility at [index] location:\n";
    std::cout << "[ ";
    for (unsigned long i = 0; i < bestSolutionTabuList.size()-1; i++) {
        std::cout << bestSolutionTabuList[i] << ", ";
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
        std::cout << "\n\n Help info \n\n"; //TODO
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
