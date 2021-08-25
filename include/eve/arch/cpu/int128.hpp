//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/uint128.hpp>

#include <bitset>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <cmath>
#include <cassert>
#include <bit>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd
  //! @{
  //================================================================================================
  //! @brief int128 type
  //!
  //! **Required header:** `#include <eve/int128.hpp>`
  //!
  //! eve::int128
  //!
  //!This header file defines 128-bit integer types, `uint128` and `int128`.
  //!
  //================================================================================================
  struct uint128;
  struct int128 //little endian
  {
    std::uint64_t lo_;
    std::int64_t hi_;

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================
    //! Default constructor
    EVE_FORCEINLINE constexpr int128() noexcept {}

    //! from smaller size ints

    EVE_FORCEINLINE  constexpr  int128(integral_scalar_value auto v) noexcept
    requires (sizeof(v) <= 8)
      : lo_{static_cast<std::uint64_t>(v)}, hi_{0} {}
    EVE_FORCEINLINE constexpr  int128( integral_scalar_value auto lo
                                     , integral_scalar_value auto hi) noexcept
    requires (sizeof(lo_) <= 8)&&(sizeof(hi_) <= 8)
      : lo_{static_cast<std::uint64_t>(lo)}, hi_{static_cast<std::int64_t>(hi)} {}

#ifdef ABSL_HAVE_INTRINSIC_INT128
    constexpr int128(__int128 v) noexcept
    : lo_{static_cast<uint64_t>(v & ~uint64_t{0})},
      hi_{static_cast<uint64_t>(static_cast<unsigned __int128>(v) >> 64)} {};

    constexpr int128(unsigned __int128 v) noexcept;
    : lo_{static_cast<uint64_t>(v & ~uint64_t{0})},
        hi_{static_cast<uint64_t>(v >> 64)} {}
#endif

    static uint128 UnsignedAbsoluteValue(int128 v) {
      // Cast to uint128 before possibly negating because -Int128Min() is undefined.
      uint128 uv(v);
      return v.hi_ < 0 ? -uv : uv;
    }

    template <typename T>
    static int128 MakeInt128FromFloat(T v) {
      // Conversion when v is NaN or cannot fit into int128 would be undefined
      // behavior if using an intrinsic 128-bit integer.
      assert(std::isfinite(v) && (std::numeric_limits<T>::max_exponent <= 127 ||
                                  (v >= -std::ldexp(static_cast<T>(1), 127) &&
                                   v < std::ldexp(static_cast<T>(1), 127))));

      // We must convert the absolute value and then negate as needed, because
      // floating point types are typically sign-magnitude. Otherwise, the
      // difference between the high and low 64 bits when interpreted as two's
      // complement overwhelms the precision of the mantissa.
      uint128 result = v < 0 ? -uint128(-v) : uint128(v);
      return int128(std::bit_cast<std::int64_t>(result.hi_),
                    result.lo_);
    }
    explicit int128(float v) : int128(MakeInt128FromFloat(v)) {}
    explicit int128(double v) : int128(MakeInt128FromFloat(v)) {}
    explicit int128(long double v) : int128(MakeInt128FromFloat(v)) {}


    //! Copy constructor
    //     constexpr int128(int128 const & v) noexcept
    //     : lo_{v.lo_}, hi_{v.hi_} {}

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assign another int128
    //   EVE_FORCEINLINE constexpr int128 &operator=(int128 const& v)  noexcept =  default;


    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name conversion operators
    //! @{
    //==============================================================================================
    EVE_FORCEINLINE constexpr operator bool()          const noexcept { return lo_ || hi_; }
    EVE_FORCEINLINE constexpr operator std::uint64_t() const noexcept { return lo_;  }
    EVE_FORCEINLINE constexpr operator std::uint32_t() const noexcept { return static_cast<std::uint32_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::uint16_t() const noexcept { return static_cast<std::uint16_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::uint8_t()  const noexcept { return static_cast<std::uint8_t>(lo_); }
    EVE_FORCEINLINE constexpr operator std::int64_t()  const noexcept { return static_cast<std::int64_t>(lo_); }
    EVE_FORCEINLINE constexpr operator std::int32_t()  const noexcept { return static_cast<std::uint32_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::int16_t()  const noexcept { return static_cast<std::uint16_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::int8_t()   const noexcept { return static_cast<std::uint8_t>(lo_); }
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//     EVE_FORCEINLINE constexpr explicit operator __int128() const noexcept {
//       return (static_cast<__int128>(hi_) << 64) + lo_;
//     }

//     EVE_FORCEINLINE constexpr explicit operator unsigned __int128() noexcept const {
//       return (static_cast<unsigned __int128>(hi_) << 64) + lo_;
//     }
// #endif
    EVE_FORCEINLINE operator float() const noexcept {
      return static_cast<float>(lo_) + std::ldexp(static_cast<float>(hi_), 64);
    }

    EVE_FORCEINLINE operator double() const noexcept {
      return static_cast<double>(lo_) + std::ldexp(static_cast<double>(hi_), 64);
    }
//    EVE_FORCEINLINE constexpr auto bits()       const noexcept { return value_; }

//     EVE_FORCEINLINE constexpr auto mask() const noexcept
//     {
//       value_type that;
//       std::memcpy(&that, &value_, sizeof(value_type));
//       return that;
//     }
    void swap( int128& other )
    {
      std::swap(lo_,other.lo_);
      std::swap(hi_,other.hi_);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    // Comparison operators
    //==============================================================================================
    constexpr friend bool operator==(int128 lhs, int128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) ==
//         static_cast<unsigned __int128>(rhs);
// #else
      return (lhs.lo_ == rhs.lo_) && (lhs.hi_ == rhs.hi_);
//#endif
    }

    constexpr friend bool operator!=(int128 lhs, int128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//         return static_cast<unsigned __int128>(lhs) !=
//           static_cast<unsigned __int128>(rhs);
// #else
      return (lhs.lo_ != rhs.lo_) || (lhs.hi_ != rhs.hi_);
//#endif
    }

    constexpr  friend bool operator<(int128 lhs, int128 rhs) {
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//   return static_cast<unsigned __int128>(lhs) <
//          static_cast<unsigned __int128>(rhs);
// #else
      return (lhs.hi_ == rhs.hi_)
        ? (lhs.lo_ < rhs.lo_)
        : (lhs.hi_ < rhs.hi_);
//#endif
    }

    constexpr friend bool operator>(int128 lhs, int128 rhs) { return rhs < lhs; }

    constexpr friend bool operator<=(int128 lhs, int128 rhs) { return !(rhs < lhs); }

    constexpr friend bool operator>=(int128 lhs, int128 rhs) { return !(lhs < rhs); }

    //arithmetic operations
    constexpr friend int128 operator/(int128 lhs, int128 rhs)
    {
      assert(lhs != Int128Min() || rhs != -1);  // UB on two's complement.

      uint128 quotient = 0;
      uint128 remainder = 0;
      DivModImpl(UnsignedAbsoluteValue(lhs), UnsignedAbsoluteValue(rhs),
                 &quotient, &remainder);
      if ((lhs.hi_ < 0) != (rhs.hi_ < 0)) quotient = -quotient;
      return int128(std::bit_cast<std::int64_t>(quotient.hi_),
                    quotient.lo_);
    }

    constexpr friend int128 operator%(int128 lhs, int128 rhs) {
      assert(lhs != Int128Min() || rhs != -1);  // UB on two's complement.

      uint128 quotient = 0;
      uint128 remainder = 0;
      DivModImpl(UnsignedAbsoluteValue(lhs), UnsignedAbsoluteValue(rhs),
                 &quotient, &remainder);
      if (lhs.hi_ < 0) remainder = -remainder;
      return int128(std::bit_cast<std::int64_t>(remainder.hi_), remainder.lo_);
    }


    EVE_FORCEINLINE int128& operator<<=(int amount) {
      *this = *this << amount;
      return *this;
    }

    EVE_FORCEINLINE int128& operator>>=(int amount) {
      *this = *this >> amount;
      return *this;
    }

    EVE_FORCEINLINE int128& operator+=(int128 other) {
      *this = *this + other;
      return *this;
    }

    EVE_FORCEINLINE int128& operator-=(int128 other) {
      *this = *this - other;
      return *this;
    }

    EVE_FORCEINLINE int128& operator*=(int128 other) {
      *this = *this * other;
      return *this;
    }

    EVE_FORCEINLINE int128& operator/=(int128 other) {
      *this = *this / other;
      return *this;
    }

    EVE_FORCEINLINE int128& operator%=(int128 other) {
      *this = *this % other;
      return *this;
    }

    EVE_FORCEINLINE int128 operator++(int) {
      int128 tmp(*this);
      *this += 1;
      return tmp;
    }

    EVE_FORCEINLINE int128 operator--(int) {
      int128 tmp(*this);
      *this -= 1;
      return tmp;
    }

    EVE_FORCEINLINE int128& operator++() {
      *this += 1;
      return *this;
    }

    EVE_FORCEINLINE int128& operator--() {
      *this -= 1;
      return *this;
    }

    EVE_FORCEINLINE int128& operator|=(int128 other) {
      *this = *this | other;
      return *this;
    }

    EVE_FORCEINLINE int128& operator&=(int128 other) {
      *this = *this & other;
      return *this;
    }

    EVE_FORCEINLINE int128& operator^=(int128 other) {
      *this = *this ^ other;
      return *this;
    }

    friend EVE_FORCEINLINE void swap(int128 &lhs, int128 &rhs) noexcept
    {
      lhs.swap(rhs);
    }

    friend EVE_FORCEINLINE constexpr int128 operator+(int128 val) {
      return val;
    }

    friend EVE_FORCEINLINE constexpr int128 operator-(int128 val) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return -static_cast<unsigned __int128>(val);
// #else
      return int128(
        ~val.hi_ + static_cast<std::uint64_t>(val.lo_ == 0),
        ~val.lo_ + 1);
//#endif
    }

    friend EVE_FORCEINLINE constexpr int128 operator+(int128 lhs, int128 rhs)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//   return static_cast<unsigned __int128>(lhs) +
//          static_cast<unsigned __int128>(rhs);
// #else
      auto tmp = int128(lhs.hi_ + rhs.hi_, lhs.lo_ + rhs.lo_);
      return AddResult(tmp, lhs);
//#endif
    }

friend EVE_FORCEINLINE constexpr int128 operator-(int128 lhs, int128 rhs)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//   return static_cast<unsigned __int128>(lhs) -
//          static_cast<unsigned __int128>(rhs);
// #else
      return SubResult(
        int128(lhs.hi_ - rhs.hi_, lhs.lo_ - rhs.lo_),
        lhs, rhs);
//#endif
    }

    friend EVE_FORCEINLINE int128 operator*(int128 lhs, int128 rhs)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       // TODO(strel) Remove once alignment issues are resolved and unsigned __int128
//       // can be used for int128 storage.
//       return static_cast<unsigned __int128>(lhs) *
//         static_cast<unsigned __int128>(rhs);
// #elif defined(_MSC_VER) && defined(_M_X64)
//   uint64_t carry;
//   uint64_t low = _umul128(Int128Low64(lhs), Int128Low64(rhs), &carry);
//   return MakeInt128(Int128Low64(lhs) * Int128High64(rhs) +
//                          Int128High64(lhs) * Int128Low64(rhs) + carry,
//                      low);
// #else   // ABSL_HAVE_INTRINSIC128
      uint64_t a32 = lhs.lo_ >> 32;
      uint64_t a00 = lhs.lo_ & 0xffffffff;
      uint64_t b32 = rhs.lo_ >> 32;
      uint64_t b00 = rhs.lo_ & 0xffffffff;
      int128 result =
        int128(lhs.hi_ * rhs.lo_ +
               lhs.lo_ * rhs.hi_ + a32 * b32,
               a00 * b00);
      result += int128(a32 * b00) << 32;
      result += int128(a00 * b32) << 32;
      return result;
//#endif  // ABSL_HAVE_INTRINSIC128
    }

    //==============================================================================================
    //shift operators
    //==============================================================================================
    friend EVE_FORCEINLINE constexpr int128 operator<<(int128 lhs, int amount)
    {
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//       return static_cast<unsigned __int128>(lhs) << amount;
// #else
      // uint64_t shifts of >= 64 are undefined, so we will need some
      // special-casing.
      return amount >= 64 ? int128(lhs.lo_ << (amount - 64), 0)
        : amount == 0 ? lhs
        : int128((lhs.hi_ << amount) | (lhs.lo_ >> (64 - amount)),
                 lhs.lo_ << amount);
//#endif
    }

    friend EVE_FORCEINLINE constexpr int128 operator>>(int128 lhs, int amount)
    {
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//       return static_cast<unsigned __int128>(lhs) >> amount;
// #else
      // uint64_t shifts of >= 64 are undefined, so we will need some
      // special-casing.
      return amount >= 64 ? int128(0, lhs.hi_ >> (amount - 64))
        : amount == 0 ? lhs
        : int128(lhs.hi_ >> amount,
                 (lhs.lo_ >> amount) | (lhs.hi_ << (64 - amount)));
//#endif
    }

    // bitwise operators.

    friend EVE_FORCEINLINE  int128 operator~(int128 val)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return ~static_cast<unsigned __int128>(val);
// #else
      return int128(~val.hi_, ~val.lo_);
//#endif
    }

    friend EVE_FORCEINLINE  int128 operator|(int128 lhs, int128 rhs)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) |
