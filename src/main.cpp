#include "Graph.h"
#include "Ant.h"
#include "../lib/CTPL/ctpl.h"

#include <iostream>


Graph graphInstance;
double bestSolutionCost = -1;
std::vector<int> bestSolutionTabuList;
std::mutex solutionMutex;

/** \Brief Generates ant object, traverses graph, and updates partial pheromone.
 *
 * Pushed to CTPL thread pool queue by solve().
 * Creates ant with graphInstance variable, and calls the ant to traverse this graph.
 * Acquires a mutex lock (solutionMutex) then checks and amends bestSolutionCost and bestSolutionTabuList as necessary.
 * Finally, adds fitness (inverse cost) to partialPheromone for appropriate nodes.
 *
 * @param ithread - Int parameter required for the CTPL thread pool library, implementation here is unused.
 */
void antSolve([[maybe_unused]] int ithread) {
    // Note that int parameter "ithread" is need for CTPL thread pool

    // Creates ant object
    Ant ant(&graphInstance);

    // traverses graph
    ant.traverseGraph();

    // Retrieves values from graph traversal
    auto cost = (float) ant.getCost();

    // Checks if no solution has been set or if new solution is best
    solutionMutex.lock();
    if (bestSolutionCost == -1 || cost < bestSolutionCost ) {
        bestSolutionCost = cost;
        bestSolutionTabuList = ant.getTabuList();
    }
    solutionMutex.unlock();

    // Updates Partial Pheromone

    ant.updatePartialPheromone( (1 / cost) );
    ant.updateInitialPartialPheromone( (1 / cost));

}

/** \brief Calls antSolve() for number of ants, then updates pheromone n times according to number of evaluations specified,
 *      then  prints results to console.
 *
 * Calls antSolve() for number of ants, adds partial pheromone after being updated by each ant.
 * Then updates pheromone, and finally evaporates pheromone.
 * Does this n times according to number of evaluations, then prints results.
 *
 * @param filePath - String filepath
 * @param ants - Number of ants
 * @param evapRate - Evaporation rate (multiplicative)
 * @param evaluations - Number of evaluations
 * @param alpha - Exponent of pheromone in determining node traversal probability.
 * @param beta - Exponent of heuristic in determining node traversal probability.
 * @param threads - Number of threads generated in thread pool to run antSolve() function calls.
 * @return - Exit status.
 */
int solve(const std::string& filePath, int ants, float evapRate, int evaluations, double alpha, double beta, int threads) {
    //Generating graph
    std::cout << "Generating Graph...                       ";
    Graph graph(filePath, alpha, beta);
    graphInstance = graph;
    std::cout << "Done\n";

    std::cout << "Running simulations...                    ";

    // Gets start time
    auto start = std::chrono::steady_clock::now();

    // Creates [threads] number of threads in thread pool
    // A thread pool is used to remove overhead of generating and destroying threads.
    ctpl::thread_pool p( threads );

    // Runs single evaluations till max evaluations have been reached
    for (int evaluation = 0; evaluation < evaluations; ++evaluation) {

        // Add antSolve function calls according to number of ants to CTPL thread pool queue
        for (int i = 0; i < ants; i++){
            p.push(antSolve);
        }

        // Wait for threads to complete work
        p.stop(true);

        // The next two function calls have not been integrated into the ant traversal (which may be more efficient) to make it easy to change the update rule from:
        // t_i_j(t+1) <- (1-p)*t_i_j(t) + delta(t_i_j(t)) [from lecture notes]
        // to:
        // t_i_j(t+1) <- (1-p)*(t_i_j(t) + delta(t_i_j(t))) [from CA specification] - default
        // to change to the first equation, swap the order of the next two function calls

        // Add partial pheromone to total pheromone
        graph.addPheromone();
        graph.addInitialPheromone();

        // Evaporate pheromone
        graph.evaporatePheromone(evapRate);

    }

    // Gets stop time
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = stop - start;

    // If bestSolutionCost has not been updated, produces error - avoids segmentation fault at line 117
    if ( bestSolutionCost == -1 ) {
        std::cout << "\n Error, no best path found.";
        return 1;
    }

    // Prints results to console
    std::cout << "Done\n";
    std::cout << "\nIn "<< evaluations << " evaluations with "<< evaluations*ants << " total paths generated, found optimal path of cost " << (bestSolutionCost) << " in ";
    std::cout <<  diff.count() << "s\n";
    std::cout << "Best solution list: (location:facility)\n";
    std::cout << "[ ";
    int numOfValues = graphInstance.getNumberOfLocations();
    for (int i = 0; i < numOfValues-1; i++) {
        std::cout << "(" << i << ":" << bestSolutionTabuList[i] << "), ";
    }
    std::cout << "(" << (int) numOfValues << ":" << bestSolutionTabuList[numOfValues-1] << ") ]\n";

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

    // ---- Reading in arguments from command line

    // If no arguments provided, uses defaults
    if (argc == 0) {
        return solve(filePath, ants, evapRate, evaluations, alpha, beta, threads);
    }

    std::string arg0 = argv[0];
    if (arg0 == "--help" || arg0 == "-h") {
        // Prints help to console if -h or --help flag specified
        std::cout << "\n\nHelp info:\n\n";
        std::cout << "Program can be run with various optional [compiler flag] [value] pairs. If a flag and value pair is not specified default values will be used (shown below).\n";
        std::string helpStringBody = "Possible arguments flags and values are:\n"
                                     "  -h/--help           : Shows this text.\n"
                                     "  -filePath           : "
                                     "  -ants [int]         : Number of ants to run on each evaluation.\n"
                                     "  -evapRate [double]  : Rate at which pheromone evaporates.\n"
                                     "  -evaluations [int]  : Number of total evaluations\n"
                                     "  -alpha [double]     : Exponent of pheromone in determining node traversal probability\n"
                                     "  -beta [double]      : Exponent of distance in determining node traversal probability\n"
                                     "  -threads [int]      : Number of thread to be created to run ants.\n\n"
                                     ""
                                     "Example:\n"
                                     "      ./QACO -filePath ../../dataSet.txt -ant 100 -evaluations 10000 -beat 0.5 -threads 2\n";

        std::cout << helpStringBody;
        return 0;
    }

    // Checks for flags and sets value
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
            threads = std::stoi(value);
        } else if (argument == "-filePath") {
            filePath = value;
        } else {
            // Catches invalid arguments
            std::cout << "\nError - Invalid arguments:\n";
            std::cout << argv[i] << "\n";
            std::cout << "Please use flag '--help' for further guidance.";
            return 1;
        }
    }

    // Runs solving function
    return solve(filePath, ants, evapRate, evaluations, alpha, beta, threads);
}
