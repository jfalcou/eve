_NOTE_: This is a temporary documentation that is just very quick to write a modify. Will migrate later.

algo is for stl/ranges style algorithms using simd.

Main eve supports it's callables for scalars. We don't do that for algorithms. The code is still portable since the cpu emulation is enabled.

# Algorithms

* all_of
* any_of
* none_of

* find/find_if

* equal
* mismatch

* reduce
* remove/remove_if

# Helpers

# as_range

taking a relaxed iterator/sentinel pair, returns a range for it.

### relaxed iterator/range(concept)

Some iterator/range like thing that can be converted to proper eve iterator/sentinel pair
using `preprocess_range`.

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
* `I.previous_partially_aligned()` - returns our best attempt to align this iterator.

### aligned_iterator(concept)

*TODO*

The main model is `aligned_ptr_iterator`

This is a `partially_aligned_iterator` but has an extra feature: we can do `unsafe` load.
When we get to unbounded algorithms it will become important.

### partially_aligned_iterator(concept)

I and partially_aligned_t<I> are the same.

The main model is `aligned_ptr_iterator`, `zip_iterator<aligned_ptr_iterator, unaligned_ptr_iterator>`

Loading/Storign is more efficient than doing the same from `unaligned`. We can only step in `I::cardinal{}()` divisible steps.

### unaligned_iterator(concept)

I and unaligned_t<I> are the same.

The main model is `unaligned_ptr_iterator`

iterator that can represent any position in the underlying range.

### always_aligned_iterator (concept)

I is the same as `partially_aligned_t<I>` and `unaligned_t<I>`

Main model: iota_iterator.

These are not phisical iterators but rather some mechanisms that pretend to be iterators.
alignment does not matter to them, every position is just as efficient as any other.

### iteration patterns

*`for_each_iteration`

A reusable component to do `while(f != l) ++f;`.
Given traits, f, l, delegate calls the delegate for each piece with (f, ignore).
The specific api of the delegate varies by iteration pattern.

Main one is `for_each_iteration`.
However for some algorithms, like `reverse` and maybe `partition` it's not a good.

### traits

* `traits`
* `function_with_traits`

* `common_with_types`
* `divisible_by_cardinal`
* `force_cardinal`
* `no_aligning`
* `unroll`

Traits is a way to customise the behaviour of the algorithm.
Different algorithms support different customizations.

The easiest way to enable a function to support traits.

```
template <typename TraitsSupport>
struct func_ : TraitsSupport
{
  // Your code here
  auto operator()( /*params*/ ) {}
};

inline constexpr auto func = eve::algo::function_with_traits<func_>[defaults];
```
TraitsSupport baseclass exposes: `traits_type` to get the type and `get_traits()` for a variable;

Then the user get:

```
// opt1
func[eve::algo::unroll<1>][eve::algo::no_aligning](/*params*/)

// opt2
eve::algo::traits in = /*external source*/
func[in](/*params*/)
```

#### Individual traits.

common_with_types
converts iteration type to a type that is a common with a given one.

divisible_by_cardinal
you know for a fact that the range is divisible by cardinal

force_cardinal
ignore default cardinal deduction and try to force smth.
Currently might fail compilation if you try to increase the cardinal, for example if you fail the alignment requirement.

no_aligning
By default we will try to find previous aligned address if  the iterators allow.
Maybe you don't want this.

unrolling
You can control how much the algorithm will be unrolled. There default one
assumes that the operation supplied is equivalent to the default one, so if you are doing something expensive,
makes sense to set to one.

### concepts

* `unaligned_t` -> a convinience to get the unaligned type.
* `partially_aligned_t` -> a convinience to get the type of `previous_partially_aligned`
* `same_unaligned_iterator<T, U>` -> checks if two iterators have the same unaligned types.
* `iterator_basics` -> checks everything about iterator except for load and store
* `readable_iterator`
* `unaligned_iterator`
* `partially_aligned_iterator`
* `always_aligned_iterator`

### iterator helpers

* `operations_with_distance` -> provides boilerplate distance operations.

### array_utils

* `array_map`
* `array_reduce`

Functional style utilites to perform common operations on arrays.
For example, using `std::reduce` on a small array to compute a sum will no be efficient,
since it will generate instructions that can be executed in parallel.
`array_reduce` will.

### converting_iterator

* `converting_iterator`
* `convert`

An iterator on top of a different iterator that applies a convertion to a different type.
Cardinal stays the same.
In the future this should use some more efficient platform loads.

convert is a helper function to get a converting iterator.

### zip_iterator

`zip_iterator`

A tuple of iterators with the same cardinal.

### ptr_iterator

* `aligned_ptr_iterator`
* `unaligned_ptr_iterator`

A pointer + cardinal with the `iterator` interface.


### preprocess_range

* `preprocess_range`

Given a more general notion of a range + traits returns enhanced traits +
iterator/sentinel pair that is understood by eve.
This is one hand a helper for `range algorithm adapters` and on the other (*TODO*)
a customization point for different ranges that need some non-default handling.

### for_each_iteration

`for_each_iteration(traits, f, l)`

_TODO_: we need some way to know where the iteration pattern starts from before actually doing anything. Example is `remove` it needs the base of where to start writing and it has to be there at the time of delegate creation.

The basic iteration pattern. A simd version of `while (f != l)`.
Delegate needs to implement `step(iterator, relative_condtional_expr)` and
_TODO_ `step_unrolled(iterator)` if the `unroll` trait is bigger than 1.
`iterator` type from steps is not guarantied to match `decltype(f)` (for when we know we can align the input for example).

`step` returns `true` if it wants to break or `false` to continue.

### unaligned

`unalign`
`uunaligned/unaligned_t`

A small helper.
For contigious iterators -> returns themselves
For aligned_ptr -> returns a raw ptr
For everything else -> returns .unaligned()

### zip

`zip`
`zip[common_type]`
`zip[divisible_by_cardinal]`
`zip[common_with_types<double>]`

`zip` is an entry point for everything over parallel arrays.
You can `zip` multiple `relaxed_iterator` which will give you a `zip_iterator` of them.
You can also `zip` multiple `relaxed_range` with some traits - this gives you a `zip_range`.
It's also OK to `zip` iterators and ranges together, which will give you a range (we will compute the end based on the range length).
All ranges passed to `zip` have to have the same length.

The traits supported are `common_type` - converts all the individual iterators to the biggest type.
`common_with_types<types...>` - same as common_type only will take the listed types into account.
`divisible_by_cardinal` - just if you know that this range is `divisible` - this will be propagated up.
