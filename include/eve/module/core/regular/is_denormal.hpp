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
  //!   @var is_denormal
  //!   @brief Returns a logical true if and only if the element value is denormal.
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
  //!      eve::as_logical<T> is_denormal(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!     The call `is_denormal(x)` is semantically  equivalent to:
  //!
  //!     @code
  //!       if constexpr(floating_value<T>)
  //!         return (eve::abs(x) < eve::smallestposval(as(x))) && is_nez(x);
  //!       else constexpr(integral_value<T>)
  //!         return eve::false_(as(x));
  //!    @endcode
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/is_denormal.cpp}
   //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::is_denormal[mask](x)` provides a masked version
  //!     of `eve::is_denormal` which is
  //!     equivalent to `if_else (mask, is_denormal(x), eve::false( eve::as(x)))`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/is_denormal.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_denormal_, is_denormal);

  namespace detail
  {
    // -----------------------------------------------------------------------------------------------
    // logical masked case
    template<conditional_expr C, value U, value V>
    EVE_FORCEINLINE auto is_denormal_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
    {
      return logical_mask_op(cond, is_denormal, u);
    }
  }
}

#include <eve/module/core/regular/impl/is_denormal.hpp>
