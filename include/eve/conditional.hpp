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

    C condition_;
  };

  //================================================================================================
  // Helper structure to encode conditional expression selecting all or nothing
  //================================================================================================
  template<bool IsNone> struct ignore_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = IsNone;
    static constexpr bool is_complete     = true;

    template<typename T> auto mask(as_<T> const&) const
    {
      return eve::as_logical_t<T>(is_inverted);
    }
  };

  inline constexpr ignore_<false> ignore_all  = {};
  inline constexpr ignore_<true>  ignore_none = {};

  //================================================================================================
  // Helper structure to encode ignoring the last N elements
  //================================================================================================
  struct ignore_last
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_last(int n) noexcept : index_(n) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      constexpr auto card = cardinal_v<T> - 1;
      return Iota(eve::as_<T>()) < (card-index_);
    }

    int index_;
  };

  //================================================================================================
  // Helper structure to encode ignoring the first N elements
  //================================================================================================
  struct ignore_first
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr ignore_first(int n) noexcept : index_(n) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      return Iota(eve::as_<T>()) >= index_;
    }

    int index_;
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
            : begin_(b.index_), end_(e.index_)
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
            : begin_(b.index_), end_(e.index_)
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

    int begin_, end_;
  };

  keep_between(int,int)                   -> keep_between<false>;
  keep_between(ignore_first, ignore_last) -> keep_between<true>;
}
