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
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve
{
  template<typename Options>
  struct nthroot_t : strict_elementwise_callable<nthroot_t, Options, raw_option>
  {
    template<eve::floating_value T, eve::integral_value U>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, U> operator()(T v, U w) const noexcept
    requires(eve::same_lanes_or_scalar<T, U>)
    { return EVE_DISPATCH_CALL(v, w); }

    template<eve::floating_value T, eve::floating_value U>
    EVE_FORCEINLINE  constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(nthroot_t, nthroot_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var nthroot
//!
//! @brief Callable object computing the nth root: \f$x^{1/n}\f$.
//!
//!   **Defined in Header**
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
//!      template< eve::floating_value T, eve::floating_value U >
//!      T nthroot(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//!   * `n`:   [integral_value](@ref eve::integral_value). Actually `n` can be a [flint](@ref
//!   eve::is_flint).
//!
//! **Return value**
//!
//!  Returns [elementwise](@ref glossary_elementwise) the value of \f$x^{1/n}\f$.
//!  For negative `x` the value returned is a Nan as soon as `n` is not an odd integer.
//!
//!  The result type is of the compatibility type of the  parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/nthroot.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto nthroot = functor<nthroot_t>;

  namespace detail
  {

    template<floating_value T,  integral_value U, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, U>
    nthroot_(EVE_REQUIRES(cpu_), O const & o, T x, U n) noexcept
    {
      using elt_t = element_type_t<T>;
      return nthroot[o](x,convert(n, as<elt_t>()));
    }

    template<floating_value  T, floating_value  U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    nthroot_(EVE_REQUIRES(cpu_), O const &, T xx, U nn) noexcept
    {
      using r_t =  common_value_t<T, U>;
      r_t x = r_t(xx);
      r_t n = r_t(nn);
      if constexpr( O::contains(raw2))
      {
        auto r      = pow(abs(x), rec[pedantic](n));
        auto islezx = is_lez(x);
        if( none(islezx) ) return r;
        else
        {
          return if_else(is_eqz(x),
                         if_else(is_ltz(n), inf(as(x)), zero),
                         if_else(islezx && !is_odd(n), allbits, r * sign(x)));
        }
      }
      else
      {
        auto an   = eve::abs(n);
        auto ax   = eve::abs(x);
        auto y    = nthroot[raw](ax, an);
        auto p    = pow(y, an);
        auto yinc = -((p-ax)/(an*p))*y;
        y         = add[is_nez(y) && is_finite(x)](y, yinc);
        y         = if_else(is_negative(x) && is_even(an), allbits, y*sign(x));
        return rec[pedantic][is_ltz(n)](y);
      }
    }
  }
}
