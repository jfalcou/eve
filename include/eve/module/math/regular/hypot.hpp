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

namespace eve
{
  template<typename Options>
  struct hypot_t : tuple_callable<hypot_t, Options, raw_option, pedantic_option, kahan_option, widen_option>
  {

    template<value... Ts>
    requires((sizeof...(Ts) !=  0) && eve::same_lanes_or_scalar<Ts...>)
      EVE_FORCEINLINE constexpr upgrade_if_t<Options, common_value_t<Ts...>> operator()(Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(ts...); }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const & t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(hypot_t, hypot_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var hypot
//! @brief `tuple_callable` computing the \f$l_2\f$ norm of its inputs.
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
//!      constexpr auto hypot(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto hypot(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto hypot[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto hypot[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto hypot[raw](/*any of the above overloads*/)                      noexcept; // 4
//!      constexpr auto hypot[pedantic](/*any of the above overloads*/)                 noexcept; // 5
//!      constexpr auto hypot[kahan](/*any of the above overloads*/)                    noexcept; // 6
//!      constexpr auto hypot[widen](/*any of the above overloads*/)                    noexcept; // 7
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
//!    1. Returns  \f$\displaystyle\sqrt{\sum_1^n |x_i|^2}\f$. (naive formula)
//!        The result type is the [common value type](@ref common_value_t) of the
//!        absolute values of the parameters. (Some appropriate scaling is done to enhance precision
//!        and avoid overflows.
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. the naive formula is used.
//!    5. The pedantic option` computes the result without undue overflow or underflow
//!        at intermediate stages of the computation and can be more accurate than the regular call.
//!    6. A kahan like compensated algorithm  is used internal for more accurate results.
//!    7. The computation is done in the double sized element type (if available).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/hypot)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Pythagorean_addition)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/hypot.cpp}
//================================================================================================
  inline constexpr auto hypot = functor<hypot_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T0, callable_options O>
    EVE_FORCEINLINE constexpr auto
    hypot_(EVE_REQUIRES(cpu_), O const &, T0 a0) noexcept
    {
      if constexpr(!O::contains(widen))
        return abs(a0);
      else
        return abs(upgrade(a0));
    }

    template<typename T0, typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    hypot_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
    {
      using r_t = common_value_t<T0, T1, Ts...>;
      using e_t = element_type_t<r_t>;
      if constexpr(O::contains(widen))
        return hypot[o.drop(widen)](upgrade(r0), upgrade(r1), upgrade(rs)...);
      else if constexpr(sizeof...(Ts) == 0) // 2 parameters
      {
        if constexpr(O::contains(pedantic))
        {
          ////////////////////////////////////////////////////////////////////////////////////////////////////
          //  This implementation is inspired by
          //  AN IMPROVED ALGORITHM FOR HYPOT(A,B) arXiv:1904.09481v6 [math.NA] 14 Jun 2019, CARLOS F. BORGES
          ////////////////////////////////////////////////////////////////////////////////////////////////////
          using eve::abs;
          r_t ax(abs(r0));
          r_t ay(abs(r1));
          auto test = ax > ay;
          eve::swap_if(test, ax, ay); // now 0 <= ax <= ay
          constexpr auto rsqspvo4 = 1/(sqrtsmallestposval(as<e_t>()));
          auto scale = if_else(ax > sqrtvalmax(as(ax)), sqrtsmallestposval(as<r_t>())/4
                              , if_else(ay < sqrtsmallestposval(as(ay)), rsqspvo4
                                        ,  one)
                              );
          ax *= scale;
          ay *= scale;
          auto h = sqrt(fma(ax,ax,ay*ay));
          auto h2 = sqr(h);
          auto ax2 = sqr(ax);
          auto x = fma(-ay,ay,h2-ax2) + fma(h,h,-h2) - fma(ax,ax,-ax2);
          h-= x/(2*h);
          h /= scale;
          h = if_else(is_eqz(ay), zero, h);
          h = if_else(ax <= ay*eve::sqrteps(as<r_t>()), ay, h);
          h = if_else(is_infinite(ax) || is_infinite(ay), inf(as<r_t>()), h);
          return h;
        }
        else if constexpr(O::contains(raw))
        {
          //naive fast computation
          return eve::sqrt(eve::sum_of_prod(r0, r0, r1, r1));
        }
        else
        {
          // scaling using the algorithm suggested by
          // https://members.loria.fr/PZimmermann/papers/split.pdf
          auto d = eve::safe_scale(average(eve::abs(r0), eve::abs(r1)));
          auto id= eve::rec(d);
          auto r0d = r0*id;
          auto r1d = r1*id;
          auto r = d*eve::sqrt(eve::sum_of_prod[pedantic](r0d, r0d, r1d, r1d));
          return if_else(is_infinite(r0) || is_infinite(r1), inf(as(r)), r);
        }
      }
      else //N parameters
      {
        if constexpr(O::contains(pedantic))
        {
          r_t that(hypot[o](r_t(r0), r_t(r1)));
          ((that = hypot[o](that, r_t(rs))), ...);
          return that;
        }
        else
        {
          r_t that = sum_of_squares[o](r_t(r0), r_t(r1), r_t(rs)...);
          return eve::sqrt(that);
        }
      }
    }
  }
}
