//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/arch/spec.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>

#include <concepts>
#include <type_traits>
#include <utility>
#include <ostream>

#define EVE_REGISTER_CALLABLE(TAG)                                                                 \
namespace tag { struct TAG {}; }                                                                   \
/**/

#define EVE_DECLARE_CALLABLE(TAG,NAME)                                                             \
  template<typename C> struct if_;                                                                 \
                                                                                                   \
  namespace detail                                                                                 \
  {                                                                                                \
    template<typename... Args>                                                                     \
    concept supports_ ## TAG = requires(Args&&... args)                                            \
    {                                                                                              \
      { TAG( delay_t{}, eve::current_api, EVE_FWD(args)...) };                                    \
    };                                                                                             \
                                                                                                   \
    template<typename Dummy>                                                                       \
    struct  callable_object<tag::TAG, Dummy>                                                       \
    {                                                                                              \
      using tag_type    = tag::TAG;                                                                \
                                                                                                   \
      template<typename Arg, typename... Args>                                                     \
      requires  (   tag_dispatchable<tag_type,Arg,Args...>                                         \
                ||  supports_ ## TAG<Arg,Args...>                                                  \
                )                                                                                  \
      static EVE_FORCEINLINE constexpr decltype(auto) call(Arg&& d, Args &&... args)  noexcept     \
      {                                                                                            \
        if constexpr( decorator<std::decay_t<Arg>> )                                               \
        {                                                                                          \
          check ( delay_t{}, ::eve::detail::types<std::decay_t<Arg>,tag_type>{},                   \
                  EVE_FWD(args)...                                                                 \
                );                                                                                 \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
          check ( delay_t{}, ::eve::detail::types<tag_type>{}, EVE_FWD(d),                         \
                  EVE_FWD(args)...                                                                 \
                );                                                                                 \
        }                                                                                          \
                                                                                                   \
        if constexpr( tag_dispatchable<tag_type,Arg,Args...> )                                     \
        {                                                                                          \
          return tagged_dispatch ( tag_type{}                                                      \
                            , EVE_FWD(d), EVE_FWD(args)...                                         \
                            );                                                                     \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
          return TAG( delay_t{}, eve::current_api                                                 \
                    , EVE_FWD(d), EVE_FWD(args)...                                                 \
                    );                                                                             \
        }                                                                                          \
      }                                                                                            \
                                                                                                   \
      template<typename... Args>                                                                   \
      requires  (   tag_dispatchable<tag_type,Args...>                                             \
                ||  supports_ ## TAG<Args...>                                                      \
                )                                                                                  \
      EVE_FORCEINLINE constexpr decltype(auto) operator()(Args &&... args) const noexcept          \
      {                                                                                            \
        return call(args...);                                                                      \
      }                                                                                            \
                                                                                                   \
      template<value Condition>                                                                    \
      EVE_FORCEINLINE constexpr auto operator[](Condition c) const noexcept                        \
      requires( eve::supports_conditional<tag_type>::value )                                       \
      {                                                                                            \
        auto cond = if_(to_logical(c));                                                            \
        return callable_object_bind_recurse<callable_object, decltype(cond)>{cond};                \
      }                                                                                            \
                                                                                                   \
      template<std::same_as<bool> T>                                                               \
      EVE_FORCEINLINE constexpr auto operator[](T c) const noexcept                                \
      requires( eve::supports_conditional<tag_type>::value )                                       \
      {                                                                                            \
        using type = std::conditional_t<std::same_as<bool,T>,std::uint8_t,T>;                      \
        return (*this)[if_(logical<type>(c))];                                                     \
      }                                                                                            \
                                                                                                   \
      template<conditional_expr Condition>                                                         \
      EVE_FORCEINLINE constexpr auto operator[](Condition c) const noexcept                        \
      requires( eve::supports_conditional<tag_type>::value )                                       \
      {                                                                                            \
        return callable_object_bind_recurse<callable_object, Condition>{c};                        \
      }                                                                                            \
    };                                                                                             \
  }                                                                                                \
/**/

#define EVE_ALIAS_CALLABLE(TAG, NAME)                                                              \
  inline detail::callable_object<tag::TAG> const NAME = {}                                         \
