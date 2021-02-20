//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <utility>
#include <ostream>

#define EVE_DECLARE_CALLABLE(TAG)                                                                  \
  namespace tag { struct TAG {}; }                                                                 \
  template<typename C> struct if_;                                                                 \
  namespace detail                                                                                 \
  {                                                                                                \
    template<typename Dummy>                                                                       \
    struct  callable_object<tag::TAG, Dummy>                                                       \
    {                                                                                              \
      using tag_type = tag::TAG;                                                                   \
                                                                                                   \
      template<value Condition>                                                                    \
      EVE_FORCEINLINE constexpr auto operator[](Condition const &c) const noexcept                 \
      requires( eve::supports_conditionnal<tag::TAG>::value )                                      \
      {                                                                                            \
        return  [cond = if_(to_logical(c))](auto const&... args) EVE_LAMBDA_FORCEINLINE            \
                {                                                                                  \
                  return callable_object{}(cond, args...);                                         \
                };                                                                                 \
      }                                                                                            \
                                                                                                   \
      template<conditional_expr Condition>                                                         \
      EVE_FORCEINLINE constexpr auto operator[](Condition const &c) const noexcept                 \
      requires( eve::supports_conditionnal<tag::TAG>::value )                                      \
      {                                                                                            \
        return  [c](auto const&... args) EVE_LAMBDA_FORCEINLINE                                    \
                {                                                                                  \
                  return callable_object{}(c, args...);                                            \
                };                                                                                 \
      }                                                                                            \
                                                                                                   \
      template<typename Arg, typename... Args>                                                     \
      EVE_FORCEINLINE constexpr auto operator()(Arg&& d, Args &&... args) const noexcept           \
          -> decltype ( TAG(delay_t{}, EVE_CURRENT_API{},                                          \
                        std::forward<Arg>(d), std::forward<Args>(args)...)                         \
                      )                                                                            \
      {                                                                                            \
        if constexpr( decorator<std::decay_t<Arg>> )                                               \
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

#define EVE_MAKE_CALLABLE(TAG, NAME)                                                                \
  EVE_DECLARE_CALLABLE(TAG)                                                                         \
  EVE_CALLABLE_API(TAG,NAME)                                                                        \
  EVE_ALIAS_CALLABLE(TAG, NAME)                                                                     \
/**/

// Flag a function to support delayed calls on given architecture
#define EVE_SUPPORTS(ARCH) delay_t const &, ARCH const &

// Flag a function to support delayed calls on given architecture
#define EVE_MATCH_CALL(...) delay_t const &, ::eve::detail::types<__VA_ARGS__> const &

// Flag a function to support delayed calls on given architecture
#define EVE_RETARGET(ARCH)  delay_t{}, ARCH {}

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
  // decorator definition, detection, combination and application to callables
  //================================================================================================
  struct decorator_ {};
  template<typename ID> concept decorator = std::derived_from<ID,decorator_>;

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

    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      if constexpr( requires{ Decoration{}(f); } )  return Decoration{}(f);
      else
      {
        return [f]<typename... X>(X&&... x) { return f(decorated{}, std::forward<X>(x)...); };
      }
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
  }

  //==============================================================================================
  // Traits for foo[cond](...) supports
  template<typename Tag>
  struct supports_conditionnal : std::true_type
  {};

  //==============================================================================================
  // Traits for optimized conversion support
  template<typename F>
  struct supports_optimized_conversion : std::false_type
  {};

  //==============================================================================================
  // Traits for function working as shuffle pattern
  template<typename F>
  struct is_pattern : std::false_type
  {};
}
