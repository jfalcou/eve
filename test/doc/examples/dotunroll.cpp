//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
//! [scalar-dot-unroll]
template <typename Value>
Value dot(Value* first1, Value* last1, Value* first2)
{
  Value v1(0), v2(0);

  for (; first1 < last1;) {
    v1 += (*first1) * (*first2);
    ++first1;
    ++first2;

    v2 += (*first1) * (*first2);
    ++first1;
    ++first2;
  }

  return v1 + v2;
}
//! [scalar-dot-unroll]
