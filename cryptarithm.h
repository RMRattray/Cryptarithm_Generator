#include "stdint.h"

namespace cryptarithm {
    enum Operat {
            Addition,
            Subtraction,
            Multiplication,
            Division
        };

    void get_permutation_update(char* prev, char* curr, uint8_t* diff);
    void string_to_int_by_permutation(char* str, char* perm, int* val);
    void string_to_int_by_diff(char* str, int* val, uint8_t* diff);
    void int_to_string_by_permutation(char* str, char* perm, int* val);
    int operation(Operat op_code, int* vals);
}
