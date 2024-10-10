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
#include <eve/module/math/constant/pi.hpp>

#include <eve/module/math/regular/cospi.hpp>
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/detail/generic/rem180.hpp>

namespace eve
{
  template<typename Options>
  struct cosd_t : elementwise_callable<cosd_t, Options, quarter_circle_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(cosd_t, cosd_);
  };

  //================================================================================================
  //! @addtogroup math_trig
  //! @{
  //! @var cosd
  //!
  //! @brief  `elementwise_callable` object object computing cosine from an input in degrees.
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
  //!      constexpr auto cosd(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto cosd[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto cosd[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto cosd[quarter_circle](floating_value auto x)          noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!     * `x`: [floating real value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) cosine of the input expressed in degrees.
  //!       In particular:
  //!         * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!         * If the element is \f$\pm\infty\f$, Nan is returned.
  //!         * If the element is a `Nan`, `Nan` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!    3. Assumes that the inputs elements  belong to \f$[-45,45]\f$ and return NaN outside.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/cosd.cpp}
  //================================================================================================
  inline constexpr auto cosd = functor<cosd_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T cosd_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        return eve::cospi[quarter_circle](div_180(a0));
      }
      else
      {
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(as<T>{});
        auto x = eve::abs(a0);
        if (eve::all(x <= T(45))) return cosd[quarter_circle](x);
        auto [fn, xr, dxr] = rem180(x);
        return cos_finalize(fn, xr, dxr);
      }
    }
  }
}
