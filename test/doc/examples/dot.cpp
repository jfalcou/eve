#//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
include <eve/function/mul.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/splat.hpp>
#include <eve/wide.hpp>

//! [scalar-dot]
template <typename Value>
Value dot(Value* first1, Value* last1, Value* first2)
{
  Value v(0);

  for (; first1 < last1; ++first1, ++first2) {
    v += (*first1) * (*first2);
  }

  return v;
}
//! [scalar-dot]