/**/

#define EVE_CALLABLE_API(TAG, NAME)                                                                 \
  using callable_##TAG  = detail::callable_object<tag::TAG>;                                        \
  inline std::ostream& operator<<(std::ostream& os, detail::callable_object<tag::TAG> const&)       \
  {                                                                                                 \
    return os << #NAME;                                                                             \
  }
/**/


#if defined(EVE_DOXYGEN_INVOKED)
#define EVE_IMPLEMENT_CALLABLE(TAG, NAME) inline constexpr callable_##TAG NAME = {};
#else
#define EVE_IMPLEMENT_CALLABLE(TAG, NAME)                                                           \
  EVE_DECLARE_CALLABLE(TAG,NAME)                                                                    \
  EVE_CALLABLE_API(TAG,NAME)                                                                        \
  EVE_ALIAS_CALLABLE(TAG, NAME)                                                                     \
/**/
#endif
#if defined(EVE_DOXYGEN_INVOKED)
#define EVE_MAKE_CALLABLE(TAG, NAME) inline constexpr callable_##TAG NAME = {};
#else
#define EVE_MAKE_CALLABLE(TAG, NAME)                                                                \
  EVE_REGISTER_CALLABLE(TAG)                                                                        \
  EVE_IMPLEMENT_CALLABLE(TAG,NAME)                                                                  \
/**/
#endif


// Flag a function to support delayed calls on given architecture
#define EVE_SUPPORTS(ARCH) delay_t const &, ARCH const &

// Flag a function to support delayed calls on given architecture
#define EVE_MATCH_CALL(...) delay_t const &, ::eve::detail::types<__VA_ARGS__> const &

// Flag a function to support delayed calls on given architecture
#define EVE_RETARGET(ARCH)  delay_t{}, ARCH {}

namespace eve
{
  //================================================================================================
  // decorator definition, detection, combination and application to callables
  //================================================================================================
  struct decorator_ {};
  template<typename ID> concept decorator = std::derived_from<ID,decorator_>;
  template<typename D, typename F> concept specific_decorator = requires(D d, F f)
  {
    { d(f) };
  };

  template<typename Decoration> struct decorated;
  template<typename Decoration, typename... Args>
  struct decorated<Decoration(Args...)> : decorator_
  {
    using base_type = Decoration;

    template<decorator Decorator>
    constexpr EVE_FORCEINLINE auto operator()(Decorator d) const noexcept
    {
      return Decoration::combine(d);
    }

    template <typename Function>
    struct fwding_lamda
    {
      Function f;

      template <typename... X>
      constexpr EVE_FORCEINLINE auto operator()(X&&... x) const
      {
        return f(decorated{}, EVE_FWD(x)...);
      }
    };

    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      if constexpr( specific_decorator<Decoration,Function> )  return Decoration{}(f);
      else                                          return fwding_lamda<Function>{f};
    }
  };

  namespace detail
  {
    //==============================================================================================
    // basic type to support delayed calls
    struct delay_t {};

    //==============================================================================================
    // Extension point for centralizing asserts & static_asserts
    template<typename Tag, typename... Args>
    void check(delay_t const&, Tag const&, Args const&... ) {}

    //==============================================================================================
    // callable_object forward declaration
    template<typename Tag, typename Dummy = void> struct callable_object;

    // Internal lambda to do force inlining
    template <typename Self, typename First>
    struct callable_object_bind_recurse
    {
      First first;

      EVE_FORCEINLINE decltype(auto) operator()(auto ... args) const noexcept
      {
        return Self::call(first, args...);
      }
    };

    //==============================================================================================
    // User-facing tag-dispatch helper
    template <typename Tag, typename... Args>
    concept tag_dispatchable = requires(Tag tag, Args... args)
    {
      { tagged_dispatch(tag, EVE_FWD(args)...) };
    };
  }

  //==============================================================================================
  // Traits for foo[cond](...) supports
  template<typename Tag>
  struct supports_conditional : std::true_type
  {};

  //==============================================================================================
  // Traits for optimized conversion support
  template<typename F>
  struct supports_optimized_conversion : std::false_type
  {};
}
