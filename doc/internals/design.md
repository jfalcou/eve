Design Decisions {#design_rationale}
================

@section rationale-simd SIMD registers as Type x Cardinal

There is multiple way to abstract away SIMD registers. The choice made by **EVE** is to provide
a type interface based on the underlying **type** and **cardinal** (or number of lanes).

One can then define a SIMD type by specifying:

  - **Only the base type: `eve::wide<float>`**

    In this case, the best cardinal for the current architecture
    will be selected and will ensure optimal performance for the user.

  - **The base type and cardinal: `eve::wide< float, eve::fixed< 8 > >`**

    This interface is more geared toward power users that may requires a specific cardinal for
    their algorithm on any architecture. In this case, **EVE** will take care of ensuring the
    semantic of such code is correct over any architecture. This includes emulating smaller than
    usual cardinal using regular registers or aggregating multiple registers to support greater
    than usual cardinal.

This enables for SIMD code to be written in a complete architecture-agnostic way from the get go.

@section rationale-callable Callable Function Objects as main API

The majority of **EVE** features is accessible as [Function Objects](https://en.cppreference.com/w/cpp/named_req/FunctionObject).
Internally, **EVE**'s implementation uses a [Customization Point Object](http://eel.is/c++draft/customization.point.object#1)
design to achieve such goals. A simplified version of this design is also available for the end-user
that may wish to specialize a given function over a user-defined type via the `eve::tagged_dispatch`
customizable function.

This choice is driven by multiple reasons:

 - It makes all **EVE** functions directly usable as an argument to another function. Contrary to
   template functions, function objects can be easily passed as parameters to algorithms or other
   higher-order functions.

 - It enables the definition of function decorators that acts as lightweight
   wrapper for modifying the behavior of a function at compile-time.

@section rationale-decorator Function customization via higher-order decorator

Decorators enable **EVE** functions to change behavior locally, enabling users to control their
choice of trade-off between speed, precision or any other design decision. Such decisions could also
have been implemented as functions in additional namespaces or functions with different names.

We decided against those options because:

  - extra namespaces may have required code duplication when combining multiple decorators or decorator
    and masking.

  - extra function names would have cluttered the API.

The use of callable object to modify another callable object also plays nicely with a purely
functional view of the library in which everything is a value, including functions.

@section rationale-mask Masked operations support

Some SIMD instruction sets provides intrinsics that can mask which lanes of the register are
affected by the operations. Those so-called **Masked operations** are accessible in **EVE** via the
following protocol:

  - Let `func` be an **EVE** object function object that supports masks and let `cond`
    be a [logical value](@ref eve::logical_value) or a [conditional expression](@ref eve::conditional_expr).

  - Then, for any [value](@ref eve::value) `x`, the expression `func[cond](x, ...)`
    is equivalent to `if_else(cond, func_(x,...), x)`.

In these basic cases, if the mask is set to `false` for a given lane, the value returned by the
function is the corresponding value of `x`, regardless of other parameters. Note that this semantic
implies that `x` must be convertible to `decltype(func(x))`.

Masks also provide proper alternatives (rather than untouched output) and indexed selection allowing
to treat only a vector part designation by indexes rather than values
(see [the masking tutorial](@ref conditional) for more details).

The availability of such syntax is indicated explicitly in each function documentation page.
