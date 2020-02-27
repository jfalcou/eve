#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

//! [substract]
#include <eve/wide.hpp>
#include <eve/cardinal.hpp>

//! [substract-include]
#include <eve/function/load.hpp>
#include <eve/function/store.hpp>
//! [substract-include]
#include <eve/function/sub.hpp>

int main()
{
  //! [substract-simd-types]
  namespace bs = eve;

  size_t size = 128;
  std::vector<int32_t> array(size);
  std::vector<int32_t> out(size);
  // Initialize input array
  std::iota(array.begin(), array.end(), 0);
  int32_t scalar = 42;
  //! [substract-simd-types]

  //! [substract-cardinal]
  using wide_t     = eve::wide<int32_t>;
  size_t wide_card = eve::cardinal_v<wide_t>;
  //! [substract-cardinal]

  //! [substract-scalar]
  // Scalar version
  for (size_t i = 0; i < size; ++i) {
    out[i] = array[i] - scalar;
  }
  //! [substract-scalar]

  {
    //! [substract-loop-con]
    for (size_t i = 0; i < size; i += wide_card) {
    }
    //! [substract-loop-con]

    //! [substract-fortytwo]
    wide_t p_out, fortytwo(scalar);
    //! [substract-fortytwo]

    //! [substract-pointer]
    for (size_t i = 0; i < size; i += wide_card) {
      wide_t p_arr(array.data() + i);
      p_out = p_arr - fortytwo;
      eve::store(p_out, out.data() + i);
    }
    //! [substract-pointer]
  }

  {
    //! [substract-load]
    // Using explicit load/store
    wide_t fortytwo{scalar};
    for (size_t i = 0; i < size; i += wide_card) {
      wide_t p_arr(array.data() + i);
      wide_t p_out = p_arr - fortytwo;
      eve::store(p_out, out.data() + i);
    }
    //! [substract-load]
  }

  {
    //! [substract-remainder]
    // Using explicit load/store
    // set size to an arbitrary value
    size = 133;
    wide_t p_out, p_arr, fortytwo{42};
    array.resize(size);
    out.resize(size);
    size_t i = 0;
    for (; i + wide_card <= size; i += wide_card) {
      wide_t p_arr(array.data() + i);
      wide_t p_out = p_arr - fortytwo;
      eve::store(p_out, out.data() + i);
    }

    for (; i < size; ++i) {
      out[i] = array[i] - scalar;
    }
    //! [substract-remainder]
  }
  return 0;
}
//! [substract]
