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
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/rec.hpp>
#include <eve/module/core/regular/two_fma_approx.hpp>

namespace eve
{
  template<typename Options>
  struct variance_t : tuple_callable<variance_t, Options, raw_option, kahan_option, widen_option, unbiased_option>
  {
    template<value... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr common_value_t<Ts...>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<value... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<Ts...> && Options::contains(widen))
      EVE_FORCEINLINE constexpr common_value_t<eve::upgrade_t<Ts>...>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<integral_value T0,  integral_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
      EVE_FORCEINLINE common_value_t<T0, T1>
    constexpr operator()(T0 t0, T1 t1)
      const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(variance_t, variance_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var variance
//!   @brief `tuple_callable` computing the variance of its arguments.
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
//!      // Regular overloads
//!      constexpr auto variance(eve::floating_value auto x, eve::floating_value auto ... xs)        noexcept; // 1
//!      constexpr auto variance(kumi::non_empty_product_type auto const& tup)                       noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto variance[conditional_expr auto c](/* any of the above overloads */)          noexcept; // 3
//!      constexpr auto variance[logical_value auto m](/* any of the above overloads */)             noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto variance[raw] (/* any of the above overloads */)                             noexcept; // 4
//!      constexpr auto variance[widen](/* any of the above overloads */)                            noexcept; // 5
//!      constexpr auto variance[kahan](/* any of the above overloads */)                            noexcept; // 6
//!      constexpr auto variance[unbiased](/* any of the above overloads */)                         noexcept; // 7
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs...`: [floating value](@ref eve::floating_value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    The value of the variance of the arguments is returned.
//!
//!     1. the  computation of the variance of its arguments.
//!     2. the  computation of  the tuple arguments.
//!     3. [The operation is performed conditionnaly](@ref conditional)
//!     4. No provision is made to avoid inaccuracies.
//!     5. The variance is computed in the double sized element type (if available).
//!     6. Compensated algorithm for better precision.
//!     7. the normalizing factor N-1 instead of N to get the best unbiased estimate.
//!
//!
//!  @groupheader{External references}
//!   *  [Wikipedia Variance](https://en.wikipedia.org/wiki/Variance)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/variance.cpp}
//================================================================================================
  inline constexpr auto variance = functor<variance_t>;
//================================================================================================
//! @}
//================================================================================================

}

namespace eve::detail
{

  template<value T0, value ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  variance_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  {
    constexpr auto siz = sizeof...(Ts)+1;
    if constexpr(O::contains(unbiased))
    {
      if constexpr(siz == 1) return eve::zero(eve::as(a0));
      else return (variance[o.drop(unbiased)](upgrade(a0), upgrade(args)...)*siz)/(siz-1);
    }
    else if constexpr(O::contains(widen))
    {
      return variance[o.drop(widen)](upgrade(a0), upgrade(args)...);
    }
    else if constexpr(sizeof...(Ts) == 0)
      return a0;
    else
    {
      auto avg = eve::average[o](a0,  args...);
      auto var = eve::average[o](eve::sqr(a0-avg), eve::sqr(args-avg)...);
      if constexpr(O::contains(raw))
        return var;
      else
        return var - eve::sqr(eve::average(a0-avg, (args-avg)...));
    }
  }
}
