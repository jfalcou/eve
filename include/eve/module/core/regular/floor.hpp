//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct floor_t : elementwise_callable<floor_t, Options, tolerant_option>
  {
    template<eve::integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return v; }

    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<eve::floating_value T, floating_value U >
    constexpr EVE_FORCEINLINE T operator()(T v, U u) const  noexcept
    { return EVE_DISPATCH_CALL(v, u); }

    template<eve::floating_value T, integral_value U >
    constexpr EVE_FORCEINLINE T operator()(T v, U u) const  noexcept
    { return EVE_DISPATCH_CALL(v, u); }

    template<eve::floating_value T, only_if<signed,unsigned>  U>
    constexpr EVE_FORCEINLINE  as_integer_t<T, U> operator()(T v,  as<U> const & target) const  noexcept
    { return EVE_DISPATCH_CALL(v, target); }

    EVE_CALLABLE_OBJECT(floor_t, floor_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var floor
//!   @brief Computes the largest integer not greater than the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T floor(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!       The largest integer not greater than `x`.
//!
//!       The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!       `FE_TOWARDZERO`. This function object implements the `FE_DOWNWARD` version.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/floor.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::floor[mask](x)` provides a masked version of `eve::floor` which is
//!     equivalent to `if_else (mask, floor(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/floor.cpp}
//!
//!   * eve::tolerant
//!
//!     The expression `tolerant(floor)(x, tol)` computes a tolerant floor value for `x`,
//!     where `x` must be a floating value.
//!
//!      * If `tol` is a floating value, computes the floor with
//!        a tolerance `tol` using Hagerty's FL5 function.
//!      * If `tol` is an integral value n, computes the floor of
//!        the next nth representable value in the `x` type.
//!      * If `tol` is omitted, the tolerance is taken to 3 times
//!        the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
//!
//!      @godbolt{doc/core/fuzzy/floor.cpp}
//! @}
//================================================================================================
  inline constexpr auto floor = functor<floor_t>;
}

#include <eve/module/core/regular/impl/floor.hpp>

// #if defined(EVE_INCLUDE_X86_HEADER)
// #  include <eve/module/core/regular/impl/simd/x86/floor.hpp>
// #endif

// #if defined(EVE_INCLUDE_POWERPC_HEADER)
// #  include <eve/module/core/regular/impl/simd/ppc/floor.hpp>
// #endif

// #if defined(EVE_INCLUDE_ARM_HEADER)
// #  include <eve/module/core/regular/impl/simd/arm/neon/floor.hpp>
// #endif

// #if defined(EVE_INCLUDE_SVE_HEADER)
// #  include <eve/module/core/regular/impl/simd/arm/sve/floor.hpp>
// #endif
