#pragma once

#include <cstdint>

#define DELARE_ALL_FUNCTIONS              \
  DECLARE_TEST_FUNCTION(std::int8_t, eve::fixed<8>)    \
  DECLARE_TEST_FUNCTION(std::uint8_t, eve::fixed<16>)  \
  DECLARE_TEST_FUNCTION(std::int8_t, eve::fixed<32>)   \
  DECLARE_TEST_FUNCTION(std::uint8_t, eve::fixed<64>)  \
                                                       \
  DECLARE_TEST_FUNCTION(std::int16_t, eve::fixed<4>)   \
  DECLARE_TEST_FUNCTION(std::uint16_t, eve::fixed<8>)  \
  DECLARE_TEST_FUNCTION(std::int16_t, eve::fixed<16>)  \
  DECLARE_TEST_FUNCTION(std::uint16_t, eve::fixed<32>) \
                                                       \
  DECLARE_TEST_FUNCTION(std::int32_t, eve::fixed<2>)   \
  DECLARE_TEST_FUNCTION(std::uint32_t, eve::fixed<4>)  \
  DECLARE_TEST_FUNCTION(std::int32_t, eve::fixed<8>)   \
  DECLARE_TEST_FUNCTION(std::uint32_t, eve::fixed<16>) \
                                                       \
  DECLARE_TEST_FUNCTION(std::int64_t, eve::fixed<1>)   \
  DECLARE_TEST_FUNCTION(std::uint64_t, eve::fixed<2>)  \
  DECLARE_TEST_FUNCTION(std::int32_t, eve::fixed<4>)   \
  DECLARE_TEST_FUNCTION(std::uint32_t, eve::fixed<8>)  \
                                                       \
  DECLARE_TEST_FUNCTION(float, eve::fixed<2>)          \
  DECLARE_TEST_FUNCTION(float, eve::fixed<4>)          \
  DECLARE_TEST_FUNCTION(float, eve::fixed<8>)          \
  DECLARE_TEST_FUNCTION(float, eve::fixed<16>)         \
                                                       \
  DECLARE_TEST_FUNCTION(double, eve::fixed<1>)         \
  DECLARE_TEST_FUNCTION(double, eve::fixed<2>)         \
  DECLARE_TEST_FUNCTION(double, eve::fixed<4>)         \
  DECLARE_TEST_FUNCTION(double, eve::fixed<8>)
