//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/assert.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/iota.hpp>
#include <eve/detail/bits.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/traits/cardinal.hpp>
#include <bitset>
#include <compare>
#include <ostream>
#include <type_traits>

namespace eve
{
  namespace detail
  {
    template <logical_simd_value Logical> struct top_bits;
  }

  //================================================================================================
  // Helper structure to encode conditional expression with alternative
  //================================================================================================
  template<typename C, typename V> struct or_ : C
  {
    static constexpr bool has_alternative = true;
    using alternative_type = V;

    or_(C const& c, V const& v) : C(c), alternative(v) {}

    template<typename T> auto rebase(T v) const
    {
      return or_<C,T>{static_cast<C const&>(*this), v};
    }

    auto map_alternative(auto op) const
    {
      auto mapped = op(alternative);
      C c = *this;
      return or_<C, decltype(mapped)>{c, mapped};
    }

    friend std::ostream& operator<<(std::ostream& os, or_ const& c)
    {
      os << static_cast<C const&>(c);
      return os << " else ( " << c.alternative << " )";
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

    if_(C c) : condition_(c) {}

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }
    template<typename T> EVE_FORCEINLINE auto mask(eve::as<T> const&)  const { return condition_; }

    friend std::ostream& operator<<(std::ostream& os, if_ const& c)
    {
      return os << "if( " << c.condition_ << " )";
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

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as<T> const&) const
    {
      return eve::as_logical_t<T>(false);
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return cardinal_v<T>;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return 0ULL;
    }

    constexpr bool friend operator==(ignore_all_ const&, ignore_all_ const&) = default;

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

    template<typename V> EVE_FORCEINLINE auto else_(V) const  {  return *this;  }

    template<typename T> EVE_FORCEINLINE auto mask(eve::as<T> const&) const
    {
      return eve::as_logical_t<T>(true);
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return cardinal_v<T>;
    }

    constexpr bool friend operator==(ignore_none_ const&, ignore_none_ const&) = default;

    friend std::ostream& operator<<(std::ostream& os, ignore_none_ const&)
    {
      return os << "ignore_none";
    }
  };

  inline constexpr ignore_none_  ignore_none = {};

  //================================================================================================
  // Helper structure to encode keep the first N elements
  //================================================================================================
  struct keep_first
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr explicit EVE_FORCEINLINE keep_first(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE as_logical_t<T> mask(eve::as<T> const&) const
    {
      using abi_t = typename T::abi_type;
      using type  = as_logical_t<T>;

      if constexpr( !abi_t::is_wide_logical )
      {
        return detail::top_bits<type>(*this).storage;
      }
      else
      {
        using i_t   = as_integer_t<typename type::mask_type>;
        if constexpr(eve::use_complete_storage<type>)
        {
          return bit_cast(detail::linear_ramp(eve::as<i_t>()) < i_t(count_), as<type>());
        }
        else
        {
          // Use the most full type to be sure to fill outside values of small wide with false
          using e_t   = eve::element_type_t<i_t>;
          using abi_t = typename i_t::abi_type;
          using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;
          return bit_cast(detail::linear_ramp(eve::as<w_t>()) < w_t(count_), as<type>());
        }
      }
    }

    constexpr bool friend operator==(keep_first const&, keep_first const&) = default;

    friend std::ostream& operator<<(std::ostream& os, keep_first const& c)
    {
      return os << "keep_first( " << c.count_ << " )";
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return cardinal_v<T> - count_;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return count_;
    }

    std::ptrdiff_t count_;
  };

  //================================================================================================
  // Helper structure to encode ignoring the last N elements
  //================================================================================================
  struct ignore_last
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr explicit EVE_FORCEINLINE ignore_last(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE as_logical_t<T> mask(eve::as<T> const& tgt) const
    {
      constexpr auto card = cardinal_v<T>;
      return keep_first{card-count_}.mask(tgt);
    }

    constexpr bool friend operator==(ignore_last const&, ignore_last const&) = default;

    friend std::ostream& operator<<(std::ostream& os, ignore_last const& c)
    {
      return os << "ignore_last( " << c.count_ << " )";
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return count_;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return cardinal_v<T> - count_;
    }

    std::ptrdiff_t count_;
  };

  //================================================================================================
  // Helper structure to encode keeping the last N elements
  //================================================================================================
  struct keep_last
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr explicit EVE_FORCEINLINE keep_last(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE as_logical_t<T> mask(eve::as<T> const&) const
    {
      using abi_t = typename T::abi_type;
      using type  = as_logical_t<T>;
      if constexpr( !abi_t::is_wide_logical )
      {
        return detail::top_bits<type>(*this).storage;
      }
      else
      {
        using i_t   = as_integer_t<typename type::mask_type>;
        constexpr std::ptrdiff_t card = cardinal_v<T>;
        if constexpr(eve::use_complete_storage<type>)
        {
          return bit_cast(detail::linear_ramp(eve::as<i_t>()) >= i_t(card-count_), as<type>());
        }
        else
        {
          // Use the most full type to be sure to fill outside values of small wide with false
          using e_t   = eve::element_type_t<i_t>;
          using abi_t = typename i_t::abi_type;
          using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;
          auto i = detail::linear_ramp(eve::as<w_t>());
          return bit_cast((i >= w_t(card-count_)) && (i < card), as<type>());
        }
      }
    }

    constexpr bool friend operator==(keep_last const&, keep_last const&) = default;

    friend std::ostream& operator<<(std::ostream& os, keep_last const& c)
    {
      return os << "keep_last( " << c.count_ << " )";
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return cardinal_v<T> - count_;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return count_;
    }

    std::ptrdiff_t count_;
  };

