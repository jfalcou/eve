_NOTE_: This is a temporary documentation that is just very quick to write a modify. Will migrate later.

algo is for stl/ranges style algorithms using simd.

Main eve supports it's callables for scalars. We don't do that for algorithms. The code is still portable since the cpu emulation is enabled.

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

### concepts

* `unaligned_t` -> a convinience to get the unaligned type.
* `same_unaligned_iterator<T, U>` -> checks if two iterators have the same unaligned types.

### iterator helpers

* `operations_with_distance` -> provides boilerplate distance operations.
* `forward_to_unaligned` -> provides boilerplate operations using `unaligned()`

### ptr_iterator

* `aligned_ptr_iterator`
* `unaligned_ptr_iterator`

A pointer + cardinal with the `iterator` interface.
