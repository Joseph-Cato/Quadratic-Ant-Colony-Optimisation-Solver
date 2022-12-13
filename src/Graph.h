
#ifndef QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H
#define QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H

#include <vector>
#include <mutex>

class Graph {
private:

    std::vector<std::vector<float>> pheromone;
    std::vector<std::vector<float>> partialPheromone;
    std::vector<float> initialPheromone;
    std::vector<float> initialPartialPheromone;
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<int>> flows;
    std::vector<std::vector<float>> heuristicMatrix;
    double ALPHA;
    double BETA;
    int numberOfLocations; // == numberOfFacilities


    /** Converts a space separated string list of integer values to a vector.
     *
     * @param string String of int values seperated by spaces
     * @return [std::vector<int> list of int values described by string
     */
    static std::vector<int> lineToVector(const std::string& string);

public:

    static std::mutex pheromoneMutex; //  Mutex dedicated to alterations of pheromone matrix

    /**
     * Default constructor calls overloaded constructor with default filePath, ALPHA_VALUE, and BETA_VALUE.
     */
    Graph();

    /**
     *
     * @param filePath
     * @param ALPHA_VALUE - Exponent of pheromone in determining node traversal probability.
     * @param BETA_VALUE - Exponent of heuristic in determining node traversal probability.
     */
    Graph(const std::string& filePath, double ALPHA_VALUE, double BETA_VALUE);

    /**
     *
     * @return [DOUBLE] ALPHA Value
     */
    [[nodiscard]] double getALPHA() const;

    /**
     *
     * @return [double] BETA value
     */
    [[nodiscard]] double getBETA() const;

    /**
     *
     * @return [std::vector<float>] Initial pheromone vector
     */
    [[nodiscard]] const std::vector<float> & getInitialPheromone();

    /** Gets distance from node startLocation to node endLocation
     *
     * @param startLocation Start node
     * @param endLocation End node
     * @return [int] distance value
     */
    [[nodiscard]] int & getDistance(int startLocation, int endLocation);

    /**
     *
     * @param startFacility Start node
     * @param endFacility End node
     * @return [const int] flow value
     */
    [[nodiscard]] const int & getFlow(int startFacility, int endFacility);

    /**
     *
     * @param fromNode
     * @param destinationNode
     * @return [float] pheromone value
     */
    [[nodiscard]] float getPheromone(int fromNode, int destinationNode);

    /**
     *
     * @return [const int] number of locations
     */
    [[nodiscard]] const int & getNumberOfLocations() const;

    /**
     *
     * @return [const std::vector<std::vector<float>>] heuristic matrix
     */
    [[nodiscard]] const std::vector<std::vector<float>> & getHeuristicMatrix();

    /** Increments partial pheromone matrix by inverseCost for all node links described by tabuList
     *
     * @param inverseCost increment value
     * @param tabuList Node traversal descriptor
     */
    void addPartialPheromone(float inverseCost, std::vector<int> tabuList);

    /** Increments partial initial pheromone vector by inverseCost at the location fo the first node travelled to
     *
     * @param inverseCost increment value
     * @param firstNode First node traveled to by ant
     */
    void addInitialPartialPheromone(float inverseCost, int firstNode);

    /** Multiplies each pheromone value by (1 - evaporation rate)
     *
     * @param evapRate evaporation rate
     */
    void evaporatePheromone(float evapRate);

    /** Adds partial pheromone to pheromone value-wise
     *
     */
    void addPheromone();

    /** Adds initial partial pheromone to initial pheromone
     *
     */
    void addInitialPheromone();

};


#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H
