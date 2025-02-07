/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct combine_t : callable<combine_t, Options>
  {
    template<simd_value T>
    constexpr EVE_FORCEINLINE typename T::combined_type operator()(T a, T b) const noexcept
    {
      return typename T::combined_type{a, b};
    }
  };

  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!   @var combine
  //!   @brief Combines two SIMD values in a larger one
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
  //!      template<simd_value W>
  //!      constexpr W combine(W a, W b) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `a`, `b`: two SIMD values of the same type and cardinal
  //!
  //!    **Return value**
  //!
  //!      * A [SIMD value](@ref eve::simd_value) contains the parameters concatenation, thus
  //!        producing a register of twice as many elements.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/combine.cpp}
  //================================================================================================
  inline constexpr auto combine = functor<combine_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
