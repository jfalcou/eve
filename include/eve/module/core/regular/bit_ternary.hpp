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
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_xor.cpp}
//================================================================================================
  inline constexpr auto bit_ternary = functor<bit_ternary_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
//    template < bit_tern K, typename T0, typename T1, typename T2, callable_options O>
//     EVE_FORCEINLINE  bit_value_t<T0, T1, T2> bit_ternary_(EVE_REQUIRES(cpu_)
//                                                          , O const &
//                                                          , std::integral_constant<bit_tern, K> const &
//                                                          , [[maybe_unused]] T0 const & a
//                                                          , [[maybe_unused]] T1 const & b
//                                                          , [[maybe_unused]] T2 const & c
//                                                          ) noexcept
//     {
//       constexpr int k = to_integer(K);
//       return bit_ternary(integral_constant<int, k>(), a, b, c);
//   }

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
      else if constexpr(K == 0x67) // function=((b xor c) or ((a or b) xor 1)), lowered=((b xor c) or ((a or b) xor 1)), set=automat
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_or(a, b);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x68) // function=(a ? (b xor c) : (b and c)), lowered=((a and (b xor c)) or (a notand (b and c))), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_and(a, t0);
        const T t2 = bit_and(b, c);
        const T t3 = bit_notand(a, t2);
        const T t4 = bit_or(t1, t3);
        return t4;
      }
      else if constexpr(K == 0x69) // function=(a xnor (b xor c)), lowered=((a xor (b xor c)) xor 1), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_xor(a, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0x6a) // function=(c xor (b and a)), lowered=(c xor (b and a)), set=intel
      {
        const T t0 = bit_and(b, a);
        const T t1 = bit_xor(c, t0);
        return t1;
      }
      else if constexpr(K == 0x6b) // function=((not (a) and c) or ((a xor 1) xor (b xor c))), lowered=((a notand c) or ((a xor 1) xor (b xor c))), set=automat
      {
        const T t0 = bit_notand(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_xor(b, c);
        const T t3 = bit_xor(t1, t2);
        const T t4 = bit_or(t0, t3);
        return t4;
      }
      else if constexpr(K == 0x6c) // function=(b xor (a and c)), lowered=(b xor (a and c)), set=intel
      {
        const T t0 = bit_and(a, c);
        const T t1 = bit_xor(b, t0);
        return t1;
      }
      else if constexpr(K == 0x6d) // function=((not (a) and b) or ((a xor 1) xor (b xor c))), lowered=((a notand b) or ((a xor 1) xor (b xor c))), set=automat
      {
        const T t0 = bit_notand(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_xor(b, c);
        const T t3 = bit_xor(t1, t2);
        const T t4 = bit_or(t0, t3);
        return t4;
      }
      else if constexpr(K == 0x6e) // function=((not (a) and b) or (b xor c)), lowered=((a notand b) or (b xor c)), set=automat
      {
        const T t0 = bit_notand(a, b);
        const T t1 = bit_xor(b, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x6f) // function=((b xor c) or (a xor 1)), lowered=((b xor c) or (a xor 1)), set=automat
      {
        const T t0 = bit_xor(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x70) // function=(a and (b nand c)), lowered=((b and c) notand a), set=intel
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_notand(t0, a);
        return t1;
      }
      else if constexpr(K == 0x71) // function=((b nor c) or (a and (b xor c))), lowered=(((b or c) xor 1) or (a and (b xor c))), set=optimized
      {
        const T t0 = bit_or(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_xor(b, c);
        const T t3 = bit_and(a, t2);
        const T t4 = bit_or(t1, t3);
        return t4;
      }
      else if constexpr(K == 0x72) // function=(c ? not (b) : a), lowered=((b notand c) or (c notand a)), set=intel
      {
        const T t0 = bit_notand(b, c);
        const T t1 = bit_notand(c, a);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x73) // function=((not (c) and a) or (b xor 1)), lowered=((c notand a) or (b xor 1)), set=automat
      {
        const T t0 = bit_notand(c, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x74) // function=(b ? not (c) : a), lowered=((c notand b) or (b notand a)), set=intel
      {
        const T t0 = bit_notand(c, b);
        const T t1 = bit_notand(b, a);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x75) // function=((not (b) and a) or (c xor 1)), lowered=((b notand a) or (c xor 1)), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x76) // function=((not (b) and a) or (b xor c)), lowered=((b notand a) or (b xor c)), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T t1 = bit_xor(b, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x77) // function=(c nand b), lowered=((c and b) xor 1), set=intel
      {
        const T t0 = bit_and(c, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        return t1;
      }
      else if constexpr(K == 0x78) // function=(a xor (b and c)), lowered=(a xor (b and c)), set=intel
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_xor(a, t0);
        return t1;
      }
      else if constexpr(K == 0x79) // function=((not (b) and a) or ((b xor 1) xor (a xor c))), lowered=((b notand a) or ((b xor 1) xor (a xor c))), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, c);
        const T t3 = bit_xor(t1, t2);
        const T t4 = bit_or(t0, t3);
        return t4;
      }
      else if constexpr(K == 0x7a) // function=((not (b) and a) or (a xor c)), lowered=((b notand a) or (a xor c)), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T t1 = bit_xor(a, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x7b) // function=((a xor c) or (b xor 1)), lowered=((a xor c) or (b xor 1)), set=automat
      {
        const T t0 = bit_xor(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x7c) // function=((not (c) and a) or (a xor b)), lowered=((c notand a) or (a xor b)), set=automat
      {
        const T t0 = bit_notand(c, a);
        const T t1 = bit_xor(a, b);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x7d) // function=((a xor b) or (c xor 1)), lowered=((a xor b) or (c xor 1)), set=automat
      {
        const T t0 = bit_xor(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x7e) // function=((a xor b) or (a xor c)), lowered=((a xor b) or (a xor c)), set=automat
      {
        const T t0 = bit_xor(a, b);
        const T t1 = bit_xor(a, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x7f) // function=(((a and b) and c) xor 1), lowered=(((a and b) and c) xor 1), set=automat
      {
        const T t0 = bit_and(a, b);
        const T t1 = bit_and(t0, c);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0x80) // function=(a and (b and c)), lowered=(a and (b and c)), set=optimized
      {
        return bit_and(a, b, c);
      }
      else if constexpr(K == 0x81) // function=(not ((a xor c)) and (a xor (b xor 1))), lowered=((a xor c) notand (a xor (b xor 1))), set=automat
      {
        const T t0 = bit_xor(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_notand(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x82) // function=(c and (b xnor a)), lowered=((b xor a) notand c), set=intel
      {
        const T t0 = bit_xor(b, a);
        const T t1 = bit_notand(t0, c);
        return t1;
      }
      else if constexpr(K == 0x83) // function=(not ((a xor b)) and ((a xor 1) or c)), lowered=((a xor b) notand ((a xor 1) or c)), set=automat
      {
        const T t0 = bit_xor(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_or(t1, c);
        const T t3 = bit_notand(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x84) // function=(b and (a xnor c)), lowered=((a xor c) notand b), set=intel
      {
        const T t0 = bit_xor(a, c);
        const T t1 = bit_notand(t0, b);
        return t1;
      }
      else if constexpr(K == 0x85) // function=(not ((a xor c)) and (b or (c xor 1))), lowered=((a xor c) notand (b or (c xor 1))), set=automat
      {
        const T t0 = bit_xor(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_or(b, t1);
        const T t3 = bit_notand(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x86) // function=((b or c) and (c xor (a xor b))), lowered=((b or c) and (c xor (a xor b))), set=automat
      {
        const T t0 = bit_or(b, c);
        const T t1 = bit_xor(a, b);
        const T t2 = bit_xor(c, t1);
        const T t3 = bit_and(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x87) // function=(a xnor (b and c)), lowered=((a xor (b and c)) xor 1), set=intel
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_xor(a, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0x88) // function=(c and b), lowered=(c and b), set=intel
      {
        const T t0 = bit_and(c, b);
        return t0;
      }
      else if constexpr(K == 0x89) // function=(not ((b xor c)) and ((a xor 1) or b)), lowered=((b xor c) notand ((a xor 1) or b)), set=automat
      {
        const T t0 = bit_xor(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_or(t1, b);
        const T t3 = bit_notand(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x8a) // function=(not ((not (b) and a)) and c), lowered=((b notand a) notand c), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T t1 = bit_notand(t0, c);
        return t1;
      }
      else if constexpr(K == 0x8b) // function=(b ? c : not (a)), lowered=((b and c) or (b notand (a xor 1))), set=intel
      {
        const T t0 = bit_and(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_notand(b, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x8c) // function=(not ((not (c) and a)) and b), lowered=((c notand a) notand b), set=automat
      {
        const T t0 = bit_notand(c, a);
        const T t1 = bit_notand(t0, b);
        return t1;
      }
      else if constexpr(K == 0x8d) // function=(c ? b : not (a)), lowered=((c and b) or (c notand (a xor 1))), set=intel
      {
        const T t0 = bit_and(c, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_notand(c, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x8e) // function=((b and c) or (not (a) and (b xor c))), lowered=((b and c) or (a notand (b xor c))), set=optimized
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_xor(b, c);
        const T t2 = bit_notand(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x8f) // function=((b and c) or (a xor 1)), lowered=((b and c) or (a xor 1)), set=automat
      {
        const T t0 = bit_and(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(a, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x90) // function=(a and (b xnor c)), lowered=((b xor c) notand a), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_notand(t0, a);
        return t1;
      }
      else if constexpr(K == 0x91) // function=(not ((b xor c)) and (a or (b xor 1))), lowered=((b xor c) notand (a or (b xor 1))), set=automat
      {
        const T t0 = bit_xor(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_or(a, t1);
        const T t3 = bit_notand(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x92) // function=((a or c) and (c xor (a xor b))), lowered=((a or c) and (c xor (a xor b))), set=automat
      {
        const T t0 = bit_or(a, c);
        const T t1 = bit_xor(a, b);
        const T t2 = bit_xor(c, t1);
        const T t3 = bit_and(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x93) // function=(b xnor (a and c)), lowered=((b xor (a and c)) xor 1), set=intel
      {
        const T t0 = bit_and(a, c);
        const T t1 = bit_xor(b, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0x94) // function=((a or b) and (b xor (a xor c))), lowered=((a or b) and (b xor (a xor c))), set=automat
      {
        const T t0 = bit_or(a, b);
        const T t1 = bit_xor(a, c);
        const T t2 = bit_xor(b, t1);
        const T t3 = bit_and(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x95) // function=(c xnor (b and a)), lowered=((c xor (b and a)) xor 1), set=intel
      {
        const T t0 = bit_and(b, a);
        const T t1 = bit_xor(c, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0x96) // function=(a xor (b xor c)), lowered=(a xor (b xor c)), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_xor(a, t0);
        return t1;
      }
      else if constexpr(K == 0x97) // function=(a ? (b xnor c) : (b nand c)), lowered=(((b xor c) notand a) or (a notand ((b and c) xor 1))), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_notand(t0, a);
        const T t2 = bit_and(b, c);
        const T c1 = allbits(as<T>());
        const T t3 = bit_xor(t2, c1);
        const T t4 = bit_notand(a, t3);
        const T t5 = bit_or(t1, t4);
        return t5;
      }
      else if constexpr(K == 0x98) // function=(not ((b xor c)) and (a or b)), lowered=((b xor c) notand (a or b)), set=automat
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_or(a, b);
        const T t2 = bit_notand(t0, t1);
        return t2;
      }
      else if constexpr(K == 0x99) // function=(c xnor b), lowered=((c xor b) xor 1), set=intel
      {
        const T t0 = bit_xor(c, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        return t1;
      }
      else if constexpr(K == 0x9a) // function=((not (b) and a) xor c), lowered=((b notand a) xor c), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T t1 = bit_xor(t0, c);
        return t1;
      }
      else if constexpr(K == 0x9b) // function=((not (a) and c) or (b xor (c xor 1))), lowered=((a notand c) or (b xor (c xor 1))), set=automat
      {
        const T t0 = bit_notand(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(b, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x9c) // function=((not (c) and a) xor b), lowered=((c notand a) xor b), set=automat
      {
        const T t0 = bit_notand(c, a);
        const T t1 = bit_xor(t0, b);
        return t1;
      }
      else if constexpr(K == 0x9d) // function=((not (a) and b) or (b xor (c xor 1))), lowered=((a notand b) or (b xor (c xor 1))), set=automat
      {
        const T t0 = bit_notand(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(b, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x9e) // function=((b and c) or (c xor (a xor b))), lowered=((b and c) or (c xor (a xor b))), set=automat
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_xor(a, b);
        const T t2 = bit_xor(c, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0x9f) // function=(a nand (b xor c)), lowered=((a and (b xor c)) xor 1), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_and(a, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0xa0) // function=(c and a), lowered=(c and a), set=intel
      {
        const T t0 = bit_and(c, a);
        return t0;
      }
      else if constexpr(K == 0xa1) // function=(not ((a xor c)) and (a or (b xor 1))), lowered=((a xor c) notand (a or (b xor 1))), set=automat
      {
        const T t0 = bit_xor(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_or(a, t1);
        const T t3 = bit_notand(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xa2) // function=(not ((not (a) and b)) and c), lowered=((a notand b) notand c), set=automat
      {
        const T t0 = bit_notand(a, b);
        const T t1 = bit_notand(t0, c);
        return t1;
      }
      else if constexpr(K == 0xa3) // function=(a ? c : not (b)), lowered=((a and c) or (a notand (b xor 1))), set=intel
      {
        const T t0 = bit_and(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_notand(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xa4) // function=(not ((a xor c)) and (a or b)), lowered=((a xor c) notand (a or b)), set=automat
      {
        const T t0 = bit_xor(a, c);
        const T t1 = bit_or(a, b);
        const T t2 = bit_notand(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xa5) // function=(c xnor a), lowered=((c xor a) xor 1), set=intel
      {
        const T t0 = bit_xor(c, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        return t1;
      }
      else if constexpr(K == 0xa6) // function=((not (a) and b) xor c), lowered=((a notand b) xor c), set=automat
      {
        const T t0 = bit_notand(a, b);
        const T t1 = bit_xor(t0, c);
        return t1;
      }
      else if constexpr(K == 0xa7) // function=((not (b) and c) or (a xor (c xor 1))), lowered=((b notand c) or (a xor (c xor 1))), set=automat
      {
        const T t0 = bit_notand(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xa8) // function=(c and (a or b)), lowered=(c and (a or b)), set=intel
      {
        const T t0 = bit_or(a, b);
        const T t1 = bit_and(c, t0);
        return t1;
      }
      else if constexpr(K == 0xa9) // function=(c xnor (b or a)), lowered=((c xor (b or a)) xor 1), set=intel
      {
        const T t0 = bit_or(b, a);
        const T t1 = bit_xor(c, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0xaa) // function=c, lowered=c, set=intel
      {
        return c;
      }
      else if constexpr(K == 0xab) // function=(c or (b nor a)), lowered=(c or ((b or a) xor 1)), set=intel
      {
        const T t0 = bit_or(b, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(c, t1);
        return t2;
      }
      else if constexpr(K == 0xac) // function=(a ? c : b), lowered=((a and c) or (a notand b)), set=intel
      {
        return eve::bit_select(a, c, b);
      }
      else if constexpr(K == 0xad) // function=((b and c) or (a xor (c xor 1))), lowered=((b and c) or (a xor (c xor 1))), set=automat
      {
        const T t0 = bit_and(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xae) // function=((not (a) and b) or c), lowered=((a notand b) or c), set=automat
      {
        const T t0 = bit_notand(a, b);
        const T t1 = bit_or(t0, c);
        return t1;
      }
      else if constexpr(K == 0xaf) // function=(c or not (a)), lowered=(c or (a xor 1)), set=intel
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(a, c1);
        const T t1 = bit_or(c, t0);
        return t1;
      }
      else if constexpr(K == 0xb0) // function=(not ((not (c) and b)) and a), lowered=((c notand b) notand a), set=automat
      {
        const T t0 = bit_notand(c, b);
        const T t1 = bit_notand(t0, a);
        return t1;
      }
      else if constexpr(K == 0xb1) // function=(c ? a : not (b)), lowered=((c and a) or (c notand (b xor 1))), set=intel
      {
        const T t0 = bit_and(c, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_notand(c, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xb2) // function=(b ? (a and c) : (a or c)), lowered=((b and (a and c)) or (b notand (a or c))), set=intel
      {
        const T t0 = bit_and(a, c);
        const T t1 = bit_and(b, t0);
        const T t2 = bit_or(a, c);
        const T t3 = bit_notand(b, t2);
        const T t4 = bit_or(t1, t3);
        return t4;
      }
      else if constexpr(K == 0xb3) // function=((a and c) or (b xor 1)), lowered=((a and c) or (b xor 1)), set=automat
      {
        const T t0 = bit_and(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xb4) // function=((not (c) and b) xor a), lowered=((c notand b) xor a), set=automat
      {
        const T t0 = bit_notand(c, b);
        const T t1 = bit_xor(t0, a);
        return t1;
      }
      else if constexpr(K == 0xb5) // function=((not (b) and a) or (a xor (c xor 1))), lowered=((b notand a) or (a xor (c xor 1))), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xb6) // function=((a and c) or (c xor (a xor b))), lowered=((a and c) or (c xor (a xor b))), set=automat
      {
        const T t0 = bit_and(a, c);
        const T t1 = bit_xor(a, b);
        const T t2 = bit_xor(c, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xb7) // function=(b nand (a xor c)), lowered=((b and (a xor c)) xor 1), set=intel
      {
        const T t0 = bit_xor(a, c);
        const T t1 = bit_and(b, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0xb8) // function=(b ? c : a), lowered=((b and c) or (b notand a)), set=intel
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_notand(b, a);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xb9) // function=((a and c) or (b xor (c xor 1))), lowered=((a and c) or (b xor (c xor 1))), set=automat
      {
        const T t0 = bit_and(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(b, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xba) // function=((not (b) and a) or c), lowered=((b notand a) or c), set=automat
      {
        const T t0 = bit_notand(b, a);
        const T t1 = bit_or(t0, c);
        return t1;
      }
      else if constexpr(K == 0xbb) // function=(c or not (b)), lowered=(c or (b xor 1)), set=intel
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(b, c1);
        const T t1 = bit_or(c, t0);
        return t1;
      }
      else if constexpr(K == 0xbc) // function=((a and c) or (a xor b)), lowered=((a and c) or (a xor b)), set=automat
      {
        const T t0 = bit_and(a, c);
        const T t1 = bit_xor(a, b);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xbd) // function=((a xor b) or (a xor (c xor 1))), lowered=((a xor b) or (a xor (c xor 1))), set=automat
      {
        const T t0 = bit_xor(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xbe) // function=(c or (b xor a)), lowered=(c or (b xor a)), set=intel
      {
        const T t0 = bit_xor(b, a);
        const T t1 = bit_or(c, t0);
        return t1;
      }
      else if constexpr(K == 0xbf) // function=(c or (b nand a)), lowered=(c or ((b and a) xor 1)), set=intel
      {
        const T t0 = bit_and(b, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(c, t1);
        return t2;
      }
      else if constexpr(K == 0xc0) // function=(b and a), lowered=(b and a), set=intel
      {
        const T t0 = bit_and(b, a);
        return t0;
      }
      else if constexpr(K == 0xc1) // function=(not ((a xor b)) and (a or (c xor 1))), lowered=((a xor b) notand (a or (c xor 1))), set=automat
      {
        const T t0 = bit_xor(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_or(a, t1);
        const T t3 = bit_notand(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xc2) // function=(not ((a xor b)) and (a or c)), lowered=((a xor b) notand (a or c)), set=automat
      {
        const T t0 = bit_xor(a, b);
        const T t1 = bit_or(a, c);
        const T t2 = bit_notand(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xc3) // function=(b xnor a), lowered=((b xor a) xor 1), set=intel
      {
        const T t0 = bit_xor(b, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        return t1;
      }
      else if constexpr(K == 0xc4) // function=(not ((not (a) and c)) and b), lowered=((a notand c) notand b), set=automat
      {
        const T t0 = bit_notand(a, c);
        const T t1 = bit_notand(t0, b);
        return t1;
      }
      else if constexpr(K == 0xc5) // function=(a ? b : not (c)), lowered=((a and b) or (a notand (c xor 1))), set=intel
      {
        const T t0 = bit_and(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_notand(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xc6) // function=((not (a) and c) xor b), lowered=((a notand c) xor b), set=automat
      {
        const T t0 = bit_notand(a, c);
        const T t1 = bit_xor(t0, b);
        return t1;
      }
      else if constexpr(K == 0xc7) // function=((not (c) and b) or (a xor (b xor 1))), lowered=((c notand b) or (a xor (b xor 1))), set=automat
      {
        const T t0 = bit_notand(c, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xc8) // function=(b and (a or c)), lowered=(b and (a or c)), set=intel
      {
        const T t0 = bit_or(a, c);
        const T t1 = bit_and(b, t0);
        return t1;
      }
      else if constexpr(K == 0xc9) // function=(b xnor (a or c)), lowered=((b xor (a or c)) xor 1), set=intel
      {
        const T t0 = bit_or(a, c);
        const T t1 = bit_xor(b, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0xca) // function=(a ? b : c), lowered=((a and b) or (a notand c)), set=intel
      {
        const T t0 = bit_and(a, b);
        const T t1 = bit_notand(a, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xcb) // function=((b and c) or (a xor (b xor 1))), lowered=((b and c) or (a xor (b xor 1))), set=automat
      {
        const T t0 = bit_and(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xcc) // function=b, lowered=b, set=intel
      {
        return b;
      }
      else if constexpr(K == 0xcd) // function=(b or (a nor c)), lowered=(b or ((a or c) xor 1)), set=intel
      {
        const T t0 = bit_or(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(b, t1);
        return t2;
      }
      else if constexpr(K == 0xce) // function=((not (a) and c) or b), lowered=((a notand c) or b), set=automat
      {
        const T t0 = bit_notand(a, c);
        const T t1 = bit_or(t0, b);
        return t1;
      }
      else if constexpr(K == 0xcf) // function=(b or not (a)), lowered=(b or (a xor 1)), set=intel
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(a, c1);
        const T t1 = bit_or(b, t0);
        return t1;
      }
      else if constexpr(K == 0xd0) // function=(not ((not (b) and c)) and a), lowered=((b notand c) notand a), set=automat
      {
        const T t0 = bit_notand(b, c);
        const T t1 = bit_notand(t0, a);
        return t1;
      }
      else if constexpr(K == 0xd1) // function=((b nor c) or (a and b)), lowered=(((b or c) xor 1) or (a and b)), set=optimized
      {
        const T t0 = bit_or(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_and(a, b);
        const T t3 = bit_or(t1, t2);
        return t3;
      }
      else if constexpr(K == 0xd2) // function=((not (b) and c) xor a), lowered=((b notand c) xor a), set=automat
      {
        const T t0 = bit_notand(b, c);
        const T t1 = bit_xor(t0, a);
        return t1;
      }
      else if constexpr(K == 0xd3) // function=((not (c) and a) or (a xor (b xor 1))), lowered=((c notand a) or (a xor (b xor 1))), set=automat
      {
        const T t0 = bit_notand(c, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xd4) // function=((b and not (c)) or (a and (b xnor c))), lowered=((c notand b) or ((b xor c) notand a)), set=optimized
      {
        const T t0 = bit_notand(c, b);
        const T t1 = bit_xor(b, c);
        const T t2 = bit_notand(t1, a);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xd5) // function=((a and b) or (c xor 1)), lowered=((a and b) or (c xor 1)), set=automat
      {
        const T t0 = bit_and(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xd6) // function=((a and b) or (b xor (a xor c))), lowered=((a and b) or (b xor (a xor c))), set=automat
      {
        const T t0 = bit_and(a, b);
        const T t1 = bit_xor(a, c);
        const T t2 = bit_xor(b, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xd7) // function=(c nand (b xor a)), lowered=((c and (b xor a)) xor 1), set=intel
      {
        const T t0 = bit_xor(b, a);
        const T t1 = bit_and(c, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0xd8) // function=(c ? b : a), lowered=((c and b) or (c notand a)), set=intel
      {
        const T t0 = bit_and(c, b);
        const T t1 = bit_notand(c, a);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xd9) // function=((a and b) or (b xor (c xor 1))), lowered=((a and b) or (b xor (c xor 1))), set=automat
      {
        const T t0 = bit_and(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(b, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xda) // function=((a and b) or (a xor c)), lowered=((a and b) or (a xor c)), set=automat
      {
        const T t0 = bit_and(a, b);
        const T t1 = bit_xor(a, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xdb) // function=((a xor c) or (a xor (b xor 1))), lowered=((a xor c) or (a xor (b xor 1))), set=automat
      {
        const T t0 = bit_xor(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xdc) // function=((not (c) and a) or b), lowered=((c notand a) or b), set=automat
      {
        const T t0 = bit_notand(c, a);
        const T t1 = bit_or(t0, b);
        return t1;
      }
      else if constexpr(K == 0xdd) // function=(b or not (c)), lowered=(b or (c xor 1)), set=intel
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(c, c1);
        const T t1 = bit_or(b, t0);
        return t1;
      }
      else if constexpr(K == 0xde) // function=(b or (a xor c)), lowered=(b or (a xor c)), set=intel
      {
        const T t0 = bit_xor(a, c);
        const T t1 = bit_or(b, t0);
        return t1;
      }
      else if constexpr(K == 0xdf) // function=(b or (a nand c)), lowered=(b or ((a and c) xor 1)), set=intel
      {
        const T t0 = bit_and(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(b, t1);
        return t2;
      }
      else if constexpr(K == 0xe0) // function=(a and (b or c)), lowered=(a and (b or c)), set=intel
      {
        const T t0 = bit_or(b, c);
        const T t1 = bit_and(a, t0);
        return t1;
      }
      else if constexpr(K == 0xe1) // function=(a xnor (b or c)), lowered=((a xor (b or c)) xor 1), set=intel
      {
        const T t0 = bit_or(b, c);
        const T t1 = bit_xor(a, t0);
        const T c1 = allbits(as<T>());
        const T t2 = bit_xor(t1, c1);
        return t2;
      }
      else if constexpr(K == 0xe2) // function=(b ? a : c), lowered=((b and a) or (b notand c)), set=intel
      {
        const T t0 = bit_and(b, a);
        const T t1 = bit_notand(b, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xe3) // function=((a and c) or (a xor (b xor 1))), lowered=((a and c) or (a xor (b xor 1))), set=automat
      {
        const T t0 = bit_and(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xe4) // function=(c ? a : b), lowered=((c and a) or (c notand b)), set=intel
      {
        const T t0 = bit_and(c, a);
        const T t1 = bit_notand(c, b);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xe5) // function=((a and b) or (a xor (c xor 1))), lowered=((a and b) or (a xor (c xor 1))), set=automat
      {
        const T t0 = bit_and(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xe6) // function=((a and b) or (b xor c)), lowered=((a and b) or (b xor c)), set=automat
      {
        const T t0 = bit_and(a, b);
        const T t1 = bit_xor(b, c);
        const T t2 = bit_or(t0, t1);
        return t2;
      }
      else if constexpr(K == 0xe7) // function=((b xor c) or (a xor (b xor 1))), lowered=((b xor c) or (a xor (b xor 1))), set=automat
      {
        const T t0 = bit_xor(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(b, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xe8) // function=((b and c) or (a and (b xor c))), lowered=((b and c) or (a and (b xor c))), set=optimized
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_xor(b, c);
        const T t2 = bit_and(a, t1);
        const T t3 = bit_or(t0, t2);
        return t3;
      }
      else if constexpr(K == 0xe9) // function=((a and b) or (b xor (a xor (c xor 1)))), lowered=((a and b) or (b xor (a xor (c xor 1)))), set=automat
      {
        const T t0 = bit_and(a, b);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(c, c1);
        const T t2 = bit_xor(a, t1);
        const T t3 = bit_xor(b, t2);
        const T t4 = bit_or(t0, t3);
        return t4;
      }
      else if constexpr(K == 0xea) // function=(c or (b and a)), lowered=(c or (b and a)), set=intel
      {
        const T t0 = bit_and(b, a);
        const T t1 = bit_or(c, t0);
        return t1;
      }
      else if constexpr(K == 0xeb) // function=(c or (b xnor a)), lowered=(c or ((b xor a) xor 1)), set=intel
      {
        const T t0 = bit_xor(b, a);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(c, t1);
        return t2;
      }
      else if constexpr(K == 0xec) // function=(b or (a and c)), lowered=(b or (a and c)), set=intel
      {
        const T t0 = bit_and(a, c);
        const T t1 = bit_or(b, t0);
        return t1;
      }
      else if constexpr(K == 0xed) // function=(b or (a xnor c)), lowered=(b or ((a xor c) xor 1)), set=intel
      {
        const T t0 = bit_xor(a, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(b, t1);
        return t2;
      }
      else if constexpr(K == 0xee) // function=(c or b), lowered=(c or b), set=intel
      {
        const T t0 = bit_or(c, b);
        return t0;
      }
      else if constexpr(K == 0xef) // function=(b or ((a xor 1) or c)), lowered=(b or ((a xor 1) or c)), set=automat
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(a, c1);
        const T t1 = bit_or(t0, c);
        const T t2 = bit_or(b, t1);
        return t2;
      }
      else if constexpr(K == 0xf0) // function= a, lowered= a, set=intel
      {
        return a;
      }
      else if constexpr(K == 0xf1) // function=(a or (b nor c)), lowered=(a or ((b or c) xor 1)), set=intel
      {
        const T t0 = bit_or(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(a, t1);
        return t2;
      }
      else if constexpr(K == 0xf2) // function=((not (b) and c) or a), lowered=((b notand c) or a), set=automat
      {
        const T t0 = bit_notand(b, c);
        const T t1 = bit_or(t0, a);
        return t1;
      }
      else if constexpr(K == 0xf3) // function=(a or not (b)), lowered=(a or (b xor 1)), set=intel
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(b, c1);
        const T t1 = bit_or(a, t0);
        return t1;
      }
      else if constexpr(K == 0xf4) // function=((not (c) and b) or a), lowered=((c notand b) or a), set=automat
      {
        const T t0 = bit_notand(c, b);
        const T t1 = bit_or(t0, a);
        return t1;
      }
      else if constexpr(K == 0xf5) // function=(a or not (c)), lowered=(a or (c xor 1)), set=intel
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(c, c1);
        const T t1 = bit_or(a, t0);
        return t1;
      }
      else if constexpr(K == 0xf6) // function=(a or (b xor c)), lowered=(a or (b xor c)), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T t1 = bit_or(a, t0);
        return t1;
      }
      else if constexpr(K == 0xf7) // function=(a or (b nand c)), lowered=(a or ((b and c) xor 1)), set=intel
      {
        const T t0 = bit_and(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(a, t1);
        return t2;
      }
      else if constexpr(K == 0xf8) // function=(a or (b and c)), lowered=(a or (b and c)), set=intel
      {
        const T t0 = bit_and(b, c);
        const T t1 = bit_or(a, t0);
        return t1;
      }
      else if constexpr(K == 0xf9) // function=(a or (b xnor c)), lowered=(a or ((b xor c) xor 1)), set=intel
      {
        const T t0 = bit_xor(b, c);
        const T c1 = allbits(as<T>());
        const T t1 = bit_xor(t0, c1);
        const T t2 = bit_or(a, t1);
        return t2;
      }
      else if constexpr(K == 0xfa) // function=(c or a), lowered=(c or a), set=intel
      {
        const T t0 = bit_or(c, a);
        return t0;
      }
      else if constexpr(K == 0xfb) // function=(a or ((b xor 1) or c)), lowered=(a or ((b xor 1) or c)), set=automat
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(b, c1);
        const T t1 = bit_or(t0, c);
        const T t2 = bit_or(a, t1);
        return t2;
      }
      else if constexpr(K == 0xfc) // function=(b or a), lowered=(b or a), set=intel
      {
        const T t0 = bit_or(b, a);
        return t0;
      }
      else if constexpr(K == 0xfd) // function=(a or (b or (c xor 1))), lowered=(a or (b or (c xor 1))), set=automat
      {
        const T c1 = allbits(as<T>());
        const T t0 = bit_xor(c, c1);
        const T t1 = bit_or(b, t0);
        const T t2 = bit_or(a, t1);
        return t2;
      }
      else if constexpr(K == 0xfe) // function=(a or (b or c)), lowered=(a or (b or c)), set=intel
      {
        const T t0 = bit_or(b, c);
        const T t1 = bit_or(a, t0);
        return t1;
      }
      else if constexpr(K == 0xff) // function=1, lowered=1, set=intel
      {
        const T c1 = allbits(as<T>());
        return c1;
      }
    }
  }
}
