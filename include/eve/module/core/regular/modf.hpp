//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/zip.hpp>
#include <eve/arch/platform.hpp>

namespace eve
{
  template<typename Options>
  struct modf_t : elementwise_callable<modf_t, Options, pedantic_option, raw_option, almost_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr zipped<T,T> operator()(T a) const noexcept
    {
      return EVE_DISPATCH_CALL(a);
    }

    EVE_CALLABLE_OBJECT(modf_t, modf_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var modf
//!   @brief `elementwise_callable` object computing the [elementwise](@ref glossary_elementwise)
//!   pair of  fractional and integral parts of the value,
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
//!      constexpr auto modf(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto modf[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto modf[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto modf[raw](floating_value auto x)                     noexcept; // 3
//!      constexpr auto modf[pedantic](floating_value auto x)                noexcept; // 3
//!      constexpr auto modf[almost](floating_value auto x)                  noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :   [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     1. A `kumi::tuple` of values containing respectively the `frac(x)` and trunc(x)`,
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. A `kumi::tuple` of values containing respectively the `frac[o](x)` and trunc[o](x)`
//!        where `o` is the chosen option.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/modf.cpp}
//! @}
//================================================================================================
  inline constexpr auto modf = functor<modf_t>;
//================================================================================================
//================================================================================================


namespace detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto modf_(EVE_REQUIRES(cpu_), O const& o, T a) noexcept
  {
    if constexpr(floating_value<T>)
    {
      auto t = trunc[o.drop(pedantic2)](a);
      if constexpr(O::contains(raw))
      {
        return eve::zip(a-t, t);
      }
      else
      {
        auto f = if_else(is_eqz(a), a, a-t);
        if constexpr(O::contains(pedantic2)  && platform::supports_infinites)
          f = if_else(is_infinite(a), eve::zero, f);
        return eve::zip(f, t);
      }
    }
    else return eve::zip(zero(eve::as(a)), a);
  }
}}
