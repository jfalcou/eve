.. _function-signnz:

######
signnz
######

**Required header:** ``#include <eve/function/signnz.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ signnz = {};
   }

Function object computing the signnz (-1 or 1) of a :ref:`Value <concept-value>`, the signnz of zero being one.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise non zero sign of the value of the :ref:`wide <type-wide>`, the sign of zero being one.
* [2] Computes the non zero signnof the value of the scalar, the sign of zero being one.

Parameters
**********

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

Return value
**************

* [1,2] A value with the same type as the parameter.

Notes
******

  - With floating point entry the ``signnz`` of negative zeo is -1
  
  - With the :ref:`pedantic_ <feature-decorator>` decorator a nan entry will return a nan output

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/signnz.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/signnz.txt
  :literal:
