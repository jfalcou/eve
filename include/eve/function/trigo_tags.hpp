//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_TRIGO_TAGS_HPP_INCLUDED
#define EVE_FUNCTION_TRIGO_TAGS_HPP_INCLUDED

#include <type_traits>
#include <eve/detail/abi.hpp>

namespace eve
{

  template < typename T, typename Enable = void>
  struct is_trigonometric_tag : std::false_type{};

  template<typename T>
  using is_trigonometric_tag_t = typename is_trigonometric_tag<T>::type;

  template<typename T>
  static inline constexpr bool is_trigonometric_tag_v = is_trigonometric_tag_t<T>::value;

  //=====================================================================================
  struct restricted_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(restricted_type{}, args...); };
    }
  };

  template <>
  struct is_trigonometric_tag<restricted_type> : std::true_type{};

  //=====================================================================================
  struct small_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(small_type{}, args...); };
    }
  };

  template <>
  struct is_trigonometric_tag<small_type> : std::true_type{};

  //=====================================================================================
  struct cephes_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(cephes_type{}, args...); };
    }
  };

  template <>
  struct is_trigonometric_tag<cephes_type> : std::true_type{};

  //=====================================================================================
  struct medium_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(medium_type{}, args...); };
    }
  };

  template <>
  struct is_trigonometric_tag<medium_type> : std::true_type{};

  //=====================================================================================
  struct big_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(big_type{}, args...); };
    }
  };

  template <>
  struct is_trigonometric_tag<big_type> : std::true_type{};


  //================================================================================================
  // Function decorator - restricted mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto restricted_(Function f) noexcept
  {
    return restricted_type{}(f);
  }

  //================================================================================================
  // Function decorator - small mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto small_(Function f) noexcept
  {
    return small_type{}(f);
  }

  //================================================================================================
  // Function decorator - cephes mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto cephes_(Function f) noexcept
  {
    return cephes_type{}(f);
  }

  //================================================================================================
  // Function decorator - medium mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto medium_(Function f) noexcept
  {
    return medium_type{}(f);
  }

  //================================================================================================
  // Function decorator - big mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto big_(Function f) noexcept
  {
    return big_type{}(f);
  }
}

#endif
