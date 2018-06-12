//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_AGGREGATE_PACK_HPP_INCLUDED
#define EVE_DETAIL_AGGREGATE_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/module/core/function/detail/make.hpp>
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

    EVE_FORCEINLINE aggregate_pack(storage_type const& r) noexcept : data_(r) {}

    template<typename T>
    EVE_FORCEINLINE explicit aggregate_pack(T const& v) noexcept
                  : data_( detail::make(as_<aggregate_pack>{},eve::emulated_{},v) )
    {}

    template<typename T, typename... Ts>
    EVE_FORCEINLINE aggregate_pack(T const& v, Ts const&... vs) noexcept
                  : aggregate_pack(detail::make(as_<aggregate_pack>{},eve::emulated_{},v,vs...))
    {
      static_assert ( 1+sizeof...(vs) == Size
                    , "[eve] Incomplete initializer list for pack"
                    );
    }

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
    EVE_FORCEINLINE iterator        begin()       noexcept  { return data_[0].begin(); }
    EVE_FORCEINLINE const_iterator  begin() const noexcept  { return data_[0].begin(); }
    EVE_FORCEINLINE const_iterator cbegin()       noexcept  { return data_[0].begin(); }

    EVE_FORCEINLINE reverse_iterator        rbegin()        noexcept { return data_[1].rbegin();  }
    EVE_FORCEINLINE const_reverse_iterator  rbegin() const  noexcept { return data_[1].rbegin();  }
    EVE_FORCEINLINE const_reverse_iterator crbegin() const  noexcept { return data_[1].crbegin(); }

    // ---------------------------------------------------------------------------------------------
    // end() variants
    EVE_FORCEINLINE iterator          end()         noexcept  { return data_[1].end();  }
    EVE_FORCEINLINE const_iterator    end()   const noexcept  { return data_[1].end();  }
    EVE_FORCEINLINE const_iterator    cend()        noexcept  { return data_[1].cend(); }
    EVE_FORCEINLINE reverse_iterator  rend()        noexcept  { return data_[0].rend(); }

    EVE_FORCEINLINE const_reverse_iterator  rend() const noexcept { return data_[0].rend();   }
    EVE_FORCEINLINE const_reverse_iterator crend() const noexcept { return data_[0].crend();  }

    // ---------------------------------------------------------------------------------------------
    // elementwise access
    EVE_FORCEINLINE reference       operator[](std::size_t i)       noexcept { return begin()[i]; }
    EVE_FORCEINLINE const_reference operator[](std::size_t i) const noexcept { return begin()[i]; }

    EVE_FORCEINLINE reference       back()        noexcept  { return data_[1].back(); }
    EVE_FORCEINLINE const_reference back() const  noexcept  { return data_[1].back(); }

    EVE_FORCEINLINE reference       front()       noexcept  { return data_[0].front(); }
    EVE_FORCEINLINE const_reference front() const noexcept  { return data_[0].front(); }

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
