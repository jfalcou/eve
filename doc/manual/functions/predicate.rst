.. _function-predicate:

###################
Predicate Functions
###################

These functions provide scalar and SIMD version of scalar predicate operations.

The main difference is those operations do not return `bool` but a :ref:`concept-logicalValue`. 

The header ``#include <eve/function/predicate.hpp>`` allows the inclusion of all specific bitwise
required headers in one shot.

.. toctree::
   :maxdepth: 1
   :glob:

   predicate/*
