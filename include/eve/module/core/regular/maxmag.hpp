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
  struct maxmag_t : tuple_callable<maxmag_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(maxmag_t, maxmag_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var maxmag
//!   @brief Computes the  maximum  of the absolute value of its arguments.
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
//!      template< eve::value T, eve::value... Ts >
//!      eve::common_value_t<T, Ts...> maxmag(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [real](@ref eve::value) arguments.
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) element of greatest absolute value is
//!      returned.
//!
//!      For instance for two elements:
//!
//!        * If `|x| >  |y|`,  `x` is returned.
//!        * If `|x| <  |y|`,  `y` is returned.
//!        * Otherwise `max(x, y)` is returned.
//!
//!      For n parameters the result is computed as if this scheme was recursively used.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/maxmag.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::maxmag[mask](x, ...)` provides a masked
//!     version of `maxmag` which is
//!     equivalent to `if_else(mask, maxmag(x, ...), x)`
//!
//!   * eve::pedantic, eve::numeric
//!
//!     The behaviour of d(eve::maxmag)(x, y) (where d is one of these two decorators
//!     is identical except that if  `|x| == |y|`, `d(max)` is used.
//!
//! @}
//================================================================================================
inline constexpr auto maxmag = functor<maxmag_t>;
}

#include <eve/module/core/regular/impl/maxmag.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/maxmag.hpp>
#endif
