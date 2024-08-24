//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_notor.hpp>
#include <eve/module/core/regular/bit_select.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <iostream>

namespace eve
{
  template<typename Options>
  struct bit_ternary_t : callable<bit_ternary_t, Options>
  {
    template<int K, value T0, value T1, value T2>
    requires(eve::same_lanes_or_scalar<T0, T1, T2> && 0 <= K && K <= 255)
      EVE_FORCEINLINE constexpr bit_value_t<T0, T1, T2>
    operator()( std::integral_constant<int, K> k, T0 t0, T1 t1, T2 t2) const noexcept
    {
      return EVE_DISPATCH_CALL(k, t0,  t1, t2);
    }

//     template<detail::bit_tern K, value T0, value T1, value T2>
//     requires(eve::same_lanes_or_scalar<T0, T1, T2>)
//       EVE_FORCEINLINE constexpr bit_value_t<T0, T1, T2>
//     operator()(std::integral_constant<detail::bit_tern, K> k, T0 t0, T1 t1, T2 t2) const noexcept
//     {
//       return EVE_DISPATCH_CALL(k, t0,  t1, t2);
//     }

    EVE_CALLABLE_OBJECT(bit_ternary_t, bit_ternary_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_xor
//!   @brief `strict_callable` object implementing ternary logic.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto bit_ternary(integral_constant k, auto a, auto b,  auto c)         noexcept; // 1
//!      constexpr auto bit_ternary(bit_tern k, auto a, auto b,  auto c)                  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bit_xor[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto bit_xor[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: first [argument](@ref eve::value).
//!     * `xs...` : other [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!      Bitwise ternary logic that provides the capability to implement any three-operand binary function;
//!      the specific binary function is specified by value of k.
//!      For each bit in each packed 32-bit integer, the corresponding bit from a, b, and c are used according
//!      to k, and the result isoutput.

//!      1. The value of the bitwise XOR of its arguments converted to their  common `bit_value`
//!        is returned.
//!      2. equivalent to the call on the elements of the tuple.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  The pattern of a truth table:
//!
//!    inputs     result
//!  A  B   C
//!  0  0   0   a
//!  0  0   1   b
//!  0  1   0   c
//!  0  1   1   d
//!  1  0   0   e
//!  1  0   1   f
//!  1  1   0   g
//!  1  1   1   h
//!
//!  A programmer supplies only the result column, i.e. defines values of bits a through h, this is a single 8-bit value.
//!  (makefrombits can be used)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_xor.cpp}
//================================================================================================
  inline constexpr auto bit_ternary = functor<bit_ternary_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    // this is adapted from Samuel neves ternary logic for sse avx etc.
    template < int K, typename T0, typename T1, typename T2, callable_options O>
    EVE_FORCEINLINE  /*bit_value_t<T0, T1, T2>*/ auto bit_ternary_(EVE_REQUIRES(cpu_)
                                                                  , O const &
                                                                  , std::integral_constant<int, K> const &
                                                                  , [[maybe_unused]] T0 const & aa
                                                                  , [[maybe_unused]] T1 const & bb
                                                                  , [[maybe_unused]] T2 const & cc
                                                                  ) noexcept
    //    requires(K <= 255)
    {

      using T = bit_value_t<T0, T1, T2>;
      auto a = T(aa);
      auto b = T(bb);
      auto c = T(cc);
      auto ao =  eve::allbits(eve::as(a));
      if constexpr(K == 0x00)      return zero(as(a));
      else if constexpr(K == 0x01) return bit_not(bit_or(a, b, c));
      else if constexpr(K == 0x02) return bit_notand(bit_or(a, b), c);
      else if constexpr(K == 0x03) return bit_not(bit_or(a, b));
      else if constexpr(K == 0x04) return bit_notand(bit_or(a, c), b);
      else if constexpr(K == 0x05) return bit_not(bit_or(a, c));
      else if constexpr(K == 0x06) return bit_notand(a,bit_xor(b, c));
      else if constexpr(K == 0x07) return bit_not(bit_or(a, bit_and(b, c)));
      else if constexpr(K == 0x08) return bit_and(bit_notand(a, b), c);
      else if constexpr(K == 0x09) return bit_not(bit_or(a, bit_xor(b, c)));
      else if constexpr(K == 0x0a) return bit_notand(a, c);
      else if constexpr(K == 0x0b) return bit_notand(a, bit_notor(b, c));
      else if constexpr(K == 0x0c) return bit_notand(a, b);
      else if constexpr(K == 0x0d) return bit_notand(a, bit_ornot(b, c));
      else if constexpr(K == 0x0e) return bit_notand(a, bit_or(b, c));
      else if constexpr(K == 0x0f) return bit_not(a);
      else if constexpr(K == 0x10) return bit_notand(bit_or(b, c), a);
      else if constexpr(K == 0x11) return bit_not(bit_or(b, c));
      else if constexpr(K == 0x12) return bit_notand(b, bit_xor(a, c));
      else if constexpr(K == 0x13) return bit_not(bit_or(b, bit_and(a, c)));
      else if constexpr(K == 0x14) return bit_notand(c, bit_xor(a, b));
      else if constexpr(K == 0x15) return bit_not(bit_or(c, bit_and(a, b)));
      else if constexpr(K == 0x16) return bit_or(bit_notand(bit_or(b, c), a), bit_notand(a, bit_xor(b, c)));
      else if constexpr(K == 0x17) return bit_or(bit_not(bit_or(b, c)), bit_notand(a,bit_xor(b, c)));
      else if constexpr(K == 0x18) return bit_and(bit_xor(a, c), bit_xor(a, b));
      else if constexpr(K == 0x19) return bit_notand(bit_and(a, b), bit_not(bit_xor(b, c)));
      else if constexpr(K == 0x1a) return bit_notand(bit_and(a, b), bit_xor(a, c));
      else if constexpr(K == 0x1b) return bit_or(bit_notand(a, c), bit_notand(c, bit_not(b)));
      else if constexpr(K == 0x1c) return bit_notand(bit_and(a, c), bit_xor(a, b));
      else if constexpr(K == 0x1d) return bit_or(bit_notand(a, b),  bit_notand(b, bit_not(c)));
      else if constexpr(K == 0x1e) return bit_xor(a, bit_or(b, c));
      else if constexpr(K == 0x1f) return bit_not(bit_and(a, bit_or(b, c)));
      else if constexpr(K == 0x20) return bit_and(bit_notand(b, a), c);
      else if constexpr(K == 0x21) return bit_not(bit_or(b, bit_xor(a, c)));
      else if constexpr(K == 0x22) return bit_notand(b, c);
      else if constexpr(K == 0x23) return bit_notand(b, bit_notor(a, c));
      else if constexpr(K == 0x24) return bit_and(bit_xor(a, b), bit_xor(b, c));
      else if constexpr(K == 0x25) return bit_notand(bit_and(a, b), bit_xor(a, bit_not(c)));
      else if constexpr(K == 0x26) return bit_notand(bit_and(a, b), bit_xor(b, c));
      else if constexpr(K == 0x27) return bit_or(bit_notand(b, c), bit_notand(c, bit_not(a)));
      else if constexpr(K == 0x28) return bit_and(c, bit_xor(a, b));
      else if constexpr(K == 0x29) return bit_or(bit_and(c, bit_xor(b, a)), bit_notand(c, bit_not(bit_or(b, a))));
      else if constexpr(K == 0x2a) return bit_notand(bit_and(b, a), c);
      else if constexpr(K == 0x2b) return bit_or(bit_notand(bit_and(b, a), c), bit_notand(c,bit_not( bit_or(b, a))));
      else if constexpr(K == 0x2c) return bit_and(bit_or(b, c), bit_xor(a, b));
      else if constexpr(K == 0x2d) return bit_xor(a, bit_or(b, bit_not(c)));
      else if constexpr(K == 0x2e) return bit_xor(bit_or(b, c), bit_and(a, b));
      else if constexpr(K == 0x2f) return bit_or(bit_notand(b, c), bit_not(a));
      else if constexpr(K == 0x30) return bit_notand(b, a);
      else if constexpr(K == 0x31) return bit_notand(b,bit_ornot(a, c));
      else if constexpr(K == 0x32) return bit_notand(b, bit_or(a, c));
      else if constexpr(K == 0x33) return bit_not(b);
      else if constexpr(K == 0x34) return bit_notand(bit_and(b, c), bit_xor(a, b));
      else if constexpr(K == 0x35) return bit_or(bit_notand(b, a), bit_notand(a,bit_not(c)));
      else if constexpr(K == 0x36) return bit_xor(b, bit_or(a, c));
      else if constexpr(K == 0x37) return bit_not(bit_and(b, bit_or(a, c)));
      else if constexpr(K == 0x38) return bit_and(bit_or(a, c), bit_xor(a, b));
      else if constexpr(K == 0x39) return bit_xor(b, bit_or(a, bit_not(c)));
      else if constexpr(K == 0x3a) return bit_or(bit_notand(b, a), bit_notand(a, c));
      else if constexpr(K == 0x3b) return bit_or(bit_notand(a, c), bit_not(b));
      else if constexpr(K == 0x3c) return bit_xor(b, a);
      else if constexpr(K == 0x3d) return bit_or(bit_xor(a, b), bit_not(bit_or(a, c)));
      else if constexpr(K == 0x3e) return bit_or(bit_notand(a, c), bit_xor(a, b));
      else if constexpr(K == 0x3f) return bit_not(bit_and(b, a));
      else if constexpr(K == 0x40) return bit_and(bit_notand(c, a), b);
      else if constexpr(K == 0x41) return bit_not(bit_or(c, bit_xor(b, a)));
      else if constexpr(K == 0x42) return bit_and(bit_xor(a, c), bit_xor(b, c));
      else if constexpr(K == 0x43) return bit_notand(bit_and(a, c), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0x44) return bit_notand(c, b);
      else if constexpr(K == 0x45) return bit_notand(c, bit_or(bit_not(a), b));
      else if constexpr(K == 0x46) return bit_notand(bit_and(a, c), bit_xor(b, c));
      else if constexpr(K == 0x47) return bit_or(bit_notand(c, b), bit_notand(b, bit_not(a)));
      else if constexpr(K == 0x48) return bit_and(b, bit_xor(a, c));
      else if constexpr(K == 0x49) return bit_or(bit_and(b, bit_xor(a, c)), bit_notand(b, bit_not(bit_or(a, c))));
      else if constexpr(K == 0x4a) return bit_and(bit_or(b, c), bit_xor(a, c));
      else if constexpr(K == 0x4b) return bit_xor(a, bit_or(bit_not(b), c));
      else if constexpr(K == 0x4c) return bit_notand(bit_and(a, c), b);
      else if constexpr(K == 0x4d) return bit_or(bit_notand(bit_and(a, c), b), bit_notand(b, bit_not(bit_or(a, c))));
      else if constexpr(K == 0x4e) return bit_or(bit_notand(a, c), bit_notand(c, b));
      else if constexpr(K == 0x4f) return bit_or(bit_not(a), bit_notand(c, b));
      else if constexpr(K == 0x50) return bit_notand(c, a);
      else if constexpr(K == 0x51) return bit_notand(c, bit_or(a, bit_not(b)));
      else if constexpr(K == 0x52) return bit_notand(bit_and(b, c), bit_xor(a, c));
      else if constexpr(K == 0x53) return bit_or(bit_notand(c, a), bit_notand(a, bit_not(b)));
      else if constexpr(K == 0x54) return bit_notand(c, bit_or(a, b));
      else if constexpr(K == 0x55) return bit_not(c);
      else if constexpr(K == 0x56) return bit_xor(c, bit_or(b, a));
      else if constexpr(K == 0x57) return bit_not(bit_and(c, bit_or(b, a)));
      else if constexpr(K == 0x58) return bit_and(bit_or(a, b), bit_xor(a, c));
      else if constexpr(K == 0x59) return bit_xor(c, bit_or(a,bit_not(b)));
      else if constexpr(K == 0x5a) return bit_xor(c, a);
      else if constexpr(K == 0x5b) return bit_or(bit_xor(a, c), bit_not(bit_or(a, b)));
      else if constexpr(K == 0x5c) return bit_or(bit_notand(c, a), bit_notand(a, b));
      else if constexpr(K == 0x5d) return bit_or(bit_notand(a, b), bit_not(c));
      else if constexpr(K == 0x5e) return bit_or(bit_notand(c, b), bit_xor(a, c));
      else if constexpr(K == 0x5f) return bit_not(bit_and(c, a));
      else if constexpr(K == 0x60) return bit_and(a, bit_xor(b, c));
      else if constexpr(K == 0x61) return bit_or(bit_and(a, bit_xor(b, c)), bit_notand(a, bit_not(bit_or(b, c))));
      else if constexpr(K == 0x62) return bit_and(bit_or(a, c), bit_xor(b, c));
      else if constexpr(K == 0x63) return bit_xor(b, bit_or(bit_not(a), c));
      else if constexpr(K == 0x64) return bit_and(bit_or(a, b), bit_xor(b, c));
      else if constexpr(K == 0x65) return bit_xor(c, bit_or(bit_not(a), b));
      else if constexpr(K == 0x66) return bit_xor(c, b);
      else if constexpr(K == 0x67) return bit_or(bit_xor(b, c), bit_not(bit_or(a, b)));
      else if constexpr(K == 0x68) return bit_or(bit_and(a,bit_xor(b, c)), bit_notand(a, bit_and(b, c)));
      else if constexpr(K == 0x69) return bit_not(bit_xor(a, b, c));
      else if constexpr(K == 0x6a) return bit_xor(c, bit_and(b, a));
      else if constexpr(K == 0x6b) return bit_or(bit_notand(a, c), bit_xor(bit_not(a), b, c));
      else if constexpr(K == 0x6c) return bit_xor(b, bit_and(a, c));
      else if constexpr(K == 0x6d) return bit_or(bit_notand(a, b), bit_xor(bit_not(a), b, c));
      else if constexpr(K == 0x6e) return bit_or(bit_notand(a, b), bit_xor(b, c));
      else if constexpr(K == 0x6f) return bit_or(bit_xor(b, c), bit_not(a));
      else if constexpr(K == 0x70) return bit_notand(bit_and(b, c), a);
      else if constexpr(K == 0x71) return bit_or(bit_not(bit_or(b, c)), bit_and(a, bit_xor(b, c)));
      else if constexpr(K == 0x72) return bit_or(bit_notand(b, c), bit_notand(c, a));
      else if constexpr(K == 0x73) return bit_or(bit_notand(c, a), bit_not(b));
      else if constexpr(K == 0x74) return bit_or(bit_notand(c, b), bit_notand(b, a));
      else if constexpr(K == 0x75) return bit_or(bit_notand(b, a), bit_not(c));
      else if constexpr(K == 0x76) return bit_or(bit_notand(b, a), bit_xor(b, c));
      else if constexpr(K == 0x77) return bit_not(bit_and(b, c));
      else if constexpr(K == 0x78) return bit_xor(a, bit_and(b, c));
      else if constexpr(K == 0x79) return bit_or(bit_notand(b, a), bit_xor(bit_not(b), bit_xor(a, c)));
      else if constexpr(K == 0x7a) return bit_or(bit_notand(b, a), bit_xor(a, c));
      else if constexpr(K == 0x7b) return bit_or(bit_xor(a, c), bit_not(b));
      else if constexpr(K == 0x7c) return bit_or(bit_notand(c, a), bit_xor(a, b));
      else if constexpr(K == 0x7d) return bit_or(bit_xor(a, b), bit_not(c));
      else if constexpr(K == 0x7e) return bit_or(bit_xor(a, b), bit_xor(a, c));
      else if constexpr(K == 0x7f) return bit_not(bit_and(a, b, c));
      else if constexpr(K == 0x80) return bit_and(a, b, c);
      else if constexpr(K == 0x81) return bit_notand(bit_xor(a, c), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0x82) return bit_notand(bit_xor(b, a), c);
      else if constexpr(K == 0x83) return bit_notand(bit_xor(a, b), bit_or(bit_not(a), c));
      else if constexpr(K == 0x84) return bit_notand(bit_xor(a, c), b);
      else if constexpr(K == 0x85) return bit_notand(bit_xor(a, c), bit_or(b, bit_not(c)));
      else if constexpr(K == 0x86) return bit_and(bit_or(b, c),  bit_xor(c, a, b));
      else if constexpr(K == 0x87) return bit_not(bit_xor(a, bit_and(b, c)));
      else if constexpr(K == 0x88) return bit_and(c, b);
      else if constexpr(K == 0x89) return bit_notand(bit_xor(b, c), bit_notor(a, b));
      else if constexpr(K == 0x8a) return bit_notand(bit_notand(b, a), c);
      else if constexpr(K == 0x8b) return bit_or(bit_and(b, c),  bit_notand(b, bit_not(a)));
      else if constexpr(K == 0x8c) return bit_notand(bit_notand(c, a), b);
      else if constexpr(K == 0x8d) return bit_or(bit_and(c, b), bit_notand(c,bit_not(a)));
      else if constexpr(K == 0x8e) return bit_or(bit_and(b, c), bit_notand(a, bit_xor(b, c)));
      else if constexpr(K == 0x8f) return bit_or(bit_and(b, c), bit_not(a));
      else if constexpr(K == 0x90) return bit_notand(bit_xor(b, c), a);
      else if constexpr(K == 0x91) return bit_notand(bit_xor(b, c),  bit_ornot(a, b));
      else if constexpr(K == 0x92) return bit_and(bit_or(a, c),  bit_xor(c, a, b));
      else if constexpr(K == 0x93) return bit_not(bit_xor(b, bit_and(a, c)));
      else if constexpr(K == 0x94) return bit_and(bit_or(a, b),  bit_xor(b, a, c));
      else if constexpr(K == 0x95) return bit_not(bit_xor(c, bit_and(b, a)));
      else if constexpr(K == 0x96) return bit_xor(a, b, c);
      else if constexpr(K == 0x97) return bit_or(bit_notand(bit_xor(b, c), a), bit_notand(a, bit_not(bit_and(b, c))));
      else if constexpr(K == 0x98) return bit_notand(bit_xor(b, c), bit_or(a, b));
      else if constexpr(K == 0x99) return bit_not(bit_xor(c, b));
      else if constexpr(K == 0x9a) return bit_xor(bit_notand(b, a), c);
      else if constexpr(K == 0x9b) return bit_or(bit_notand(a, c), bit_xor(b, bit_not(c)));
      else if constexpr(K == 0x9c) return bit_xor(bit_notand(c, a), b);
      else if constexpr(K == 0x9d) return bit_or(bit_notand(a, b), bit_xor(b, bit_not(c)));
      else if constexpr(K == 0x9e) return bit_or(bit_and(b, c), bit_xor(c, a, b));
      else if constexpr(K == 0x9f) return bit_not(bit_and(a, bit_xor(b, c)));
      else if constexpr(K == 0xa0) return bit_and(c, a);
      else if constexpr(K == 0xa1) return bit_notand(bit_xor(a, c), bit_ornot(a, b));
      else if constexpr(K == 0xa2) return bit_notand(bit_notand(a, b), c);
      else if constexpr(K == 0xa3) return bit_or(bit_and(a, c), bit_notand(a,bit_not(b)));
      else if constexpr(K == 0xa4) return bit_notand( bit_xor(a, c), bit_or(a, b));
      else if constexpr(K == 0xa5) return bit_not(bit_xor(c, a));
      else if constexpr(K == 0xa6) return bit_xor(bit_notand(a, b), c);
      else if constexpr(K == 0xa7) return bit_or(bit_notand(b, c), bit_xor(a, bit_not(c)));
      else if constexpr(K == 0xa8) return bit_and(c, bit_or(a, b));
      else if constexpr(K == 0xa9) return bit_not(bit_xor(c, bit_or(b, a)));
      else if constexpr(K == 0xaa) return c;
      else if constexpr(K == 0xab) return bit_or(c, bit_not(bit_or(b, a)));
      else if constexpr(K == 0xac) return bit_select(a, c, b);
      else if constexpr(K == 0xad) return bit_or(bit_and(b, c), bit_xor(a, bit_not(c)));
      else if constexpr(K == 0xae) return bit_or(c, bit_notand(a, b));
      else if constexpr(K == 0xaf) return bit_ornot(c, a);
      else if constexpr(K == 0xb0) return bit_notand(bit_notand(c, b), a);
      else if constexpr(K == 0xb1) return bit_select(c, a, bit_not(b));
      else if constexpr(K == 0xb2) return bit_select(b, bit_and(a, c), bit_or(a, c));
      else if constexpr(K == 0xb3) return bit_or(bit_and(a, c), bit_not(b));
      else if constexpr(K == 0xb4) return bit_xor(bit_notand(c, b), a);
      else if constexpr(K == 0xb5) return bit_or(bit_notand(b, a), bit_xor(a, bit_not(c)));
      else if constexpr(K == 0xb6) return bit_or(bit_and(a, c), bit_xor(a, b, c));
      else if constexpr(K == 0xb7) return bit_not(bit_and(b, bit_xor(a, c)));
      else if constexpr(K == 0xb8) return bit_or(bit_and(b, c), bit_notand(b, a));
      else if constexpr(K == 0xb9) return bit_or(bit_and(a, c), bit_xor(b, bit_not(c)));
      else if constexpr(K == 0xba) return bit_or(bit_notand(b, a), c);
      else if constexpr(K == 0xbb) return bit_or(c, bit_not(b));
      else if constexpr(K == 0xbc) return bit_or(bit_and(a, c), bit_xor(a, b));
      else if constexpr(K == 0xbd) return bit_or(bit_xor(a, b), bit_xor(a, bit_not(c)));
      else if constexpr(K == 0xbe) return bit_or(c, bit_xor(b, a));
      else if constexpr(K == 0xbf) return bit_or(c,bit_not(bit_and(b, a)));
      else if constexpr(K == 0xc0) return bit_and(b, a);
      else if constexpr(K == 0xc1) return bit_notand(bit_xor(a, b), bit_or(a, bit_not(c)));
      else if constexpr(K == 0xc2) return bit_notand(bit_xor(b, a), bit_or(a, c));
      else if constexpr(K == 0xc3) return bit_not(bit_xor(b, a));
      else if constexpr(K == 0xc4) return bit_notand(bit_notand(a, c), b);
      else if constexpr(K == 0xc5) return bit_or(bit_and(a, b), bit_notand(a, bit_not(c)));
      else if constexpr(K == 0xc6) return bit_xor(bit_notand(a, c), b);
      else if constexpr(K == 0xc7) return bit_or(bit_notand(c, b), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0xc8) return bit_and(b, bit_or(a, c));
      else if constexpr(K == 0xc9) return bit_not(bit_xor(b, bit_or(a, c)));
      else if constexpr(K == 0xca) return bit_or(bit_and(a, b), bit_notand(a, c));
      else if constexpr(K == 0xcb) return bit_or(bit_and(b, c), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0xcc) return b;
      else if constexpr(K == 0xcd) return bit_or(b, bit_not(bit_or(a, c)));
      else if constexpr(K == 0xce) return bit_or(bit_notand(a, c), b);
      else if constexpr(K == 0xcf) return bit_or(b,bit_not(a));
      else if constexpr(K == 0xd0) return bit_notand(bit_notand(b, c), a);
      else if constexpr(K == 0xd1) return bit_or(bit_not(bit_or(b, c)), bit_and(a, b));
      else if constexpr(K == 0xd2) return bit_xor(bit_notand(b, c), a);
      else if constexpr(K == 0xd3) return bit_or(bit_notand(c, a), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0xd4) return bit_or(bit_notand(c, b),  bit_notand(bit_xor(b, c), a));
      else if constexpr(K == 0xd5) return bit_or(bit_and(a, b), bit_not(c));
      else if constexpr(K == 0xd6) return bit_or(bit_and(a, b), bit_xor(b, a, c));
      else if constexpr(K == 0xd7) return bit_not(bit_and(c, bit_xor(b, a)));
      else if constexpr(K == 0xd8) return bit_or(bit_and(c, b), bit_notand(c, a));
      else if constexpr(K == 0xd9) return bit_or(bit_and(a, b), bit_xor(b, bit_not(c)));
      else if constexpr(K == 0xda) return bit_or(bit_and(a, b), bit_xor(a, c));
      else if constexpr(K == 0xdb) return bit_or(bit_xor(a, c), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0xdc) return bit_or(bit_notand(c, a), b);
      else if constexpr(K == 0xdd) return bit_or(b, bit_not(c));
      else if constexpr(K == 0xde) return bit_or(b, bit_xor(a, c));
      else if constexpr(K == 0xdf) return bit_or(b, bit_not(bit_and(a, c)));
      else if constexpr(K == 0xe0) return bit_and(a, bit_or(b, c));
      else if constexpr(K == 0xe1) return bit_not(bit_xor(a, bit_or(b, c)));
      else if constexpr(K == 0xe2) return bit_or(bit_and(b, a),  bit_notand(b, c));
      else if constexpr(K == 0xe3) return bit_or(bit_and(a, c), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0xe4) return bit_select(c, a, b);
      else if constexpr(K == 0xe5) return bit_or(bit_and(a, b), bit_xor(a, bit_not(c)));
      else if constexpr(K == 0xe6) return bit_or(bit_and(a, b), bit_xor(b, c));
      else if constexpr(K == 0xe7) return bit_or(bit_xor(b, c), bit_xor(a, bit_not(b)));
      else if constexpr(K == 0xe8) return bit_or(bit_and(b, c), bit_and(a, bit_xor(b, c)));
      else if constexpr(K == 0xe9) return bit_or(bit_and(a, b), bit_xor(b, a, bit_not(c)));
      else if constexpr(K == 0xea) return bit_or(c, bit_and(b, a));
      else if constexpr(K == 0xeb) return bit_or(c, bit_not( bit_xor(b, a)));
      else if constexpr(K == 0xec) return bit_or(b, bit_and(a, c));
      else if constexpr(K == 0xed) return bit_or(b, bit_not(bit_xor(a, c)));
      else if constexpr(K == 0xee) return bit_or(c, b);
      else if constexpr(K == 0xef) return bit_or(b, bit_or(bit_not(a), c));
      else if constexpr(K == 0xf0) return a;
      else if constexpr(K == 0xf1) return bit_or(a, bit_not(bit_or(b, c)));
      else if constexpr(K == 0xf2) return bit_or(bit_notand(b, c), a);
      else if constexpr(K == 0xf3) return bit_or(a, bit_not(b));
      else if constexpr(K == 0xf4) return bit_or(bit_notand(c, b), a);
      else if constexpr(K == 0xf5) return bit_or(a, bit_not(c));
      else if constexpr(K == 0xf6) return bit_or(a, bit_xor(b, c));
      else if constexpr(K == 0xf7) return bit_or(a, bit_not(bit_and(b, c)));
      else if constexpr(K == 0xf8) return bit_or(a, bit_and(b, c));
      else if constexpr(K == 0xf9) return bit_or(a, bit_not(bit_xor(b, c)));
      else if constexpr(K == 0xfa) return bit_or(c, a);
      else if constexpr(K == 0xfb) return bit_or(a, bit_or(bit_not(b), c));
      else if constexpr(K == 0xfc) return bit_or(b, a);
      else if constexpr(K == 0xfd) return bit_or(a, b, bit_not(c));
      else if constexpr(K == 0xfe) return bit_or(a, b, c);
      else if constexpr(K == 0xff) return eve::allbits(as(a));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_ternary.hpp>
#endif
