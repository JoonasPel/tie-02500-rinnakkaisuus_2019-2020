#include "concur2020lib/concur2020.hh"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

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

void processSample(unsigned int* processedSamples, std::mutex* mutex) {

    mutex->lock();

    // Tarkistaa, onko valmista. Ei säiturvallinen
    if (*processedSamples >= SAMPLES){
        mutex->unlock();
        return;
    }

    auto sample = concur2020::detect(); // Dokumentaation mukaan ei säiturvallinen
    (*processedSamples)++;    // Ei säiturvallinen
    std::cout << "Read: " << concur2020::itemName( sample ) << std::endl;
    countSample( sample );    //Ei säiturvallinen
    mutex->unlock();

    processSample(processedSamples, mutex);
}

int main() {
    unsigned short int numOfThreads = 8;
    unsigned int processedSamples = 0;

    std::mutex mtx;
    std::vector<std::thread> threads;
    threads.reserve(numOfThreads);

    for( auto i = 0; i < numOfThreads; i++ ) {
        threads.emplace_back(std::thread(processSample, &processedSamples, &mtx));
    }

    for(int i = 0; i < numOfThreads; i++) {
        threads.at(i).join();   // Odotetaan kaikki säikeet tähän
    }

    printCounters();
    return EXIT_SUCCESS;

}
