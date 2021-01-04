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

#include <eve/as.hpp>
#include <eve/assert.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/iota.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/traits.hpp>
#include <bitset>
#include <iosfwd>

namespace eve
{
  //================================================================================================
  // Helper structure to encode conditional expression with alternative
  //================================================================================================
  template<typename C, typename V> struct or_ : C
  {
    static constexpr bool has_alternative = true;

    or_(C const& c, V const& v) : C(c), alternative(v) {}

    template<typename T>
    EVE_FORCEINLINE auto mask(eve::as_<T> const& tgt) const { return C::mask(tgt); }

    friend std::ostream& operator<<(std::ostream& os, or_ const& c)
    {
      return os << c.condition_ << " else ( " << c.alternative << " )";
    }

    V alternative;
  };

  //================================================================================================
  // Helper structure to encode negated conditional expression with alternative
  //================================================================================================
  template<typename C, typename V> struct not_or_ : C
  {
    static constexpr bool has_alternative = true;
    static constexpr bool is_inverted     = true;

    not_or_(C const& c, V const& v) : C(c), alternative(v) {}

    template<typename T>
    EVE_FORCEINLINE auto mask(eve::as_<T> const& tgt) const { return C::mask(tgt); }

    friend std::ostream& operator<<(std::ostream& os, not_or_ const& c)
    {
      return os << "( " << c.alternative << " ) else " << c.condition_;
    }

    V alternative;
  };

