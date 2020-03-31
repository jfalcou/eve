.. _function-horizontal:

########################
Horizontal Functions
########################

These functions provide (scalar and) SIMD  horizontal  functions. A function is told to be 'horizontal' on a SIMD vector if it returns
a scalar (or SIMD) result depending on all elements of the input vector. 

The header ``#include <eve/function/horizontal.hpp>`` allows the inclusion of all specific horizontal functions required headers in one shot.

.. toctree::
   :maxdepth: 1
   :glob:

   horizontal/*
