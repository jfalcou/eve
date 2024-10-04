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

#include <eve/module/math/regular/cos.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>

namespace eve
{
  template<typename Options>
  struct tanpi_t : elementwise_callable<tanpi_t, Options, quarter_circle_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(tanpi_t, tanpi_);
  };

  //================================================================================================
  //! @addtogroup math_trig
  //! @{
  //! @var tanpi
  //!
  //! @brief `elementwise_callable` object computing the tangent from an input in \f$\pi\f$ multiples.
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
  //!      constexpr auto tanpi(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto tanpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto tanpi[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto tanpi[quarter_circle](floating_value auto x)          noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!      * `x`: [floating value](@ref floating_value).
  //!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!      * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) tangent of the input expressed in \f$\pi\f$
  //!       multiples. In particular:
  //!        * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!        * If the element is \f$\pm\infty\f$, Nan is returned.
  //!        * If the element is a `Nan`, `NaN` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!    3. Assumes that the inputs elements  belong to \f$[-1/4,1/4]\f$ and return NaN outside.
  //!
  //!  @groupheader{Example}
  //================================================================================================
  inline constexpr auto tanpi = functor<tanpi_t>;
  //================================================================================================
  //!  @godbolt{doc/math/tanpi.cpp}
  //================================================================================================
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tanpi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        return tan[eve::quarter_circle](a0 * pi(eve::as<T>()));
      }
      else
      {
        auto x = eve::abs(a0);
        if( eve::all(x <= T(0.25)) ) return tanpi[eve::quarter_circle](a0);
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return a0;
          if( is_not_finite(x) || (frac[raw](x) == half(eve::as<T>())) ) return nan(eve::as<T>());
          if( x > maxflint(eve::as<T>()) || is_flint(x) ) return T(0);
        }
        else
        {
          x = if_else(is_greater(x, maxflint(eve::as(x))) || is_flint(x), eve::zero, x);
          x = if_else(is_not_finite(a0) || (frac[raw](x) == half(eve::as<T>())), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return tan_finalize(a0 * pi(eve::as<T>()), fn, xr, dxr);
      }
    }
  }
}
