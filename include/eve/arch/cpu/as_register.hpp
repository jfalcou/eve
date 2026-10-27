//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/widths.hpp>
#include <eve/arch/cpu/blob.hpp>
#include <eve/detail/abi.hpp>
#include <eve/deps/kumi.hpp>
#include <eve/arch/abi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_wide.hpp>
#include <cstring>
#include <array>

namespace eve::_
{
  // Type marking the absence of a register for the given type
  template<typename T>
  struct no_register{ static_assert(!std::is_void_v<T>, "[EVE] - Type is not usable in a SIMD register"); };

  template<typename T, width_type N, typename ABI>
  extern no_register<void> as_register;

  template<typename T, width_type N>
  extern std::array<T, N> as_register<T, N, eve::emulated_>;

  template<typename T, width_type N>
  extern _::blob<T, N> as_register<T, N, eve::aggregated_>;

  template<typename T, width_type N, typename ABI>
  extern no_register<void> as_logical_register;

  template<typename T, width_type N>
  extern std::array<logical<T>, N> as_logical_register<T, N, eve::emulated_>;

  template<typename T, width_type N>
  extern _::blob<logical<T>, N> as_logical_register<T, N, eve::aggregated_>;

  //================================================================================================
  // Special case : product_type
  //================================================================================================
  template<width_type N>
  struct apply_as_wide
  {
    template<typename T>
    using type = as_wide<T, N>;
  };

  template<eve::product_type T, width_type N>
  extern kumi::as_tuple_t<T, _::apply_as_wide<N>::template type> as_register<T, N, eve::bundle_>;
}
