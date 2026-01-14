#include "BitArray.hpp"

BitArray::BitArray() {
    // TODO
    //set arrSizr to 8
    this->arrSize = 8;
    this->valid = true;
    //Declare an 8 bit array with all bits set to 0
    int arr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
}

BitArray::BitArray(intmax_t size) {
    // TODO
    int arr[size];
    for (int i; i < size; i++){
        arr[i] = 0;
    }
}

BitArray::BitArray(const std::string & value) {
    // TODO
}

BitArray::~BitArray() {
    // TODO
}

// TODO: other methods
// size method
intmax_t BitArray::size() const{
    return this->arrSize;
}

//good mehtod
bool BitArray::good() const {
    return this->valid;
}

//set method
void BitArray::set(intmax_t index){

}

//reset method
void BitArray::reset(intmax_t index) {

}

//toggle method
void BitArray::toggle(intmax_t index) {

}

//test method
bool BitArray::test(intmax_t index) {
    return false;
}

//asString method
std::string BitArray::asString() const {
    return "";
}


