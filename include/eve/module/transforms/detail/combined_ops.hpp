//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
/// various combinations of +/-operators used massively in fft/fht algorthms
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace eve::detail
{
  /////////////////////////////////////////////////////////////////////////////////////////////
  // functions computing sum and (reversed) difference
  /////////////////////////////////////////////////////////////////////////////////////////////

  // 2 parameters sum and difference inplace  {a, b}  -> {a+b, a-b}
  EVE_FORCEINLINE void sd(auto &a, auto &b) noexcept { auto t=a-b; a+=b; b=t; }
  // 3 parameters sum and difference {a, b}  -> {a+b, b, a-b}
  // b untouched a receives sum and d receive difference
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

  // 2 parameters difference and sum inplace  {a, b}  -> {a-b, a+b}
  EVE_FORCEINLINE void ds(auto &a, auto &b) noexcept { auto t=a-b; b+= a; a = t; }
  // 3 parameters difference {a, b} and sum -> {a-b, b, a+b}
  // a untouched b receives difference and s receive sum
  EVE_FORCEINLINE auto ds(auto a, auto &b, auto & s ) noexcept {s=a+b; b = a-b; }
  // 4 parameters sum and difference {a, b}  -> {a, b, a+b, a-b}
  // a, b untouched, s receives sum and d receives difference
  EVE_FORCEINLINE void ds(auto a, auto b, auto & d, auto &s) noexcept {s = a+b; d = a-b; }

  // 2 parameters half sum and difference inplace  {a, b}  -> {(a+b)/2, (a-b)/2}
  EVE_FORCEINLINE void hsd(auto &a, auto &b) noexcept { auto t=average(a, -b); a = average(a, b); b=t; }
  // 3 parameters half sum and difference {a, b}  -> {(a+b)/2, b, (a-b)/2}
  // b untouched a receives half sum and hd receive half difference
  EVE_FORCEINLINE auto hsd(auto &a, auto b, auto & hd ) noexcept {hd=average(a, -b); a = average(a, b); }
  // 4 parameters half sum and difference {a, b}  -> {a, b, (a+b)/2, (a-b)/2}
  // a, b untouched, hs receives half sum and hd receives half difference
  EVE_FORCEINLINE void hsd(auto a, auto b, auto & hs, auto & hd) noexcept {hs = average(a, b); hd = average(a, -b); }

}
