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
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/is_infinite.hpp>

namespace eve
{
  template<typename Options>
  struct manhattan_t : tuple_callable<manhattan_t, Options, pedantic_option, saturated_option, lower_option,
                                upper_option, strict_option, kahan_option>
  {
    template<value T0, eve::value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0,T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(manhattan_t, manhattan_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var manhattan
//!   @brief `tuple_callable` object computing the manhattan norm (\f$l_1\f$)  of its arguments.
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
//!      constexpr auto manhattan(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto manhattan(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto manhattan[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto manhattan[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto manhattan[saturated](/*any of the above overloads*/)                noexcept; // 4
//!      constexpr auto manhattan[pedantic](/*any of the above overloads*/)                 noexcept; // 5
//!      constexpr auto manhattan[kahan](/*any of the above overloads*/)                    noexcept; // 6
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
//!       1. The value of the sum of the absolute value of the arguments is returned.
//!       2. equivalent to the call on the elements of the tuple.
//!       3. [The operation is performed conditionnaly](@ref conditional)
//!       4. internally uses `saturated` options.
//!       5. returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
//!       6. uses kahan compensated algorihtm for better accuracy.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/manhattan.cpp}
//================================================================================================
  inline constexpr auto manhattan = functor<manhattan_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    manhattan_(EVE_REQUIRES(cpu_), O const &, T a0) noexcept
    {
      if constexpr (!O::contains(saturated) || floating_value<T>)
        return eve::abs(a0);
      else
        return eve::abs[saturated](a0);
    }

    template<typename T0,typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    manhattan_(EVE_REQUIRES(cpu_), O const & o , T0 a0, T1 a1, Ts... args) noexcept
    {
      using r_t = common_value_t<T0, T1, Ts...>;
      auto l_abs = [](){
        if constexpr(integral_value<r_t> && O::contains(saturated))
        return eve::abs[saturated];
        else
          return eve::abs;
      };
      r_t r;
      r = eve::add[o](l_abs()(r_t(a0)), l_abs()(r_t(a1)), l_abs()(r_t(args))...);
      if constexpr(O::contains(pedantic))
      {
        auto inf_found = is_infinite(r_t(a0)) || is_infinite(r_t(a1));
        inf_found =  (inf_found || ... || is_infinite(r_t(args)));
        return if_else(inf_found, inf(as(r)), r);
      }
      else
        return r;
    }
  }
}
