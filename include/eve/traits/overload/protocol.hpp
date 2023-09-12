//======================================================================================================================
//! @file
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch/tags.hpp>

//======================================================================================================================
//! @addtogroup simd
//! @{
//!   @defgroup extensions Extensions points
//!   @brief Macros, classes and functions designed to extend EVE externally.
//! @}
//======================================================================================================================

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @concept callable
  //!   @brief **EVE** callable
  //!
  //!   A type `T` satisfies eve::callable if and only if it is tagged as such manually.
  //!
  //!   @tparam T  T type for the @callable to check
  //! @}
  //====================================================================================================================
  template<typename T, typename...>
  concept callable = requires(T const&) { typename T::callable_tag_type; };

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //    @concept decorated_callable
  //    @brief Concept modelling the fact a eve::callable has decorations
  //!   @tparam T  T type for the @callable to check
  //! @}
  //====================================================================================================================
  template<typename T, typename...>
  concept decorated_callable = requires(T const&)
  {
    typename T::is_decorated_callable;
  };
}

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def   EVE_CALLABLE_OBJECT_FROM
//!   @brief Generate the generic function interface for any EVE-compatible @callable
//!
//!   Use inside a @callable definition to generate the required EVE protocol of function's resolution based on type
//!   and architecture informations.
//!
//!   @param NS   Namespace in which specialization of the @callable will be found. This namespace must have been
//!               registered via EVE_CALLABLE_NAMESPACE.
//!   @param TYPE Current @callable type
//!   @param NAME Function identifier for overloads. Calls to `NS::NAME` are supposed to succeed.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/traits/callable_object_from.cpp}
//! @}
//======================================================================================================================
#define EVE_CALLABLE_OBJECT_FROM(NS,TYPE,NAME)                                                                         \
template<typename... Args>                                                                                             \
EVE_FORCEINLINE constexpr auto operator()(Args&&... args) const                                                        \
-> decltype(std::declval<TYPE>().call(std::declval<Args>()...))                                                        \
requires( requires { std::declval<TYPE>().call(EVE_FWD(args)...); })                                                   \
{                                                                                                                      \
  if constexpr(eve::decorated_callable<TYPE,Args...>)                                                                  \
    return TYPE::deferred_call(eve::current_api, eve::detail::defaults<TYPE,Args...>(), EVE_FWD(args)...);             \
  else                                                                                                                 \
    return TYPE::deferred_call(eve::current_api, EVE_FWD(args)...);                                                    \
}                                                                                                                      \
static EVE_FORCEINLINE decltype(auto) deferred_call(auto arch, auto&&...args) noexcept                                 \
requires(requires { NAME(NS::adl_helper, arch, EVE_FWD(args)...); })                                                   \
{                                                                                                                      \
  return NAME(NS::adl_helper, arch, EVE_FWD(args)...);                                                                 \
}                                                                                                                      \
template<typename... Args>                                                                                             \
static EVE_FORCEINLINE decltype(auto) deferred_call(auto arch, Args&&...args) noexcept                                 \
requires(!requires { NAME(NS::adl_helper, arch, EVE_FWD(args)...); })                                                  \
{                                                                                                                      \
  return eve::detail::default_behavior<TYPE,Args...>::call(arch, EVE_FWD(args)...);                                    \
}                                                                                                                      \
using callable_tag_type     = TYPE                                                                                     \
/**/

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def   EVE_CALLABLE_OBJECT
//!   @brief Generate the generic function interface for an actual eve::callable
//!
//!   Use inside a @callable definition to generate the required EVE protocol of function's resolution based on type
//!   and architecture informations using overload from the `eve::detail` namespace.
//!
//!   @warning @ref EVE_CALLABLE_OBJECT is mostly used for EVE @callable definition. If you want to use EVE's overload
//!   facility for your own library, use @ref EVE_CALLABLE_OBJECT_FROM.
//!
//!   @param TYPE Current @callable type
//!   @param NAME Function identifier for overloads. Calls to `eve::detail::NAME` are supposed to succeed.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/traits/callable_object.cpp}
//! @}
//======================================================================================================================
// THIS MACRO IS DUPLICATED TO ENSURE ERROR MESSAGE QUALITY
#define EVE_CALLABLE_OBJECT(TYPE,NAME)                                                                                 \
template<typename... Args>                                                                                             \
EVE_FORCEINLINE constexpr auto operator()(Args&&... args) const                                                        \
-> decltype(std::declval<TYPE>().call(std::declval<Args>()...))                                                        \
requires( requires { std::declval<TYPE>().call(EVE_FWD(args)...); })                                                   \
{                                                                                                                      \
  if constexpr(eve::decorated_callable<TYPE,Args...>)                                                                  \
    return TYPE::deferred_call(eve::current_api, eve::detail::defaults<TYPE,Args...>(), EVE_FWD(args)...);             \
  else                                                                                                                 \
    return TYPE::deferred_call(eve::current_api, EVE_FWD(args)...);                                                    \
}                                                                                                                      \
static EVE_FORCEINLINE decltype(auto) deferred_call(auto arch, auto&&...args) noexcept                                 \
requires(requires { NAME(eve::detail::adl_helper, arch, EVE_FWD(args)...); })                                          \
{                                                                                                                      \
  return NAME(eve::detail::adl_helper, arch, EVE_FWD(args)...);                                                        \
}                                                                                                                      \
template<typename... Args>                                                                                             \
static EVE_FORCEINLINE decltype(auto) deferred_call(auto arch, Args&&...args) noexcept                                 \
requires(!requires { NAME(eve::detail::adl_helper, arch, EVE_FWD(args)...); })                                         \
{                                                                                                                      \
  return eve::detail::default_behavior<TYPE,Args...>::call(arch, EVE_FWD(args)...);                                    \
}                                                                                                                      \
using callable_tag_type     = TYPE                                                                                     \
/**/

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def EVE_CALLABLE_NAMESPACE
//!   @brief Register a namespace as suitable for containing eve::callable overloads.
//! @}
//======================================================================================================================
#define EVE_CALLABLE_NAMESPACE()                                                                                       \
struct adl_helper_t {};                                                                                                \
inline constexpr auto adl_helper = adl_helper_t {}                                                                     \
/**/

// Flag a function to support delayed calls on given architecture
#define EVE_EXPECTS(ARCH) adl_helper_t const &, ARCH const &

// Register eve::detail as the deferred namespace by default
namespace eve::detail { EVE_CALLABLE_NAMESPACE(); }
