//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_OVERLOAD_HPP_INCLUDED
#define EVE_DETAIL_OVERLOAD_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/detail/meta.hpp>
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
    struct  callable_object<tag::TAG, void, Dummy>                                                 \
          : conditionnal_support<tag::TAG, eve::supports_conditionnal<tag::TAG>::value>            \
    {                                                                                              \
      using tag_type = tag::TAG;                                                                   \
                                                                                                   \
      template<typename Arg, typename... Args>                                                     \
      EVE_FORCEINLINE constexpr auto operator()(Arg&& d, Args &&... args) const noexcept           \
          -> decltype ( TAG(delay_t{}, EVE_CURRENT_API{},                                          \
                        std::forward<Arg>(d), std::forward<Args>(args)...)                         \
                      )                                                                            \
      {                                                                                            \
        if constexpr( is_decorator<std::decay_t<Arg>>::value )                                     \
        {                                                                                          \
          check ( delay_t{}, ::eve::detail::types<std::decay_t<Arg>,tag::TAG>{},                   \
                  std::forward<Args>(args)...                                                      \
                );                                                                                 \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
          check ( delay_t{}, ::eve::detail::types<tag::TAG>{}, std::forward<Arg>(d),               \
                  std::forward<Args>(args)...                                                      \
                );                                                                                 \
        }                                                                                          \
                                                                                                   \
        return TAG(delay_t{},EVE_CURRENT_API{},std::forward<Arg>(d),std::forward<Args>(args)...);  \
      };                                                                                           \
    };                                                                                             \
                                                                                                   \
    template<typename Condition, typename Dummy>                                                   \
    struct callable_object<tag::TAG, Condition, Dummy>                                             \
    {                                                                                              \
      Condition state_;                                                                            \
      using tag_type = tag::TAG;                                                                   \
                                                                                                   \
      template<typename Arg, typename... Args>                                                     \
      EVE_FORCEINLINE constexpr auto operator()(Arg&& d, Args &&... args) const noexcept           \
          -> decltype ( TAG(delay_t{}, EVE_CURRENT_API{},                                          \
                         state_, std::forward<Arg>(d), std::forward<Args>(args)...)                \
                      )                                                                            \
      {                                                                                            \
        if constexpr( is_decorator<std::decay_t<Arg>>::value )                                     \
        {                                                                                          \
          check ( delay_t{}, ::eve::detail::types<std::decay_t<Arg>,tag::TAG>{},                   \
                  state_, std::forward<Args>(args)...                                              \
                );                                                                                 \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
          check ( delay_t{}, ::eve::detail::types<tag::TAG>{},std::forward<Arg>(d),                \
                  state_, std::forward<Args>(args)...                                              \
                );                                                                                 \
        }                                                                                          \
                                                                                                   \
        return TAG( delay_t{},EVE_CURRENT_API{}, state_,                                           \
                    std::forward<Arg>(d),std::forward<Args>(args)...                               \
                  );                                                                               \
      };                                                                                           \
    };                                                                                             \
  }                                                                                                \
  /**/

#define EVE_MAKE_CALLABLE(TAG, NAME)                                                               \
  EVE_DECLARE_CALLABLE(TAG)                                                                        \
  using callable_##TAG                                = detail::callable_object<tag::TAG>;         \
  inline detail::callable_object<tag::TAG> const NAME = {} /**/

// Flag a function to support delayed calls on given architecture
#define EVE_SUPPORTS(ARCH) delay_t const &, ARCH const &

// Flag a function to support delayed calls on given architecture
#define EVE_MATCH_CALL(...) delay_t const &, ::eve::detail::types<__VA_ARGS__> const &

// Flag a function to support delayed calls on given architecture
#define EVE_RETARGET(ARCH)                                                                         \
  delay_t{}, ARCH {}

// Create named object for constant
#define EVE_MAKE_NAMED_CONSTANT(TAG, FUNC)                                                         \
  namespace detail                                                                                 \
  {                                                                                                \
    template<typename T>                                                                           \
    EVE_FORCEINLINE constexpr auto TAG(EVE_SUPPORTS(cpu_), as_<T> const &) noexcept                \
    {                                                                                              \
      return FUNC<T>();                                                                            \
    }                                                                                              \
  }                                                                                                \
/**/

namespace eve
{
  //================================================================================================
  // decorator mark-up and detection
  struct decorator_ {};
  template<typename ID> struct is_decorator : std::is_base_of<decorator_,ID> {};

  namespace detail
  {
    //==============================================================================================
    // basic type to support delayed calls
    struct delay_t
    {
    };

    //==============================================================================================
    // Helper for conditional function negation optimization
    template<typename T>
    struct not_t
    {
      T value;
    };

    //==============================================================================================
    // Extension point for centralizing asserts & static_asserts
    template<typename Tag, typename... Args>
    void check(delay_t const&, Tag const&, Args const&... ) {}

    //==============================================================================================
    // callable_object forward declaration
    template< typename Tag,
              typename Condition = void,
              typename Dummy     = void
            >
    struct callable_object;

    //==============================================================================================
    // Extension point for controlling supports for foo[cond](...) calls
    template<typename Tag, bool isSupported>
    struct conditionnal_support
    {
      template<typename Condition>
      EVE_FORCEINLINE constexpr auto operator[](Condition const &o) const noexcept
      {
        return callable_object<Tag, Condition>{o};
      }

      struct negator
      {
        template<typename Condition>
        EVE_FORCEINLINE constexpr auto operator[](Condition const &o) const noexcept
        {
          return callable_object<Tag, not_t<Condition>>{o};
        }
      };

      negator not_;
    };

    template<typename Tag> struct conditionnal_support<Tag,false> {};
  }

  //==============================================================================================
  // Traits for foo[cond](...) supports
  template<typename Tag>
  struct supports_conditionnal : std::true_type
  {};
}

#endif
