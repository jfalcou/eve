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
  struct absmax_t : tuple_callable<absmax_t, Options, numeric_option, pedantic_option,
                                   saturated_option>
  {
    template<eve::value T0, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, Ts...>
    operator()(T0 t0, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(absmax_t, absmax_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var absmax
//!   @brief `tuple_callable` computing the absolute value of the maximal element.
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
//!      constexpr auto absmax(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto absmax(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto absmax[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto absmax[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Semantic option
//!      constexpr auto absmax[saturated](/* any of the above overloads */)               noexcept; // 4
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto absmax[pedantic](/* any of the above overloads */)                noexcept; // 5.1
//!      constexpr auto absmax[numeric ](/* any of the above overloads */)                noexcept; // 5.2
//!   }
//!   @endcode
//!
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      The absolute value of the maximal element is returned.
//!        1. If any element of the inputs is a NaN the corresponding output element is system-dependent
//!        2. equivalent to the call on the elements of the tuple.
//!        3. [The operation is performed conditionnaly](@ref conditional)
//!        4. computation internally uses `abs[saturated]` instead of `abs`
//!        5. with `numeric` (resp. `pedantic`) `max[numeric]` (5.1) (resp. `max[pedantic]` (5.2))
//!           is used internally
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/absmax.cpp}
//================================================================================================
  inline constexpr auto absmax = functor<absmax_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/absmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmax.hpp>
#endif
