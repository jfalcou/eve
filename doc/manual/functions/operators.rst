.. _function-infix:

###############
Infix Operators
###############

These functions provide scalar and SIMD version of the native C and **C++** operators as functional
interface.

.. rubric:: Arithmetic Operators

For most of those operators, their semantic are the same than for regular language operator
with the one restriction that both parameters must share a type. Note also that operations are
performed within the input type's range.

This implies that the use of these infix notations on integral scalars (standard **C++** call) 
will NOT necessarily lead to the same result as the function object call.

.. toctree::
   :maxdepth: 1

   arithmetic/add
   arithmetic/div
   arithmetic/mul
   arithmetic/shl
   arithmetic/shr
   arithmetic/sub


.. rubric:: Comparison Operators


The header ``#include <eve/function/predicate.hpp>`` allows the inclusion of all specific predicate
required headers in one shot.

.. toctree::
   :maxdepth: 1

   predicate/is_equal
   predicate/is_greater
   predicate/is_greater_equal
   predicate/is_less
   predicate/is_less_equal
   predicate/is_not_equal

.. rubric:: Logical Operators

As usual for overloaded operators, beware that those operators lose their short-cut behavior
when called on :ref:`concept-vectorized` types.

The header ``#include <eve/function/logical.hpp>`` allows the inclusion of all specific logical
required headers in one shot.

.. toctree::
   :maxdepth: 1

   logical/logical_and
   logical/logical_not
   logical/logical_or


.. rubric:: Bitwise Operators

Bitwise operations are extended to work on any :ref:`concept-ieeevalue` types by considering the masking
operations to apply on the value bit patterns while retaining its original types.

The header ``#include <eve/function/bitwise.hpp>`` allows the inclusion of all specific bitwise
required headers in one shot.

.. toctree::
   :maxdepth: 1

   bit/bit_and
   bit/bit_not
   bit/bit_or
   bit/bit_shl
   bit/bit_shr
   bit/bit_xor



