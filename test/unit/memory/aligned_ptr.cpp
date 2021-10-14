//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/memory/aligned_ptr.hpp>

#include <array>
#include <memory>

TTS_CASE("aligned_ptr exposes proper traits")
{
  using it_t  = eve::pointer_traits<eve::aligned_ptr<double>>;
  using cit_t = eve::pointer_traits<eve::aligned_ptr<double const>>;

  TTS_TYPE_IS( it_t::value_type , double);
  TTS_TYPE_IS( cit_t::value_type, double);
};

TTS_CASE("aligned_ptr constructor from nullptr")
{
  eve::aligned_ptr<double> nullptr_constructed_ptr = nullptr;

  TTS_EQUAL(nullptr_constructed_ptr.get() , nullptr);
  TTS_EQUAL(nullptr_constructed_ptr       , nullptr);
};

TTS_CASE("aligned_ptr factory functions - Default SIMD alignment")
{
  constexpr auto size = EVE_CURRENT_ABI::bytes;

  alignas(size) std::array<std::byte, 2 * size> values;
  TTS_EQUAL(eve::as_aligned(&values[ 0 ]).get()   , &values[ 0 ]);
  TTS_EQUAL(eve::as_aligned(&values[ 0 ])         , &values[ 0 ]);
  TTS_EQUAL(eve::as_aligned(&values[ 0 ])         , eve::as_aligned(&values[ 0 ]));
  TTS_NOT_EQUAL(eve::as_aligned(&values[ 0 ])     , &values[ 3 ]);
  TTS_NOT_EQUAL(eve::as_aligned(&values[ 0 ])     , eve::as_aligned(&values[ size ]));
};

TTS_CASE("aligned_ptr factory functions - Specific alignment")
{
  alignas(8) std::array<std::byte, 64> values;
  TTS_EQUAL(eve::as_aligned(&values[0], eve::lane<8>).get(), &values[0]);
  TTS_EQUAL(eve::as_aligned(&values[0], eve::lane<8>)      , &values[0]);
  TTS_EQUAL(eve::as_aligned(&values[0], eve::lane<8>)      , eve::as_aligned(&values[0], eve::lane<8>));
  TTS_NOT_EQUAL(eve::as_aligned(&values[0], eve::lane<8>)  , &values[3]);
  TTS_NOT_EQUAL(eve::as_aligned(&values[0], eve::lane<8>)  , eve::as_aligned(&values[8], eve::lane<8>));
};

TTS_CASE("aligned_ptr ordering")
{
  std::byte                      values[ 2 ];
  eve::aligned_ptr<std::byte, eve::fixed<1>> ptr = &values[ 0 ];
  eve::aligned_ptr<std::byte, eve::fixed<1>> ptr1= ptr;

  ptr1++;
  TTS_EXPECT(ptr < ptr1);

  ptr1--;
  TTS_EXPECT(ptr ==  ptr1);

  ptr1--;
  TTS_EXPECT(ptr >  ptr1);
};

TTS_CASE("aligned_ptr pre/post increment & decrement")
{
  std::byte                            values[ 2 ];
  eve::aligned_ptr<std::byte, eve::fixed<1>> ptr = &values[ 0 ];

  ptr++;
  TTS_EQUAL(ptr.get(), &values[ 1 ]);

  ptr--;
  TTS_EQUAL(ptr.get(), &values[ 0 ]);

  ++ptr;
  TTS_EQUAL(ptr.get(), &values[ 1 ]);

  --ptr;
  TTS_EQUAL(ptr.get(), &values[ 0 ]);
};

struct type
{
  auto         method() const { return this; }
  std::uint8_t member;
};

