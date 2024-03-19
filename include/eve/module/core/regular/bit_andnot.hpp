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

namespace eve
{
  template<typename Options>
  struct bit_andnot_t : tuple_callable<bit_andnot_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::ordered_value T0, ordered_value T1, ordered_value... Ts>
    EVE_FORCEINLINE constexpr as_wide_as_t<T0, common_value_t<T0, T1, Ts...>>
    operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    requires bit_compatible_values<T0, T1> && (bit_compatible_values<T1, Ts> &&...)
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<kumi::member_t<0, Tup>, kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(bit_andnot_t, bit_andnot_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_andnot
//!   @brief Computes the bitwise ANDNOT of its arguments.
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
//!      T bit_andnot(T x, Ts... xs) noexcept;
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
//!     * For two parameters it computes the  bitwise ANDNOT of the two parameters
//!     * For more than two parameters the call is  semantically equivalent to to `bit_andnot(a0,
//!     bit_and(xs...))`
//!     *  The value returned is in the type of the first parameter
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_andnot.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_andnot[mask](x, ...)` provides a masked
//!     version of `bit_andnot` which is
//!     equivalent to `if_else(mask, bit_andnot(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_andnot.cpp}
//! @}
//================================================================================================
inline constexpr auto bit_andnot = functor<bit_andnot_t>;

}

#include <eve/module/core/regular/impl/bit_andnot.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/bit_andnot.hpp>
#endif