//         static_cast<unsigned __int128>(rhs);
// #else
      return int128(lhs.hi_ | rhs.hi_, lhs.lo_ | rhs.lo_);
//#endif
    }

    friend EVE_FORCEINLINE  int128 operator&(int128 lhs, int128 rhs)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) &
//         static_cast<unsigned __int128>(rhs);
// #else
      return int128(lhs.hi_ & rhs.hi_, lhs.lo_ & rhs.lo_);
//#endif
    }

    friend EVE_FORCEINLINE  int128 operator^(int128 lhs, int128 rhs)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) ^
//         static_cast<unsigned __int128>(rhs);
// #else
      return int128(lhs.hi_ ^ rhs.hi_, lhs.lo_ ^ rhs.lo_);
//#endif
    }

    //==============================================================================================
    // Stream insertion operator
    //==============================================================================================
    friend EVE_FORCEINLINE std::ostream& operator<<(std::ostream& os, int128 v)
    {
      std::ios_base::fmtflags flags = os.flags();
      std::string rep;

      // Add the sign if needed.
      bool print_as_decimal =
        (flags & std::ios::basefield) == std::ios::dec ||
        (flags & std::ios::basefield) == std::ios_base::fmtflags();
      if (print_as_decimal) {
        if (v.hi_ < 0) {
          rep = "-";
        } else if (flags & std::ios::showpos) {
          rep = "+";
        }
      }
    }
  private:

