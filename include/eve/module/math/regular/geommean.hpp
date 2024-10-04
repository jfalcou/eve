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
  struct geommean_t : tuple_callable<geommean_t, Options, pedantic_option>
  {
    template<floating_value T0, floating_value T1, floating_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
      requires (same_lanes_or_scalar<T0, T1, Ts...>)
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T0, T1, Ts...>), t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<common_value, Tup> operator()(Tup const& t) const noexcept 
      requires (same_lanes_or_scalar_tuple<Tup> && (kumi::size_v<Tup> >= 2))
    {
      return EVE_DISPATCH_CALL_PT((kumi::apply_traits_t<common_value, Tup>), t);
    }

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
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!     * `x`, `...xs`: [real](@ref value) arguments.
  //!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. The geometric mean of the inputs is returned
  //!    2. equivalent to the call on the elements of the tuple.
  //!    3. [The operation is performed conditionnaly](@ref conditional)
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
    template<typename T0,typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    geommean_(EVE_REQUIRES(cpu_), O const & o, T0 a0, T1 a1, Ts... args) noexcept
    {

      using r_t   = common_value_t<T0, T1, Ts...>;
      using elt_t = element_type_t<r_t>;
      constexpr std::uint64_t sz = sizeof...(Ts);
      if constexpr(sz == 0)
      {
        auto a = r_t(a0);
        auto b = r_t(a1);
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
        elt_t invn  = rec[pedantic](elt_t(sizeof...(args) + 2u));
        if (O::contains(pedantic))
        { //perhaps this is always more efficient TODO bench it
          auto e  = -maxmag(exponent(r_t(a0)), exponent(r_t(a1)), exponent(r_t(args))...);
          auto p  = mul( r_t(ldexp[o](a0, e)), r_t(ldexp[o](a1, e)), r_t(ldexp[o](args, e))...);
          auto sgn = sign(p);
          p = pow_abs(p, invn);
          p = ldexp[pedantic](p, -e);
          return if_else(eve::is_even(sz) && is_ltz(sgn), eve::allbits, sgn * p);
        }
        else
        {
          r_t   that(pow_abs(r_t(a0), invn) * pow_abs(r_t(a1), invn));
          r_t   sgn  = sign(r_t(a0)) * sign(r_t(a1));
          auto  next = [&](auto avg, auto x){
            sgn *= sign(x);
            return avg * pow_abs(r_t(x), invn);
          };
          ((that = next(that, args)), ...);
          return if_else(eve::is_even(sz) && is_ltz(sgn), eve::allbits, sgn * that);
        }
      }
    }
  }
}
