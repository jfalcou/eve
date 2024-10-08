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
#include <eve/module/core.hpp>
#include <eve/module/math/regular/cotpi.hpp>
#include <eve/module/math/regular/deginrad.hpp>
#include <eve/module/math/regular/div_180.hpp>

namespace eve
{
  template<typename Options>
  struct cotd_t : elementwise_callable<cotd_t, Options, quarter_circle_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(cotd_t, cotd_);
  };

  //================================================================================================
  //! @addtogroup math_trig
  //! @{
  //! @var cotd
  //! @brief `elementwise_callable` object computing the cotangent from an input in degrees.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto cotd(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto cotd[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto cotd[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto cotd[quarter_circle](floating_value auto x)          noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!     * `x`:[floating real value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) cosine of the input expressed in degrees.
  //!       In particular:
  //!         * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
  //!         * If the element is \f$\pm\infty\f$, Nan is returned.
  //!         * If the element is a `Nan`, `Nan` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!    3. Assumes that the inputs elements  belong to \f$[-45,45]\f$ and return NaN outside.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/cotd.cpp}
  //================================================================================================
  inline constexpr auto cotd = functor<cotd_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T cotd_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      auto x = abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
          if( is_not_less_equal(x, T(45)) ) return nan(eve::as<T>());
          return rec[pedantic](tancot_eval(deginrad(a0)));
        }
        else
        {
          return if_else(
            is_eqz(a0),
            bit_or(a0, inf(eve::as(a0))),
            if_else(is_not_less_equal(x, T(45)), eve::allbits, rec[pedantic](tancot_eval(deginrad(a0)))));
        }
      }
      else
      {
        if( eve::all(x <= T(45)) ) return cotd[quarter_circle](a0);
        T    a0_180 = div_180(a0);
        auto test   = is_nez(a0_180) && is_flint(a0_180);
        if constexpr( scalar_value<T> ) // early return for nans in scalar case
        {
          if( test ) return nan(eve::as<T>());
        }
        else { x = if_else(test, eve::allbits, x); }
        auto [fn, xr, dxr] = rem180(x);
        return cot_finalize(deginrad(a0), fn, xr, dxr);
      }
    }
  }
}
