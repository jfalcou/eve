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
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise least power of two values greater or equal to the value of the :ref:`wide <type-wide>`.
* [2] Computes the least power of two value greater or equal to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - if the expected result is not representable in the parameter type the result is undefined.

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/ceil2.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ceil2.txt
  :literal:
