.. _constant-true_:

True
=====

**Required header** ``#include <eve/constant/true.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> True<Value>() noexcept
   }

This 'constant' returns the  :ref:`Value <concept-value>` corresponding to true


.. seealso::  :ref:`False <constant-false_>`,  :ref:`Zero <constant-zero>`

Template parameter
------------------

  - ``Value``  : the returned value is of type ``as_logical_t<Value>``

