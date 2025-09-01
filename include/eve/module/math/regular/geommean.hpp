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
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve
{
  template<typename Options>
  struct geommean_t : tuple_callable<geommean_t, Options, pedantic_option, widen_option, kahan_option>
  {
    template<floating_value... Ts>
    requires(sizeof...(Ts) != 0 && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr common_value_t<Ts...> operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<floating_value... Ts>
    requires(sizeof...(Ts) != 0 && eve::same_lanes_or_scalar<Ts...> && Options::contains(widen))
      EVE_FORCEINLINE constexpr upgrade_t<common_value_t<Ts...>> operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(geommean_t, geommean_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var geommean
//!
//! @brief Callable object computing the geometric mean of the inputs.\f$ \left(\prod_{i = 1}^n
//! x_i\right)^{1/n} \f$.
//!
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
//!      // Regular overloads
//!      constexpr auto geommean(floating_value auto x, floating_value auto ... xs)        noexcept; // 1
//!      constexpr auto geommean(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto geommean[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto geommean[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto geommean[kahan](/*any of the above overloads*/)                    noexcept; // 4
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`, `...xs`: [real](@ref eve::value) arguments.
//!    * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. The geometric mean of the inputs is returned
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. uses kahan like compensated algorithm for better accuracy.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/geommean.cpp}
//================================================================================================
  inline constexpr auto geommean = functor<geommean_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T0, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    geommean_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts... args) noexcept
    {
      using r_t   = common_value_t<Ts...>;
      using elt_t = element_type_t<r_t>;
      constexpr std::uint64_t sz = sizeof...(Ts)+1;
      if constexpr(O::contains(widen))
        return geommean[o.drop(widen)](upgrade(a0), upgrade(args)...);
      else if constexpr(sz == 1)
        return a0;
      else if constexpr(sz == 2)
      {
        auto a = r_t(a0);
        auto b = r_t(args...);
        if (O::contains(pedantic))
        {
          auto m  = max(a, b);
          auto im = if_else(is_nez(m), rec[pedantic](m), m);
          auto z  = min(a, b) * im;
          return if_else(is_nltz(a) || is_nltz(b), sqrt(z) * m, allbits);
        }
        else
        {
          return if_else(is_nltz(sign(a)*sign(b)), sqrt(abs(a))*sqrt(abs(b)), allbits);
        }
      }
      else
      {
        elt_t invn  = rec(elt_t(sz));
        auto e  = -maxmag(exponent(r_t(a0)), exponent(r_t(args))...);
        auto p  = mul[o]( r_t(ldexp[o](a0, e)), r_t(ldexp[o](args, e))...);
        auto sgn = sign(p);
        p = pow_abs(p, invn);
        p = ldexp[pedantic](p, -e);
        return if_else(eve::is_even(sz) && is_ltz(sgn), eve::allbits, sgn * p);
      }
    }
  }
}
