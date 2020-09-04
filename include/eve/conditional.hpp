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
#include <eve/detail/abi.hpp>
#include <eve/traits.hpp>
#include <eve/concept/value.hpp>
#include <iosfwd>

namespace eve
{
  //================================================================================================
  // Concept for conditional expression
  //================================================================================================
  template<typename T> concept conditional_expr = requires(T a)
  {
    { T::has_alternative  };
    { T::is_inverted      };
    { T::is_complete      };
    { a.mask(as_<int>())  };
  };

  //================================================================================================
  // Helper structure to encode conditional expression with alternative
  //================================================================================================
  template<typename C, typename V> struct if_or_
  {
    static constexpr bool has_alternative = true;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    if_or_(C const& c, V const& v) : condition_(c), alternative(v) {}

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&)  const { return condition_; }

    friend std::ostream& operator<<(std::ostream& os, if_or_ const& c)
    {
      return os << "if( " << c.condition_ << " ) else ( " << c.alternative << " )";
    }

    V alternative;
    C condition_;
  };

  //================================================================================================
  // Helper structure to encode negated conditional expression with alternative
  //================================================================================================
  template<typename C, typename V> struct if_not_or_
  {
    static constexpr bool has_alternative = true;
    static constexpr bool is_inverted     = true;
    static constexpr bool is_complete     = false;

    if_not_or_(C const& c, V const& v) : condition_(c), alternative(v) {}

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const { return condition_;  }

    friend std::ostream& operator<<(std::ostream& os, if_not_or_ const& c)
    {
      return os << "if( !" << c.condition_ << " ) else ( " << c.alternative << " )";
    }

    V alternative;
    C condition_;
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

    template<typename V> EVE_FORCEINLINE auto else_(V v) const { return if_or_(condition_,v); }
    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&)  const { return condition_; }

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

    template<typename V> EVE_FORCEINLINE auto else_(V v) const { return if_not_or_(condition_,v); }
    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&)  const { return condition_;  }

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

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      return eve::as_logical_t<T>(false);
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

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      return eve::as_logical_t<T>(true);
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

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      constexpr auto card = cardinal_v<T>;
      return Iota(eve::as_<T>()) < (card-count_);
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_last_ const& c)
    {
      return os << "ignore_last( " << c.count_ << " )";
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

    template<typename T> auto mask(as_<T> const&) const
    {
      constexpr auto card = cardinal_v<T>;
      return Iota(eve::as_<T>()) >= (card-count_);
    }

    friend std::ostream& operator<<(std::ostream& os, keep_last_ const& c)
    {
      return os << "keep_last( " << c.count_ << " )";
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

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      return Iota(eve::as_<T>()) >= count_;
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

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      return Iota(eve::as_<T>()) < count_;
    }

    friend std::ostream& operator<<(std::ostream& os, keep_first_ const& c)
    {
      return os << "keep_first( " << c.count_ << " )";
    }

    std::ptrdiff_t count_;
  };

  EVE_FORCEINLINE keep_first_ keep_first(std::ptrdiff_t n) noexcept
  {
    return {n};
  }

  //================================================================================================
  // Helper structure to encode ignoring elements in between two index
  //================================================================================================
  struct ignore_between_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_between_(std::ptrdiff_t b, std::ptrdiff_t e) noexcept : begin_(b), end_(e) {}

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      auto const i = Iota(eve::as_<T>());
      return (i < begin_) || (i > end_);
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_between_ const& c)
    {
      return os << "ignore_between( " << c.begin_ << ", " << c.end_ << " )";
    }

    std::ptrdiff_t begin_, end_;
  };

  EVE_FORCEINLINE ignore_between_ ignore_between(std::ptrdiff_t b, std::ptrdiff_t e)
  {
    return {b,e};
  }

  //================================================================================================
  // Helper structure to encode keeping elements in between two index and ignoring the rest
  //================================================================================================
  struct keep_between_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr keep_between_(std::ptrdiff_t b, std::ptrdiff_t e) noexcept : begin_(b), end_(e) {}

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      auto const i = Iota(eve::as_<T>());
      return (i >= begin_) && (i <= end_);
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

    template<typename T> EVE_FORCEINLINE auto mask(as_<T> const&) const
    {
      auto const i = Iota(eve::as_<T>());
      constexpr auto card = cardinal_v<T> - 1;
      return (i >= first_count_) && (i <= (card-last_count_));
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
