#include <memory>
#include <vector>

#include <eve/memory/allocate.hpp>
#include <eve/memory/allocator.hpp>
#include <eve/wide.hpp>

int main(int argc, char** argv)
{
  {
    //! [align-manual]
    namespace bs = eve;
    using wide_t = eve::wide<int>;

    std::size_t num_elements = 1024;
    std::size_t alignment    = wide_t::alignment;
    std::size_t buffer_size  = num_elements + alignment;
    std::unique_ptr<char[]> ptr(new char[buffer_size]);
    void* pv = ptr.get();
    if (std::align(alignment, num_elements, pv, buffer_size) == nullptr) {
      std::cerr << " alignment failed " << std::endl;
    }
    //! [align-manual]
  }

  {
    //! [align-allocate]
    std::size_t num_elements = 1024;
    using aligned_ptr        = std::unique_ptr<int[], eve::aligned_delete>;

    aligned_ptr ptr2(eve::allocate<int>(num_elements));
    //! [align-allocate]
  }

  {
    //! [align-vector]
    std::size_t num_elements = 1024;
    std::vector<int, eve::allocator<float>> input_buffer(num_elements);
    //! [align-vector]
  }
}
