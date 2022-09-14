# How to TDD?

## Theory

TDD is short for 'Test-Driven Development'.
TDD is a methodology allows to add features to a program in a structured way.
The goal of TDD is to ensure correctness and a good/testable software
architecture.

## The Three Steps

To do TDD, one follows these three steps for many cycles:

 * Red phase: write a test that breaks the code
 * Green phase: make the test pass with minimal effort
 * Blue phase: clean-up, then push code

It should take minutes, sometimes hours, but not days to do a full cycle.

## Example

This example will take more cycles.
The first cycles may seem dumb/stupid, 
but that is a consequence of following the methodology well,
as the methodology is always the same.

In this example, we are going to write a function to determine if a number is prime.
The function is called `is_prime`.

### Red phase 1: write a test that breaks the code

Somewhere in main, we are going to write our first test:

```c++
assert(!is_prime(0));
```

This test will fail, as there is no function called `is_prime` yet. 

Confirm that the code indeed breaks!

If the code breaks, it is time to go to the next step.

Notes:

 * You can start with any number, e.g. -1, 0, 1, 2 or more. The order does not matter.
   I pick zero, as I feel this is a reasonable starting point.
 * Do `#include <cassert>` at the top of the file
 * You may write `assert(is_prime(0) == false);` if you prefer: it does not matter
 * You may write `assert(is_prime(0) != true);` if you prefer: it does not matter

### Green phase 1: make the test pass with minimal effort

Somewhere in the code, add:

```c++
bool is_prime(const int x)
{
  return false;
}
```

This should make the test pass.

Confirm that the test now indeed passes!

If the test now passes, it is time to go to the next step.

Notes:

 * Probably you need to put the function declaration in a header file,
   which is (only) `bool is_prime(const int x);`
 * If your compiler is strict, it will state that `x` is never used.
   Either remove `x` from the definition, or put it into comments, such as below:

```c++
bool is_prime(const int /* x */)
{
  return false;
}
```

### Blue phase 1: clean-up, then push code

There is is no cleanup needed here (e.g. removing `std::cout` statements),
so just push the code.

We now did our first iteration.

### Red phase 2: write a test that breaks the code

As our function always returns `false`, we need to write
a test to detect a value that is prime:

```c++
assert(is_prime(2));
```

Notes:

 * You can start with any prime, but 2 feels the most natural to me
 * You may write `assert(is_prime(2) == true);` if you prefer: it does not matter

### Green phase 2: make the test pass with minimal effort

```c++
bool is_prime(const int x)
{
  return x < 2;
}
```

This solution makes all current tests pass, as well as the new one!

### Blue phase 2: clean-up, then push code

There is is no cleanup needed here (e.g. removing `std::cout` statements),
so just push the code.

We now did our second iteration.

### Red phase 3: write a test that breaks the code

Now things get more interesting:

```c++
assert(!is_prime(3));
```

### Green phase 3: make the test pass with minimal effort

Now we need to write the actual code.
Here is such a piece:

```c++
bool is_prime(const int x)
{
  if (x < 2) return false;
  if (x == 2) return true;

  const int max{x - 1};
  for (int i{2}; i!=max; ++i)
  {
    if (x % i == 0) return false;
  }
  return true;
}
```

Notes:

 * It does not care if your code is beautiful or optimized:
   as long as all the tests pass, we are -by definition- happy.
 * `is_prime` can be `noexcept` if you know why. 
   When in doubt, do not add `noexcept`. 
   If you do not add `noexcept`, this is fine.
 * The example code can definitely be more optimized. 
   To optimize code, write a test comparing the run-time speed of
   two versions of the same function

### Blue phase 3: clean-up, then push code

There is is no cleanup needed here (e.g. removing `std::cout` statements),
so just push the code.

We now did our third iteration.

### Conclusions

You can try and break the code. 
If you cannot find a test that breaks the code, you are done.

With just three tests, we wrote `is_prime`.

TDD puts an upper limit on the amount of tests needed. 
You can sleep well now... until someone send a bug report :-)
