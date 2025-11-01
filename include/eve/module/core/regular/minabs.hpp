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
  struct minabs_t : tuple_callable<minabs_t, Options, numeric_option, widen_option,
                                   pedantic_option, saturated_option>
  {
//     template<value... Ts>
//     requires(eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen))
//     EVE_FORCEINLINE constexpr common_value_t<Ts...> operator()(Ts...ts) const noexcept
//     {
//       return EVE_DISPATCH_CALL(ts...);
//     }

//     template<value... Ts>
//     requires(eve::same_lanes_or_scalar<Ts...> && Options::contains(widen))
//     EVE_FORCEINLINE constexpr upgrade_t<common_value_t<Ts...>> operator()(Ts...ts) const noexcept
//     {
//       return EVE_DISPATCH_CALL(ts...);
//     }

    template<value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    EVE_FORCEINLINE constexpr upgrade_if_t<Options, common_value_t<Ts...>> operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
//     EVE_FORCEINLINE constexpr  kumi::apply_traits_t<eve::common_value,Tup>
//     operator()(Tup t) const noexcept
//     { return EVE_DISPATCH_CALL(t); }

//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
//     EVE_FORCEINLINE constexpr  upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>
//     operator()(Tup t) const noexcept
//     { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr  upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup t) const noexcept
    { return EVE_DISPATCH_CALL(t); }


    EVE_CALLABLE_OBJECT(minabs_t, minabs_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minabs
//!   @brief Computes the  minimum  of the absolute value of its arguments.
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
//!      constexpr auto minabs(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto minabs(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto minabs[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto minabs[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto minabs[pedantic](/* any of the above overloads */)                noexcept; // 4
//!      constexpr auto minabs[numeric ](/* any of the above overloads */)                noexcept; // 5
//!      constexpr auto minabs[widen](/* any of the above overloads */)                   noexcept; // 6
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...`: [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!     1. the value of the minimum of the absolute values is returned. If one of the elements
//!        is `NaN` the result is system dependant.
//!     2. equivalent to the call on the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional)
//!     4. Ensures conformity to the standard. That is for two parameters to be equivalent to:
//!        `(|x| < |y|) ? |x| : |y|` and this behaviour is also ensured on n parameters calls
//!        as if this scheme was recursively used.  If one of the arguments is \f$\pm0\f$
//!        returns \f$0\f$ even if some other arguments are NaNs.
//!     5. `NaNs` are considered greater than anything else.
//!     6. compute the upgraded result if available.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/minabs.cpp}
//================================================================================================
  inline constexpr auto minabs = functor<minabs_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/minabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minabs.hpp>
#endif
