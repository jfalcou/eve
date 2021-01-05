//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/traits/alignment.hpp>
#include <type_traits>

namespace eve
{
  namespace detail
  {
    template<typename T> struct is_aligned_ptr : std::false_type {};

    template<typename T, std::size_t A>
    struct is_aligned_ptr<aligned_ptr<T,A>> : std::true_type {};
  }

  template<typename T, typename SIMD>
  concept simd_compatible_ptr = simd_value<SIMD> && (   std::is_pointer_v<T>
                                                    ||  (detail::is_aligned_ptr<T>::value
                                                         && (pointer_alignment_v<T> >= alignment_v<SIMD>))
                                                    );
}
