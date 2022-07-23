//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var true_
  //!   @brief Computes the logical true_ value.
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
  //!      template< eve::value T >
  //!      as_logical<T> true_(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::true_(as<T>())` returns [elementwise](@ref glossary_elementwise), the true
  //!      logical value.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/true_.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(true__, true_);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto true__(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
       return as_logical_t<T>(true);
    }
  }
}
