//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var constant
//!   @brief Computes a floating constant from its scalar hexadecimal integral representation.
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
//!      template< eve::floating_value T, auto BitsPattern >
//!      T constant(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::constant<Bitpattern>(as<T>())` returns a value of type T
//!      from the bits found in Bitpattern.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/constant.cpp}
//! @}
//================================================================================================

template<typename T, auto BitsPattern>
EVE_FORCEINLINE auto
Constant(eve::as<T> const& = {})
{
  using t_t = element_type_t<T>;

  if constexpr( std::is_integral_v<t_t> ) { return static_cast<T>(BitsPattern); }
  else
  {
    if constexpr( sizeof(t_t) != sizeof(BitsPattern) )
    {
      static_assert(sizeof(t_t) == sizeof(BitsPattern),
                    "[eve::constant] floating_point case - BitsPattern has not the correct size");
      return T {};
    }
    else { return static_cast<T>(bit_cast(BitsPattern, as<t_t> {})); }
  }
}
}
