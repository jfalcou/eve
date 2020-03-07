.. _function-oneminus:

########
oneminus
########

**Required header:** ``#include <eve/function/oneminus.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ oneminus = {};
   }

Function object computing ``1-x`` of a :ref:`Value <concept-value>` x.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise oneminusument of the :ref:`wide <type-wide>`.
* [2] Computes the oneminusument of the scalar.

Parameters
**********

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

Return value
**************

* [1,2] A value with the same type as the parameter.

Options
*******

  - the :ref:`saturated_ <feature-decorator>` decorator acts as ``saturated_(sub)(1,x)``


Example
*******

.. include:: ../../../../test/doc/core/oneminus.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/oneminus.txt
  :literal:
