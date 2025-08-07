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
  struct precision_t : callable<precision_t, Options>
  {
    template<typename T>
    constexpr EVE_FORCEINLINE int  operator()(T t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(precision_t, precision_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var precision
//!   @brief Computes the precision of the hardware implementation of a floating point type
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
//!      constexpr int template < floating_scalar_value t>
//!      int precision(T dummy) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `dummy` :  [floatinf scalar arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!     Utility that computes a int containing the number of mantissa bits of a floating type
//!     as delivered by the hardware (including the hidden bit)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/precision.cpp}
//!
//================================================================================================
  inline constexpr auto precision = functor<precision_t>;
//================================================================================================
///! @}
//================================================================================================

  namespace detail
  {
    template < typename T, callable_options O>
    constexpr int precision_ (EVE_REQUIRES(cpu_), O const&, T) noexcept
    {
      //     constexpr T z(0);
      constexpr int radix = 2; //malcolm(z);

      constexpr T o = T(1);
      int i = 0;
      auto a = o;
      while ((a + o) - a == o)
      {
        a *= radix;
        ++i;
      }
      return i;
    }
  }
}
