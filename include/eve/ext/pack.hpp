//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_PACK_HPP_INCLUDED
#define EVE_EXT_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/is_iterator.hpp>
#include <eve/detail/is_range.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/plus.hpp>
#include <eve/ext/is_pack.hpp>
#include <type_traits>
#include <iterator>
#include <iostream>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

namespace eve
{
  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  template<typename Type, typename Size, typename ABI>
  struct pack
  {
    using storage_type            = ::eve::ext::as_register_t<Type,Size::value,ABI>;
    using abi_type                = ABI;
    using value_type              = Type;
    using size_type               = std::size_t;
    using reference               = Type&;
    using const_reference         = Type const&;
    using iterator                = Type*;
    using const_iterator          = Type const*;
    using reverse_iterator        = std::reverse_iterator<iterator>;
    using const_reverse_iterator  = std::reverse_iterator<const_iterator>;

    using target_type = std::conditional_t< std::is_same_v<abi_type,eve::emulated_>
                                          , storage_type
                                          , value_type
                                          >;

    static constexpr std::size_t static_size  = Size::value;
    static constexpr std::size_t alignment    = alignof(storage_type);

    // ---------------------------------------------------------------------------------------------
    // Ctor
    EVE_FORCEINLINE pack()            noexcept {}

    EVE_FORCEINLINE pack(storage_type const& r) noexcept : data_(r) {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a Range
    template<typename Iterator>
    EVE_FORCEINLINE explicit pack ( Iterator b, Iterator e
                                  , std::enable_if_t< detail::is_iterator_v<Iterator>>* = 0
                                  ) noexcept
                  : data_(detail::load(as_<pack>{},abi_type{},b,e))
    {}

    template<typename Range>
    EVE_FORCEINLINE explicit pack ( Range&& r
                                  , std::enable_if_t<   detail::is_range_v<Range>
                                                    && !ext::is_pack_v<Range>
                                                    && !std::is_same_v<storage_type,Range>
                                                    >* = 0
                                  ) noexcept
                  : pack( std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a pointer
    EVE_FORCEINLINE explicit pack(Type* ptr) noexcept
                  : data_(detail::load(as_<pack>{},abi_type{},ptr))
    {}

    template< std::size_t Alignment
            , typename = std::enable_if_t<(Alignment>=alignment)>
            >
    EVE_FORCEINLINE explicit pack(aligned_ptr<Type,Alignment> ptr) noexcept
                  : data_(detail::load(as_<pack>{},abi_type{},ptr))
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a single value
    template< typename T
            , typename = std::enable_if_t <std::is_convertible_v<T,Type>>
            >
    EVE_FORCEINLINE explicit pack(T const& v) noexcept
                  : data_( detail::make(as_<target_type>{},abi_type{},v) )
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a sequence of values
    template< typename T0, typename T1, typename... Ts
            , bool ConvertProperly = (... && std::is_convertible_v<Ts,Type>)
            , typename = std::enable_if_t <  std::is_convertible_v<T0,Type>
                                          && std::is_convertible_v<T1,Type>
                                          && !Size::is_default
                                          && ConvertProperly
                                          >
            >
    EVE_FORCEINLINE pack(T0 const& v0, T1 const& v1, Ts const&... vs) noexcept
                  : data_( detail::make(as_<target_type>{},abi_type{},v0,v1,vs...) )
    {
      static_assert ( 2+sizeof...(vs) == static_size
                    , "[eve] Size mismatch in initializer list for pack"
                    );
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack with a generator function
    template<typename Generator>
    EVE_FORCEINLINE pack( Generator&& g
                        , std::enable_if_t<std::is_invocable_v< Generator
                                                              , std::size_t,std::size_t
                                                              >
                                          >* = 0
                        ) noexcept
    {
      for(std::size_t i=0;i<size();++i)
        this->operator[](i) = static_cast<Type>(std::forward<Generator>(g)(i,static_size));
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a pair of sub-pack
    EVE_FORCEINLINE pack( pack<Type,typename Size::split_type> const& l
                        , pack<Type,typename Size::split_type> const& h
                        )
                    : data_( detail::combine(EVE_CURRENT_API{},l,h) )
    {}

    // ---------------------------------------------------------------------------------------------
    // Assign a single value to a pack
    EVE_FORCEINLINE pack& operator=(Type v) noexcept
    {
      data_ = detail::make(as_<target_type>{},abi_type{},v);
      return *this;
    }

    // ---------------------------------------------------------------------------------------------
    // Raw storage access
    EVE_FORCEINLINE pack& operator=(storage_type const& o) noexcept { data_ = o; return *this; }

    // ---------------------------------------------------------------------------------------------
    // Raw storage access
    EVE_FORCEINLINE storage_type   storage() const  noexcept { return data_; }
    EVE_FORCEINLINE storage_type&  storage()        noexcept { return data_; }

    EVE_FORCEINLINE operator storage_type()  const noexcept { return data_; }

    // ---------------------------------------------------------------------------------------------
    // array-like interface
    static EVE_FORCEINLINE constexpr std::size_t  size()     noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type    max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool         empty()    noexcept { return false;       }

    // ---------------------------------------------------------------------------------------------
    // slice interface
    EVE_FORCEINLINE auto slice()                const { return detail::slice(*this); }

    template<typename Slice>
    EVE_FORCEINLINE auto slice(Slice const& s)  const { return detail::slice(*this,s); }

    // ---------------------------------------------------------------------------------------------
    // swap
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

    // ---------------------------------------------------------------------------------------------
    // Self-increment/decrement operators
    EVE_FORCEINLINE pack& operator++() noexcept
    {
      *this += Type{1};
      return *this;
    }

    EVE_FORCEINLINE pack operator++(int) noexcept
    {
      auto that(*this);
      operator++();
      return that;
    }

    EVE_FORCEINLINE pack& operator--() noexcept
    {
      *this -= Type{1};
      return *this;
    }

    EVE_FORCEINLINE pack operator--(int) noexcept
    {
      auto that(*this);
      operator--();
      return that;
    }

    // ---------------------------------------------------------------------------------------------
    // Self-assignment operators
    template<typename Other>
    EVE_FORCEINLINE pack& operator+=(Other const& other) noexcept
    {
      *this = eve::plus(*this, other);
      return *this;
    }

    template<typename Other>
    EVE_FORCEINLINE pack& operator-=(Other const& other) noexcept
    {
      *this = eve::minus(*this, other);
      return *this;
    }

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
}

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
