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
#include <eve/module/core/regular/is_nez.hpp>

namespace eve
{
  template<typename Options>
  struct bit_mask_t : elementwise_callable<bit_mask_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_mask_t, bit_mask_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_mask
//!   @brief Computes a bit mask full of zeroes or ones
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
//!      template< eve::value T >
//!      T bit_mask(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      For each [elementwise](@ref glossary_elementwise) of `x`:
//!
//!        *  if the [element](@ref glossary_elementwise) is zero, an element
//!           with all bits unset is returned.
//!        *  else an element of the type with all bits set is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_mask.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_mask[mask](x)` provides a masked
//!     version of `bit_mask` which is
//!     equivalent to `if_else(mask, bit_mask(x), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_mask.cpp}
//! @}
//================================================================================================
  inline constexpr auto bit_mask = functor<bit_mask_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_mask_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      return is_nez(v).mask();
    }
  }
}
