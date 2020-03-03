// TIE-0250x Concurrency, spring 2020. Mandatory project 2. Project library.
//                https://www.cs.tut.fi/~rinn/projects
//                DO NOT make any changes to this file!

#include "concur2020.hh"
#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <thread>

namespace concur2020 {

namespace {

    const unsigned int ITEMS = 4;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,ITEMS-1);

    std::array< std::pair< std::string, concur2020::DetectorData_t >, ITEMS > blobs = {
        std::make_pair( "alpha"   , 0xfa94f710d61de002 ),
        std::make_pair( "beta"    , 0xa2e87e2870033f42 ),
        std::make_pair( "gamma"   , 0x12984b9c48ecdb4b ),
        std::make_pair( "unknown" , 0x9de355f3575a5322 )
    };

    std::map< DetectorData_t, std::string > mapping;
    int initMapping() {
        for( auto item : blobs ) {
            mapping[item.second] = item.first;
        }
        return 42;
    }
    int __attribute__((unused)) justtriggerinit = initMapping();

    void my_assert( bool cond, const char* WHAT, const char* FILE, int LINE ) {
        if(!cond) {
            std::cerr << FILE << ":" << LINE << ":"
                      << WHAT << ":" << "Assertion failed" << std::endl;
            exit(1);
        }
    }
    #define MY_ASSERT( cond ) my_assert(cond, #cond, __FILE__, __LINE__)

    std::atomic<int> DetectorCounter(0);

}

DetectorData_t detect() {

    DetectorCounter++;
    std::this_thread::sleep_for( std::chrono::microseconds( dis(gen)*100 ) );
    MY_ASSERT( DetectorCounter.load() == 1 );

    auto idx = dis(gen);
    auto ret = blobs.at(idx).second;

    DetectorCounter--;
    std::this_thread::sleep_for( std::chrono::microseconds( dis(gen)*20 ) );
    MY_ASSERT( DetectorCounter.load() == 0 );

    return ret;

}

std::string itemName( DetectorData_t item ) {

    return mapping.at( item );

}

}
