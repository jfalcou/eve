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
  //! @var log
  //!
  //! @brief Callable object computing the natural logarithm: \f$\log x\f$.
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
  //!      T log(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) the natural logarithm  of `x`: \f$\log x\f$.
  //!
  //!   * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
  //!   * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!   * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
  //!   * If the element is less than 0, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/log.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::log[mask](x)` provides a masked version of `eve::log` which is
  //!     equivalent to `if_else (mask, log(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/log.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log_, log);
}

#include <eve/module/math/regular/impl/log.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/math/regular/impl/simd/x86/log.hpp>
#endif
