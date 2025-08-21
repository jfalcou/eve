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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve
{
  template<typename Options>
  struct inc_t : elementwise_callable<inc_t, Options, saturated_option, lower_option,
                                      upper_option, strict_option, mod_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(inc_t, inc_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var inc
//!   @brief `elementwise_callable` object returning the input incremented by 1.
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
//!      constexpr auto inc(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto inc[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto inc[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto inc[saturated](value auto x)               noexcept; // 3
//!      constexpr auto inc[lower](value auto x)                   noexcept; // 4
//!      constexpr auto inc[upper](value auto x)                   noexcept; // 5
//!      constexpr auto inc[lower][strict](value auto x)           noexcept; // 4
//!      constexpr auto inc[upper][strict](value auto x)           noexcept; // 5
//!      constexpr auto inc[mod = p][strict](value auto x)         noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [SIMD or scalar value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!     * `p`: modulo p operation. p must be flint less than maxflint.
//!
//!    **Return value**
//!
//!      1. The value of `x + 1` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The saturated incrementation of `x`. More specifically, for signed
//!         integral, `inc[saturated](valmax(as<T>{}))` returns `eve:valmax(as<T>{}))`
//!      4. The increment is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!         to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!      5. The increment is computed  in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!         to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!      6. compute the result in modular arithmetic. the parameter must be flint positive
//!        and less than the modulus. The modulus itself must be less than maxflint.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/inc.cpp}
//================================================================================================
  inline constexpr auto inc = functor<inc_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T inc_(EVE_REQUIRES(cpu_), O const& o, T const& a) noexcept
    {
      if constexpr(integral_value<T> && O::contains(saturated))
        return inc[a != valmax(eve::as(a))](a);
      else if constexpr( signed_integral_scalar_value<T>)
      {
        using u_t = as_integer_t<T>;
        return T(u_t(a)+u_t(1));
      }
      else
        return eve::add[o](a, one(eve::as(a)));
    }


    template<conditional_expr C, value T, callable_options O>
    EVE_FORCEINLINE constexpr T inc_(EVE_REQUIRES(cpu_), C cond, O const& o, T const& a) noexcept
    {
      if constexpr(simd_value<T>)
      {
        constexpr bool  iwl = T::abi_type::is_wide_logical;
        using           m_t = as_logical_t<T>;

        if      constexpr(O::contains(saturated))  return inc[cond.mask(as<m_t>{}) && (a != valmax(eve::as(a)))](a);
        else if constexpr(integral_value<T> && iwl)
        {
          auto m = cond.mask(as<m_t>{});

          if constexpr (simd_value<decltype(m)>) return a - convert(m.bits(), as_element<T>{});
          else                                   return a - bit_cast(m.mask(), int_from<decltype(m.mask())>{});
        }
        else                                     return add[o][cond](a,one(eve::as(a)));
      }
      else
      {
        return add[o][cond](a,one(eve::as(a)));
      }
    }
  }
}
