/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>

namespace eve
{
  template<typename Options>
  struct combine_t : strict_elementwise_callable<combine_t, Options>
  {
    template<value T>
    constexpr EVE_FORCEINLINE typename T::combined_type operator()(T a, T b) const noexcept
    {
      return typename T::combined_type{a, b};
    }
  };

  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!   @var combine
  //!   @brief Computes the TODO
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
  //!      constexpr auto combine(simd_value a, simd_value b)   noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `a`:  An instance of a [SIMD value](@ref eve::simd_value)
  //!      * `b`:  An instance of a [SIMD value](@ref eve::simd_value) of the same type and cardinal
  //!
  //!    **Return value**
  //!
  //!      * A [SIMD value](@ref eve::simd_value) of the same type and twice the cardinal of that of
  //!        the parameters
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/combine.cpp}
  //================================================================================================
  inline constexpr auto combine = functor<combine_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
