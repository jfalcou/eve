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
  struct hypot_t : tuple_callable<hypot_t, Options, pedantic_option>
  {
    template<eve::ordered_value T0, ordered_value T1, ordered_value... Ts>
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
//!
//! @brief Callable object computing the \f$l_2\f$ norm of its inputs.
//!
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
//!      template< value T, value ... Ts>
//!      auto hypot( T x,Ts ... args ) const noexcept
//!   }
//!   @endcode
//!
//!
//! **Parameters**
//!
//!   `x`, `... args`:   [floating real values](@ref eve::floating_value)
//!
//! **Return value**
//!
//!   \f$\sqrt{\sum_1^n |x_i|^2}\f$ is returned.
//!   The result type is the [common value type](@ref common_value_t) of the
//!   absolute values of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/hypot.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!    * eve::pedantic
//!
//!      The call `pedantic(hypot)(x,args...)`  computes the square root of the sum of
//!      the absolute squares of the parameters
//!      without undue overflow or underflow at intermediate stages of the computation
//!      and can be more accurate than the non-decorated call.
//!
//!      Morever it returns \f$\infty\f$ as soon as one of its parameter is infinite,
//!      regardless of possible `Nan` values.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/pedantic/hypot.cpp}
//!  @}
//================================================================================================
  inline constexpr auto hypot = functor<hypot_t>;

  namespace detail
  {
    template<typename T0, typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    hypot_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
    {
      using r_t = common_value_t<T0, T1, Ts...>;
      using e_t = element_type_t<r_t>;
      if constexpr( has_native_abi_v<r_t> )
      {
        if constexpr(sizeof...(Ts) == 0) // 2 parameters
        {
          if constexpr(O::contains(pedantic2))
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
          else
          {
            return eve::sqrt(add(sqr(r_t(r0)), sqr(r_t(r1))));
          }
        }
        else //N parameters
        {
          if constexpr(O::contains(pedantic2))
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
      else
        return apply_over(hypot[o], r_t(r0), r_t(r1), r_t(rs)...);
    }
  }
}
