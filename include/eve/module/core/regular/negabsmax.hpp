//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{

  template<typename Options>
  struct negabsmax_t : elementwise_callable<negabsmax_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::ordered_value T0, ordered_value T1, ordered_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(negabsmax_t, negabsmax_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negabsmax
//!   @brief Computes the negated absolute value of the maximal element
//!
//!   This is equivalent to -eve::abs ( eve::max(...) ). but can be subject to optimizations.
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
//!      eve::common_value_t<T, Ts ...> negabsmax( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The negated absolute value of the maximal element
//!    is returned.
//!
//!    @note
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/negabsmax.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::negabsmax[mask](x, ...)` provides a masked version of `eve::negabsmax` which
//!     is equivalent to `eve::if_else (mask, negabsmax(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/negabsmax.cpp}
//!
//!   * eve::pedantic,  eve::numeric
//!
//!     The call `d(eve::negabsmax)(...)`, where d is one of these two decorators, is equivalent to
//!     `-eve::abs (d( eve::max )(...))`.
//!
//! @}
//================================================================================================
inline constexpr auto negabsmax = functor<negabsmax_t>;
}

#include <eve/module/core/regular/impl/negabsmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negabsmax.hpp>
#endif
