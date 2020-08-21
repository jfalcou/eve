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

    template<typename T> auto mask(as_<T> const&)  const { return condition_; }

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

    template<typename T> auto mask(as_<T> const&) const { return condition_;  }

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

    template<typename V>
    auto else_(V v) const { return if_or_(condition_,v); }

    template<typename T> auto mask(as_<T> const&)  const { return condition_; }

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

    template<typename V>
    auto else_(V v) const { return if_not_or_(condition_,v); }

    template<typename T> auto mask(as_<T> const&)  const { return condition_;  }

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

    template<typename T> auto mask(as_<T> const&) const
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

    template<typename T> auto mask(as_<T> const&) const
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
  struct ignore_last
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_last(int n) noexcept : count_(n) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      constexpr auto card = cardinal_v<T>;
      return Iota(eve::as_<T>()) < (card-count_);
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_last const& c)
    {
      return os << "ignore_last( " << c.count_ << " )";
    }

    int count_;
  };

  //================================================================================================
  // Helper structure to encode ignoring the first N elements
  //================================================================================================
  struct ignore_first
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_first(int n) noexcept : count_(n) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      return Iota(eve::as_<T>()) >= count_;
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_first const& c)
    {
      return os << "ignore_first( " << c.count_ << " )";
    }

    int count_;
  };

  //================================================================================================
  // Helper structure to encode ignoring elements in between two index
  //================================================================================================
  template<bool isRelative> struct ignore_between
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_between(int b, int e) noexcept : begin_(b), end_(e) {}

    constexpr ignore_between(ignore_first b, ignore_last e) noexcept
            : begin_(b.count_), end_(e.count_)
    {}

    template<typename T> auto mask(as_<T> const&) const
    {
      auto const i = Iota(eve::as_<T>());

      if constexpr(isRelative)
      {
        constexpr auto card = cardinal_v<T> - 1;
        return (i < begin_) || (i > (card-end_));
      }
      else
      {
        return (i < begin_) || (i > end_);
      }
    }

    friend std::ostream& operator<<(std::ostream& os, ignore_between const& c)
    {
      if constexpr(isRelative)
      {
        return os << "ignore_between( first(" << c.begin_ << "), last(" << c.end_ << ") )";
      }
      else
      {
        return os << "ignore_between( " << c.begin_ << ", " << c.end_ << " )";
      }
    }

    int begin_, end_;
  };

  ignore_between(int,int)                   -> ignore_between<false>;
  ignore_between(ignore_first, ignore_last) -> ignore_between<true>;

  //================================================================================================
  // Helper structure to encode keeping elements in between two index and ignoring the rest
  // with optional remembrance of relative indexing
  //================================================================================================
  template<bool isRelative> struct keep_between
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr keep_between(int b, int e) noexcept : begin_(b), end_(e) {}

    constexpr keep_between(ignore_first b, ignore_last e) noexcept
            : begin_(b.count_), end_(e.count_)
    {}

    template<typename T> auto mask(as_<T> const&) const
    {
      auto const i = Iota(eve::as_<T>());

      if constexpr(isRelative)
      {
        constexpr auto card = cardinal_v<T> - 1;
        return (i >= begin_) && (i <= (card-end_));
      }
      else
      {
        return (i >= begin_) && (i <= end_);
      }
    }

    friend std::ostream& operator<<(std::ostream& os, keep_between const& c)
    {
      if constexpr(isRelative)
      {
        return os << "keep_between( first(" << c.begin_ << "), last(" << c.end_ << ") )";
      }
      else
      {
        return os << "keep_between( " << c.begin_ << ", " << c.end_ << " )";
      }
    }

    int begin_, end_;
  };

  keep_between(int,int)                   -> keep_between<false>;
  keep_between(ignore_first, ignore_last) -> keep_between<true>;
}
