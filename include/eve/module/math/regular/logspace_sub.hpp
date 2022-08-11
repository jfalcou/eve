//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math_log
  //! @{
  //! @var logspace_sub
  //!
  //! @brief Callable object computing the logspace_sub operation:
  //!        \f$\log\left(e^{x_0}-\sum_{i = 1}^n e^{x_i}\right)\f$.
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
  //!      template< eve::floating_value T, eve::floating_value U, eve::floating_value ... Ts >
  //!      auto logspace_sub(T arg0, U arg1, Ts ... args) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`arg0`, `arg1`, `args`, ...:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //! The call `logspace_sub(arg0, arg1, args...)` is semantically equivalent to
  //!`log(exp(arg0) - exp(arg1) - exp(args)...)`.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the parameters.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/logspace_sub.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(logspace_sub_, logspace_sub);
}

#include <eve/module/math/regular/impl/logspace_sub.hpp>
