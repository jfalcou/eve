//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_PACK_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>



#include <iostream>

namespace eve { namespace detail
{
  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  template<typename Type, typename Size, typename ABI>
  struct pack
  {
    using register_type = ::eve::ext::as_register_t<Type,Size::value,ABI>;
    using value_type    = Type;
    using size_type     = std::size_t;

    EVE_FORCEINLINE pack() noexcept {};

    EVE_FORCEINLINE pack(register_type const& r) noexcept : data_(r) {}
    EVE_FORCEINLINE pack& operator=(register_type const& o) noexcept { data_ = o; return *this; }

    // template<typename T0, typename T1, typename... Ts
    //         , typename = std::enable_if_t<!Size::is_default && sizeof(T0)>
    //         >
    // EVE_FORCEINLINE pack(T0 const& v0, T1 const& v1, Ts const&... vn) noexcept
    // {
    //   std::cout << "WOOT: " << 2+sizeof...(vn) << "\n";
    // }

    EVE_FORCEINLINE register_type   storage() const noexcept { return data_; }
    EVE_FORCEINLINE operator register_type()  const noexcept { return data_; }

    static EVE_FORCEINLINE constexpr std::size_t size() noexcept { return Size::value; }

    EVE_FORCEINLINE void swap(pack& rhs) noexcept
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    private:
    register_type data_;
  };
} }

#endif