  //================================================================================================
  // Helper structure to encode conditional expression without alternative
  //================================================================================================
  template<typename C> struct if_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    if_(C const& c) : condition_(c) {}

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }
    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&)  const { return condition_; }

    friend std::ostream& operator<<(std::ostream& os, if_ const& c)
    {
      return os << "if( " << c.condition_ << " )";
    }

    C condition_;
  };

  //================================================================================================
  // Helper structure to encode negated conditional expression without alternative
  //================================================================================================
  template<typename C> struct if_not_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = true;
    static constexpr bool is_complete     = false;

    if_not_(C const& c) : condition_(c) {}

    template<typename V> EVE_FORCEINLINE auto else_(V v) const { return not_or_(*this,v); }
    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&)  const { return condition_;  }

    friend std::ostream& operator<<(std::ostream& os, if_not_ const& c)
    {
      return os << "if( !" << c.condition_ << " )";
    }

    C condition_;
  };

  //================================================================================================
  // Helper structure to encode conditional expression selecting all or nothing
  //================================================================================================
  struct ignore_all_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = true;

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&) const
    {
      return eve::as_logical_t<T>(false);
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      detail::make_integer_t<sz/8,unsigned> mask = 0;
      return mask;
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return 0ULL;
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_all_ const&)
    {
      return os << "ignore_all";
    }
  };

  inline constexpr ignore_all_ ignore_all  = {};

  struct ignore_none_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = true;
    static constexpr bool is_complete     = true;

    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&) const
    {
      return eve::as_logical_t<T>(true);
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      using mask_t = detail::make_integer_t<sz/8,unsigned>;
      return static_cast<mask_t>(~0ULL);
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return sizeof(T);
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_none_ const&)
    {
      return os << "ignore_none";
    }
  };

  inline constexpr ignore_none_  ignore_none = {};

  //================================================================================================
  // Helper structure to encode ignoring the last N elements
  //================================================================================================
  struct ignore_last_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_last_(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&) const
    {
      constexpr std::ptrdiff_t card = cardinal_v<T>;
      using i_t = as_arithmetic_t<detail::as_integer_t<T>>;

      auto const m = detail::linear_ramp(eve::as_<i_t>()) < (card-count_);
      return bit_cast(m, as_<as_logical_t<T>>());
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      detail::make_integer_t<sz/8,unsigned> mask = ~(((1ULL << count_)-1) << (cardinal_v<T> - count_));
      return mask;
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_last_ const& c)
    {
      return os << "ignore_last( " << c.count_ << " )";
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return sizeof(T) - sizeof(element_type_t<T>) * count_;
    }

    std::ptrdiff_t count_;
  };

  EVE_FORCEINLINE ignore_last_ ignore_last(std::ptrdiff_t n) noexcept
  {
    return {n};
  }

  //================================================================================================
  // Helper structure to encode keeping the last N elements
  //================================================================================================
  struct keep_last_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr EVE_FORCEINLINE keep_last_(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }

    template<typename T> auto mask(eve::as_<T> const&) const
    {
      using i_t = as_arithmetic_t<detail::as_integer_t<T>>;
      constexpr std::ptrdiff_t card = cardinal_v<T>;

      auto const m = detail::linear_ramp(eve::as_<i_t>()) >= i_t(card-count_);

      return bit_cast(m, as_<as_logical_t<T>>());
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      detail::make_integer_t<sz/8,unsigned> mask = (((1ULL << count_)-1) << (cardinal_v<T> - count_));
      return mask;
    }

    friend std::ostream& operator<<(std::ostream& os, keep_last_ const& c)
    {
      return os << "keep_last( " << c.count_ << " )";
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return cardinal_v<T> - count_;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return sizeof(element_type_t<T>) * count_;
    }

    std::ptrdiff_t count_;
  };

  EVE_FORCEINLINE keep_last_ keep_last(std::ptrdiff_t n) noexcept
  {
    return {n};
  }

  //================================================================================================
  // Helper structure to encode ignoring the first N elements
  //================================================================================================
  struct ignore_first_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_first_(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&) const
    {
      using i_t = as_arithmetic_t<detail::as_integer_t<T>>;
      auto const m = detail::linear_ramp(eve::as_<i_t>()) >= i_t(count_);

      return bit_cast(m, as_<as_logical_t<T>>());
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      detail::make_integer_t<sz/8,unsigned> mask = ~count_;
      return mask;
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return count_;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return sizeof(T) - sizeof(element_type_t<T>) * count_;
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_first_ const& c)
    {
      return os << "ignore_first( " << c.count_ << " )";
    }

    std::ptrdiff_t count_;
  };

  EVE_FORCEINLINE ignore_first_ ignore_first(std::ptrdiff_t n) noexcept
  {
    return {n};
  }

  //================================================================================================
  // Helper structure to encode keep the first N elements
  //================================================================================================
  struct keep_first_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr keep_first_(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&) const
    {
      using i_t = as_arithmetic_t<detail::as_integer_t<T>>;
      auto const m = detail::linear_ramp(eve::as_<i_t>()) < i_t(count_);

      return bit_cast(m, as_<as_logical_t<T>>());
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      detail::make_integer_t<sz/8,unsigned> mask = (1ULL << count_) - 1;
      return mask;
    }

    friend std::ostream& operator<<(std::ostream& os, keep_first_ const& c)
    {
      return os << "keep_first( " << c.count_ << " )";
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return sizeof(element_type_t<T>) * count_;
    }

    std::ptrdiff_t count_;
  };

  EVE_FORCEINLINE keep_first_ keep_first(std::ptrdiff_t n) noexcept
  {
    return {n};
  }

  //================================================================================================
  // Helper structure to encode keeping elements in between two index and ignoring the rest
  //================================================================================================
  struct keep_between_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    keep_between_(std::ptrdiff_t b, std::ptrdiff_t e) noexcept : begin_(b), end_(e)
    {
      EVE_ASSERT(b<=e, "[eve::keep_between] Index mismatch for begin/end");
    }

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&) const
    {
      using i_t = as_arithmetic_t<detail::as_integer_t<T>>;
      auto const i = detail::linear_ramp(eve::as_<i_t>());
      auto const m = (i >= begin_) && (i < end_);

      return bit_cast(m, as_<as_logical_t<T>>());
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      auto const cnt = end_ - begin_;
      detail::make_integer_t<sz/8,unsigned> mask = (1ULL << cnt) - 1;
      return mask << begin_;
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return begin_;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return sizeof(element_type_t<T>) * (end_ - begin_);
    }

    friend std::ostream& operator<<(std::ostream& os, keep_between_ const& c)
    {
      return os << "keep_between( " << c.begin_ << ", " << c.end_ << " )";
    }

    std::ptrdiff_t begin_, end_;
  };

  EVE_FORCEINLINE keep_between_ keep_between(std::ptrdiff_t b, std::ptrdiff_t e)
  {
    return {b,e};
  }

  //================================================================================================
  // Helper structure to encode ignoring N elements on both extrema.
  //================================================================================================
  struct ignore_extrema_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_extrema_(std::ptrdiff_t b, std::ptrdiff_t e) noexcept
            : first_count_(b), last_count_(e)
    {}

    template<typename V> EVE_FORCEINLINE auto else_(V v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as_<T> const&) const
    {
      using i_t = as_arithmetic_t<detail::as_integer_t<T>>;
      auto const i = detail::linear_ramp(eve::as_<i_t>());
      auto const m = (i >= first_count_) && (i < (cardinal_v<T>-last_count_));

      return bit_cast(m, as_<as_logical_t<T>>());
    }

    template<typename T> EVE_FORCEINLINE auto bitmap(eve::as_<T> const&) const
    {
      constexpr auto sz = cardinal_v<T> < 8 ? 8 : cardinal_v<T>;
      auto const cnt = (cardinal_v<T>-last_count_) - first_count_;
      detail::make_integer_t<sz/8,unsigned> mask = (1ULL << cnt) - 1;
      return mask << first_count_;
    }

    template<typename T> EVE_FORCEINLINE std::ptrdiff_t offset(eve::as_<T> const&) const
    {
      return first_count_;
    }

    template<typename T> EVE_FORCEINLINE auto count(eve::as_<T> const&) const
    {
      return sizeof(element_type_t<T>) * (cardinal_v<T> - last_count_ - first_count_);
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_extrema_ const& c)
    {
      return os << "ignore( first(" << c.first_count_ << "), last(" << c.last_count_ << ") )";
    }

    std::ptrdiff_t first_count_, last_count_;
  };

  constexpr EVE_FORCEINLINE ignore_extrema_ operator&&( ignore_first_ a, ignore_last_ b) noexcept
  {
    return {a.count_, b.count_};
  }
}
