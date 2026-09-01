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

    template<eve::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const & t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(hypot_t, hypot_);
  };

//================================================================================================
//! @addtogroup eve_math_exp
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
//!      constexpr auto hypot(eve::non_empty_product_type auto const& tup)             noexcept; // 2
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
//!    * `tup`: [non empty tuple](@ref kumi::concepts::non_empty_product_type) of arguments.
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
//!    3. [The operation is performed conditionally](@ref conditional)
//!    4. the naive formula is used.This option is faster, but does not care about avoiding overflows
//!       or treating 'Nans' in special ways.
//!    5. The pedantic option. returns \f$\infty\f$ as soon as after disabling possible `Nan` parameters
//!       the result is \f$\infty\f$,  and computes the result without undue overflows or underflows.
//!        at intermediate stages of the computation.
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

  namespace _
  {
    template<callable_options O, typename... Ts>
    EVE_FORCEINLINE constexpr auto hypot_(EVE_REQUIRES(emulated_), O const & o, Ts... ts) noexcept
    requires (O::contains(widen) && _::fp16_should_apply<common_value_t<Ts...>>)
    {
      return hypot[o.drop(widen)](upgrade(ts)...);
    }

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
      if constexpr(std::same_as<e_t, eve::float16_t>)
      {
        return eve::_::apply_fp16_as_fp32(eve::hypot[o],r0, r1, rs...);
      }
      else
      {
        if constexpr(O::contains(raw))
        {
          r_t that = sum_of_squares[o](r_t(r0), r_t(r1), r_t(rs)...);
          return eve::sqrt(that);
        }
        else
        {
          auto expo = [&](auto x){return if_else(is_nan(x), zero, exponent(r_t(x))); };
          auto e  = -maxmag(expo(r0), expo(r1), expo(rs)...);
          auto s2 = sum_of_squares[o](ldexp[o](r_t(r0), e), ldexp[o](r_t(r1), e), ldexp[o](r_t(rs), e)...);
          return ldexp[o](sqrt(s2), -e);
        }
      }
    }
  }
}
