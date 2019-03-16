.. _function-predicate:

###################
Predicate Functions
###################

These functions provide scalar and SIMD version of classical scalar predicate operations.

The main difference with standard is those operations do not return `bool` but a :ref:`concept-logicalValue`. 

The header ``#include <eve/function/predicate.hpp>`` allows the inclusion of all specific bitwise
required headers in one shot.

.. toctree::
   :maxdepth: 1
   :glob:

   predicate/*
