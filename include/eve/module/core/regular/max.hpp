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
  struct max_t : tuple_callable<max_t, Options, pedantic_option, numeric_option>
  {
    template<eve::value T, value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T t, U u) const noexcept { return EVE_DISPATCH_CALL(t, u); }

    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const & t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    template<typename Callable>
    requires(!kumi::product_type<Callable> && !eve::value<Callable>)
    EVE_FORCEINLINE constexpr auto operator()(Callable const & f) const noexcept { return EVE_DISPATCH_CALL(f); }

    EVE_CALLABLE_OBJECT(max_t, max_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var max
//!   @brief Computes the  maximum  of its arguments.
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
//!      constexpr auto max(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto max(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto max[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto max[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto max[pedantic](/* any of the above overloads */)                noexcept; // 4
//!      constexpr auto max[numeric ](/* any of the above overloads */)                noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!     1. the maximal element is returned. If one of the elements is `NaN` the result is system dependant.
//!     2. equivalent to the call on the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional)
//!     4. Ensures conformity to the standard. That is for two parameters to be equivalent to:
//!       `(x < y) ? y : x` and this behaviour is also ensured on n parameters calls
//!       as if this scheme is recursively used.
//!     5. `NaNs` are considered less than anything else.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/max.cpp}
//! @}
//================================================================================================
inline constexpr auto max = functor<max_t>;
}

#include <eve/module/core/regular/impl/max.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/max.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/max.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/max.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/max.hpp>
#endif
