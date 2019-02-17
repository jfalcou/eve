.. _concept-logical:

Logical
=======

A :ref:`concept-logical` type is representing a boolean value while keeping track of the type used
to generate those boolean.

Requirements
------------

A type ``T`` satisfies :ref:`concept-logical` if it refines Regular, is convertible to ``bool``
and if :

  - ``T``::value_type evaluates to a :ref:`concept-vectorizable` type that represent the original type used to
    generate this instance of ``T``.

  - ``T`` is constructible from any type convertible to ``bool``
  - For any ``a`` of type ``T`` and any ``u`` of any type convertible to ``bool``, ``a = u`` is a valid expression of :ref:`concept-logical` type
  - For any ``a`` of type ``T``, ``!a`` is a valid expression of :ref:`concept-logical` type
  - For any ``a`` of type ``T``, ``~a`` is a valid expression of :ref:`concept-logical` type
  - For any ``a`` and ``b`` of type ``T``, ``a && b`` is a valid expression of :ref:`concept-logical` type
  - For any ``a`` and ``b`` of type ``T``, ``a || b`` is a valid expression of :ref:`concept-logical` type

Example
-------

  - ``eve::logical<short>``
