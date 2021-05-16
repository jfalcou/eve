_NOTE_: This is a temporary documentation that is just very quick to write a modify. Will migrate later.

algo is for stl/ranges style algorithms using simd.

Main eve supports it's callables for scalars. We don't do that for algorithms. The code is still portable since the cpu emulation is enabled.

# Algorithms

* any_of

# Helpers

### iterator (concept)

*TODO*

Main models:
* `algined_ptr` with attached cardinal
* pointer with attached cardinal
* zip of `aligned_ptr` and pointer

The basic concept for writing algorithms against.

The minimum requirements are:
* `eve::load` or `eve::store` are defined (returned types are not restricted).
* `I::cardinal` is defined and is eve::fixed.
* `I += n`  // `n` is `std::ptrdiff_t` is divisible by `I::cardinal{}()`
* `I - I` - returns the distance between two iterators (in elements).
* I is totally ordered
* `I.unaligned()` - returns an `unaligned_iterator` pointing to the same place.
* `I.unaligned()` and `I` are comparible

### aligned_iterator(concept)

*TODO*

The main model is `aligned_ptr_iterator`

The concept around a general purpose `aligned_ptr`. We can only step in `I::cardinal{}()` divisible steps. We guarantee that all loads stores will happen from an aligned address.

### unaligned_iterator(concept)

*TODO*

The main model is `unaligned_ptr_iterator`

iterator that can represent any position in the underlying range.

### iteration pattern (concept)

A reusable component to do `while(f != l) ++f;`.
Given traits, f, l, delegate calls the delegate for each piece with (f, ignore).
The specific api of the delegate varies by iteration pattern.

Main one is `for_each_iteration`.
However for some algorithms, like `reverse` and maybe `partition` it's not a good.

### traits

* `traits`
* `unroll`
* `divisible_by_cardinal`

traits is a way to customise the behaviour of the algorithm.
Different algorithms support different customizations.

### concepts

* `unaligned_t` -> a convinience to get the unaligned type.
* `same_unaligned_iterator<T, U>` -> checks if two iterators have the same unaligned types.

### iterator helpers

* `operations_with_distance` -> provides boilerplate distance operations.
* `forward_to_unaligned` -> provides boilerplate operations using `unaligned()`

### array_utils

* `array_map`
* `array_reduce`

Functional style utilites to perform common operations on arrays.
For example, using `std::reduce` on a small array to compute a sum will no be efficient,
since it will generate instructions that can be executed in parallel.
`array_reduce` will.

### ptr_iterator

* `aligned_ptr_iterator`
* `unaligned_ptr_iterator`

A pointer + cardinal with the `iterator` interface.

### preprocess_range

* `preprocess_range`

Given a more general notion of a range + traits returns enhanced traits +
iterator/sentinel pair that is understood by eve.

### for_each_iteration

`for_each_iteration(traits, f, l)`

_TODO_: we need some way to know where the iteration pattern starts from before actually doing anything. Example is `remove` it needs the base of where to start writing and it has to be there at the time of delegate creation.

The basic iteration pattern. A simd version of `while (f != l)`.
Delegate needs to implement `step(iterator, relative_condtional_expr)` and
_TODO_ `step_unrolled(iterator)` if the `unroll` trait is bigger than 1.
`iterator` type from steps is not guarantied to match `decltype(f)` (for when we know we can align the input for example).

`step` returns `true` if it wants to break or `false` to continue.
