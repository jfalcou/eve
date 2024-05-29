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
//!      template< eve::value T,  eve::value... Ts>
//!      eve::common_value_t<T, Ts ...> absmax( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [real](@ref eve::value) arguments.
//!
//!    **Return value**
//!
//!    The absolute value of the maximal element is returned.
//!
//!    @note
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/absmax.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::absmax[mask](x, ...)` provides a masked version of `eve::absmax` which is
//!     equivalent to `eve::if_else (mask, absmax(x, ...), x)`
//!
//!   * eve::pedantic, eve::numeric, eve::saturated
//!
//!     The call `eve::absmax[d](...)`, where d is one of these two first decorators, is equivalent to
//!     `eve::abs (d( eve::max )(...))`.
//!
//!     The call `eve::absmax[d][saturated](...)`, where d is one of these two first decorators or is not present, is equivalent to
//!     `eve::abs[saturated](d( eve::max )(...))`.
//!
//! @}
//================================================================================================
inline constexpr auto absmax = functor<absmax_t>;
}

#include <eve/module/core/regular/impl/absmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmax.hpp>
#endif
