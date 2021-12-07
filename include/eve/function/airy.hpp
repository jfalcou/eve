//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup special
  //! @{
  //! @var airy
  //!
  //! @brief Callable object computing the airy function \f$ Ai(x)\f$ and \f$ Bi(x)\f$.
  //!
  //! **Required header:** `#include <eve/function/airy.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the airy function                                          |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating_real_value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Computes simultaneously and [elementwise](@ref glossary_elementwise) the values of
  //!  [airy_ai](@ref airy_ai) and [airy_bi](@ref airy_bi).
  //!
  //! ---
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/airy.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(airy_, airy);
}

#include <eve/module/real/special/function/regular/generic/airy.hpp>
