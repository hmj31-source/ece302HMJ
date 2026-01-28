#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <string>

/** Abstract interface which represents a set of bits.
 * @file Bitset.hpp
 * @Author Harrison Jordan
 */
class Bitset{
  public:

    virtual ~Bitset(){};
    
    // TODO COMMENT
    /** Gets number of bits in the set
     * @pre none
     * @post The bitset remains the same
     * @return The number of bits
    */
    virtual intmax_t size() const = 0;
    
    // TODO COMMENT
    /**Indicates if the bitset is a valid state
     * @pre none
     * @post Bitset remains the same
     * @return Boolean that represets true for a valid set and false for invalid set
     */
    virtual bool good() const = 0;
    
    // TODO COMMENT
    /** Set the given index to 1
     * @param index   The position of the bit to be set to one
     * @pre index is in a valid range, [0, size()]
     * @post If valid the bit at the index is set to 1
     */
    virtual void set(intmax_t index) = 0;
    
    // TODO COMMENT
    /** Resets the index bit to 0
     * @param index   The position of the bit to be set to 0
     * @pre index must be in range [0, size()]
     * @post If valid the bit at index is set to 0
     */
    virtual void reset(intmax_t index) = 0;
    
    // TODO COMMENT
    /** Toggels the bit at index to the opposite state it is currently in
     * @param index The positon of the bit to toggle
     * @pre Index must be in range [0, size()]
     * @post If valid the bit at the index will be toggled
     */
    virtual void toggle(intmax_t index) = 0;

    // TODO COMMENT
    /** Tests if the bit at a given index is set or 1
     * @param index The positon you want to test the bit at
     * @pre index within the range of [0, size()]
     * @post The bitset is unchanged
     * @return True if the bit is 1, False if the bit is 0
     */
    virtual bool test(intmax_t index) = 0;

    // TODO COMMENT
    /** Retruns a string representation of the bitset
     * @pre none
     * @post The bitset is unchanged
     * @return A string of '0' and '1' characters that represent the bits, the most significant bit is first
     */
    virtual std::string asString() const = 0;

};

#endif
