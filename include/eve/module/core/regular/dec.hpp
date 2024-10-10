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
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/convert.hpp>
namespace eve
{
  template<typename Options>
  struct dec_t : elementwise_callable<dec_t, Options, saturated_option, lower_option, upper_option, strict_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(dec_t, dec_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dec
//!   @brief `elementwise_callable` object returning the input decremented by 1.
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
//!      constexpr auto dec(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto dec[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto dec[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto dec[saturated](value auto x)               noexcept; // 3
//!      constexpr auto dec[lower](value auto x)                   noexcept; // 4
//!      constexpr auto dec[upper](value auto x)                   noexcept; // 5
//!      constexpr auto dec[lower][strict](value auto x)           noexcept; // 4
//!      constexpr auto dec[upper][strict](value auto x)           noexcept; // 5
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [SIMD or scalar value](@ref value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of `x - 1` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The saturated decrementation of `x`. More specifically, for signed
//!         integral, `abs[saturated](valmin(as<T>{}))` returns `eve:valmin(as<T>{}))`
//!      4. The decrement is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!         to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!      5. The decrement is computed  in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!         to be greater or equal to the exact one (except for Nans).Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/dec.cpp}
//================================================================================================
  inline constexpr auto dec = functor<dec_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T dec_(EVE_REQUIRES(cpu_), O const& o, T const& a) noexcept
    {
      if constexpr(integral_value<T> && O::contains(saturated))  return dec[a != valmin(eve::as{a})](a);
      else if constexpr( signed_integral_scalar_value<T>)
      {
        using u_t = as_integer_t<T>;
        return T(u_t(a)+u_t(-1));
      }
      else
        return add[o](a, mone(eve::as{a}));
    }

    template<conditional_expr C, value T, callable_options O>
    EVE_FORCEINLINE constexpr T dec_(EVE_REQUIRES(cpu_), C cond, O const& o, T const& a) noexcept
    {
      if constexpr(simd_value<T>)
      {
        using           m_t = as_logical_t<T>;
        constexpr bool  iwl = T::abi_type::is_wide_logical;

        if      constexpr(O::contains(saturated))  return dec[cond.mask(as<m_t>{}) && (a != valmin(eve::as{a}))](a);
        else if constexpr(integral_value<T> && iwl)
        {
          auto m = cond.mask(as<m_t>{});

          if constexpr (simd_value<decltype(m)>) return a + convert(m.bits(), as_element<T>{});
          else                                   return a + bit_cast(m.mask(), int_from<decltype(m.mask())>{});
        }
        else                                     return add[o](a,mone(eve::as{a}));
      }
      else
      {
        return add[o](a,mone(eve::as{a}));
      }
    }
  }
}
