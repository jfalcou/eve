//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>
#include <eve/detail/kumi.hpp>

#include <concepts>

namespace eve
{
  template<typename T> struct pointer_traits {};

  template<typename T> struct pointer_traits<T*>        { using value_type = T; };
  template<typename T> struct pointer_traits<T const*>  { using value_type = T; };

  template<typename T>
  requires requires { typename T::value_type; }
  struct pointer_traits<T>
  {
    using value_type = typename T::value_type;
  };

  template<typename... Ptrs>
  struct pointer_traits<kumi::tuple<Ptrs...>>
  {
    using value_type = kumi::tuple<typename pointer_traits<Ptrs>::value_type...>;
  };

  template<typename T>
  struct pointer_cardinal : expected_cardinal<typename pointer_traits<T>::value_type>
  {};

  template<typename T>
  requires requires { typename T::cardinal; }
  struct pointer_cardinal<T>
  {
    using type = typename T::cardinal;
  };

  template<typename T>
  requires requires { T::iterator_cardinal(); }
  struct pointer_cardinal<T>
  {
    using type = decltype(T::iterator_cardinal());
  };

  template<typename Type, typename Lanes>
  struct  pointer_cardinal<eve::aligned_ptr<Type, Lanes>> : expected_cardinal<Type>
  {};
}

namespace eve::detail
{

  template<typename Ptr>
  concept data_source = requires(Ptr p)
  {
    typename pointer_traits<Ptr>::value_type;
  };

  template <typename Ptr>
  concept scalar_pointer = std::is_pointer_v<Ptr> || instance_of<Ptr, aligned_ptr>;

  template<typename T, typename Ptr> struct dereference_as;

  template<typename T, typename Ptr>
  requires( !kumi::product_type<Ptr> )
  struct dereference_as<T,Ptr>
  {
    using base = typename pointer_traits<Ptr>::value_type;
    static constexpr bool value = std::same_as<T,base>;
  };

  template<typename T, typename... Ptrs>
  struct dereference_as<T, kumi::tuple<Ptrs...>>
  {
    using base = kumi::tuple<typename pointer_traits<Ptrs>::value_type...>;
    static constexpr bool value = std::same_as<T,base>;
  };

  template <typename U, typename T, typename Lanes>
  EVE_FORCEINLINE auto ptr_cast(eve::aligned_ptr<T, Lanes> p)
  {
    return aligned_ptr<U, eve::fixed<Lanes() * sizeof(T) / sizeof(U)>>{(U*)(p.get())};
  }

  template <typename U, typename T>
  EVE_FORCEINLINE auto ptr_cast(T* p)
  {
    return (U*)p;
  }
}
