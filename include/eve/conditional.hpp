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

namespace eve
{
  //================================================================================================
  // Concept for conditional expression
  //================================================================================================
  template<typename T> concept conditional_expr = requires(T a)
  {
    { T::has_alternative      };
    { T::is_inverted          };
    { a.mask(as_<int>())      };
    { a.condition(as_<int>()) };
  };

  //================================================================================================
  // Helper structure to encode conditional expression with alternative
  //================================================================================================
  template<typename C, typename V> struct if_or_
  {
    static constexpr bool has_alternative = true;
    static constexpr bool is_inverted     = false;

    if_or_(C const& c, V const& v) : condition_(c), alternative(v) {}

    template<typename T> auto mask(as_<T> const&)       const { return condition_; }
    template<typename T> auto condition(as_<T> const&)  const { return condition_; }

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

    if_not_or_(C const& c, V const& v) : condition_(c), alternative(v) {}

    template<typename T> auto mask(as_<T> const&)       const { return !condition_;  }
    template<typename T> auto condition(as_<T> const&)  const { return condition_;   }

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

    if_(C const& c) : condition_(c) {}

    template<typename V>
    auto else_(V v) const { return if_or_(condition_,v); }

    template<typename T> auto mask(as_<T> const&)       const { return condition_; }
    template<typename T> auto condition(as_<T> const&)  const { return condition_; }

    C condition_;
  };

  //================================================================================================
  // Helper structure to encode negated conditional expression without alternative
  //================================================================================================
  template<typename C> struct if_not_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = true;

    if_not_(C const& c) : condition_(c) {}

    template<typename V>
    auto else_(V v) const { return if_not_or_(condition_,v); }

    template<typename T> auto mask(as_<T> const&)       const { return !condition_; }
    template<typename T> auto condition(as_<T> const&)  const { return condition_;  }

    C condition_;
  };

  //================================================================================================
  // Helper structure to encode conditional based on indexing
  //================================================================================================
  template<bool IsNone> struct ignore_
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = IsNone;

    template<typename T> auto mask(as_<T> const&) const
    {
      return eve::as_logical_t<T>(is_inverted);
    }

    template<typename T> auto condition(as_<T> const& tgt)  const { return mask(tgt);  }
  };

  inline constexpr ignore_<false> ignore_all = {};
  inline constexpr ignore_<false> keep_none  = {};

  inline constexpr ignore_<true> ignore_none = {};
  inline constexpr ignore_<true> keep_all    = {};

  struct ignore_last
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;

    ignore_last(int n) : index_(n) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      constexpr auto card = cardinal_v<T>;
      return Iota(eve::as_<T>()) < (card-index_);
    }

    template<typename T> auto condition(as_<T> const& tgt)  const { return mask(tgt);  }

    int index_;
  };

  struct ignore_first
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;

    ignore_first(int n) : index_(n) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      return Iota(eve::as_<T>()) >= index_;
    }

    template<typename T> auto condition(as_<T> const& tgt)  const { return mask(tgt);  }

    int index_;
  };

  struct ignore_between
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;

    ignore_between(int b, int e) : begin_(b), end_(e) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      auto const i = Iota(eve::as_<T>());
      return (i < begin_) || (i > end_);
    }

    template<typename T> auto condition(as_<T> const& tgt)  const { return mask(tgt);  }

    int begin_, end_;
  };

  struct ignore_except
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;

    ignore_except(int b, int e) : begin_(b), end_(e) {}

    template<typename T> auto mask(as_<T> const&) const
    {
      auto const i = Iota(eve::as_<T>());
      return (i >= begin_) && (i <= end_);
    }

    template<typename T> auto condition(as_<T> const& tgt)  const { return mask(tgt);  }

    int begin_, end_;
  };
}
