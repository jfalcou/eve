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
#include <eve/traits/bit_value.hpp>

namespace eve
{
  template<typename Options>
  struct bit_and_t : strict_tuple_callable<bit_and_t, Options>
  {
    template<eve::value T0, value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
    EVE_FORCEINLINE constexpr bit_value_t<T0, T1>
    operator()(T0 t0, T1 t1) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
    operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::bit_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(bit_and_t, bit_and_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_and
//!   @brief Computes the bitwise AND of its arguments.
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
//!      template< eve::value T, eve::value Ts... >
//!      bit_value<T, Ts...> bit_and(T x, Ts... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:       first [argument](@ref eve::value).
//!     * `xs...` :  other [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the bitwise AND of its arguments converted to the bit_value<T,  Ts...>
//!      type is returned.
//!
//!    @note
//!
//!      Although the infix notation with `&` is supported for two parameters, the `&` operator on
//!      standard scalar types is the original one and so can lead to automatic promotion.
//!      Moreover, and due to C++ limitations is not available for floating point scalar entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_and.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_and[mask](x, ...)` provides a masked
//!     version of `bit_and` which is
//!     equivalent to `if_else(mask, bit_and(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto bit_and = functor<bit_and_t>;
}

#include <eve/module/core/regular/impl/bit_and.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_and.hpp>
#endif
