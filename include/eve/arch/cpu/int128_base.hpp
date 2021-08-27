//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <bitset>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <cmath>
#include <cassert>
#include <bit>

#define EVE_EMULATE_INT128

#ifdef EVE_EMULATE_INT128
# undef SPY_SIMD_SUPPORTS_INT128
#endif

namespace eve
{
  //================================================================================================
  //! @addtogroup simd
  //! @{
  //================================================================================================
  //! @brief int128_base type
  //!
  //! **Required header:** `#include <eve/int128_base.hpp>`
  //!
  //! eve::int128_base
  //!
  //!This header file defines the common part of 128-bit integer types, `uint128` and `int128`.
  //!
  //================================================================================================
  template<typename, typename> struct int128_base;

  typedef int128_base<int64_t, uint64_t> int128_t;
  typedef int128_base<uint64_t, uint64_t> uint128_t;

  template<integral_scalar_value T>
  struct half_mask : std::integral_constant<T, (T(1) << (4 * sizeof(T))) - T(1)> {
  };

  template < unsigned_scalar_value H,  integral_scalar_value L> struct
#if defined(SPY_SIMD_SUPPORTS_INT128)
  alignas(__int128)
#else
    alignas((sizeof(std::uint64_t) * 2))
#endif
    int128_base final
  {
    static_assert(sizeof(H) == sizeof(L), "low type, high type should have same size");
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    L lo_;
    H hi_;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    H hi_;
    L lo_;
#else  // byte order
#error "Unsupported byte order: must be little-endian or big-endian."
#endif  // byte order

        struct integral_tag {
        };
        struct signed_integral_tag : integral_tag {
        };
        struct unsigned_integral_tag : integral_tag {
        };
        struct float_tag {
        };
        template<size_t>
        struct size_constant {
        };

    private:
        template<class T>
        constexpr int128_base(T value_, signed_integral_tag, size_constant<8>) :
                int128_base(-(value_ < 0), value_) {}

        template<class T>
        constexpr int128_base(T value_, unsigned_integral_tag, size_constant<8>) :
                int128_base(0, L(value_)) {}

        template<class T>
        constexpr int128_base(T value_, integral_tag, size_constant<16>) : // NOLINT explicit
                int128_base(H(value_ >> 64U), L(value_)) {} // NOLINT signed shift

  public:

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================
    //! Default constructor
    EVE_FORCEINLINE constexpr int128_base() noexcept {}

 
    EVE_FORCEINLINE constexpr  int128_base( integral_scalar_value auto hi
                                          , integral_scalar_value auto lo) noexcept
    requires (sizeof(lo_) <= 8)&&(sizeof(hi_) <= 8)
      : lo_{static_cast<L>(lo)}, hi_{static_cast<H>(hi)} {}

#ifdef SPY_SIMD_SUPPORTS_INT128
      
      constexpr explicit int128_base(__int128 val_) :
        int128_base(val_, signed_integral_tag(), size_constant<sizeof(val_)>()) {}
        
      constexpr explicit int128_base(unsigned __int128 val_) :
          int128_base(val_, unsigned_integral_tag(), size_constant<sizeof(val_)>()) {}
          
      constexpr explicit operator unsigned __int128() const {
        return static_cast<unsigned __int128>(high_) << 64U | static_cast<unsigned __int128>(low_);
      }

      constexpr explicit operator __int128() const {
        return static_cast<__int128>(static_cast<unsigned __int128>(*this));
      }
      
//      constexpr int128_base(__int128 v) noexcept
//         : lo_{static_cast<L>(v & ~L{0})}
//         , hi_{static_cast<L>(static_cast<unsigned __int128>(v) >> 64)} {};
      
//       constexpr int128_base(unsigned __int128 v) noexcept
//         : lo_{static_cast<L>(v & ~L{0})}
//         , hi_{static_cast<L>(v >> 64)} {}
      
#endif

//   constexpr int128_base(int128 v) noexcept
//    : lo_{low(v)}, hi_{static_cast<L>(hig(v))} {}

    //! from floating values
    template<class T> constexpr int128_base(T val, float_tag) :
        int128_base(H(std::ldexp(val, -64)) - (val < 0), L(val_)) {}
      
    constexpr explicit int128_base(float val_)  : int128_base(val_, float_tag()) {}        
    constexpr explicit int128_base(double val_) : int128_base(val_, float_tag()) {}

   //! from smaller size ints
      
    constexpr int128_base(std::int64_t val) : 
                int128_base(val_, signed_integral_tag(), size_constant<sizeof(val)>()) {}

    constexpr int128_base(std::int32_t val) :
                int128_base(static_cast<std::int64_t>(val)) {} 

    constexpr int128_base(std::int16_t val_) :
                int128_base(std::int32_t(val_)) {} 

    constexpr int128_base(std::int8_t val_) :
                int128_base(std::int16_t(val_)) {} 
      
    constexpr int128_base(std::uint64_t val_) : 
                int128_base(val_, unsigned_integral_tag(), size_constant<sizeof(val_)>()) {}

    constexpr int128_base(std::uint64_t val_) :
                int128_base(val_, signed_integral_tag(), size_constant<sizeof(val_)>()) {}

     constexpr int128_base(unsigned_scalar_value auto val_)
       requires(sizeof(val_) <= 4) :
       int128_base(std::int64_t(val_)) {}
     

    //! Copy constructor
    EVE_FORCEINLINE constexpr int128_base(int128_base const&) noexcept = default;

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assign another int128_base
    EVE_FORCEINLINE constexpr int128_base &operator=(int128_base const& v)  noexcept =  default;

    //==============================================================================================
    //! @}
    //==============================================================================================
    //==============================================================================================
    //! @name lo,  hi
    //! @{
    //==============================================================================================
    EVE_FORCEINLINE constexpr L & lo()  {return lo_; };
    EVE_FORCEINLINE constexpr L & hi()  {return hi_; };
    EVE_FORCEINLINE constexpr L lo() const {return lo_; };
    EVE_FORCEINLINE constexpr L hi() const {return hi_; };

    EVE_FORCEINLINE constexpr friend L low(int128_base v)  {return v.lo_; };
    EVE_FORCEINLINE constexpr friend L high(int128_base v)  {return v.hi_; };

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name conversion operators
    //! @{
    //==============================================================================================
    EVE_FORCEINLINE constexpr operator bool()          const noexcept { return lo_ || hi_; }
    EVE_FORCEINLINE constexpr operator L() const noexcept { return lo_;  }
    EVE_FORCEINLINE constexpr operator std::uint32_t() const noexcept { return static_cast<std::uint32_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::uint16_t() const noexcept { return static_cast<std::uint16_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::uint8_t()  const noexcept { return static_cast<std::uint8_t>(lo_); }
    EVE_FORCEINLINE constexpr operator std::int64_t()  const noexcept { return static_cast<std::int64_t>(lo_); }
    EVE_FORCEINLINE constexpr operator std::int32_t()  const noexcept { return static_cast<std::uint32_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::int16_t()  const noexcept { return static_cast<std::uint16_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::int8_t()   const noexcept { return static_cast<std::uint8_t>(lo_); }

#ifdef SPY_SIMD_SUPPORTS_INT128
    EVE_FORCEINLINE constexpr explicit operator __int128() const noexcept {
      return (static_cast<__int128>(hi_) << 64) + lo_;
    }

    EVE_FORCEINLINE constexpr explicit operator unsigned __int128() const noexcept {
      return (static_cast<unsigned __int128>(hi_) << 64) + lo_;
    }
#endif

    EVE_FORCEINLINE operator float() const noexcept {
      return static_cast<float>(lo_) + std::ldexp(static_cast<float>(hi_), 64);
    }

    EVE_FORCEINLINE operator double() const noexcept {
      return static_cast<double>(lo_) + std::ldexp(static_cast<double>(hi_), 64);
    }

    void swap( int128_base& other )
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
    // ==
    constexpr friend bool operator==(int128_base lhs, eve::integral_scalar_value auto rhs) {
      return int128_base(rhs) == lhs;
    }

    constexpr friend bool operator==(eve::integral_scalar_value auto lhs, int128_base rhs) {
      return int128_base(lhs) == rhs;
    }

    constexpr friend bool operator==(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return static_cast<unsigned __int128>(lhs) == static_cast<unsigned __int128>(rhs);
#else
      return (low(lhs) == low(rhs)) && (high(lhs) == high(rhs));
#endif
      }

    constexpr friend bool operator!=(int128_base lhs, eve::integral_scalar_value auto rhs) {
      return int128_base(rhs) != lhs;
    }
    constexpr friend bool operator!=(eve::integral_scalar_value auto lhs, int128_base rhs) {
      return int128_base(lhs) != rhs;
    }
    constexpr friend bool operator!=(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
        return static_cast<unsigned __int128>(lhs) !=
          static_cast<unsigned __int128>(rhs);
#else
      return (low(lhs) != low(rhs)) || (high(lhs) != high(rhs));
#endif
      }

    constexpr friend bool operator!(int128_base val) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return !static_cast<unsigned __int128>(val);
#else
      return !low(val) && !high(val);
#endif
    }

    constexpr  friend bool operator<(int128_base lhs, int128_base rhs)
    {
#ifdef SPY_SIMD_SUPPORTS_INT128
      return static_cast<unsigned __int128>(lhs) <
        static_cast<unsigned __int128>(rhs);
#else
      return (high(lhs) == high(rhs))
        ? (low(lhs) < low(rhs))
        : (high(lhs) < high(rhs));
#endif
    }

    constexpr friend bool operator>(int128_base lhs, int128_base rhs) { return rhs < lhs; }
    constexpr friend bool operator<=(int128_base lhs, int128_base rhs){ return !(lhs > rhs);}
    constexpr friend bool operator>=(int128_base lhs, int128_base rhs) { return !(lhs < rhs);  }

    //arithmetic operations
    friend int128_base operator/(int128_base lhs, eve::integral_scalar_value auto rhs)
    {
      return lhs/int128_base(rhs);
    }
    friend int128_base operator/(eve::integral_scalar_value auto lhs, int128_base rhs )
    {
      return int128_base(lhs)/rhs;
    }

    friend int128_base operator/(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return static_cast<int128_base>(static_cast<unsigned __int128>(lhs)/static_cast<unsigned __int128>(rhs));
#else
      int128_base quotient = 0;
      int128_base remainder = 0;
      DivModImpl(lhs, rhs, &quotient, &remainder);
      return quotient;
#endif
     }

    friend int128_base operator%(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return static_cast<int128_base>(static_cast<unsigned __int128>(lhs)%static_cast<unsigned __int128>(rhs));
#else
      int128_base quotient = 0;
      int128_base remainder = 0;
      DivModImpl(lhs, rhs, &quotient, &remainder);
      return remainder;
#endif
    }

    EVE_FORCEINLINE int128_base& operator<<=(int amount) {
      *this = *this << amount;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator>>=(int amount) {
      *this = *this >> amount;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator+=(int128_base other) {
      *this = *this + other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator-=(int128_base other) {
      *this = *this - other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator*=(int128_base other) {
      *this = *this * other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator/=(int128_base other) {
      *this = *this / other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator%=(int128_base other) {
      *this = *this % other;
      return *this;
    }

     EVE_FORCEINLINE int128_base& operator+=(eve::unsigned_value auto other) {
      *this = *this + other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator-=(eve::unsigned_value auto other) {
      *this = *this - other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator*=(eve::unsigned_value auto other) {
      *this = *this * other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator/=(eve::unsigned_value auto other) {
      *this = *this / other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator%=(eve::unsigned_value auto other) {
      *this = *this % other;
      return *this;
    }

    EVE_FORCEINLINE int128_base operator++(int) {
      int128_base tmp(*this);
      *this += 1;
      return tmp;
    }

    EVE_FORCEINLINE int128_base operator--(int) {
      int128_base tmp(*this);
      *this -= 1;
      return tmp;
    }

    EVE_FORCEINLINE int128_base& operator++() {
      *this += 1;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator--() {
      *this -= 1;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator|=(int128_base other) {
      *this = *this | other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator&=(int128_base other) {
      *this = *this & other;
      return *this;
    }

    EVE_FORCEINLINE int128_base& operator^=(int128_base other) {
      *this = *this ^ other;
      return *this;
}

    friend EVE_FORCEINLINE void swap(int128_base &lhs, int128_base &rhs) noexcept
    {
      lhs.swap(rhs);
    }

    friend EVE_FORCEINLINE constexpr int128_base operator+(int128_base val) {
      return val;
    }

    friend EVE_FORCEINLINE constexpr int128_base operator-(int128_base val) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return -static_cast<unsigned __int128>(val);
#else
      return int128_base(
        ~high(val) + static_cast<L>(low(val) == 0),
        ~low(val) + 1);
#endif
    }

    friend EVE_FORCEINLINE int128_base operator+(int128_base lhs, eve::integral_scalar_value auto rhs) { return lhs+int128_base(rhs); }
    friend EVE_FORCEINLINE int128_base operator+(eve::integral_scalar_value auto lhs, int128_base rhs) { return rhs+lhs; }

    friend EVE_FORCEINLINE int128_base operator+(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
  return static_cast<unsigned __int128>(lhs) +
         static_cast<unsigned __int128>(rhs);
#else
      return AddResult(
        int128_base(high(lhs) + high(rhs), low(lhs) + low(rhs))
        , lhs);
#endif
    }

    friend EVE_FORCEINLINE int128_base operator-(int128_base lhs, eve::integral_scalar_value auto rhs) { return lhs-int128_base(rhs); }
    friend EVE_FORCEINLINE int128_base operator-(eve::integral_scalar_value auto lhs, int128_base rhs) { return int128_base(lhs)-rhs; }
    friend EVE_FORCEINLINE constexpr int128_base operator-(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
  return static_cast<unsigned __int128>(lhs) -
         static_cast<unsigned __int128>(rhs);
#else
      return SubResult(
        int128_base(high(lhs) - high(rhs), low(lhs) - low(rhs)),
        lhs, rhs);
#endif
    }

    friend EVE_FORCEINLINE int128_base operator*(int128_base lhs, unsigned_scalar_value auto rhs)
    {
      return int128_base(rhs)*lhs;
    }
     friend EVE_FORCEINLINE int128_base operator*(unsigned_scalar_value auto lhs, int128_base rhs)
    {
      return rhs*lhs;
    }

    friend EVE_FORCEINLINE int128_base operator*(int128_base lhs, int128_base rhs)
    {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return static_cast<unsigned __int128>(lhs) * static_cast<unsigned __int128>(rhs);
#elif defined(_MSC_VER) && defined(_M_X64)
      L carry;
      L low = _umul128(Int128_BaseLow64(lhs), Int128_BaseLow64(rhs), &carry);
      return int128_base(lo(lhs) * hi(rhs) + hi(lhs) * lo(rhs) + carry, low);
#else
      L a32 = low(lhs) >> 32;
      L a00 = low(lhs) & 0xffffffff;
      L b32 = low(rhs) >> 32;
      L b00 = low(rhs) & 0xffffffff;
      int128_base result(high(lhs) * low(rhs) + low(lhs) * high(rhs) + a32 * b32, a00 * b00);
      result += int128_base(a32 * b00) << 32;
      result += int128_base(a00 * b32) << 32;
      return result;
#endif
    }

    //==============================================================================================
    //shift operators
    //==============================================================================================
    friend EVE_FORCEINLINE constexpr int128_base operator<<(int128_base lhs, int amount) {
#ifdef SPY_SIMD_SUPPORTS_INT128
      return static_cast<unsigned __int128>(lhs) << amount;
#else
      // L shifts of >= 64 are undefined, so we will need some
      // special-casing.
      return amount >= 64 ? int128_base(low(lhs) << (amount - 64), 0)
        : amount == 0 ? lhs
        : int128_base((high(lhs) << amount) | (low(lhs) >> (64 - amount)),
                  low(lhs) << amount);
#endif
    }

    friend EVE_FORCEINLINE constexpr int128_base operator>>(int128_base lhs, int amount) {
#ifdef SPY_SIMD_SUPPORTS_INT128
      return static_cast<unsigned __int128>(lhs) >> amount;
#else
      // L shifts of >= 64 are undefined, so we will need some
      // special-casing.
      return amount >= 64 ? int128_base(0, high(lhs) >> (amount - 64))
        : amount == 0 ? lhs
        : int128_base(high(lhs) >> amount,
                  (low(lhs) >> amount) | (high(lhs) << (64 - amount)));
#endif
    }

   // bitwise operators.

    friend EVE_FORCEINLINE  int128_base operator~(int128_base val) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return ~static_cast<unsigned __int128>(val);
#else
      return int128_base(~high(val), ~low(val));
#endif
    }

    friend EVE_FORCEINLINE  int128_base operator|(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return static_cast<unsigned __int128>(lhs) |
        static_cast<unsigned __int128>(rhs);
#else
      return int128_base(high(lhs) | high(rhs), low(lhs) | low(rhs));
#endif
    }

    friend EVE_FORCEINLINE  int128_base operator&(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return static_cast<unsigned __int128>(lhs) &
        static_cast<unsigned __int128>(rhs);
#else
      return int128_base(high(lhs) & high(rhs), low(lhs) & low(rhs));
#endif
    }

    friend EVE_FORCEINLINE  int128_base operator^(int128_base lhs, int128_base rhs) {
#if defined(SPY_SIMD_SUPPORTS_INT128)
      return static_cast<unsigned __int128>(lhs) ^
        static_cast<unsigned __int128>(rhs);
#else
      return int128_base(high(lhs) ^ high(rhs), low(lhs) ^ low(rhs));
#endif
    }

    //==============================================================================================
    // Stream insertion operator
    //==============================================================================================
    friend EVE_FORCEINLINE std::ostream& operator<<(std::ostream& os, int128_base v) {
      std::ios_base::fmtflags flags = os.flags();
      std::string rep = Int128_BaseToFormattedString(v, flags);

      // Add the requisite padding.
      std::streamsize width = os.width(0);
      if (static_cast<size_t>(width) > rep.size()) {
        std::ios::fmtflags adjustfield = flags & std::ios::adjustfield;
        if (adjustfield == std::ios::left) {
          rep.append(width - rep.size(), os.fill());
        } else if (adjustfield == std::ios::internal &&
                   (flags & std::ios::showbase) &&
                   (flags & std::ios::basefield) == std::ios::hex && (low(v)  || high(v)) ) //TODO
        {
          rep.insert(2, width - rep.size(), os.fill());
        } else {
          rep.insert(0, width - rep.size(), os.fill());
        }
      }

      return os << rep;
    }

  private:

    static EVE_FORCEINLINE int128_base AddResult(int128_base result, int128_base lhs)
    {
      // check for carry
      return (result.lo_ < low(lhs))
        ? int128_base(result.hi_ + 1, result.lo_)
        : result;
    }

    static EVE_FORCEINLINE int128_base SubResult(int128_base result, int128_base lhs, int128_base rhs) {
      // check for augment
      return (low(lhs) < low(rhs))
        ? int128_base(result.hi_ - 1, result.lo_)
        : result;
    }

  public:

    // Long division/modulo for int128_base implemented using the shift-subtract
    // division algorithm adapted from:
    // https://stackoverflow.com/questions/5386377/division-without-using
    static EVE_FORCEINLINE void DivModImpl(int128_base dividend, int128_base divisor, int128_base* quotient_ret,
                                           int128_base* remainder_ret) {
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

      int128_base denominator = divisor;
      int128_base quotient = 0;

      auto Fls128 = [](int128_base n){
        // Returns the 0-based position of the last set bit (i.e., most significant bit)
        // in the given int128_base. The argument is not 0.
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
          quotient |= 1;
        }
        denominator >>= 1;
      }

      *quotient_ret = quotient;
      *remainder_ret = dividend;
    }


    static std::string Int128_BaseToFormattedString(int128_base v, std::ios_base::fmtflags flags)
    {
      // Select a divisor which is the largest power of the base < 2^64.
      int128_base div;
      int div_base_log;
      switch (flags & std::ios::basefield) {
      case std::ios::hex:
        div = 0x1000000000000000;  // 16^15
        div_base_log = 15;
        break;
      case std::ios::oct:
        div = 01000000000000000000000;  // 8^21
        div_base_log = 21; //21;
        break;
      default:  // std::ios::dec
        div = 10000000000000000000u;  // 10^19
        div_base_log = 19;
        break;
      }

      // Now piece together the int128_base representation from three chunks of the
      // original value, each less than "div" and therefore representable as a
      // L.
      std::ostringstream os;
      std::ios_base::fmtflags copy_mask =
        std::ios::basefield | std::ios::showbase | std::ios::uppercase;
      os.setf(flags & copy_mask, copy_mask);
      int128_base high = v;
      int128_base low;
      DivModImpl(high, div, &high, &low);
      int128_base mid;
      DivModImpl(high, div, &high, &mid);
      if (high.lo_ != 0)
      {
        os << (high.lo_);
        os << std::noshowbase << std::setfill('0') << std::setw(div_base_log);
        os << (mid.lo_);
        os << std::setw(div_base_log);
      }
      else if (mid.lo_ != 0)
      {
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

  class hl
  {
  public:
    hl(int128_base n) : n_ (n) {}
    std::ostream &operator()(std::ostream & out) const
    {
      std::ios_base::fmtflags flags = out.flags();
      std::string m;
      switch (flags & std::ios::basefield) {
      case std::ios::hex:
        m = "0x";
        break;
      case std::ios::oct:
        m = "0";
        break;
      default:  // std::ios::dec
        m = "";
        break;
      }
      out << '(' << m << n_.hi() << ", " << m << n_.lo() << ')';
      return out;
    }
  private:
    int128_base n_;
  };

  std::ostream &operator <<(std::ostream &out, hl n)
  {
    return n(out);
  }

  inline namespace literals {
    namespace impl_ {
      template<char _Ch, int Rad>
      struct static_digit : std::integral_constant<int,
                                                   '0' <= _Ch && _Ch <= '9' ? _Ch - '0' :
      'a' <= _Ch && _Ch <= 'z' ? _Ch - 'a' + 10 :
      'A' <= _Ch && _Ch <= 'Z' ? _Ch - 'A' + 10 : Rad> {
        static_assert(Rad > static_digit::value, "character not a digit");
      };

      template<class, int, char ...>
      struct int128_literal_radix;

      template<class T, int Rad, char _Ch>
      struct int128_literal_radix<T, Rad, _Ch> {
        constexpr operator T() const { return T(static_digit<_Ch, Rad>::value); } // NOLINT explicit

        constexpr T operator()(T v) const { return v * T(Rad) + *this; }
      };

      template<class T, int Rad, char _Ch, char ..._Args>
      struct int128_literal_radix<T, Rad, _Ch, _Args...> {
        int128_literal_radix<T, Rad, _Ch> _Cur;
        int128_literal_radix<T, Rad, _Args...> _Tgt;

        constexpr operator T() const { return _Tgt(_Cur); }; // NOLINT explicit

        constexpr T operator()(T v) const { return _Tgt(_Cur(v)); };
      };

      template<class T, char ..._Args>
      struct int128_literal : int128_literal_radix<T, 10, _Args...> {
      };
      template<class T>
      struct int128_literal<T, '0'> : int128_literal_radix<T, 10, '0'> {
      };
      template<class T, char ..._Args>
      struct int128_literal<T, '0', _Args...> : int128_literal_radix<T, 8, _Args...> {
      };
      template<class T, char ..._Args>
      struct int128_literal<T, '0', 'x', _Args...> : int128_literal_radix<T, 16, _Args...> {
      };
      template<class T, char ..._Args>
      struct int128_literal<T, '0', 'X', _Args...> : int128_literal_radix<T, 16, _Args...> {
      };
      template<class T, char ..._Args>
      struct int128_literal<T, '0', 'b', _Args...> : int128_literal_radix<T, 2, _Args...> {
      };
      template<class T, char ..._Args>
      struct int128_literal<T, '0', 'B', _Args...> : int128_literal_radix<T, 2, _Args...> {
      };
    }

    template<char ..._Args>
    constexpr int128_base operator "" _u128() { return impl_::int128_literal<int128_base, _Args...>(); }

//    template<char ..._Args>
//     constexpr int128 operator "" _l128() { return impl_::int128_literal<int128, _Args...>(); }

    template<char ..._Args>
    constexpr int128_base operator "" _U128() { return impl_::int128_literal<int128_base, _Args...>(); }

//     template<char ..._Args>
//     constexpr int128 operator "" _L128() { return impl_::int128_literal<int128, _Args...>(); }
  }


}
// Specialized numeric_limits for int128_base.
namespace std {
  template <>
  class numeric_limits<eve::int128_base> {
  public:
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr float_round_style round_style = round_toward_zero;
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = true;
    static constexpr int digits = 128;
    static constexpr int digits10 = 38;
    static constexpr int max_digits10 = 0;
    static constexpr int radix = 2;
    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
#ifdef SPY_SIMD_SUPPORTS_INT128
    static constexpr bool traps = numeric_limits<unsigned __int128>::traps;
#else
    static constexpr bool traps = numeric_limits<L>::traps;
#endif
    static constexpr bool tinyness_before = false;

    static constexpr eve::int128_base (min)() { return 0; }
    static constexpr eve::int128_base lowest() { return 0; }
    static constexpr eve::int128_base (max)() {
      return eve::int128_base(std::numeric_limits<L>::max(),std::numeric_limits<L>::max()); }
    static constexpr eve::int128_base epsilon() { return 0; }
    static constexpr eve::int128_base round_error() { return 0; }
    static constexpr eve::int128_base infinity() { return 0; }
    static constexpr eve::int128_base quiet_NaN() { return 0; }
    static constexpr eve::int128_base signaling_NaN() { return 0; }
    static constexpr eve::int128_base denorm_min() { return 0; }
  };
}  // namespace std
