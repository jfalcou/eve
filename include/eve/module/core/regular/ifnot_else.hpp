//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
 //================================================================================================
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var ifnot_else
  //!   @brief `eve::ifnot_else``(x, y, z)`syntaxic sugar for `eve::if_else``(x, z, y)`
  //!
  //!   $details$
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
  //!      template< eve::value T, eve::value U, eve::value V >
  //!      auto ifnot_else(T x, U, y, V z ) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: condition
  //!     * `y`, `z`:  choice [arguments](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!     The call `eve::ifnot_else``(x, y, z)`is equivalent to `eve::if_else``(x, z, y)`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/ifnot_else.cpp}
  //!
  //! @}
  //================================================================================================
  namespace tag { struct ifnot_else_; }
  template<> struct supports_conditional<tag::ifnot_else_> : std::false_type {};

  EVE_MAKE_CALLABLE(ifnot_else_, ifnot_else);
}

#include <eve/module/core/regular/impl/ifnot_else.hpp>
