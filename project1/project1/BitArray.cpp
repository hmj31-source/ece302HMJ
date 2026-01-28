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
    valid = true;
    arr = new int[size];
    for (intmax_t i = 0; i < arrSize; i++){
        arr[i] = 0;
    }
}

BitArray::BitArray(const std::string & value) {
    // TODO
    if (value.empty()){
        valid = false;
        arrSize =0;
        arr = nullptr;
        return;
    }
    arrSize = value.size();
    arr = new int[arrSize];
    valid = true;

    for (intmax_t i = 0; i < arrSize; i++){
        if (value[i] == '0') arr[arrSize-1 - i] = 0;
        else if (value[i] == '1') arr[arrSize -1 -i] = 1;
        else{
            valid = false;
            delete[] arr;
            arr = nullptr;
            arrSize = 0;
            return;
        }
    }
}

BitArray::~BitArray() {
    // TODO
    delete[] arr;
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
    if (index >= arrSize || index <0 ){
        valid = false;
        return;
    }
    arr[index] = 1;
}

//reset method
void BitArray::reset(intmax_t index) {
    if (index >= arrSize || index <0 ){
        valid = false;
        return;
    }
    arr[index] = 0;
}

//toggle method
void BitArray::toggle(intmax_t index) {
    if (index >= arrSize || index <0 ){
        valid = false;
        return;
    }
    if (arr[index] == 0) arr[index] = 1;
    else if (arr[index] == 1) arr[index] = 0;
}

//test method
bool BitArray::test(intmax_t index) {
    if (index >= arrSize || index <0 ){
        valid = false;
        return false;
    }
    if (arr[index] ==1) return true;
    else return false;
}

//asString method
std::string BitArray::asString() const {
    std::string s = "";
    int max = arrSize - 1;
    for (intmax_t i = arrSize - 1; i >= 0; --i){
        s += (arr[i] ? '1' : '0');
        if (i ==0) break;
    }
    return s;
}


