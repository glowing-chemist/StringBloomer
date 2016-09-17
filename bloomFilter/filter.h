#include <boost/dynamic_bitset.hpp>
#include<math.h>
#include<vector>

#include "murmur.cpp"

#define ln2 log(2)

using namespace std;

class bloomFilter {
    using fn = unsigned int(*)(const string, const int, const int);

    boost::dynamic_bitset<> setArray;//keep track of hash sets
    vector<fn> hashes;//store pointer to hash functions
    int hashSz;
    unsigned int buckets;
        
    public:
    bloomFilter(int, double);//estimate of number of elemnst in set
    void add(string);//add an element to the set
    bool check(string);//check if param is in set
};


void bloomFilter::add(string element) {
    for (int i = 0;i < hashSz;i++) {
        int hash = (hashes[i])(element, buckets, (i * i));
        if (setArray[hash] != true) {
            setArray[hash] = true;
        }
    }
}

bool bloomFilter::check(string possible) {
    for (int i = 0;i < hashSz;i++) {
        int hash = (hashes[i])(possible, buckets, (i * i));
        if (setArray[hash] == false) {
            return false;
        }
    }
    return true;
}

bloomFilter::bloomFilter(int items, double prob) {//prob is value from 0 - 1
    buckets = -((log(prob) * items) / (ln2 * ln2));//representing accepted false positive rate.
    setArray = boost::dynamic_bitset<>{buckets};
    hashSz = (buckets / items) * ln2;
    hashes = vector<fn>(hashSz, murmur);
}