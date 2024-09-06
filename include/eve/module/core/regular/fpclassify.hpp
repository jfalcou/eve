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
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_eqmz.hpp>
#include <eve/module/core/regular/is_eqpz.hpp>
#include <eve/module/core/regular/is_minf.hpp>
#include <eve/module/core/regular/is_pinf.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>

namespace eve
{
  template<typename Options>
  struct fpclassify_t : strict_elementwise_callable<fpclassify_t, Options>
  {
    template<std::uint8_t I, eve::floating_value T>
    constexpr EVE_FORCEINLINE logical<T>
    operator()(std::integral_constant<std::uint8_t, I>i, T v) const noexcept
    { return EVE_DISPATCH_CALL(i, v); }

    EVE_CALLABLE_OBJECT(fpclassify_t, fpclassify_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fpclassify
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
//!      constexpr auto fpclassify(value auto x)                          noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref value).
//!     * `i`: std:uint8_t integral value
//!        this parameter can be constructed by the consteval functions {eve::selected_classes{
//!        (see the example)
//!
//!   **Return value**
//!
//!     the elementwise classifications
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Subnormal_number)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/core/fpclassify.cpp}
//================================================================================================
  inline constexpr auto fpclassify = functor<fpclassify_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<std::uint8_t I, typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    fpclassify_(EVE_REQUIRES(cpu_), O const &,
                std::integral_constant<std::uint8_t, I>, T const& x) noexcept
    {
      using li_t = logical<T>;
      li_t r{};
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

  template < eve::detail::fpclass  c0 ,
             eve::detail::fpclass  c1 = eve::detail::fpclass::none,
             eve::detail::fpclass  c2 = eve::detail::fpclass::none,
             eve::detail::fpclass  c3 = eve::detail::fpclass::none,
             eve::detail::fpclass  c4 = eve::detail::fpclass::none,
             eve::detail::fpclass  c5 = eve::detail::fpclass::none,
             eve::detail::fpclass  c6 = eve::detail::fpclass::none,
             eve::detail::fpclass  c7 = eve::detail::fpclass::none >
  consteval auto selected_classes()
  {
    constexpr std::uint8_t orc = eve::detail::to_integer(c0) |
      eve::detail::to_integer(c1) |
      eve::detail::to_integer(c2) |
      eve::detail::to_integer(c3) |
      eve::detail::to_integer(c4) |
      eve::detail::to_integer(c5) |
      eve::detail::to_integer(c6) |
      eve::detail::to_integer(c7);
    return std::integral_constant<std::uint8_t, orc >();
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fpclassify.hpp>
#endif
