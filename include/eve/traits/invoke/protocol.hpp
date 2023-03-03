//====================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//====================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/traits/invoke/tag_invoke.hpp>

namespace eve
{
//==================================================================================================
//! @addtogroup invoke
//! @{
//==================================================================================================

//==================================================================================================
//! @struct unsupported_call
//! @brief Overloading error reporting helper
//!
//! eve::unsupported_call is used as a return type when an **EVE** @callable is called with some
//! incorrect parameter types or quantity. Its template parameters embed the tag of the @callable
//! along with the parameter types that caused the error.
//!
//! @tparam Signature Function type describing the erroneous call
//==================================================================================================
template<typename Signature>
struct unsupported_call
{};

//! @brief Tag type for elementwise @callable properties
struct elementwise
{
  using elementwise_tag = void;
};

//! @brief Tag type for reduction @callable properties
struct reduction
{
  using reduction_tag = void;
};

//! @brief Tag type for constant @callable properties
struct constant
{
  using constant_tag = void;
};

//==================================================================================================
//! @concept callable
//! @brief **EVE** callable
//!
//! A type `T` satisfies eve::callable if and only if it is tagged as such either
//! manually or by inheriting from a T properties.
//!
//! @tparam T  T type for the @callable to check
//==================================================================================================
template<typename T>
concept callable = requires(T) { typename T::callable_tag_type; };

//==================================================================================================
//! @concept deferred_callable
//! @brief **EVE** deferred callable
//!
//! A type `T` satisfies eve::deferred_callable_tag if and only if it is a eve::callable and
//! provides the required static function `deferred_call`.
//!
//! @tparam T  T type for the @callable to check
//==================================================================================================
template<typename T>
concept deferred_callable = requires(T) { typename T::deferred_callable_tag; };

//==================================================================================================
//! @concept named_callable
//! @brief **EVE** callable with a text description
//!
//! A type `T` satisfies eve::callable if and only if it is an eve::callable and provides a
//! `callable_tag_name` static member that can be streamed.
//!
//! @tparam T Tag type for the @callable to check
//==================================================================================================
template<typename T>
concept named_callable = callable<T> && requires(T, std::ostream& os) { os << T::callable_id; };

//==================================================================================================
//! @concept elementwise_callable
//! @brief **EVE** callable with elementwise semantic
//!
//! A type `T` satisfies eve::elementwise_callable if and only if it is an eve::callable that
//! inherits from eve::elementwise.
//!
//! @tparam T  T type for the @callable to check
//==================================================================================================
template<typename T>
concept elementwise_callable = callable<T> && requires(T) { typename T::elementwise_tag; };

//==================================================================================================
//! @concept reduction_callable
//! @brief **EVE** callable with reduction semantic
//!
//! A type `T` satisfies eve::reduction_callable if and only if it is an eve::callable that
//! inherits from eve::reduction.
//!
//! @tparam T  T type for the @callable to check
//==================================================================================================
template<typename T>
concept reduction_callable = callable<T> && requires(T) { typename T::reduction_tag; };

//==================================================================================================
//! @concept constant_callable
//! @brief **EVE** callable with constant semantic
//!
//! A type `T` satisfies eve::constant_callable if and only if it is an eve::callable that
//! inherits from eve::constant.
//!
//! @tparam T  T type for the @callable to check
//==================================================================================================
template<typename T>
concept constant_callable = callable<T> && requires(T) { typename T::constant_tag; };
}

//==================================================================================================
// Basic hook for tag_invoke that just forward to the proper deferred call if possible.
// This binds all existing implementation of <func>_ back to tag_invoke.
// This specialization lives in eve::tags to be found by ADL as tag themselves will be defines
// in eve::tags.
//
// The EVE_DEFERRED_INVOKE macro is there to help use this mechanism in external project;
//==================================================================================================
namespace eve::tags
{
  constexpr   auto tag_invoke(deferred_callable auto tag, auto arch, auto... x)
  noexcept(noexcept(tag.deferred_call(arch, x...))) -> decltype(tag.deferred_call(arch, x...))
  {
    return tag.deferred_call(arch, x...);
  }
}

