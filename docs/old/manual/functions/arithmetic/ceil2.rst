.. _function-ceil2:

#####
ceil2
#####

**Required header:** ``#include <eve/function/ceil2.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ceil2 = {};
   }

Function object computing the least power of two value greater or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise least power of two values greater or equal to the value of the parameter.

Parameter
**********

* ``x``: Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Note
******

  - if the expected result is not representable in the parameter type the result is undefined.

Example
*******

.. include:: ../../../../test/doc/core/ceil2.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ceil2.txt
  :literal:
