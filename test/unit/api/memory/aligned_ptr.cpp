//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/memory/aligned_ptr.hpp>
#include <tts/tests/relation.hpp>
#include <array>

TTS_CASE("aligned_ptr constructor from nullptr")
{
  eve::aligned_ptr<double> nullptr_constructed_ptr = nullptr;

  TTS_EQUAL(nullptr_constructed_ptr.get() , nullptr);
  TTS_EQUAL(nullptr_constructed_ptr       , nullptr);
}

TTS_CASE("aligned_ptr factory functions")
{
  alignas(8) std::array<char, 10> values;
  TTS_EQUAL(eve::as_aligned(&values[ 0 ]).get()   , &values[ 0 ]);
  TTS_EQUAL(eve::as_aligned(&values[ 0 ])         , &values[ 0 ]);
  TTS_EQUAL(eve::as_aligned(&values[ 0 ])         , eve::as_aligned(&values[ 0 ]));
  TTS_NOT_EQUAL(eve::as_aligned(&values[ 0 ])     , &values[ 3 ]);
  TTS_NOT_EQUAL(eve::as_aligned(&values[ 0 ])     , eve::as_aligned(&values[ 3 ]));

  TTS_EQUAL(eve::as_aligned<8>(&values[ 0 ]).get(), &values[ 0 ]);
  TTS_EQUAL(eve::as_aligned<8>(&values[ 0 ])      , &values[ 0 ]);
  TTS_EQUAL(eve::as_aligned<8>(&values[ 0 ])      , eve::as_aligned<8>(&values[ 0 ]));
  TTS_NOT_EQUAL(eve::as_aligned<8>(&values[ 0 ])  , &values[ 8 ]);
  TTS_NOT_EQUAL(eve::as_aligned<8>(&values[ 0 ])  , eve::as_aligned<8>(&values[ 8 ]));
}

TTS_CASE("aligned_ptr pre/post increment & decrement")
{
  char                      values[ 2 ];
  eve::aligned_ptr<char, 1> ptr = &values[ 0 ];

  ptr++;
  TTS_EQUAL(ptr.get(), &values[ 1 ]);
  ptr--;
  TTS_EQUAL(ptr.get(), &values[ 0 ]);
  ++ptr;
  TTS_EQUAL(ptr.get(), &values[ 1 ]);
  --ptr;
  TTS_EQUAL(ptr.get(), &values[ 0 ]);
}

struct type
{
  auto         method() const { return this; }
  std::uint8_t member;
};

TTS_CASE("aligned_ptr provides pointer-like interface")
{
  TTS_WHEN("We initialize a aligned_ptr")
  {

    type            value{42}, other_value{17};
    alignas(8) type extra_aligned_value{87};

    eve::aligned_ptr<type>    ptr           = &value;
    eve::aligned_ptr<type>    other_ptr     = &other_value;
    eve::aligned_ptr<type, 8> realigned_ptr = &extra_aligned_value;

    TTS_AND_THEN("we check the proper default alignment")
    {
      TTS_EQUAL(ptr.alignment(), alignof(type));
    }

    TTS_AND_THEN("we check access to its pointee members")
    {
      TTS_EQUAL(ptr.get(), &value);
      TTS_EQUAL(ptr->method(), &value);
      TTS_EQUAL(ptr->member, 42);
      ptr->member = 69;
      TTS_EQUAL(value.member, 69);
    }

    TTS_AND_THEN("we check re-assignment from raw pointer")
    {
      ptr = &other_value;
      TTS_EQUAL(ptr->method(), &other_value);
      TTS_EQUAL(ptr->member, 17);
      ptr->member = 101;
      TTS_EQUAL(other_value.member, 101);
    }

    TTS_AND_THEN("we check re-assignment from other aligned_ptr")
    {
      ptr = other_ptr;
      TTS_EQUAL(ptr->method(), &other_value);
      TTS_EQUAL(ptr->member, 17);
      ptr->member = 99;
      TTS_EQUAL(other_value.member, 99);
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
      ptr[ 0 ] = other_value;
      TTS_EQUAL(ptr->method(), &value);
      TTS_EQUAL(ptr->member, 17);
      ptr->member = 99;
      TTS_EQUAL(value.member, 99);
    }

    TTS_AND_THEN("we check incrementing by valid value")
    {
      ptr += ptr.alignment();
      TTS_EQUAL(ptr.get(), &value + ptr.alignment());
    }

    TTS_AND_THEN("we check decrementing by valid value")
    {
      auto shifted = &value;
      shifted -= ptr.alignment();
      ptr     -= ptr.alignment();
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
  }
}
