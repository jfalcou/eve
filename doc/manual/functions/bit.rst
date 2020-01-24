.. _function-bit:

#################
Bitwise Functions
#################

These functions provide scalar and SIMD version of bit operations.
Bitwise operations are extended to work on any :ref:`concept-value` (including :ref:`concept-ieeevalue`)  types by considering the masking
operations to apply on the value bit patterns while retaining its original types.

The header ``#include <eve/function/bit.hpp>`` allows the inclusion of all specific bit
required headers in one shot.

.. toctree::
   :maxdepth: 1
   :glob:

   bit/*