TTS_CASE("aligned_ptr provides pointer-like interface")
{
  TTS_WHEN("We initialize a aligned_ptr")
  {
    type values[2] = {{42},{17}};
    alignas(8) type extra_aligned_value{87};

    eve::aligned_ptr<type, eve::fixed<1>> ptr           = &values[0];
    eve::aligned_ptr<type, eve::fixed<1>> other_ptr     = &values[1];
    eve::aligned_ptr<type, eve::fixed<8>> realigned_ptr = &extra_aligned_value;

    TTS_AND_THEN("we check the proper default alignment")
    {
      TTS_EQUAL(ptr.alignment(), eve::alignment_v<type>);
    }

    TTS_AND_THEN("we check access to its pointee members")
    {
      TTS_EQUAL(ptr.get(), &values[0]);
      TTS_EQUAL(ptr->method(), &values[0]);
      TTS_EQUAL(ptr->member, 42);
      ptr->member = 69;
      TTS_EQUAL(values[0].member, 69);
    }

    TTS_AND_THEN("we check re-assignment from raw pointer")
    {
      ptr = &values[1];
      TTS_EQUAL(ptr->method(), &values[1]);
      TTS_EQUAL(ptr->member, 17);
      ptr->member = 101;
      TTS_EQUAL(values[1].member, 101);
    }

    TTS_AND_THEN("we check re-assignment from other aligned_ptr")
    {
      ptr = other_ptr;
      TTS_EQUAL(ptr->method(), &values[1]);
      TTS_EQUAL(ptr->member, 17);
      ptr->member = 99;
      TTS_EQUAL(values[1].member, 99);
    }

    TTS_AND_THEN("we check re-assignment from other aligned_ptr of different alignment")
    {
      ptr = realigned_ptr;
      TTS_EQUAL(ptr->method(), &extra_aligned_value);
      TTS_EQUAL(ptr->member, 87);
      ptr->member = 99;
      TTS_EQUAL(extra_aligned_value.member, 99);
    }

    TTS_AND_THEN("we check subscripting operator")
    {
      ptr[ 0 ] = values[1];
      TTS_EQUAL(ptr->method(), &values[0]);
      TTS_EQUAL(ptr->member, 17);
      ptr->member = 99;
      TTS_EQUAL(values[0].member, 99);
    }

    TTS_AND_THEN("we check incrementing by valid value")
    {
      ptr += ptr.alignment();
      TTS_EQUAL(ptr.get(), &values[0] + ptr.alignment());
    }

    TTS_AND_THEN("we check decrementing by valid value")
    {
      auto shifted = &values[1];
      shifted -= ptr.alignment();
      TTS_EQUAL(ptr.get(), shifted);
    }

    TTS_AND_THEN("we check swap")
    {
      ptr.swap(other_ptr);
      TTS_EQUAL(ptr->member, 17);
      TTS_EQUAL(other_ptr->member, 42);

      swap(ptr, other_ptr);
      TTS_EQUAL(ptr->member, 42);
      TTS_EQUAL(other_ptr->member, 17);
    }

    TTS_AND_THEN("we check interation with raw ptr")
    {
      TTS_EQUAL(ptr, ptr.get());
      TTS_EQUAL(ptr.get(), ptr);
      TTS_NOT_EQUAL(ptr, other_ptr.get());
      TTS_NOT_EQUAL(ptr.get(), other_ptr);
      TTS_EQUAL((other_ptr.get() - ptr), 1);
      TTS_EQUAL((other_ptr - ptr.get()), 1);
    }
  }
};

TTS_CASE("previous aligned address")
{
  using eve::aligned_ptr;
  using lanes = eve::fixed<16>;
  alignas(16 * 2) std::array<short, 16 * 4> data;

  for( int i = 0; i != static_cast<int>(data.size()); ++i)
  {
    short*            cur = data.begin() + i;
    short const* expected = data.begin() + (i / 16) * 16;

    aligned_ptr<short, lanes> aligned = eve::previous_aligned_address(cur, lanes{});
    TTS_EQUAL(aligned.get(), expected);

    aligned_ptr<short const, lanes> aligned_const = eve::previous_aligned_address((short const*)cur, lanes{});
    TTS_EQUAL(aligned_const.get(), expected);
  }
};
