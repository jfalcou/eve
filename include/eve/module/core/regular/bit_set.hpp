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
#include <eve/module/core/regular/bit_shl.hpp>

namespace eve
{
  template<typename Options>
  struct bit_set_t : strict_elementwise_callable<bit_set_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T, integral_scalar_value I >
    constexpr EVE_FORCEINLINE T operator()(T v, I i) const
    { return EVE_DISPATCH_CALL(v, i); }

    EVE_CALLABLE_OBJECT(bit_set_t, bit_set_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_set
//!   @brief set to 1 the ith bit of each element.
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
//!      template< unsigned_value T, integral_value I>
//!      T bit_set(T x, I i) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `i` :  index to set
//!
//!    **Return value**
//!
//!    The value of the parameter is returned with the ith bit set to 1
//!    if the index is out of range the call will assert.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_set.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_set[mask](x, ...)` provides a masked
//!     version of `bit_set` which is
//!     equivalent to `if_else(mask, bit_set(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto bit_set = functor<bit_set_t>;

  namespace detail
  {
    template<typename T, typename I, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_set_(EVE_REQUIRES(cpu_), O const&, T a, I i) noexcept
    {
      [[maybe_unused]] constexpr std::ptrdiff_t S8 = sizeof(element_type_t<T>)*8;
      EVE_ASSERT(eve::all(i >= 0 && i < S8), "index is out or range");
      return bit_or(a, bit_shl(one(as(a)), i));
    }
  }
}
