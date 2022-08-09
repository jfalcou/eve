//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/value_type.hpp>
#include <type_traits>

namespace eve
{
  template<typename T, typename SIMD>
  concept simd_compatible_ptr = simd_value<SIMD> &&
    (!detail::range<T>) &&
    std::same_as<element_type_t<SIMD>, value_type_t<T>>;
}
