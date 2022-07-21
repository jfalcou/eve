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
  //! @addtogroup core_accuracy
  //! @{
  //!   @var sum_of_prod
  //!   @brief Computes the sum of products operation with better accuracy
  //!   than the naive formula.
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
  //!      template< eve::floating_real_value T
  //!              , eve::floating_real_value U
  //!              , eve::floating_real_value V
  //!              , eve::floating_real_value W>
  //!      T sum_of_prod(T x, U y, V z, W t ) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z`, `t`:  |floating value arguments](@ref floating_value).
  //!
  //!    **Return value**
  //!
  //!    The value of `x*y+z*t`,  with better precision if correct fma is available,
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/sum_of_prod.cpp}
  //! @}
  //================================================================================================
  namespace tag { struct sum_of_prod_; }
  template<> struct supports_conditional<tag::sum_of_prod_> : std::false_type {};

  EVE_MAKE_CALLABLE(sum_of_prod_, sum_of_prod);
}

#include <eve/module/core/regular/impl/sum_of_prod.hpp>
