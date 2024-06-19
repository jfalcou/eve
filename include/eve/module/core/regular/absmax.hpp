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
  struct absmax_t : tuple_callable<absmax_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(absmax_t, absmax_);
  };

//================================================================================================

//! @addtogroup core_arithmetic
//! @{
//!   @var absmax
//!   @brief Computes the absolute value of the maximal element
//!
//!   This is equivalent to eve::abs ( eve::max(...) ). but can be subject to optimizations.
//!
//!   **Defined in Header**
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
//!      constexpr auto absmax(value auto x, value auto ... xs)                       noexcept;  // 1
//!      constexpr auto absmax[conditional auto c](value auto x, value auto ... xs)   noexcept;  // 2
//!      constexpr auto absmax[logical_value auto m](value auto x, value auto ... xs) noexcept;  // 2
//!      constexpr auto absmax[saturated](value auto x, value auto ... xs)            noexcept;  // 3
//!      constexpr auto absmax[numeric] (value auto x, value auto ... xs)             noexcept;  // 4.1
//!      constexpr auto absmax[pedantic] (value auto x, value auto ... xs)            noexcept;  // 4.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [real](@ref value) arguments.
//!     * `c` : [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m` : [Logical value](logical) masking the operation.
//!
//!    **Return value**
//!
//!    The absolute value of the maximal element is returned.
//!    1. equivalent to `abs(max(...)`
//!    2. masked call
//!    3. computation uses internally  abs[saturated] instead of abs
//!    4. with numeric (resp. pedantic) max[numeric] (4.1) (resp. max[pedantic] (4.2)) is used internally
//!
//!    @note
//!      - If any element of the inputs is a NaN the corresponding output element is system-dependent.
//!      - saturated, and  pedantic or numeric are not incompatible,  but first one if of no use if the
//!        parameter common type is floating point the last two have no influence
//!        if the parameter common_type is not floating point.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/absmax.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto absmax = functor<absmax_t>;
}

#include <eve/module/core/regular/impl/absmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmax.hpp>
#endif
