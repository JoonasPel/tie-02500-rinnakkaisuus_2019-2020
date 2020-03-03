// TIE-0250x Concurrency, spring 2020. Mandatory project 2. Project library.
//                https://www.cs.tut.fi/~rinn/projects
//                DO NOT make any changes to this file!

#ifndef CONCUR2020API
#define CONCUR2020API

#include <string>

namespace concur2020 {

    // Data type for binary data (i.e. binary identifier for radiation).
    typedef uint_least64_t DetectorData_t;

    // Returns one sample from the detector.
    // THREADS: NOT threadsafe.
    DetectorData_t detect();

    // Converts one sample to string format.
    // Returns one of the following strings: "alpha","beta","gamma","unknown"
    // THREADS: Threadsafe.
    // PRE: Parameter "item" must be returned by the detect() -function.
    std::string itemName( DetectorData_t item );

}

#endif