//#if !defined(ABSL_HAVE_INTRINSIC_INT128)


//#endif


    // Long division/modulo for uint128 implemented using the shift-subtract
    // division algorithm adapted from:
    // https://stackoverflow.com/questions/5386377/division-without-using
    static EVE_FORCEINLINE void DivModImpl(uint128 dividend, uint128 divisor, uint128* quotient_ret,
                                           uint128* remainder_ret) {
      assert(divisor.lo_ != 0 || divisor.hi_ != 0);

      if (divisor > dividend) {
        *quotient_ret = 0;
        *remainder_ret = dividend;
        return;
      }

      if (divisor == dividend) {
        *quotient_ret = 1;
        *remainder_ret = 0;
        return;
      }

      uint128 denominator = divisor;
      uint128 quotient = 0;

      auto Fls128 = [](uint128 n){
        // Returns the 0-based position of the last set bit (i.e., most significant bit)
        // in the given uint128. The argument is not 0.
        //
        // For example:
        //   Given: 5 (decimal) == 101 (binary)
        //   Returns: 2
        return (n.hi_) ? 127 - std::countl_zero(n.hi_): 63 - std::countl_zero(n.lo_);
      };
      // Left aligns the MSB of the denominator and the dividend.
      const int shift = Fls128(dividend) - Fls128(denominator);
      denominator <<= shift;

      // Uses shift-subtract algorithm to divide dividend by denominator. The
      // remainder will be left in dividend.
      for (int i = 0; i <= shift; ++i) {
        quotient <<= 1;
        if (dividend >= denominator) {
          dividend -= denominator;
          quotient |= uint128(1);
        }
        denominator >>= 1;
      }

      *quotient_ret = quotient;
      *remainder_ret = dividend;
    }

    static EVE_FORCEINLINE uint128 AddResult(uint128 result, uint128 lhs)
    {
      // check for carry
      return (result.lo_ < lhs.lo_)
        ? uint128(result.hi_ + 1, result.lo_)
        : result;
    }

    static EVE_FORCEINLINE uint128 SubResult(uint128 result, uint128 lhs, uint128 rhs) {
      // check for augment
      return (lhs.lo_ < rhs.lo_)
        ? uint128(result.hi_ - 1, result.lo_)
        : result;
    }

    static std::string Uint128ToFormattedString(uint128 v, std::ios_base::fmtflags flags) {
      // Select a divisor which is the largest power of the base < 2^64.
      uint128 div;
      int div_base_log;
      switch (flags & std::ios::basefield) {
      case std::ios::hex:
        div = 0x1000000000000000;  // 16^15
        div_base_log = 15;
        break;
      case std::ios::oct:
        div = 01000000000000000000000;  // 8^21
        div_base_log = 21;
        break;
      default:  // std::ios::dec
        div = 10000000000000000000u;  // 10^19
        div_base_log = 19;
        break;
      }

      // Now piece together the uint128 representation from three chunks of the
      // original value, each less than "div" and therefore representable as a
      // uint64_t.
      std::ostringstream os;
      std::ios_base::fmtflags copy_mask =
        std::ios::basefield | std::ios::showbase | std::ios::uppercase;
      os.setf(flags & copy_mask, copy_mask) ;
      uint128 high = v;
      uint128 low;
      DivModImpl(high, div, &high, &low);
      uint128 mid;
      DivModImpl(high, div, &high, &mid);
      if (high.lo_ != 0) {
        os << (high.lo_);
        os << std::noshowbase << std::setfill('0') << std::setw(div_base_log);
        os << (mid.lo_);
        os << std::setw(div_base_log);
      } else if (mid.lo_ != 0) {
        os << (mid.lo_);
        os << std::noshowbase << std::setfill('0') << std::setw(div_base_log);
      }
      os << (low.lo_);
      return os.str();
    }

  };
  //================================================================================================
  //! @}
  //================================================================================================

}
