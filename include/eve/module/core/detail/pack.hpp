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
#include <eve/detail/alias.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/function/detail/make.hpp>
#include <type_traits>
#include <iterator>
#include <iostream>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve { namespace detail
{
  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  template<typename Type, typename Size, typename ABI>
  struct pack
  {
    using storage_type            = ::eve::ext::as_register_t<Type,Size::value,ABI>;
    using value_type              = Type;
    using size_type               = std::size_t;
    using reference               = Type&;
    using const_reference         = Type const&;
    using iterator                = Type*;
    using const_iterator          = Type const*;
    using reverse_iterator        = std::reverse_iterator<iterator>;
    using const_reverse_iterator  = std::reverse_iterator<const_iterator>;

    // ---------------------------------------------------------------------------------------------
    // Ctor
    EVE_FORCEINLINE pack() noexcept {};

    EVE_FORCEINLINE pack(storage_type const& r) noexcept : data_(r) {}

    template<typename T>
    EVE_FORCEINLINE explicit pack(T const& v) noexcept
                  : data_( detail::make(as_<value_type>{},ABI{},v) )
    {}

    template<typename T0, typename T1, typename... Ts
            , typename = std::enable_if_t<!Size::is_default && sizeof(T0)>
            >
    EVE_FORCEINLINE pack(T0 const& v0, T1 const& v1, Ts const&... vs) noexcept
                  : data_( detail::make(as_<value_type>{},ABI{},v0,v1,vs...) )
    {
      static_assert ( 2+sizeof...(vs) == Size::value
                    , "[eve] Incomplete initializer list for pack"
                    );
    }

    template< typename Generator
            , typename = std::enable_if_t<std::is_invocable_v<Generator,std::size_t,std::size_t>>
            >
    EVE_FORCEINLINE pack(Generator&& g) noexcept
    {
      for(std::size_t i=0;i<size();++i)
        this->operator[](i) = std::forward<Generator>(g)(i,size());
    }

    // ---------------------------------------------------------------------------------------------
    // Raw storage access
    EVE_FORCEINLINE pack& operator=(storage_type const& o) noexcept { data_ = o; return *this; }

    EVE_FORCEINLINE storage_type   storage() const noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type()  const noexcept { return data_; }

    // ---------------------------------------------------------------------------------------------
    // array-like interface
    static EVE_FORCEINLINE constexpr std::size_t  size()     noexcept { return Size::value; }
    static EVE_FORCEINLINE constexpr size_type    max_size() noexcept { return size();      }
    static EVE_FORCEINLINE constexpr bool         empty()    noexcept { return false;       }

    EVE_FORCEINLINE void swap(pack& rhs) noexcept
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    // ---------------------------------------------------------------------------------------------
    // begin() variants
    EVE_FORCEINLINE iterator begin() noexcept
    {
      return reinterpret_cast<detail::alias_t<value_type>*>( &data_ );
    }

    EVE_FORCEINLINE const_iterator begin() const noexcept
    {
      return reinterpret_cast<detail::alias_t<value_type> const*>( &data_ );
    }

    EVE_FORCEINLINE const_iterator cbegin() noexcept
    {
      return reinterpret_cast<detail::alias_t<value_type> const*>( &data_ );
    }

    EVE_FORCEINLINE reverse_iterator        rbegin()        noexcept { return reverse_iterator(end()); }
    EVE_FORCEINLINE const_reverse_iterator  rbegin() const  noexcept { return reverse_iterator(end()); }
    EVE_FORCEINLINE const_reverse_iterator crbegin() const  noexcept { return const_reverse_iterator(cend()); }

    // ---------------------------------------------------------------------------------------------
    // end() variants
    EVE_FORCEINLINE iterator          end()         noexcept  { return begin() + size(); }
    EVE_FORCEINLINE const_iterator    end()   const noexcept  { return begin() + size(); }
    EVE_FORCEINLINE const_iterator    cend()        noexcept  { return begin() + size(); }
    EVE_FORCEINLINE reverse_iterator  rend()        noexcept  { return reverse_iterator(begin()); }

    EVE_FORCEINLINE const_reverse_iterator  rend() const noexcept { return reverse_iterator(begin()); }
    EVE_FORCEINLINE const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    // ---------------------------------------------------------------------------------------------
    // elementwise access
    EVE_FORCEINLINE reference       operator[](std::size_t i)       noexcept { return begin()[i]; }
    EVE_FORCEINLINE const_reference operator[](std::size_t i) const noexcept { return begin()[i]; }

    EVE_FORCEINLINE reference       back()        noexcept  { return this->operator[](size()-1); }
    EVE_FORCEINLINE const_reference back() const  noexcept  { return this->operator[](size()-1); }

    EVE_FORCEINLINE reference       front()       noexcept  { return this->operator[](0); }
    EVE_FORCEINLINE const_reference front() const noexcept  { return this->operator[](0); }

    private:
    storage_type data_;
  };

  template <typename T, typename N, typename ABI>
  EVE_FORCEINLINE void swap(pack<T, N, ABI>& lhs, pack<T, N, ABI>& rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template <typename T, typename N, typename ABI>
  std::ostream& operator<<(std::ostream& os, pack<T, N, ABI> const& p)
  {
    os << '(' << +p[0];

    for (std::size_t i=1; i != p.size(); ++i)
      os << ", " << +p[i];

    return os << ')';
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
