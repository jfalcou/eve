Conditional operations {#tutorial_if_else}
======================

@tableofcontents

When you call a function on one or more [SIMD values](../reference/concepts/simd_value.html#simd_value), you expect the computation to be performed on every elements of its parameters. Sometimes, you may want to make the application of a given function dependent on some condition. Let's explore the functionalities **EVE** provides for this kind of task.

## Explicit Selection
Let's say the function we want to write computes the product of two values `a` and `b` if `a` is equal to `b` and their difference otherwise. 

The scalar code is looking like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
auto square_or_diff( float a, float  b) { return a == b ? a * b : a - b; }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<br/>

The SIMD version of this code can't use `if` nor the ternary operator directly. The correct approach is to use the [if_else][doc_if_else] function.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/if_else.hpp>
#include <eve/wide.hpp>
#include <iostream>

using w_t = eve::wide<float, eve::fixed<4>>;

auto square_or_diff( w_t const& a, w_t const& b )
{
  std::cout << a == b << "\n";
  std::cout << a*b    << "\n";
  std::cout << a-b    << "\n";
  return eve::if_else( a == b, a * b, a - b );
}

int main()
{
  w_t v1 = { 1,  2, 3 , 4 };
  w_t v2 = { 1, -2, 10, 4 };

  std::cout << square_or_diff(v1,v2) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The [if_else][doc_if_else] call explicitly requests we pass:
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

!!! WARNING
    Contrary to a `if ... else` statement, [if_else][doc_if_else] will evaluates all its arguments
    before performing its selection even if potential short-cut can be applied later on.

## Conditional Function Syntax
Let's define a `safe_sqrt` function that computes the square root of its argument if it's positive or
returns it unchanged otherwise. One can write:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/if_else.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto safe_sqrt( w_t const& a )
{
  return eve::if_else( a >= 0, eve::sqrt(a), a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << safe_sqrt(v) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This code is perfectly valid and will produce the correct result. However, it has some issues:
 - the code looks like the important part is the test
 - the code can't be optimized in case the current architecture support masked operations (i.e. AVX512)

**EVE** functions supports -- whenever it makes sense -- a conditional call syntax that solves
both issues:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto safe_sqrt( w_t const& a )
{
  return eve::sqrt[a >= 0](a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << safe_sqrt(v) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The code of `safe_sqrt` now plays differently:
 - the `a >= 0` expression is evaluated
 - the `eve::sqrt[a >= 0]` expression builds a new callable object that will perform the conditional
   call to `eve::sqrt`
 - this new callable object is then called over `a`
 - Wherever the condition is true, the `eve::sqrt` function will be applied.
 - Wherever the condition is false, the value of the first argument of the function will be returned.

The fact the conditional syntax builds a new callable object is interesting because it ensures
that any optimization over the conditional computation can be captured and that this new callable
can be passed as-if to algorithms without having to worry about changing the number of arguments
requested.

!!! Tip
    If required, the callable object produced by the conditional syntax can be stored into a
    variable:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
auto safe_sqrt( w_t const& a )
{
  auto const f = eve::sqrt[a >= 0];
  return f(a);
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
Conditional Expressions
====================================================================================================
If passing a simple logical expression is the most common use-case of the conditional syntax, one
may requires more flexibility. To do so, **EVE** provides various objects to express more
interesting conditions.

Mask with alternative
----------------------------------------------------------------------------------------------------
One may want to use the conditional syntax to call a function but instead of returning the first
argument if the condition is false, one may want to return an arbitrary value. Another use case
could be that you want to use a given condition but you happen to just have computed its complement.
You may want to not recompute the proper condition but use the already computed complement.

Both those use cases are handled by the [if_](../reference/types/mask.html#eve::if_) and
[if_not_](../reference/types/mask.html#eve::if_not_) helpers. Those helpers are used to wrap a
logical expression so that either an alternative value can be specified or the logical expression
will be interpreted as its complement.

Let's modify `safe_sqrt` so that, if the argument is not positive, 0 is returned instead.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto safe_sqrt_old( w_t const& a )
{
  return eve::sqrt[ eve::if_(a >= 0) ](a);
}

auto safe_sqrt( w_t const& a )
{
  return eve::sqrt[ eve::if_(a >= 0).else_(0) ](a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << safe_sqrt_old(v) << "\n";
  std::cout << safe_sqrt(v) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The output is then:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(1, -2, 3.16228, -3.5)
(1, 0, 3.16228, 0)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The same thing can be achieved with [if_not_](../reference/types/mask.html#eve::if_not_):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto safe_sqrt_old( w_t const& a )
{
  return eve::sqrt[ eve::if_not_(a < 0) ](a);
}

auto safe_sqrt( w_t const& a )
{
  return eve::sqrt[ eve::if_not_(a < 0).else_(0) ](a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << safe_sqrt_old(v) << "\n";
  std::cout << safe_sqrt(v) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The output is then:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(1, -2, 3.16228, -3.5)
(1, 0, 3.16228, 0)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Context-sensitive mask
----------------------------------------------------------------------------------------------------
Some algorithms require conditional function calls but use logical expression relative to the
element index inside a [SIMD value](../reference/concepts/simd_value.html#simd_value) rather than its value.
One may want for example to not compute an expression on the first and last element of such
[SIMD values](../reference/concepts/simd_value.html#simd_value).

Let's write a function that computes the differences between two vectors in multiple scenarios: not
using the first elements and not using the last elements.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/sub.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto sub_not_first( w_t const& a, w_t const& b )
{
  return eve::sub[ eve::ignore_first(1) ](a,b);
}

auto sub_not_last( w_t const& a, w_t const& b )
{
  return eve::sub[ eve::ignore_last(1) ](a,b);
}

int main()
{
  w_t v = { 10, 20, 30, 40 };
  w_t w = {  4,  3,  2,  1 };

  std::cout << sub_not_first(v,w) << "\n";
  std::cout << sub_not_last(v,w) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The output is then:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(10, 17, 28, 39)
(6, 17, 30, 40)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

!!! Tip
    The [ignore_first](../reference/types/mask.html#eve::ignore_first) and
    [ignore_last](../reference/types/mask.html#eve::ignore_last) conditional takes a number of elements
    as parameter so they can be applied generically on any size of [SIMD value](../reference/concepts/simd_value.html#simd_value)

But what if we want to apply our operation to every element but the first and last one ? Clearly,
calling two operations with two different conditional masks is sub-optimal. **EVE** provides some
more conditional expression to express just that like [keep_between](../reference/types/mask.html#eve::keep_between).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/sub.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto sub_not_first_nor_last( w_t const& a, w_t const& b )
{
  return eve::sub[ eve::keep_between(1,2) ](a,b);
}

int main()
{
  w_t v = { 10, 20, 30, 40 };
  w_t w = {  4,  3,  2,  1 };

  std::cout << sub_not_first_nor_last(v,w) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The output is then:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(10, 17, 28, 40)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this case, we used [keep_between](../reference/types/mask.html#eve::keep_between) with ad-hoc
indexes, which makes the code a bit too size dependent. One can also use the same conditional but
use [ignore_first](../reference/types/mask.html#eve::ignore_first) and [ignore_last](../reference/types/mask.html#eve::ignore_last) as parameters, keeping the relative aspect of the code.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eve/function/sub.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto sub_not_first_nor_last( w_t const& a, w_t const& b )
{
  return eve::sub[ eve::keep_between(eve::ignore_first(1),eve::ignore_last(1)) ](a,b);
}

int main()
{
  w_t v = { 10, 20, 30, 40 };
  w_t w = {  4,  3,  2,  1 };

  std::cout << sub_not_first_nor_last(v,w) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The output is the same obviously:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash
(10, 17, 28, 40)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Conclusion
====================================================================================================

Conditional operations on [SIMD values](../reference/concepts/simd_value.html#simd_value) is a good way to
keep a high level code over some complex computations. **EVE** provides different levels of abstraction
for such operations as well as various helpers to specify how the conditions can be computed based
either on values or indexes.
