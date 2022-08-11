//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math_log
  //! @{
  //! @var log_abs
  //!
  //! @brief Callable object computing the natural logarithm of the absolute value of the input.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_value T >
  //!      T log_abs(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!   * `x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //!
  //! **Return value**
  //!
  //!    *  Returns [elementwise](@ref glossary_elementwise) the natural logarithm  of
  //!       the absolute value of `x`: \f$\log |x|\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/log_abs.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log_abs_, log_abs);
}

#include <eve/module/math/regular/impl/log_abs.hpp>
