//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/expm1.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve
{

  template<typename Options>
  struct logspace_sub_t : tuple_callable<logspace_sub_t, Options>
  {
    template<eve::floating_value T, floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T t, U u) const noexcept
    {
      return EVE_DISPATCH_CALL(t, u);
    }

    template<eve::floating_value T0, floating_value T1, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tuple>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<eve::common_value,Tuple>
    operator()(Tuple const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(logspace_sub_t, logspace_sub_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var logspace_sub
//!
//! @brief `tuple_callable` object computing the logspace_sub operation:
//!        \f$\log\left(e^{\log x_0}-\sum_{i = 1}^n e^{\log x_i}\right)\f$.
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
//!      // Regular overloads
//!      constexpr auto logspace_sub(floating_value auto x, floating_value auto ... xs)        noexcept; // 1
//!      constexpr auto logspace_sub(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto logspace_sub[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto logspace_sub[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`, `...xs`: [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. The call `logspace_sub(x, xs...)` is semantically equivalent to`log(exp(log(x)) - exp(log(xs))...)`.
//!       without causing unnecessary overflows or throwing away too much accuracy.
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/logspace_sub.cpp}
//================================================================================================
  inline constexpr auto logspace_sub = functor<logspace_sub_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T0, typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    logspace_sub_(EVE_REQUIRES(cpu_), O const &, T0 a0, T1 a1, Ts... args) noexcept
    {
      using r_t = common_value_t<T0, T1, Ts...>;
      if constexpr(sizeof...(Ts) == 0)
      {
        if constexpr( has_native_abi_v<T0> )
        {
          auto r0 = r_t(a0);
          auto r1 = r_t(a1);
          auto x    = r1-r0;
          auto test = x > -log_2(as(x));
          if( eve::all(test) )
            return r0 + eve::log(-expm1(x));
          else if( eve::any(test) )
            return r0+ if_else(test, log(-expm1(x)), log1p(-exp(x)));
          else
            return r0 + log1p(-exp(x));
        }
        else return arithmetic_call(logspace_sub, r_t(a0), r_t(a1));
      }
      else
      {
        r_t  that(logspace_sub(a0, a1));
        auto lsub = [](auto that_, auto next) -> r_t
          {
            that_ = logspace_sub(that_, next);
            return that_;
          };
        ((that = lsub(that, args)), ...);
        return that;
      }
    }
  }
}
