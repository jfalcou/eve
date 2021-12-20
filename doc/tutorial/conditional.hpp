#error This file is for documentation only - DO NOT INCLUDE
/**

@page conditional Conditional operations

@tableofcontents

When you call a function on one or more [SIMD values](../reference/concepts/simd_value.html#simd_value),
you expect the computation to be performed on every elements of its parameters. Sometimes, you may
want to make the application of a given function dependent on some condition.

Let's explore the functionalities **EVE** provides for achieving those results.

## Explicit Selection
Let's say the function we want to write computes the product of two values `a` and `b` if `a`
is equal to `b` and their difference otherwise.

The scalar code is looking like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
auto square_or_diff( float a, float  b)
{
  return a == b ? a * b : a - b;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The SIMD version of this code can't use `if` nor the ternary operator directly. The correct approach
is to use the eve::if_else function.

@snippet tutorial/square_or_diff.cpp snippet

The eve::if_else call explicitly requests we pass:
 - the condition, i.e the comparison between `a` and `b`
 - the value to use whenever an element of said condition evaluates to `true`, here the product of `a` and `b`
 - the value to use whenever an element of said condition evaluates to `false`, here the difference of `a` and `b`

The expected result of this program is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(true, false, false, true)
(1, -4, 30, 16)
(0, 4, -7, 0)
(1, 4, -7, 16)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

@warning  Contrary to a `if ... else` statement, eve::if_else will evaluates all its arguments
          before performing its selection even if potential short-cut can be applied later on.

## Conditional Function Syntax
Let's define a `safe_sqrt` function that computes the square root of its argument if it's positive
or returns it unchanged otherwise. One can write:

@snippet tutorial/safe_sqrt.cpp snippet

This code is perfectly valid and will produce the correct result. However, it has some issues:
 - the code looks like the important part is the test
 - the code can't be optimized in case the current architecture support masked operations (i.e. AVX512)

To go beyond those limitations, **EVE** functions supports -- whenever it makes sense -- a
conditional call syntax:

@snippet tutorial/safe_sqrt_op.cpp snippet

The code of `safe_sqrt` now works differently:
 - the `a >= 0` expression is evaluated
 - the eve::sqrt[a >= 0] expression builds a new callable object that will perform the conditional
   call to eve::sqrt
 - this new callable object is then called over `a`
 - Wherever the condition is true, the eve::sqrt function will be applied.
 - Wherever the condition is false, the value of the first argument of the function will be returned.

The fact the conditional syntax builds a new callable object is interesting because it ensures
that any optimization over the conditional computation can be captured and that this new callable
can be passed as-if to algorithms without having to worry about changing the number of arguments
requested.

If required, the callable object produced by the conditional syntax can be stored into a variable:

@snippet tutorial/safe_sqrt_op.cpp snippet-alt

## Conditional Expressions
If passing a simple logical expression is the most common use-case of the conditional syntax, one
may requires more flexibility. To do so, **EVE** provides various objects to express more
interesting conditions.

### Mask with alternative
One may want to use the conditional syntax to call a function but instead of returning the first
argument if the condition is false, one may want to return an arbitrary value. This use case is
handled by the eve::if_ helper by wrapping logical expression so that an alternative value can be specified.

Let's modify `safe_sqrt` so that, if the argument is not positive, 0 is returned instead.

@snippet tutorial/safe_sqrt_else.cpp snippet

The output is then:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(1, -2, 3.16228, -3.5)
(1, 0, 3.16228, 0)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Context-sensitive mask
Some algorithms require conditional function calls but use logical expression relative to the
element index inside a eve::simd_value rather than its value. One may want for example to not
compute an expression on the first and last element of such eve::simd_value.

Let's write a function that computes the differences between two vectors in multiple scenarios: not
using the first elements and not using the last elements.

@snippet tutorial/safe_sqrt_ignore.cpp snippet

The output is then:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(10, 17, 28, 39)
(6, 17, 28, 40)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here, the eve::ignore_first and eve::ignore_last conditionals take a number of elements
as parameter that describe which zone of the eve::simd_value won't be affected.

But what if we want to apply our operation to every element but the first and last one ? Clearly,
calling two operations with two different conditional masks is sub-optimal.

**EVE** provides some more conditional expression to express this need.

The first is to use the eve::keep_between helper:

@snippet tutorial/safe_sqrt_between.cpp snippet

The output is then:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(10, 17, 28, 40)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

eve::keep_between uses ad-hoc indexes, which makes the code a bit too size dependent. One can
also use the same conditional but use a similar interface to eve::ignore_first.

@snippet tutorial/safe_sqrt_ignore_both.cpp snippet

The output is the same obviously:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(10, 17, 28, 40)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Conclusion

Conditional operations on [SIMD values](../reference/concepts/simd_value.html#simd_value) is a good way to
keep a high level code over some complex computations. **EVE** provides different levels of abstraction
for such operations as well as various helpers to specify how the conditions can be computed based
either on values or indexes.

**/