//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <type_traits>
#include <eve/module/core/detail/flags.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_eqmz.hpp>
#include <eve/module/core/regular/is_eqpz.hpp>
#include <eve/module/core/regular/is_minf.hpp>
#include <eve/module/core/regular/is_pinf.hpp>

namespace eve
{
  template<typename Options>
  struct of_class_t : strict_elementwise_callable<of_class_t, Options>
  {
    template<std::uint8_t I, eve::floating_value T>
    constexpr EVE_FORCEINLINE logical<T>
    operator()(T v, fp_class<I> i) const noexcept
    { return EVE_DISPATCH_CALL( v, i); }

    EVE_CALLABLE_OBJECT(of_class_t, of_class_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var of_class
//!   @brief `strict_elementwise_callable` object computing classification of elements of the input.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      template<std::uint8_t I, eve::floating_value T>
//!      constexpr auto of_class(value auto x, fp_class<I> i) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref value).
//!     * `i`: fp_class to check
//!
//!   **Return value**
//!
//!     the elementwise classifications
//!
//!   **Helpers**
//!
//!     the `i`parameter can be constructed easily by using the `fp_class` values
//!     `qnan`, `poszero, `negzero, `posinf`,`neginf`, `denorn`,`neg`, `snan`(see the example).
//!
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Subnormal_number)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/core/of_class.cpp}
//================================================================================================
  inline constexpr auto of_class = functor<of_class_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<std::uint8_t I, typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    of_class_(EVE_REQUIRES(cpu_), O const &, T const& x,  fp_class<I>) noexcept
    {
      using li_t = logical<T>;
      li_t r{false};
      constexpr std::uint8_t o(1);
      if constexpr((I       &o) == o) r = is_nan(x);
      if constexpr(((I >> 1)&o) == o) r = r || is_eqpz(x);
      if constexpr(((I >> 2)&o) == o) r = r || is_eqmz(x);
      if constexpr(((I >> 3)&o) == o) r = r || is_pinf(x);
      if constexpr(((I >> 4)&o) == o) r = r || is_minf(x);
      if constexpr(((I >> 5)&o) == o) r = r || is_denormal(x);
      if constexpr(((I >> 6)&o) == o) r = r || (is_finite(x) && is_ltz(x));
      if constexpr(((I >> 7)&o) == o) r = r || is_nan(x);
      return r;
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/of_class.hpp>
#endif
