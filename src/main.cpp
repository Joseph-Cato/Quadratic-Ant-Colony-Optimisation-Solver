#include "Graph.h"
#include "Ant.h"
#include "../lib/CTPL/ctpl.h"

#include <iostream>
#include <fstream>


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
 * @param filePath String filepath
 * @param ants Number of ants
 * @param evapRate Evaporation rate (multiplicative)
 * @param evaluations Number of evaluations
 * @param alpha Exponent of pheromone in determining node traversal probability.
 * @param beta Exponent of heuristic in determining node traversal probability.
 * @param threads Number of threads generated in thread pool to run antSolve() function calls.
 * @param heuristic Whether to include local heuristic in calculation.
 * @param writeToFile Whether to write results to file or just print to console.
 * @return - Exit status.
 */
int solve(const std::string& filePath, int ants, float evapRate, int evaluations, double alpha, double beta, int threads, bool heuristic, bool writeToFile) {
    //Generating graph
    std::cout << "Generating Graph...                       ";
    Graph graph(filePath, alpha, beta, heuristic);
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

    // If -writeToFile true
    if (writeToFile) {
        std::string line = std::to_string(ants) + "," + std::to_string(heuristic)
                + "," + std::to_string(evapRate) + "," + std::to_string(evaluations)
                + "," + std::to_string(alpha) + "," + std::to_string(beta)
                + "," + std::to_string(threads) + "," + std::to_string(bestSolutionCost)
                + "," + std::to_string(diff.count()) + "\n";

        std::ofstream outputFile;
        outputFile.open("output.txt", std::ios_base::app); // Opens in 'append' mode
        outputFile << line;
        outputFile.close();
    }

    return 0;
}

int argumentError(const std::string& argument, const std::string& extra) {
    std::cout << "\nError - Invalid argument:\n";
    std::cout << argument << "\n";
    std::cout << extra;
    std::cout << "Please use flag '--help' or '-h' for further guidance.\n\n";
    return 1;
}

int main(int argc, char **argv) {

    using namespace std::literals;

    // Default Arguments
    std::string filePath = "../../res/dataSet.txt";
    int ants = 100;
    float evapRate = 0.9;
    int evaluations = 10000;
    double alpha = 2.0;
    double beta = 1.0;
    int threads = 4;
    bool heuristic = true;
    bool writeToFile = false;

    // ---- Reading in arguments from command line

    // If no arguments provided, uses defaults
    if (argc <= 1) {
        std::cout << "\n Running with default parameters, run with argument '-h' or '--help' for more information.\n\n";
        return solve(filePath, ants, evapRate, evaluations, alpha, beta, threads, heuristic, writeToFile);
    }

    std::string arg0 = (std::string) argv[1];
    if (arg0 == "--help"sv || arg0 == "-h"sv) {
        // Prints help to console if -h or --help flag specified
        std::cout << "\nHelp info:\n\n";
        std::cout << "Program can be run with various optional [compiler flag] [value] pairs. If a flag and value pair is not specified default values will be used (shown below).\n";
        std::string helpStringBody = "Possible arguments flags and values are:\n"
                                     "  -h/--help                   : Shows this text.\n"
                                     "  -filePath                   : Specifies file path to data set.\n"
                                     "  -writeToFile [true/false]   : If results should also be writen to file or only printed to console.\n"
                                     "  -ants [int]                 : Number of ants to run on each evaluation.\n"
                                     "  -heuristic [true/false]     : Whether local heuristic will be included in graph traversal calculation.\n"
                                     "  -evapRate [double]          : Rate at which pheromone evaporates.\n"
                                     "  -evaluations [int]          : Number of total evaluations.\n"
                                     "  -alpha [double]             : Exponent of pheromone in determining node traversal probability.\n"
                                     "  -beta [double]              : Exponent of distance in determining node traversal probability.\n"
                                     "  -threads [int]              : Number of threads to be created to run ants.\n\n"
                                     ""
                                     "Example:\n"
                                     "      ./Quadratic_Ant_Colony_Optimisation_Solver -filePath ../../res/dataSet.txt -ants 100 -evaluations 10000 -beta 0.5 -threads 2 -heuristic true\n";

        std::cout << helpStringBody;
        return 0;
    }

    // Checks for flags and sets value
    for (int i = 1; i < argc-1; i += 2) {
        std::string argument = (std::string) argv[i];
        std::string value = (std::string) argv[i+1];
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
            if (std::stoi(value) < 1) {
                std::string info = "Program must have at least one thread enabled.\n";
                return argumentError(argv[i], info);
            }
            threads = std::stoi(value);
        } else if (argument == "-filePath") {
            filePath = value;
        } else if (argument == "-heuristic") {
            if (value == "true") {
                heuristic = true;
            } else if (value == "false") {
                heuristic = false;
            } else {
                // Catches invalid arguments
                std::string info = "Please choose 'true' or 'false' for this flag.\n";
                return argumentError(argv[i], info);
            }
        } else if(argument == "-writeToFile") {
            if (value == "false") {
                writeToFile = false;
            } else if (value != "true") {
                // Catches invalid arguments
                std::string info = "Please choose 'true' or 'false' for this flag.\n";
                return argumentError(argv[i], info);
            }
        } else {
                // Catches invalid arguments
                return argumentError(argv[i], argv[i+1]);
        }
    }

    // Runs solving function
    return solve(filePath, ants, evapRate, evaluations, alpha, beta, threads, heuristic, writeToFile);
}
