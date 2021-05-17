Building strlen {#tutorial_strlen}
===============

@tableofcontents

*NOTE: this documentation was valid at [commit](https://github.com/jfalcou/eve/commit/98b73427f16e580853202000d87c0eb0b6739905)*

In this tutorial we will introduce some of the basic EVE concepts and see how they come together to implement strlen. <br/>
The strlen we will implement is discussed in this
[stackoverflow](https://stackoverflow.com/questions/25566302/vectorized-strlen-getting-away-with-reading-unallocated-memory)
and is very close to [MacOs x86](https://opensource.apple.com/source/Libc/Libc-997.90.3/x86_64/string/strlen.s)
and [glibc arm-v8](https://code.woboq.org/userspace/glibc/sysdeps/aarch64/multiarch/strlen_asimd.S.html) implemenations. <br/>
You can also find this tutorial in [this talk](https://youtu.be/d6NcnyXjc3I) though the syntax was updated.

*NOTE: we are not advocating rewriting `strlen` with EVE - this was just an example
to show the interfaces and to prove that we have high quality codegen.*

# Key idea

SIMD allows us to test multiple chars at once for zero and that what will do with EVE.
However, how can we read multiple bytes if the string can be less that what we try to read?
We are just going to state the solution here: **reading a register from an address aligned to the size of the register
is safe due to allocations happening in pages**. <br/>
You can find a detailed discussion on
[stackoverflow](https://stackoverflow.com/questions/25566302/vectorized-strlen-getting-away-with-reading-unallocated-memory)
or in [this talk](https://youtu.be/d6NcnyXjc3I).

  (insert src/strlen.src.html here)

Let's break it down.

### `reinterpret_cast`.
`char` is not guarantied to be a `signed char` or an `unsigned char` and can be an individual type.
EVE supports `int8_t` and `uint8_t` but not weird `char`, so we have to cast.

### typedef for `eve::wide<std::uint8_t>`
`eve::wide` is EVE's abstraction on top of the simd register. By default EVE will select the native register size for your platform.
You can override that with an arbitraty power of 2 by providing `eve::fixed<N>` as a second parameter,
which is useful in certain cases.

### `const wide zero{0};`
We will compare each element we load with 0 and this populates us a full wide of zeroes.
You can construct a wide from a constant or a variable.

### `eve::previous_aligned_address(s);`
This returns the previous address aligned to the default width of the register.
You can specify an `eve::fixed<N>{}` as a second parameter if you wanted to override how many elements you
needed to align to (for non-default width).
There is a convenience template variable `eve::lane<N>` that has `eve::fixed<N>` type.
It returns a special type eve::aligned_ptr[T, size_t] - second parameter is alignment in bytes. (there is a default = native register size),
Here we want the library to take care of all of that, so we just rely on CTAD.

### `eve::unsafe(eve::load)(aligned_s);`
We load a `wide` from `aligned_s` pointer. There are two ways to do it:
* `wide(ptr)` constructor
* `eve::load` function
Here we are perfectly fine doing either of those until we decide to use our strlen with dynamic analysis.
As was mentioned previously, it is OK to load from an aligned address but not from the view of C++.
The dynamic analysis on this `strlen` will report an issue because you read outside of the allocated memory.
For `asan` and `tsan` we have special modifier `unsafe`. When we call `eve::unsafe(eve::load)(aligned_s)`,
EVE detects build with these sanitizers and disable them for this load.
`wide(ptr)` constructor does not have a way to do this.

### `cur == zeroes`
This is an elementwise comparison for equality between `cur` and `zeroes`.
The result is `eve::logical<wide>` - a class representing N booleans where N is the cardinal of our wide.

### `eve::ignore_first ignore / eve::first_true[ignore]`
`first_true` takes a `logical` and returns the optional position of the first `true` element.
However we compute `previous_aligned_address(s)` and not just `s`, so there might be some 0s we are not interested in. <br/>
For this purpose `eve` provides some conditional mutators, most commonly used ones are:
`ignore_first`, `ignore_last`, `ignore_extrema` (ignores from both sides).

### `while (!match) / aligned_s += wide::static_size`
While we didn't find the 0, we go to the next chunk. `wide::static_size` is the cardinal of the  `wide`.
Alternatively we could have used `wide.size()`. but `static_size` has the advantage of being `constexpr` friendly.

### `match = eve::first_true(cur == zeroes);`
This is the same `first_true` but we no longer need to ignore anything.

### `aligned_s.get() + *match - s`
Finally, compute where we finished.

# Comparison with real strlens

The code above closely resembles [MacOs x86 strlen](https://opensource.apple.com/source/Libc/Libc-997.90.3/x86_64/string/strlen.s). <br/>
With EVE compiled for `sse2`: [godbolt](https://godbolt.org/z/hvr3P5) <br/>
The differences are minimal: clang handles the bit and address manipulations slightly differently.

When comparing against [glibc arm-v8 (aarch64)](https://code.woboq.org/userspace/glibc/sysdeps/aarch64/multiarch/strlen_asimd.S.html) <br/>
With eve we get: [eve, aarch64](https://godbolt.org/z/nz5eWe). <br/>
The interesting differences are:
  * they do not immediatly load from the previous aligned address for the first block. Instead they check if they load from s,
    and only if not, they start dealing with the previous address.
  * they compute position of the first match differently.
  * we compare with 0 and then look for `true` using `umaxv` instruction.
    They rely on 0 being unsigned minimum and use `uminv` on the register directly.
    Unfortunatly this trick only works for looking for 0 and we can look for arbitraty value.

There are some substantial improvements one can make to this `strlen`,
like unrolling which can be found in [glibc avx2
implementation](https://code.woboq.org/userspace/glibc/sysdeps/x86_64/multiarch/strlen-avx2.S.html).
