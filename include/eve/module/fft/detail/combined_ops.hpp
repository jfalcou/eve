//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
/// various combinations of +/-operators easing writing fft algorthms
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace eve::detail
{
  /////////////////////////////////////////////////////////////////////////////////////////////
  // functions computing sum and (reversed) difference
  /////////////////////////////////////////////////////////////////////////////////////////////

  // 2 parameters sum and difference inplace  {a, b}  -> {a+b, a-b}
  EVE_FORCEINLINE void sd(auto &a, auto &b) noexcept { auto t=a-b; a+=b; b=t; }
  // 3 parameters sum and difference {a, b}  -> {a+b, b, a-b}
  // a, b untouched s receives sum and d receive difference
  EVE_FORCEINLINE auto sd(auto &a, auto b, auto & d ) noexcept {d=a-b; a+=b; }
  // 4 parameters sum and difference {a, b}  -> {a, b, a+b, a-b}
  // a, b untouched, s receives sum and d receives difference
  EVE_FORCEINLINE void sd(auto a, auto b, auto & s, auto &d) noexcept {s = a+b; d = a-b; }


  // 2 parameters sum and reversed difference inplace  {a, b}  -> {a+b, b-a}
  EVE_FORCEINLINE void srd(auto &a, auto &b) noexcept { auto t=b-a; a+=b; b=t; }
  // 3 parameters sum and difference {a, b}  -> {a+b, b, b-ab}
  // b untouched, a replaced by sum and rd receives reversed difference
  EVE_FORCEINLINE auto srd(auto &a, auto b, auto & rd ) noexcept {rd=b-a; a+=b; }
  // 4 parameters sum and reversed difference {a, b}  -> {a, b, a+b, b-a}
  // a, b untouched, s receives sum and  rd receives reversed difference
  EVE_FORCEINLINE auto srd(auto &a, auto b, auto & s, auto & rd ) noexcept {rd=b-a; s = a+b; }


}
