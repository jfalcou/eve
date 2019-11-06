.. _function-abs:

###
abs
###

**Required header:** ``#include <eve/function/abs.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ abs = {};
   }

Function object computing the absolute value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise absolute value of the :ref:`wide <type-wide>`.
* [2] Computes the absolute value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - Be aware that for signed integers the absolute value of :ref:`Valmin <constant-valmin>` is
    not representable  in the input type and the result is undefined.

  - ``abs`` is a also a standard library function name and there possibly exists
    a C macro version which may be called instead of the boost simd version.
    To avoid this you may prefix ``abs`` using ``eve::abs`` notation.


Options
*******

Example
*******

.. include:: ../../../../test/doc/core/abs.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/abs.txt
  :literal:
