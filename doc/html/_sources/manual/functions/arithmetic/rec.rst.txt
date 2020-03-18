.. _function-rec:

###
rec
###

**Required header:** ``#include <eve/function/rec.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rec = {};
   }

Function object computing the inverse of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise inverse value of the :ref:`Value <concept-value>`.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Options
*******

  - With the :ref:`raw_ <feature-decorator>` decorator: if a proper intrinsic exist it is called with possibly poor accuracy in return
  - With no decorator an accurate inverse is provided
  - With :ref:`pedantic_ <feature-decorator>` decorator: with integral inputs the inverse of 0 is the maximal value of the input type.


.. seealso::  :ref:`div <function-div>`

Example
*******

.. include:: ../../../../test/doc/core/rec.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rec.txt
  :literal:
