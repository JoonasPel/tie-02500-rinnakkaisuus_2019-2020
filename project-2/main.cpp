#include "concur2020lib/concur2020.hh"
#include <iostream>

const int SAMPLES = 1000;

typedef uint64_t Counter;
struct {
    Counter alpha;
    Counter beta;
    Counter gamma;
} counters = { 0, 0, 0 };

void printCounters() {

    std::cout << "COUNTER:" << std::endl;
    std::cout << "alpha: " << counters.alpha << std::endl;
    std::cout << "beta : " << counters.beta << std::endl;
    std::cout << "gamma: " << counters.gamma << std::endl;

}

void countSample( concur2020::DetectorData_t sample ) {

    auto name = concur2020::itemName( sample );
    if( name == "alpha" ) {
        counters.alpha++;
    } else if( name == "beta" ) {
        counters.beta++;
    } else if( name == "gamma" ) {
        counters.gamma++;
    }

}

void processSample() {

    auto sample = concur2020::detect();
    std::cout << "Read: " << concur2020::itemName( sample ) << std::endl;
    countSample( sample );

}

int main() {

    for( auto i = 0; i < SAMPLES; i++ ) {
        processSample();
    }
    printCounters();
    return EXIT_SUCCESS;

}
