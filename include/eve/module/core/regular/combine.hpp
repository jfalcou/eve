/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_translation.hpp>

namespace eve
{
  template<typename Options>
  struct combine_t : callable<combine_t, Options>
  {
    template<simd_value T>
    constexpr EVE_FORCEINLINE typename T::combined_type operator()(T a, T b) const noexcept
    {
      return translate_into(
        detail::combine(eve::current_api, translate(a), translate(b)),
        as<typename T::combined_type>{});
    }

    template<simd_value T0, simd_value T1, simd_value T2, simd_value... Ts>
    constexpr EVE_FORCEINLINE typename T0::template rescale<fixed<(T0::size() * (3 + sizeof...(Ts)))>>
    operator()(T0 a, T1 b, T2 c, Ts... ts) const noexcept
      requires (combinable<T0, T1, T2, Ts...>)
    {
      return translate_into(
        detail::combine(eve::current_api, translate(a), translate(b), translate(c), translate(ts)...),
        as<typename T0::template rescale<fixed<(T0::size() * (3 + sizeof...(Ts)))>>>{});
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
  //!      typename W::combined_type combine(W a, W b) noexcept;
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
