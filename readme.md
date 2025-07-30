
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

Right now this framework is still in an early stage, so it's also a test-bed for ideas, concepts and trying stuff out. And that is
fine if you view it as a collection of tools that you can use or take as inspiration for your own codebase. This is not the type of 
framework that will try to preach to you on what is the "right" way.

Because of it's straightforward implemention compilers are likely able to highly optimize the code. Furthermore we also
extensively use `constexpr` to allow the compiler to evaluate expressions at compile time, which can lead to further optimizations.

Currently the framework is setup as a module enabled C++20/23 library. I will eventually also provide a regular header implementation, but you can
already extract the hpp files in the `src/lib` folder  and copy to them to your own project (make sure to include the MIT license and accreditation!) and use this
framework with a compiler which doesn't support modules yet.


## Disclaimer

In the end C++ will always allow you to bypass this framework and write unsafe code. So using this framework
is not a guarantee that your code is safe. It is just a tool to help you write safer code and to make it more obvious
when you are not using the framework as intended. It is also not a replacement for good programming practices, but rather a tool which
you can add to your toolbox to help you write safer code. In no way does this framework guarantee that your code is free of bugs or security vulnerabilities. 

As such a take no responsibility for any issues that may arise from using this framework. It is provided "as is" without any warranties or guarantees of any kind, either express or implied. Use it at your own risk.

## Why did you write this framework?
I wanted to write a framework that encourages safe programming practices in C++. Although the language is often critized as either unsafe
or too complex, it also offers the flexibility to model the language to your own requirements. Therefore, I wanted to show that although
right now C++ might not be the safest language by default, you can have a framework within it that encourages you to take a saffer programming approach
and that - where you use it - it can help prevent situations where you might otherwise shoot yourself in the foot.

## The goals of the framework
- Be verbose and descriptive.
- Help the developer to avoid unsafe coding practices.
- Make it explicit when the developer opts out of the safety features of the framework.
- If there are multiple ways to do something, the framework will encourage the developer to make a consious choice which
is traceable in the code.
- The framework should be opinionated, but not dogmatic. It should not force you to use it, but rather encourage you to do so.
- The framework will take away flexibility in some areas, but only to make it easier to write safe code.
- It should complement the safe features in the C++ standard, like `std::unique_ptr`, STL containers, etc.
- It should be (relatively) easy to read, use and understand.

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

## The basics

The framework consists out of a set of classes that help you in writing safer code. It is trying to avoid security related bugs due to:

- Accessing references, pointers etc byond their lifetime.
- Returning references or pointers to local variables.
- Passing invalid values to functions or methods that fall outside the expected range, which can result into accessing
data beyond the end of an array or buffer for example.
- Not using smart pointers.

Below this you will find a list of the main classes and what their purpose is.

```C++
safe::owner<T>
```

Description: An instance of this class holds and owns an value of type `T`. The owner class will allow the developer to modify the value, copy it, etc.
It can hand out safe references to the value to other methods. The owner instance itself can also be copied, in effect also creating multiple
copies of the value that it holds.

```C++
safe::ref<T>
```

Description: An instance of this class holds a reference to a value of type `T`. It will allow read-only operations on the reference. The ref instance is not
allowed to be copied. The idea behind it is that that you want to pass these references around for allow for reading data, but you want to prevent that other methods
decide to store the reference somewhere allow situations where the reference might become invalid after the actual value expires it's lifetime. The value which is referenced can
also be cloned (effectively creating a copy of the value) if the type `T` supports it.

```C++
safe::mut<T>
```

Description: An instance of this class holds a mutable reference to a value of type `T`. It will allow the developer to change the value to which the reference points. The mut instance is not
allowed to be copied. The idea behind it is that that you want to pass these mutable references around to interact with data, but you want to prevent that other methods
decide to store the reference somewhere allow situations where the reference might become invalid after the actual value expires it's lifetime. The value which is referenced can
also be cloned (effectively creating a copy of the value) if the type `T` supports it.


```C++
safe::ptr<T>
```
This is effectively a wrapper around around a reference to a unique pointer. It allows you to temporarily share the pointer with other methods so they can interact with the object
to which the underlying unique pointer points to, but it prevents that a developer can mess with methods that will modify the unique pointer such as `reset` or `release`, etc.
It does offer methods to check if the pointer is still valid or to clone the object to which the underlying pointer points to.

```C++
safe::return_of<TRet>
```
This class enforces certain behavior when returning values from methods. It toforbids return references and pointers, unless they are in the form of
`safe::ref<T>` or `safe::mut<T>`. Or the developer can decide to actually return a value of type T, which will be copied. When returning a return_of object it will implicitly
convert to a safe::owner<T> in any case. It will also implictly convert to a `safe::ref<T>` or `safe::mut<T>` if the `TRet` argument is a `safe::ref<T>` or `safe::mut<T>`.
Converting to a regular type T is not implicitly allowed, because we want the developer to make a concious choice about that. In that case the `as_clone` method should be called
on the `safe::return_of<TRet>` instance.

```C++
safe::var<T, TDefault = T{}>
```
A very simple wrapper around a value of type 'T', which basically ensures that the value is always initialized. Either to the default value of the type itself or to a provided default value
which can be passed as a template argument. This type is primarily usefull when used as a function/member argument. For members it is advised to use an safe::owner<T>, because that will also
apply a default value if not specified.

```C++
safe::ranged<typename T, T TFrom, T TTo, T TDefault = T{}>
```
Can be used as an argument to a function to enforce that the numerical value that is passed always fits in the range between TFrom and TTo. It only accepts numerical types like char, shor, int, float, double etc.
This variable is also default initialized to TDefault. It is also one of the types which is allowed to implicitly cast to its underlying type, because we are talking about numerical primitives.