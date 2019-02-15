//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_OVERLOAD_HPP_INCLUDED
#define EVE_DETAIL_OVERLOAD_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/detail/abi.hpp>
#include <utility>

#define EVE_DECLARE_CALLABLE(TAG)                                                                  \
  namespace tag                                                                                    \
  {                                                                                                \
    struct TAG                                                                                     \
    {                                                                                              \
    };                                                                                             \
  }                                                                                                \
  namespace detail                                                                                 \
  {                                                                                                \
    template<typename Dummy>                                                                       \
    struct callable_object<tag::TAG, void, Dummy>                                                  \
    {                                                                                              \
      using tag_type = tag::TAG;                                                                   \
      template<typename... Args>                                                                   \
      EVE_FORCEINLINE constexpr auto operator()(Args &&... args) const noexcept                    \
          -> decltype(TAG(delay_t{}, EVE_CURRENT_API{}, std::forward<Args>(args)...))              \
      {                                                                                            \
        return TAG(delay_t{}, EVE_CURRENT_API{}, std::forward<Args>(args)...);                     \
      };                                                                                           \
                                                                                                   \
      template<typename Option>                                                                    \
      EVE_FORCEINLINE constexpr auto operator[](Option const &o) const noexcept                    \
      {                                                                                            \
        return callable_object<tag_type, Option>{o};                                               \
      }                                                                                            \
                                                                                                   \
      struct negator                                                                               \
      {                                                                                            \
        template<typename Option>                                                                  \
        EVE_FORCEINLINE constexpr auto operator[](Option const &o) const noexcept                  \
        {                                                                                          \
          return callable_object<tag_type, not_t<Option>>{o};                                      \
        }                                                                                          \
      };                                                                                           \
                                                                                                   \
      negator not_;                                                                                \
    };                                                                                             \
                                                                                                   \
    template<typename Mode, typename Dummy>                                                        \
    struct callable_object<tag::TAG, Mode, Dummy>                                                  \
    {                                                                                              \
      Mode state_;                                                                                 \
      using tag_type = tag::TAG;                                                                   \
      template<typename... Args>                                                                   \
      EVE_FORCEINLINE constexpr auto operator()(Args &&... args) const noexcept                    \
          -> decltype(TAG(delay_t{}, EVE_CURRENT_API{}, Mode{}, std::forward<Args>(args)...))      \
      {                                                                                            \
        return TAG(delay_t{}, EVE_CURRENT_API{}, state_, std::forward<Args>(args)...);             \
      };                                                                                           \
    };                                                                                             \
  }                                                                                                \
  /**/

#define EVE_MAKE_CALLABLE(TAG, NAME)                                                               \
  EVE_DECLARE_CALLABLE(TAG)                                                                        \
  inline detail::callable_object<tag::TAG> const NAME = {} /**/

// Flag a function to support delayed calls on given architecture
#define EVE_SUPPORTS(ARCH) delay_t const &, ARCH const &

// basic type to support delayed calls
namespace eve::detail
{
  struct delay_t
  {
  };

  template<typename T>
  struct not_t
  {
    T value;
  };

  template<typename Tag, typename Mode = void, typename Enabler = void>
  struct callable_object;
}

#endif
