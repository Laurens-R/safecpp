//
// Created by laure on 29/07/2025.
//

#include <print>

import safe;

struct Example {
    int id = 0;
    double value = 0.0;
};

/*
 * The var class is a simple wrapper around a default initialized value that can be modified.
 * It is useful for ensuring that a value is always initialized to a valid state.
 */
void var_example() {
    safe::var<int> example_var; // Default initialized to 0
    safe::var<int, 10> example_var2; // Default initialized to 10
    safe::var<int> example_var3(5); // Initialized to 5
    safe::var<int> example_var4 = 10; // Initialized to 10
}

/*
 * Safe ranges are used to ensure that values are within a specific range.
 * This is useful for validating inputs or ensuring that values do not exceed certain limits.
 * These validations happen at runtime.
 */
void ranged_example(const safe::ranged<int, 0, 20> ranged_value) {
    safe::ranged<int, 0, 20> ranged_value2(0);
    
    ranged_value2 = 12; //throws an exception
}

void reference_example(const safe::ref<Example> &example_ref) {

    // Accessing a readonly version of the struct.
    std::print("ID provided: {0}", example_ref->id);
    
    /* This is a safe copy, as it does not modify the original reference.
     * also because the reference is copied, we don't have to care about
     * the lifetime of the original data.
     */
    Example a = example_ref;

    /* This would not compile. If you were able to copy the reference or seperately
     * store it across the lifetime of the original data, you would create unsafe
     * references/UB.
     
    safe::ref<Example> bad_example_ref = example_ref;
    Example & bad_example_ref2 = example_ref;
    
    */
}

int main() {
    safe::owner<Example> example(Example{1, 2.0});

    //we can make a copy
    Example e = example;
    
    reference_example(example);

    ranged_example(22);
    
    return 0;
}