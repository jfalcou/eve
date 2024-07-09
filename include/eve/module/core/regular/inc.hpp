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

namespace eve
{
  template<typename Options>
  struct inc_t : elementwise_callable<inc_t, Options, saturated_option>
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
//!   }
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
//!      1. The value of `x + 1` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The saturated incrementation of `x`. More specifically, for signed
//!         integral, `abs[saturated](valmin(as<T>{}))` returns `eve:valmin(as<T>{}))`
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/inc.cpp}
//! @}
//================================================================================================
  inline constexpr auto inc = functor<inc_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T inc_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr(integral_value<T> && O::contains(saturated2))
        return inc[a != valmax(eve::as(a))](a);
      else
        return a + one(eve::as(a));
    }


    template<conditional_expr C, value T, callable_options O>
    EVE_FORCEINLINE constexpr T inc_(EVE_REQUIRES(cpu_), C cond, O const&, T const& a) noexcept
    {
      if constexpr(simd_value<T>)
      {
        using           m_t = as<as_logical_t<T>>;
        constexpr bool  iwl = T::abi_type::is_wide_logical;

        if      constexpr(O::contains(saturated2))  return inc[cond.mask(m_t{}) && (a != valmin(eve::as(a)))](a);
        else if constexpr(integral_value<T> && iwl) return a - bit_cast(cond.mask(m_t{}),m_t{}).mask();
        else                                        return add[cond](a,one(eve::as(a)));
      }
      else
      {
        return add[cond](a,one(eve::as(a)));
      }
    }
  }
}
