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
  struct hypot_t : tuple_callable<hypot_t, Options, raw_option, pedantic_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(t0,  t1, ts...); }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const & t) const noexcept
    requires(kumi::size_v<Tup> >= 2)
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
//!    1. Returns  \f$\displaystyle\sqrt{\sum_1^n |x_i|^2}\f$.
//!        The result type is the [common value type](@ref common_value_t) of the
//!        absolute values of the parameters. (Some appropriate scaling is done to enhance precision
//!        and avoid overflows.
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. the naive formula is used.
//!    5. The pedantic option`  computes the result without undue overflow or underflow
//!        at intermediate stages of the computation and can be more accurate than the regular call.
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
    template<typename T0, typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    hypot_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
    {
      using r_t = common_value_t<T0, T1, Ts...>;
      using e_t = element_type_t<r_t>;
      if constexpr(sizeof...(Ts) == 0) // 2 parameters
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
          auto d = eve::scale(average(eve::abs(r0), eve::abs(r1)));
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
          r_t that = add(sqr(r_t(r0)), sqr(r_t(r1)), sqr(r_t(rs))...);
          return eve::sqrt(that);
        }
      }
    }
  }
}
