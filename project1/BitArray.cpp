#include "BitArray.hpp"

BitArray::BitArray() {
    // TODO
    //set arrSizr to 8
    arrSize = 8;
    valid = true;
    //Declare an 8 bit array with all bits set to 0
    arr = new int[arrSize];
    for (intmax_t i =0; i < arrSize; i++){
        arr[i] = 0;
    }
}

BitArray::BitArray(intmax_t size) {
    // TODO
    if (size <= 0){
        arrSize = 0;
        valid = false;
        arr = nullptr;
        return;
    }
    arrSize = size;
    arr = new int[size];
    for (intmax_t i = 0; i < arrSize; i++){
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
    std::string strArray = "";
    for (intmax_t i = arrSize - 1; i >= 0; i--){
        strArray += (arr[i] ? '1' : '0');
        if (i == 0) break;
    }
    return strArray;
}


