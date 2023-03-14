//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cardinals.hpp>
#include <eve/arch/spec.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::detail
{
  template<typename Type, regular_abi ABI>
  constexpr std::ptrdiff_t find_expected_cardinal()
  {
    if constexpr(kumi::product_type<Type>)
    {
      return kumi::min( kumi::result::flatten_all_t<kumi::as_tuple_t<Type>>{}
                      , []<typename M>(M) { return ABI::template expected_cardinal<M>; }
                      );
    }
    else
    {
      return ABI::template expected_cardinal<Type>;
    }
  }
}

namespace eve
{
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  constexpr inline auto expected_cardinal_v = detail::find_expected_cardinal<Type, ABI>();

  //================================================================================================
  //! @addtogroup arch
  //! @{
  //!   @typedef expected_cardinal_t
  //!   @brief Computes the expected cardinal of a given type
  //!
  //!   **Required header:** `#include <eve/arch/expected_cardinal.hpp>`
  //!
  //!   @ref eve::expected_cardinal_t is the exact cardinal type of the register able to store
  //!   values of type `Type` for a given SIMD `ABI` as a native register type.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //!    #### Helper variable template
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    inline constexpr auto expected_cardinal_v = expected_cardinal_t<Type, ABI>::value;
  //!    @endcode
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using expected_cardinal_t = fixed<expected_cardinal_v<Type,ABI>>;
}
