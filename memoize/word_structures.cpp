#include "stdint.h"
#include "stdio.h"
#include "word_structures.h"

namespace crypt
{
    class word_structures
    {
    private:
    public:
        uint8_t word[MAX_WORD_LEN / 2];
        word_structures(/* args */);
        ~word_structures();
        void operator++();
        uint8_t operator[](int index);
        void inc_at(int index);
        void max_by(int index);
    };
    
    word_structures::word_structures(/* args */)
    {
        uint8_t* digit = word;
        while (digit < word + MAX_WORD_LEN / 2) {
            *digit = 0; ++digit;
        }
    }
    
    word_structures::~word_structures()
    {
    }

    void word_structures::operator++ () {
        
    }

    uint8_t word_structures::operator[] (int index) {
        // if (index > MAX_WORD_LEN) return 0; // Memory unsafe!  I gotta be responsible
        uint8_t* digit = word + (index >> 1);
        return (index & 1) ? (*digit >> 4) : (*digit & 0xF);
    }

    void word_structures::inc_at(int index) {
        uint8_t* digit = word + (index >> 1);
        if (index & 1) *digit += (1 << 4);
        else *digit += 1;
    }

    void word_structures::max_by(int index) { // TODO!
        uint8_t* digit = word + (index >> 1);
        uint8_t max = (index & 1) ? 1 : 0;
    }

    
} // namespace crypt

int main() {
    crypt::word_structures first;
    first.inc_at(0);
    first.inc_at(3);
    first.inc_at(5);
    printf("Value: %x\n", *(uint32_t *)first.word);
    return 0;
}
