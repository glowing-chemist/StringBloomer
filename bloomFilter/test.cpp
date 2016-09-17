#include<iostream>
#include"filter.h"

int main() {
    auto filter = bloomFilter{10, 0.1};
    filter.add("hello world");
    filter.add("Rick");
    std::cout<<filter.check("hello world")<<'\n';
    std::cout<<filter.check("Morty")<<'\n';
    std::cout<<filter.check("Rick")<<'\n';
    std::cout<<filter.check("wubadubdub")<<'\n';
}