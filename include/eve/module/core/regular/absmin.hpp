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
//!      template< eve::value T,  eve::value... Ts>
//!      eve::common_value_t<T, Ts ...> absmin( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [real arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The absolute value of the minimal element
//!    is returned.
//!
//!    @note
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/absmin.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::absmin[mask](x, ...)` provides a masked version of `eve::absmin` which is
//!     equivalent to `eve::if_else (mask, absmin(x, ...), x)`
//!
//!   * eve::pedantic,  eve::numeric, eve::saturated
//!
//!     The call `eve::absmin[d](...)`, where d is one of these two first decorators, is equivalent to
//!     `eve::abs (d( eve::min )(...))`.
//!
//!     The call `eve::absmin[d][saturated](...)`, where d is one of these two first decorators or is not present, is equivalent to
//!     `eve::abs[saturated](d( eve::min )(...))`.
//!
//! @}
//================================================================================================
inline constexpr auto absmin = functor<absmin_t>;
}

#include <eve/module/core/regular/impl/absmin.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmin.hpp>
#endif
