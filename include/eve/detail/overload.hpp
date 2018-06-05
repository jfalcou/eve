//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_DETAIL_OVERLOAD_HPP_INCLUDED
#define EVE_DETAIL_OVERLOAD_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/detail/abi.hpp>

#define EVE_DECLARE_CALLABLE(TAG)                                                                   \
namespace tag { struct TAG {}; }                                                                    \
namespace detail                                                                                    \
{                                                                                                   \
  template<typename Mode> struct callable_object<tag::TAG,Mode>                                     \
  {                                                                                                 \
    using tag_type = tag::TAG;                                                                      \
    template<typename... Args> EVE_FORCEINLINE                                                      \
    constexpr auto operator()(Args&&... args) const noexcept                                        \
                    -> decltype(TAG( delay_t{}, EVE_CURRENT_API{}, std::forward<Args>(args)... ))   \
    {                                                                                               \
      return TAG( delay_t{}, EVE_CURRENT_API{}, std::forward<Args>(args)... );                      \
    };                                                                                              \
  };                                                                                                \
}                                                                                                   \
/**/

#define EVE_MAKE_CALLABLE(TAG,NAME)                                                                 \
EVE_DECLARE_CALLABLE(TAG)                                                                           \
inline detail::callable_object<tag::TAG> const NAME = {}                                            \
/**/

// Flag a function to support delayed calls on given architecture
#define EVE_SUPPORTS(ARCH) delay_t const&, ARCH const&

// basic type to support delayed calls
namespace eve { namespace detail
{
  struct delay_t {};
  template<typename Tag, typename Mode = void> struct callable_object;
} }

#endif
