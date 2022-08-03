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
  //! @addtogroup core_conversions
  //! @{
  //!   @var binarize_not
  //!   @brief transform logical values to numerical values
  //!
  //!   binarize_not(c, v) is semantically  equivalent to: if_else(c, T(0), v);
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
  //!      template< eve::value C  >
  //!      C binarize_not(eve::as_logical<C> c) noexcept;          //1
  //!
  //!      template<eve::value C, eve::value V >
  //!      T binarize_not(eve::as_logical<C> c, T v) noexcept;     //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `c` :  [condition](@ref eve::logical_value).
  //!
  //!     * `v` :  [value](@ref eve::value) to return if the condition is not met (C(1) if omitted).
  //!
  //!    **Return value**
  //!
  //!      * 1) The value of if_else(c, T(0), v); is returned.
  //!      * 2) The value of if_else(c, C(0), C(1)); is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/binarize_not.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(binarize_not_, binarize_not);
}

#include <eve/module/core/regular/impl/binarize_not.hpp>
