.. _function-bitwise:

#################
Bitwise Functions
#################

These functions provide scalar and SIMD version of bitwise operations.
Bitwise operations are extended to work on any floating-point types by considering the masking
operations to apply on the value bit patterns while retaining its original types.

The header ``#include <eve/function/bitwise.hpp>`` allows the inclusion of all specific bitwise
required headers in one shot.

.. toctree::
   :maxdepth: 1
   :glob:

   bitwise/*
