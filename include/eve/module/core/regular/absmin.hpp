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
  struct absmin_t : tuple_callable<absmin_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(absmin_t, absmin_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var absmin
//!   @brief Computes the absolute value of the minimal element
//!
//!   This is equivalent to eve::abs ( eve::min(...) ). but can be subject to optimizations.
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
//!      constexpr auto absmin(value auto x, value auto ... xs)                       noexcept;  // 1
//!      constexpr auto absmin[conditional auto c](value auto x, value auto ... xs)   noexcept;  // 2
//!      constexpr auto absmin[logical_value auto m](value auto x, value auto ... xs) noexcept;  // 2
//!      constexpr auto absmin[saturated](value auto x, value auto ... xs)            noexcept;  // 3
//!      constexpr auto absmin[numeric] (value auto x, value auto ... xs)             noexcept;  // 4.1
//!      constexpr auto absmin[pedantic] (value auto x, value auto ... xs)            noexcept;  // 4.2
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
//!    The absolute value of the minimal element is returned.
//!    1. equivalent to `abs(min(...)`
//!    2. masked call
//!    3. computation uses internally  abs[saturated] instead of abs
//!    4. with numeric (resp. pedantic) min[numeric] (4.1) (resp. min[pedantic] (4.2)) is used internally
//!
//!    @note
//!      - If any element of the inputs is a NaN the corresponding output element is system-dependent.
//!      - saturated, and  pedantic or numeric are not incompatible,  but first one if of no use if the
//!        parameter common type is floating point the last two have no influence
//!        if the parameter common_type is not floating point.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/absmin.cpp}
//!
//! @}
//================================================================================================

inline constexpr auto absmin = functor<absmin_t>;
}

#include <eve/module/core/regular/impl/absmin.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmin.hpp>
#endif