  //================================================================================================
  // Helper structure to encode ignoring the first N elements
  //================================================================================================
  struct ignore_first
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr explicit EVE_FORCEINLINE ignore_first(std::ptrdiff_t n) noexcept : count_(n) {}

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE as_logical_t<T> mask(eve::as<T> const& tgt) const
    {
      constexpr auto card = cardinal_v<T>;
      return keep_last{card-count_}.mask(tgt);
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return count_;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return 0;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return cardinal_v<T> - count_;
    }

    constexpr bool friend operator==(ignore_first const&, ignore_first const&) = default;

    friend std::ostream& operator<<(std::ostream& os, ignore_first const& c)
    {
      return os << "ignore_first( " << c.count_ << " )";
    }

    std::ptrdiff_t count_;
  };

  //================================================================================================
  // Helper structure to encode keeping elements in between two index and ignoring the rest
  //================================================================================================
  struct keep_between
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr EVE_FORCEINLINE keep_between(std::ptrdiff_t b, std::ptrdiff_t e) noexcept : begin_(b), end_(e)
    {
      EVE_ASSERT(b<=e, "[eve::keep_between] Index mismatch for begin/end");
    }

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE as_logical_t<T> mask(eve::as<T> const&) const
    {
      using abi_t = typename T::abi_type;
      using type  = as_logical_t<T>;

      if constexpr( !abi_t::is_wide_logical )
      {
        return detail::top_bits<type>(*this).storage;
      }
      else
      {
        using i_t = as_integer_t<typename type::mask_type>;

        if constexpr(eve::use_complete_storage<type>)
        {
          auto const i = detail::linear_ramp(eve::as<i_t>());
          return bit_cast((i >= begin_) && (i < end_), as<type>());
        }
        else
        {
          // Use the most full type to be sure to fill outside values of small wide with false
          using e_t   = eve::element_type_t<i_t>;
          using abi_t = typename i_t::abi_type;
          using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

          auto const i = detail::linear_ramp(eve::as<w_t>());
          return bit_cast((i >= begin_) && (i < end_), as<type>());
        }
      }
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return begin_;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return cardinal_v<T> - end_;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return end_ - begin_;
    }

    constexpr bool friend operator==(keep_between const&, keep_between const&) = default;

    friend std::ostream& operator<<(std::ostream& os, keep_between const& c)
    {
      return os << "keep_between( " << c.begin_ << ", " << c.end_ << " )";
    }

    std::ptrdiff_t begin_, end_;
  };

  //================================================================================================
  // Helper structure to encode ignoring N elements on both extrema.
  //================================================================================================
  struct ignore_extrema
  {
    static constexpr bool has_alternative = false;
    static constexpr bool is_inverted     = false;
    static constexpr bool is_complete     = false;

    constexpr EVE_FORCEINLINE ignore_extrema(std::ptrdiff_t b, std::ptrdiff_t e) noexcept
            : first_count_(b), last_count_(e)
    {}

    template<typename V> EVE_FORCEINLINE auto else_(V const& v) const  {  return or_(*this,v);  }

    template<typename T> EVE_FORCEINLINE as_logical_t<T> mask(eve::as<T> const& tgt) const
    {
      EVE_ASSERT( (first_count_ + last_count_) <= cardinal_v<T>
                , "[eve::ignore_extrema] Index mismatch for first/last"
                );

      return keep_between(first_count_, cardinal_v<T>-last_count_).mask(tgt);
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t offset(eve::as<T> const&) const
    {
      return first_count_;
    }

    template<typename T> EVE_FORCEINLINE constexpr std::ptrdiff_t roffset(eve::as<T> const&) const
    {
      return last_count_;
    }

    template<typename T> EVE_FORCEINLINE constexpr auto count(eve::as<T> const&) const
    {
      return cardinal_v<T> - last_count_ - first_count_;
    }

    constexpr bool friend operator==(ignore_extrema const&, ignore_extrema const&) = default;

    friend std::ostream& operator<<(std::ostream& os, ignore_extrema const& c)
    {
      return os << "ignore( first(" << c.first_count_ << "), last(" << c.last_count_ << ") )";
    }

    std::ptrdiff_t first_count_, last_count_;
  };

  constexpr EVE_FORCEINLINE ignore_extrema operator&&( ignore_first a, ignore_last b) noexcept
  {
    return {a.count_, b.count_};
  }

  constexpr EVE_FORCEINLINE ignore_extrema operator&&( ignore_last b, ignore_first a) noexcept
  {
    return a && b;
  }

  template <eve::relative_conditional_expr C>
  auto map_alternative(C c, auto map) {
    if constexpr (!C::has_alternative) return c;
    else                               return c.map_alternative(map);
  }
}
