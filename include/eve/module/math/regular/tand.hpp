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

#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/deginrad.hpp>
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/regular/tanpi.hpp>

namespace eve
{
  template<typename Options>
  struct tand_t : elementwise_callable<tand_t, Options, quarter_circle_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(tand_t, tand_);
  };

  //================================================================================================
  //! @addtogroup math_trig
  //! @{
  //! @var tand
  //!
  //! @brief `elementwise_callable` object computing the tangent from an input in degrees.
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
  //!      constexpr auto tand(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto tand[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto tand[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto tand[quarter_circle](floating_value auto x)          noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!     * `x`: [floating value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) tangent of the input expressed in
  //!       degrees. In particular:
  //!         * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!         * If the element is \f$\pm\infty\f$, Nan is returned.
  //!         * If the element is a `NaN`, `NaN` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!    3. Assumes that the inputs elements  belong to \f$[-45,45]\f$ and return NaN outside.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/tand.cpp}
  //================================================================================================
  inline constexpr auto tand = functor<tand_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tand_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        return tanpi[eve::quarter_circle](div_180(a0));
      }
      else
      {
        auto x = eve::abs(a0);
        if( eve::all(x <= T(45)) ) return tand[eve::quarter_circle](a0);
        auto a0_180 = div_180(a0);
        auto test   = is_not_flint(a0_180) && is_flint(a0_180 + mhalf(eve::as(a0_180)));
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return a0;
          if( test ) return nan(eve::as<T>());
        }
        else
          x = if_else(test, eve::allbits, x);
        auto [fn, xr, dxr] = rem180(x);
        return tan_finalize(deginrad(a0), fn, xr, dxr);
      }
    }
  }
}
