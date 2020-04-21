#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <array>
#include <vector>
#include "timing.h"
#include "timing.c"

#include "helpers.cpp"

int main(int argc, char** argv){
    // argc is count of arguments provided
    // argv is array of arguments
    int ntrees, mtry;
    timing_t tstart, tend;

    printf("Starting...\n");
    // record starting time in tstart
    get_time(&tstart);

    // get parameters if specified, otherwise use defaults
    ntrees = (argc > 1) ? atoi(argv[1]) : 5;
    mtry = (argc > 2) ? atoi(argv[2]) : 2;
    printf("ntrees = %d, mtry = %d\n", ntrees, mtry);

    // contrived dataset for testing: (input1, input2, class)
    // https://www.geeksforgeeks.org/multidimensional-arrays-c-cpp/
    //double dataset[10][3] = {
    std::array<std::array<double, 3>, 10> dataset = {{
        {2.7810836,2.550537003,0}, 
        {1.465489372,2.362125076,0}, 
        {3.396561688,4.400293529,0}, 
        {1.38807019,1.850220317,0}, 
        {3.06407232,3.005305973,0}, 
        {7.627531214,2.759262235,1}, 
        {5.332441248,2.088626775,1}, 
        {6.922596716,1.77106367,1}, 
        {8.675418651,-0.242068655,1}, 
        {7.673756466,3.508563011,1}
    }};

    printf("Rows: %lu\n", dataset.size());
    printf("Cols: %lu\n", dataset[0].size());

    // should print 4.400293529
    printf("Row 3, Col 2: %f\n", dataset[2][1]);
    //printf("Row 0: %f\n", **dataset);

    /* ----- BEGIN ----- */

    // Test that accuracy scoring from helpers.cpp works
    std::vector<int> tar = {0, 1, 1, 0, 0};
    // should print 5/5 == 1.0:
    std::vector<int> pred1 = {0, 1, 1, 0, 0};
    printf("Accuracy pred1: %f\n", accuracy_score(tar, pred1));
    // should print 3/5 = =0.6:
    std::vector<int> pred2 = {0, 0, 1, 1, 0};
    printf("Accuracy pred2: %f\n", accuracy_score(tar, pred2));

    /* ----- WRAP UP ----- */
    // record end time
    get_time(&tend);
    // print results
    printf("Done in %Lg seconds\n", timespec_diff(tstart, tend));
}

