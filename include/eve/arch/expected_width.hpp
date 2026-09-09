//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/widths.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/deps/kumi.hpp>
#include <eve/detail/meta.hpp>

namespace eve::_
{
  template<typename T> struct fec_box { using type = always<T>; };

  template<scalar_value Type, regular_abi ABI>
  consteval width_type find_expected_width()
  {
    if constexpr(eve::product_type<Type>)
    {
      return kumi::min_flat ( kumi::as_tuple_t<Type, fec_box>{}
                            , []<typename M>(M) { return find_expected_width<typename M::type,ABI>(); }
                            );
    }
    else
    {
      return ABI::template expected_width<Type>;
    }
  }
}

namespace eve
{
  template<scalar_value Type, regular_abi ABI = eve::current_abi_type>
  constexpr inline width_type expected_width_v = _::find_expected_width<Type, ABI>();

  //================================================================================================
  //! @addtogroup eve_arch
  //! @{
  //!   @typedef expected_width_t
  //!   @brief Computes the expected width of a given type
  //!
  //!   **Required header:** `#include <eve/arch/expected_width.hpp>`
  //!
  //!   @ref eve::expected_width_t is the exact width type of the register able to store
  //!   values of type `Type` for a given SIMD `ABI` as a native register type.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //!    #### Helper variable template
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    inline constexpr auto expected_width_v = expected_width_t<Type, ABI>::value;
  //!    @endcode
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using expected_width_t = fixed<expected_width_v<Type,ABI>>;
}
