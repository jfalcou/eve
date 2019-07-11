.. _function-infix:

###############
Infix Operators
###############

These functions provide scalar and SIMD version of the native C and C++ operators as functional
interface.

.. rubric:: Arithmetic Operators

For most of those operators, their semantic are the same than for regular language operator
with the one restriction that both parameters must share a type. Note also that operations are
performed within the input type's range.

.. toctree::
   :maxdepth: 1

   arithmetic/add
   arithmetic/sub

.. rubric:: Comparison Operators

.. toctree::
   :maxdepth: 1

   predicate/is_equal

.. rubric:: Logical Operators

As usual for overloaded operators, beware that those operators lose their short-cut behavior
when called on :ref:`concept-vectorized` types.

.. toctree::
   :maxdepth: 1

.. rubric:: Bitwise Operators

Bitwise operations are extended to work on any :ref:`concept-ieeevalue` types by considering the masking
operations to apply on the value bit patterns while retaining its original types.

The header ``#include <eve/function/bitwise.hpp>`` allows the inclusion of all specific bitwise
required headers in one shot.

.. toctree::
   :maxdepth: 1

   bitwise/bitwise_and
   bitwise/bitwise_not
   bitwise/bitwise_or
   bitwise/bitwise_xor



