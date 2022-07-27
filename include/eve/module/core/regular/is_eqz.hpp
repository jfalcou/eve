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
  //! @addtogroup core_predicates
  //! @{
  //!   @var is_eqz
  //!   @brief Returns a logical true  if and only if the element value is zero.
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
  //!      template< eve::value T >
  //!      eve::as_logical<T> is_eqz(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!    The truth value of x == 0
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/is_eqz.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::is_eqz[mask](x)` provides a masked version of `eve::is_eqz` which is
  //!     equivalent to `if_else (mask, is_eqz(x), eve::false( eve::as(x)))`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/is_eqz.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_eqz_, is_eqz);

  namespace detail
  {
    // -----------------------------------------------------------------------------------------------
    // logical masked case
    template<conditional_expr C, value U, value V>
    EVE_FORCEINLINE auto is_eqz_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
    {
      return logical_mask_op(cond, is_eqz, u);
    }
  }
}

#include <eve/module/core/regular/impl/is_eqz.hpp>
