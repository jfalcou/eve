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

namespace eve
{
  template<typename Options>
  struct negminabs_t : tuple_callable<negminabs_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<value T0, value T1, value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
      requires (same_lanes_or_scalar<T0, T1, Ts...>)
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T0, T1, Ts...>), t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<common_value, Tup> operator()(Tup t) const noexcept
      requires (same_lanes_or_scalar_tuple<Tup> && (kumi::size_v<Tup> >= 2))
    {
      return EVE_DISPATCH_CALL_PT((kumi::apply_traits_t<common_value, Tup>), t);
    }

    EVE_CALLABLE_OBJECT(negminabs_t, negminabs_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negminabs
//!   @brief  `tuple_callable` computing the negated value of the element of minimal absolute value.
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
//!      constexpr auto negminabs(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto negminabs(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto negminabs[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto negminabs[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Semantic option
//!      constexpr auto negminabs[saturated](/* any of the above overloads */)               noexcept; // 4
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto negminabs[pedantic](/* any of the above overloads */)                noexcept; // 5.1
//!      constexpr auto negminabs[numeric ](/* any of the above overloads */)                noexcept; // 5.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      The negated value of the element of minimal  absolute value is returned.
//!        1. If any element of the inputs is a NaN the corresponding output element is system-dependent
//!        2. equivalent to the call on the elements of the tuple.
//!        3. [The operation is performed conditionnaly](@ref conditional)
//!        4. computation internally uses `abs[saturated]` instead of `abs`
//!        5. with `numeric` (resp. `pedantic`) `max[numeric]` (5.1) (resp. `max[pedantic]` (5.2))
//!           is used internally
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/negminabs.cpp}
//================================================================================================
  inline constexpr auto negminabs = functor<negminabs_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/negminabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negminabs.hpp>
#endif