#define EVE_DEFERRED_INVOKE()                                                                     \
constexpr   auto tag_invoke(eve::deferred_callable auto tag, auto arch, auto... x)                \
noexcept(noexcept(tag.deferred_call(arch, x...))) -> decltype(tag.deferred_call(arch, x...))      \
{                                                                                                 \
  return tag.deferred_call(arch, x...);                                                           \
}                                                                                                 \
/**/

//==================================================================================================
//! @}
//==================================================================================================

//==================================================================================================
//  Helpers macros
//  NOTE: Those macros are here for convenience but are no way mandatory to use in either EVE, any
//        EVE-dependent library or any user-facing code. The required interface for EVE callable is
//        short enough to be written manually if the need arise.
//==================================================================================================

//==================================================================================================
//  Short-cut macro for defining the basic interface to satisfy callable and named_callable.
//  Also defined a hidden friend stream insertion operator
//==================================================================================================
#define EVE_DEFINES_CALLABLE(TYPE, ID)                                                            \
inline friend std::ostream& operator<<(std::ostream& os, TYPE const&)                             \
{                                                                                                 \
  return os << ID;                                                                                \
}                                                                                                 \
using callable_tag_type                       = TYPE;                                             \
static constexpr std::string_view callable_id = ID                                                \
/**/

//==================================================================================================
// When using external deferred call to shorten the overload set of any given function, EVE expects
// the use of an ADL delay type that lives in the namespace where the deferred functions live.
// In EVE, this namespace is eve::detail but in other library, it may be desirable to change this.
// This macro generate the required type and object in the namespace of your choice so that the
// whole deferred call system works.
//==================================================================================================
#define EVE_DEFERRED_NAMESPACE()                                                                  \
struct adl_delay_t {};                                                                            \
inline constexpr auto adl_delay = adl_delay_t {}                                                  \
/**/

// Register eve::detail as the deferred namespace
namespace eve::detail
{
  EVE_DEFERRED_NAMESPACE();
}

// Flag a function to support delayed calls on given architecture
#define EVE_EXPECTS(ARCH) adl_delay_t const &, ARCH const &

//==================================================================================================
//  Defines the static deferred call interface. This static function in tag_invoke callable let
//  external types specify their implementation by asking the callable to forward the call to an
//  externally defined function with a specific name. This reduces the amount of overloads to look
//  at by not looking at all the non NAME related calls.
//==================================================================================================
//  General macro taking the deferred namespace NS and the function NAME
//==================================================================================================
#define EVE_DEFERS_CALLABLE_FROM(NS,NAME)                                                         \
static auto deferred_call(auto arch, auto&&...args) noexcept                                      \
    -> decltype(NAME(NS::adl_delay, arch, EVE_FWD(args)...))                                      \
{                                                                                                 \
  return NAME(NS::adl_delay, arch, EVE_FWD(args)...);                                             \
}                                                                                                 \
using deferred_callable_tag = void                                                                \
/**/

//==================================================================================================
//  EVE-specific macro that use eve::detail as the deferred namespace
//==================================================================================================
#define EVE_DEFERS_CALLABLE(NAME) EVE_DEFERS_CALLABLE_FROM(eve::detail,NAME)

//==================================================================================================
//  Defines the extended tag_invoke with deferred call support and named_callable interface
//==================================================================================================
//  General macro taking the deferred namespace NS and the function NAME
//  NOTE: Don't hesitate to wrap this macro if you need it in your EVE-dependent library.
//==================================================================================================
#define EVE_IMPLEMENTS_CALLABLE_FROM(NS, TYPE, NAME, ID)                                          \
EVE_DEFERS_CALLABLE_FROM(NS,NAME);                                                                \
EVE_DEFINES_CALLABLE(TYPE, ID)                                                                    \
/**/

//==================================================================================================
//  EVE-specific macro that use eve::detail as the deferred namespace
//==================================================================================================
#define EVE_IMPLEMENTS_CALLABLE(TYPE,NAME,ID)                                                     \
EVE_DEFERS_CALLABLE(NAME);                                                                        \
EVE_DEFINES_CALLABLE(TYPE, ID)                                                                    \
/**/
