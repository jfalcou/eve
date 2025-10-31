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
#include <eve/module/core/detail/force_if_any.hpp>
#include <eve/module/core/constant/inf.hpp>

namespace eve
{
  template<typename Options>
  struct manhattan_t : tuple_callable<manhattan_t, Options, pedantic_option, saturated_option, lower_option,
                                upper_option, strict_option, widen_option, kahan_option>
  {

    template<value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) != 0))
      EVE_FORCEINLINE upgrade_if_t<Options, common_value_t<Ts...>>
    constexpr operator()(Ts...ts)
      const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE constexpr
    upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

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
//!       6. uses kahan like compensated algorithm for better accuracy.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia taxicab norm](https://en.wikipedia.org/wiki/Norm_(mathematics))

//!  @groupheader{Example}
//!  @godbolt{doc/core/manhattan.cpp}
//================================================================================================
  inline constexpr auto manhattan = functor<manhattan_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    manhattan_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    {
      if constexpr(O::contains(widen))
        return manhattan[o.drop(widen)](upgrade(args)...);
      else
      {
        using r_t = common_value_t<Ts...>;
        auto l_abs = [](){
          if constexpr(integral_value<r_t> && O::contains(saturated))
          return eve::abs[saturated];
          else
            return eve::abs;
        }();
        if constexpr(sizeof...(Ts) == 1)
          return l_abs(args...);
        else
        {
          r_t r = eve::add[o](l_abs(r_t(args))...);
          if constexpr(integral_value<r_t>)
            return r;
          else
            return force_if_any(o, r, eve::is_infinite, inf(as(r)), args...);
        }
      }
    }
  }
}
