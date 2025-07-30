
# The Safe C++ (safecpp) framework

This library or framework is designed to encourage safe programming practices in a C++ based application.
If you look closely at the implementation and the classes that make the tools to write safe code, you will notice
that the actual implementation is not the focus, but rather the design of the classes and the way they interact with each other.
In other words, the framework is designed to enforce safe programming behavior. Other than storing values, they only model
what type of operations are allowed and how they can be used together.

The library offers safer ways of passing data around in a safe matter. For both function/method arguments as well as
return values. It also provides a way to model the state of an object and how it can be used in a safe manner. This doesn't
mean you are not allowed to use less safe constructs, but if you do, you will have to explicitly opt-in to use them by calling
methods with the word 'unsafe' in the name. This makes sure that it is very clear that you are opting out of the safety constructs
of this framework. A 'positive' side effect of this is that it 'unsafe' code instantly becomes a visible code smell, because
because nobody likes to see the word 'unsafe' in their code.

Because of it's straightforward implemention compilers are likely able to highly optimize the code. Furthermore we also
extensively use `constexpr` to allow the compiler to evaluate expressions at compile time, which can lead to further optimizations.

## Why did you write this framework?
I wanted to write a framework that encourages safe programming practices in C++. Although the language is often critized as either unsafe
or too complex, it also offers the flexibility to model the language to your own requirements. Therefore I wanted to show that although
right now C++ might not be the safest language by default, you can have a framework within it that forces you to take a saffer programming approach.
It is not my intent to be preachy about this, but rather that it is possible and to offer some tools to help writing safer code.


## The assumptions behind this framework

- This framework takes very black and white approach. Safe code is always preferred, so you will not find
many compromises in what it allows you to do in a regular C++ manner if you decide to stick with the usage of the framework.
- We understand this is an opinionated framework, but ofcourse you are free to apply multiple approaches to your codebase. Because
the framework is very descriptive in terms of the used language, it also becomes very apparant when you don't use it.
- This opinionated approach also causes the resulting code to feel a bit less like regular C++. But based on the goals of this
framework we view that as a positive thing.
- It is designed to complement the safe features in the C++ standard, like std::unique_ptr, STL containers, etc.
- The 'language of the framework' is very descriptive/verbose on purpose so it forces the developer to make conscious choices which
are then literally spelled out in the code. We do this to make sure that the purpose behind the code becomes very clear. Also if that means
that it becomes very clear if the developer decides to opt-out of the safety features of the framework (for example by using unsafe-named methods).
- In other words it's OK if the developer decides to use less safe constructs for a specific reason like performance for example, but at least
it becomes very clear in the code that this is a conscious choice and not an accident. So it also adds to the self-documenting aspects of the code.
- C++ remains a very liberal language however, so don't expect that this code can force you to write safe code. It can only encourages and helps you to do so.

