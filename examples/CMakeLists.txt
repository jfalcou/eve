##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
make_unit( "examples" start_here.cpp )

make_unit( "examples" algorithms/using_existing/memcmp__two_range_algorithms_interface_specifics.cpp )
make_unit( "examples" algorithms/using_existing/inclusive_scan_zip__using_zip_with_algorithms.cpp )
make_unit( "examples" algorithms/using_existing/inclusive_scan_par_unseq__using_eve_to_build_both_vectorized_and_parallel_algos.cpp )

make_unit( "examples" algorithms/writing_new/collect_indexes__complicated_real_example.cpp )
make_unit( "examples" algorithms/writing_new/strlen__showing_basic_conepts.cpp )

make_unit( "examples" oop/complex_numbers__declaring_an_object_type.cpp )
make_unit( "examples" oop/data_driven_physics.cpp                       )
