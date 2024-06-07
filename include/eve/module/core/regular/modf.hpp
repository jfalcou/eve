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
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  fractional and integral parts of the value,
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
//!      zipped<T,T> modf(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :   [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     A pair of values containing respectively the [elementwise](@ref glossary_elementwise)
//!     fractional and integral parts of `x`, each having the type and sign of `x`.
//!
//!     In particular:
//!       * If `x` is infinite `{Nan, x}` is returned. (this is not standard conformant: see pedantic)
//!       * If `x` is a `Nan`  `{Nan, Nan}` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/modf.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * eve::raw
//!
//!     The call `modf[raw](x)` does care about limits nor zero sign.
//!
//!   * eve::pedantic
//!
//!     The call `modf[pedantic](x)` ensures standard conformity : if `x` is infinite,
//!     `{0, x}` is returned.
//!
//!   * eve::almost
//!
//!     The call `modf[almost [= tol}](x)` use `trunc[almost [= tol}](x)` to compute the integral part

//! @}
//================================================================================================

inline constexpr auto modf = functor<modf_t>;

namespace detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto modf_(EVE_REQUIRES(cpu_), O const& o, T a) noexcept
  {
    if constexpr(floating_value<T>)
    {
      auto t = trunc[o.drop(pedantic2)](a);
      if constexpr(O::contains(raw2))
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
