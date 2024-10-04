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
  struct min_t : tuple_callable<min_t, Options, pedantic_option, numeric_option>
  {
    template<value T, value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T t, U u) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T, U>), t, u);
    }

    template<value T0, value T1, value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
      requires(same_lanes_or_scalar<T0, T1, Ts...>)
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T0, T1, Ts...>), t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<common_value, Tup> operator()(Tup const& t) const noexcept 
      requires (same_lanes_or_scalar_tuple<Tup> && (kumi::size_v<Tup> >= 2))
    {
      return EVE_DISPATCH_CALL_PT((kumi::apply_traits_t<common_value, Tup>), t);
    }

    template<typename Callable>
    EVE_FORCEINLINE constexpr auto operator()(Callable const & f) const noexcept
      requires (!kumi::product_type<Callable> && !value<Callable>)
    {
      return EVE_DISPATCH_CALL(f);
    }

    EVE_CALLABLE_OBJECT(min_t, min_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var min
//!   @brief Computes the  minimum  of its arguments.
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
//!      constexpr auto min(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto min(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto min[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto min[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto min[pedantic](/* any of the above overloads */)                noexcept; // 4
//!      constexpr auto min[numeric ](/* any of the above overloads */)                noexcept; // 5
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...`:  [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!     1. the miniimal element is returned. If one of the elements is `NaN` the result is system dependant.
//!     2. equivalent to the call on the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional)
//!     4. Ensures conformity to the standard. That is for two parameters to be equivalent to:
//!       `(x < y) ? x : y` and this behaviour is also ensured on n parameters calls
//!       as if this scheme is recursively used.
//!     5. `NaNs` are considered greater than anything else.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/min.cpp}
//================================================================================================
  inline constexpr auto min = functor<min_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/min.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/min.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/min.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/min.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/min.hpp>
#endif
