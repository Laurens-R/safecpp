/*
    MIT License

    Copyright (c) 2025 Laurens Ruijtenberg

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


#include <print>

import safe;

struct Example {
    safe::owner<int> id; //no initialization needed because safe::owner initializes to a default value
    double regular_value; //a regular value to also demonstrate how those interact with the framework elements

    Example() = default;

    Example(const int id, const safe::ranged<double, 0.0, 100.0>& value) : id(id), regular_value(value) {}
};

void printExample(const safe::ref<Example>& example);

int main() {

    //initializes with the default value of the type, which is false for bool.
    safe::owner<bool> boolExample;

    //initialization with a value.
    safe::owner<int> numberExample(10);

    //assigning a value after initialization
    numberExample = 20;

    //the safe::owner will also forward constructor arguments to Example
    safe::owner<Example> example(20, 25.7);

    //passing the example value to a function that takes a safe::ref<Example>
    printExample(example);
    
    return 0;
}

void printExample(const safe::ref<Example>& example) {

    /* if I try to modify the example data it will fail to compile if you uncomment this.
     * this is by design because a ref is meant to be a read-only reference.
    example->regular_value = 10;
    */

    safe::ref<int> id = example->id;

    //notice in the statement below in the difference between id and regular value. I have to tell the
    //id (because it is a safe::owner) to convert it to a value, while the regular_value will just pass.
    //now this is a bit of a silly example but I hope it explains the difference in how the safe::owner
    //forces you to be a bit more descriptive on what you are doing and it forces you to make a decision.
    //if you want to use the id as a value, you have to call to_value() on it.
    std::print("Example ID:{0}, Value:{1} \n", example->id.value() , example->regular_value);;

    //now I'm going to pass the id as an unsafe reference. This works (because the print function
    //accepts it) but it does indicate we perhaps should look for a better alternative (such as .value()). It becomes
    //a visual code smell.
    std::print("Unsafe example ID:{0}, Value:{1} \n", example->id.unsafe_reference() , example->regular_value);;
}