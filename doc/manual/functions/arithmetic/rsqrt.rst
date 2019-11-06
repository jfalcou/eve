.. _function-rsqrt:

#####
rsqrt
#####

**Required header:** ``#include <eve/function/rsqrt.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rsqrt = {};
   }

Function object computing the inverse of the square root value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise inverse square root value of the :ref:`wide <type-wide>`.
* [2] Computes the inverse square root value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
*******

 Not defined for Integral typed entries

Options
*******

  - ``raw_``: if any fast and dirty intrinsic exists it will be returned by the ``rsqrt[raw_]`` call

Example
*******

.. include:: ../../../../test/doc/core/rsqrt.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rsqrt.txt
  :literal:
