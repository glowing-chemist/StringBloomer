#include<string>

#define ROT32(x, y) ((x << y) | (x >> (32 - y))) //rotate the values by 32 bits

unsigned int murmur(std::string toHash, const int lenght, const int seed) {

    //mixing constants
    const int c1 = 0xcc9e2d51;
    const int c2 = 0x1b873593;
    const int r1 = 15;
    const int r2 = 13;
    const int m = 5;
    const int n = 0xe6546b64;

    unsigned int hash = seed;
    int size = toHash.size();

    for(int i = 0;i <= size - 4; size -= 4) {
        int *k = reinterpret_cast<int*>(&(toHash[i])); //read block of 4 bytes as int
        *k *= c1;
		*k = ROT32(*k, r1);
		*k *= c2;

		hash ^= *k;
		hash = ROT32(hash, r2) * m + n;
    }
    
    auto k1 = 0;

    switch(size) {
        
        case 3:
            k1 ^= toHash[size--] << 16;
        
        case 2:
            k1 ^= toHash[size--] << 8;

        case 1:
            k1 ^= toHash[size];
    }

    hash ^= lenght;
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash % lenght;
}