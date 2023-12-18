//====================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//====================================================================================================
#pragma once

#include <eve/detail/raberu.hpp>
#include <eve/arch/spec.hpp>
#include <eve/traits/invoke/tag_invoke.hpp>

namespace eve
{
template<typename Signature>
struct unsupported_call
{
  constexpr operator bool() const noexcept { return false; }
};

struct elementwise
{
  using elementwise_tag = void;
};

struct reduction
{
  using reduction_tag = void;
};

struct constant
{
  using constant_tag = void;
};

template<typename T>
concept callable_entity = requires(T) { typename T::callable_tag_type; };

template<typename T>
concept deferred_callable = requires(T) { typename T::deferred_callable_tag; };

template<typename T>
concept elementwise_entity = callable_entity<T> && requires(T) { typename T::elementwise_tag; };

template<typename T>
concept reduction_entity = callable_entity<T> && requires(T) { typename T::reduction_tag; };

template<typename T>
concept constant_entity = callable_entity<T> && requires(T) { typename T::constant_tag; };

template<callable_entity Tag>
std::ostream& operator<<(std::ostream& os, Tag const&)
{
  return os << rbr::detail::type<Tag>.name();
}
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
  template<deferred_callable Tag>
  EVE_FORCEINLINE constexpr auto tag_invoke(Tag, auto arch, auto&&... x)
  noexcept(noexcept(Tag::deferred_call(arch, EVE_FWD(x)...)))
  -> decltype(Tag::deferred_call(arch, EVE_FWD(x)...))
  {
    return Tag::deferred_call(arch, EVE_FWD(x)...);
  }
}

#define EVE_DEFERRED_INVOKE()                                                                     \
template<eve::deferred_callable Tag>                                                              \
EVE_FORCEINLINE constexpr auto tag_invoke(Tag, auto arch, auto&&... x)                            \
noexcept(noexcept(Tag::deferred_call(arch, EVE_FWD(x)...)))                                       \
-> decltype(Tag::deferred_call(arch, EVE_FWD(x)...))                                              \
{                                                                                                 \
  return Tag::deferred_call(arch, EVE_FWD(x)...);                                                 \
}                                                                                                 \
/**/

//==================================================================================================
//  Helpers macros
//  NOTE: Those macros are here for convenience but are no way mandatory to use in either EVE, any
//        EVE-dependent library or any user-facing code. The required interface for EVE callable is
//        short enough to be written manually if the need arise.
//==================================================================================================

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
static EVE_FORCEINLINE auto deferred_call(auto arch, auto&&...args) noexcept                      \
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
#define EVE_IMPLEMENTS_CALLABLE_FROM(NS, TYPE, NAME)                                              \
EVE_DEFERS_CALLABLE_FROM(NS,NAME);                                                                \
using callable_tag_type = TYPE                                                                    \
/**/

//==================================================================================================
//  EVE-specific macro that use eve::detail as the deferred namespace
//==================================================================================================
#define EVE_IMPLEMENTS_CALLABLE(TYPE,NAME)  EVE_IMPLEMENTS_CALLABLE_FROM(eve::detail,TYPE,NAME)
