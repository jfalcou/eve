//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_DETAIL_AGGREGATE_PACK_HPP_INCLUDED
#define EVE_DETAIL_AGGREGATE_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/abi.hpp>
#include <iostream>
#include <array>

namespace eve { namespace detail
{
  // Wrapper for SIMD registers holding multiple native SIMD registers
  template<typename Pack, std::size_t Size>
  struct aggregate_pack
  {
    using storage_type            = std::array<Pack,2>;
    using value_type              = typename Pack::value_type;
    using size_type               = std::size_t;
    using reference               = typename Pack::reference;
    using const_reference         = typename Pack::const_reference;
    using iterator                = typename Pack::iterator;
    using const_iterator          = typename Pack::const_iterator;
    using reverse_iterator        = typename Pack::reverse_iterator;
    using const_reverse_iterator  = typename Pack::const_reverse_iterator;

    // ---------------------------------------------------------------------------------------------
    // Ctor
    EVE_FORCEINLINE aggregate_pack() noexcept {};

    template< typename Generator
            , typename = std::enable_if_t<std::is_invocable_v<Generator,std::size_t,std::size_t>>
            >
    EVE_FORCEINLINE aggregate_pack(Generator&& g) noexcept
    {
      for(std::size_t i=0;i<size();++i)
        this->operator[](i) = std::forward<Generator>(g)(i,Size);
    }

    // ---------------------------------------------------------------------------------------------
    // Raw storage access
    EVE_FORCEINLINE storage_type   storage() const noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type()  const noexcept { return data_; }

    // ---------------------------------------------------------------------------------------------
    // array-like interface
    static EVE_FORCEINLINE constexpr std::size_t  size()     noexcept { return Size;  }
    static EVE_FORCEINLINE constexpr size_type    max_size() noexcept { return Size;  }
    static EVE_FORCEINLINE constexpr bool         empty()    noexcept { return false; }

    EVE_FORCEINLINE void swap(aggregate_pack& rhs) noexcept
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    // ---------------------------------------------------------------------------------------------
    // begin() variants
    EVE_FORCEINLINE iterator begin() noexcept
    {
      return reinterpret_cast<detail::alias_t<value_type>*>( &data_[0] );
    }

    EVE_FORCEINLINE const_iterator begin() const noexcept
    {
      return reinterpret_cast<detail::alias_t<value_type> const*>( &data_[0] );
    }

    EVE_FORCEINLINE const_iterator cbegin() noexcept
    {
      return reinterpret_cast<detail::alias_t<value_type> const*>( &data_[0] );
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

    EVE_FORCEINLINE reference       back()        noexcept  { return this->operator[](Size-1); }
    EVE_FORCEINLINE const_reference back() const  noexcept  { return this->operator[](Size-1); }

    EVE_FORCEINLINE reference       front()       noexcept  { return this->operator[](0); }
    EVE_FORCEINLINE const_reference front() const noexcept  { return this->operator[](0); }

    private:
    storage_type data_;
  };

  template<typename P, std::size_t S>
  void swap(aggregate_pack<P,S>& lhs, aggregate_pack<P,S>& rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template<typename P, std::size_t S>
  std::ostream& operator<<(std::ostream& os, aggregate_pack<P,S> const& p)
  {
    os << '(' << +p[0];

    for (std::size_t i=1; i != p.size(); ++i)
      os << ", " << +p[i];

    return os << ')';
  }
} }

#endif
