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
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/sqr.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/two_fma_approx.hpp>
#include <eve/module/core/detail/force_if_any.hpp>
#include <eve/module/core/constant/inf.hpp>

namespace eve
{
  template<typename Options>
  struct sum_of_squares_t : tuple_callable<sum_of_squares_t, Options, pedantic_option,
                                           saturated_option, lower_option, upper_option,
                                           strict_option, widen_option, kahan_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && !Options::contains(widen))
      EVE_FORCEINLINE common_value_t<T0, T1, Ts...> constexpr operator()(T0 t0, T1 t1, Ts...ts)
      const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && Options::contains(widen))
      EVE_FORCEINLINE common_value_t<upgrade_t<T0>, upgrade_t<T1>, upgrade_t<Ts>... >
    constexpr operator()(T0 t0, T1 t1, Ts...ts)
      const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }


    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(sum_of_squares_t, sum_of_squares_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sum_of_squares
//!   @brief `tuple_callable` object computing the sum_of_squares norm (\f$l_1\f$)  of its arguments.
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
//!      constexpr auto sum_of_squares(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto sum_of_squares(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sum_of_squares[saturated](/*any of the above overloads*/)                noexcept; // 3
//!      constexpr auto sum_of_squares[pedantic](/*any of the above overloads*/)                 noexcept; // 4
//!      constexpr auto sum_of_squares[kahan](/*any of the above overloads*/)                    noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!       1. The value of the sum of the squared values of the arguments is returned.
//!       2. equivalent to the call on the elements of the tuple.
//!       3. internally uses `saturated` options.
//!       4. returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
//!       5. uses kahan like compensated algorithm for better accuracy.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sum_of_squares.cpp}
//================================================================================================
  inline constexpr auto sum_of_squares = functor<sum_of_squares_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    sum_of_squares_(EVE_REQUIRES(cpu_), O const & o ,Ts... args) noexcept
    requires(O::contains(widen))
    {
      return sum_of_squares[o.drop(widen)](upgrade(args)...);
    }

    template<value T0, value... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    sum_of_squares_(EVE_REQUIRES(cpu_), O const & o , T0 a0, Ts... args) noexcept
    requires(!O::contains(widen))
    {
      using r_t = common_value_t<T0, Ts...>;
      if constexpr(sizeof...(Ts) == 0) return eve::sqr[o](a0);
      else if constexpr(O::contains(kahan))
      {
        auto pair_sqr_add = [](auto pair0, auto r1){
          auto [r0, e0] = pair0;
          auto [s, e1] = eve::two_fma_approx(r1, r1, r0);
          return zip(s, e0+e1);
        };
        auto p0   = two_prod(a0, a0);
        ((p0 = pair_sqr_add(p0,args)),...);
        auto [r, e] = p0;
        auto res = r+e;
        return force_if_any(o, res, eve::is_infinite, inf(as(res)), a0, args...);
      }
      else
      {
        auto l_sqr = [](){
          if constexpr(integral_value<r_t> && O::contains(saturated))
            return eve::sqr[saturated];
          else
            return eve::sqr;
        };
        r_t r = eve::add[o](l_sqr()(r_t(a0)), l_sqr()(r_t(args))...);
        if constexpr(integral_value<r_t>)
          return r;
        else
          return force_if_any(o, r, eve::is_infinite, inf(as(r)), a0, args...);
      }
    }
  }
}
