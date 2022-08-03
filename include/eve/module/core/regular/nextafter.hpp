//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/concept/value.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_internal
  //! @{
  //!   @var nextafter
  //!   @brief Computes the nth next representable element
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
  //!      template< eve::value T, eve::value U >
  //!      eve::common_compatible_t<T, U> nextafter(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`:  [arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!      The value of the next representable value greater than `x` in the `y` direction
  //!      is returned.
  //!      If `y == x` returns `x`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/nextafter.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::nextafter[mask](x, ...)` provides a masked
  //!     version of `nextafter` which is
  //!     equivalent to `if_else(mask, nextafter(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/nextafter.cpp}
  //!
  //! @}
  //================================================================================================

  namespace tag { struct nextafter_; }
  template<> struct supports_conditional<tag::nextafter_> : std::false_type {};

  EVE_MAKE_CALLABLE(nextafter_, nextafter);
}

#include <eve/module/core/regular/impl/nextafter.hpp>
