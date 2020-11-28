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

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct extract_; }

  namespace detail
  {
    template<typename T, typename I>
    EVE_FORCEINLINE void check( EVE_MATCH_CALL(eve::tag::extract_),
                                T const&,  [[maybe_unused]] I const& i
                              )
    {
      EVE_ASSERT( (i < I(cardinal_v<T>)),
                  "[eve::extract] Index " << i << "is out of [0," << cardinal_v<T> << "[ range."
                );
    }

    template<typename T, typename I, auto V>
    EVE_FORCEINLINE void check( EVE_MATCH_CALL(eve::tag::extract_),
                                T const&, std::integral_constant<I, V> const&
                              )
    {
      static_assert ( (V < cardinal_v<T>),
                      "[eve::extract] Index is out of bound"
                    );
    }
  }
  EVE_MAKE_CALLABLE(extract_, extract);
}

#include <eve/module/core/function/regular/generic/extract.hpp>
