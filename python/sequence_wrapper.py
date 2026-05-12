import ctypes
import os

_lib_path = os.path.join(os.path.dirname(__file__), "..", "build", "libsequence_lib.so")
_lib = ctypes.CDLL(_lib_path)


class BitSequence:
    def __init__(self, obj=None):
        if obj is None:
            self.obj = _lib.BitSequence_new()
        else:
            self.obj = obj
        if not self.obj:
            raise RuntimeError("Failed to create BitSequence")

    def __del__(self):
        if hasattr(self, "obj") and self.obj:
            _lib.BitSequence_delete(self.obj)
            self.obj = None

    def append(self, value: int):
        if value not in (0, 1):
            raise ValueError("BitSequence accepts only 0 or 1")
        ok = _lib.BitSequence_append(self.obj, value)
        if not ok:
            raise RuntimeError("Append failed")

    def prepend(self, value: int):
        if value not in (0, 1):
            raise ValueError("BitSequence accepts only 0 or 1")
        ok = _lib.BitSequence_prepend(self.obj, value)
        if not ok:
            raise RuntimeError("Prepend failed")

    def insert_at(self, index: int, value: int):
        if value not in (0, 1):
            raise ValueError("BitSequence accepts only 0 or 1")
        ok = _lib.BitSequence_insertAt(self.obj, index, value)
        if not ok:
            raise RuntimeError("InsertAt failed")

    def get(self, index: int) -> int:
        err = ctypes.c_int(0)
        val = _lib.BitSequence_get(self.obj, index, ctypes.byref(err))
        if err.value:
            raise IndexError("Index out of range")
        return val

    def get_length(self) -> int:
        err = ctypes.c_int(0)
        length = _lib.BitSequence_length(self.obj, ctypes.byref(err))
        if err.value:
            raise RuntimeError("Failed to get length")
        return length

    def get_subsequence(self, start: int, end: int):
        err = ctypes.c_int(0)
        sub_obj = _lib.BitSequence_getSubsequence(self.obj, start, end, ctypes.byref(err))
        if err.value or not sub_obj:
            raise IndexError("Invalid indices")
        return BitSequence(sub_obj)

    def concat(self, other):
        err = ctypes.c_int(0)
        res_obj = _lib.BitSequence_concat(self.obj, other.obj, ctypes.byref(err))
        if err.value or not res_obj:
            raise RuntimeError("Concat failed")
        return BitSequence(res_obj)

    def bitwise_and(self, other):
        err = ctypes.c_int(0)
        res_obj = _lib.BitSequence_and(self.obj, other.obj, ctypes.byref(err))
        if err.value or not res_obj:
            raise RuntimeError("AND operation failed")
        return BitSequence(res_obj)

    def bitwise_or(self, other):
        err = ctypes.c_int(0)
        res_obj = _lib.BitSequence_or(self.obj, other.obj, ctypes.byref(err))
        if err.value or not res_obj:
            raise RuntimeError("OR operation failed")
        return BitSequence(res_obj)

    def bitwise_xor(self, other):
        err = ctypes.c_int(0)
        res_obj = _lib.BitSequence_xor(self.obj, other.obj, ctypes.byref(err))
        if err.value or not res_obj:
            raise RuntimeError("XOR operation failed")
        return BitSequence(res_obj)

    def bitwise_not(self):
        err = ctypes.c_int(0)
        res_obj = _lib.BitSequence_not(self.obj, ctypes.byref(err))
        if err.value or not res_obj:
            raise RuntimeError("NOT operation failed")
        return BitSequence(res_obj)

    def to_string(self) -> str:
        length = self.get_length()
        items = [str(self.get(i)) for i in range(length)]
        return "[" + ", ".join(items) + "]"


_lib.BitSequence_new.argtypes = []
_lib.BitSequence_new.restype = ctypes.c_void_p

_lib.BitSequence_delete.argtypes = [ctypes.c_void_p]
_lib.BitSequence_delete.restype = ctypes.c_int

_lib.BitSequence_append.argtypes = [ctypes.c_void_p, ctypes.c_int]
_lib.BitSequence_append.restype = ctypes.c_int

_lib.BitSequence_prepend.argtypes = [ctypes.c_void_p, ctypes.c_int]
_lib.BitSequence_prepend.restype = ctypes.c_int

_lib.BitSequence_insertAt.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
_lib.BitSequence_insertAt.restype = ctypes.c_int

_lib.BitSequence_get.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
_lib.BitSequence_get.restype = ctypes.c_int

_lib.BitSequence_length.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.BitSequence_length.restype = ctypes.c_int

_lib.BitSequence_getSubsequence.argtypes = [
    ctypes.c_void_p,
    ctypes.c_int,
    ctypes.c_int,
    ctypes.POINTER(ctypes.c_int),
]
_lib.BitSequence_getSubsequence.restype = ctypes.c_void_p

_lib.BitSequence_concat.argtypes = [
    ctypes.c_void_p,
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_int),
]
_lib.BitSequence_concat.restype = ctypes.c_void_p

_lib.BitSequence_and.argtypes = [
    ctypes.c_void_p,
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_int),
]
_lib.BitSequence_and.restype = ctypes.c_void_p

_lib.BitSequence_or.argtypes = [
    ctypes.c_void_p,
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_int),
]
_lib.BitSequence_or.restype = ctypes.c_void_p

_lib.BitSequence_xor.argtypes = [
    ctypes.c_void_p,
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_int),
]
_lib.BitSequence_xor.restype = ctypes.c_void_p

_lib.BitSequence_not.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.BitSequence_not.restype = ctypes.c_void_p


class MutableArraySequence:
    def __init__(self, obj=None):
        if obj is None:
            self.obj = _lib.MutableArraySequence_new()
        else:
            self.obj = obj
        if not self.obj:
            raise RuntimeError("Failed to create MutableArraySequence")

    def __del__(self):
        if hasattr(self, "obj") and self.obj:
            _lib.MutableArraySequence_delete(self.obj)
            self.obj = None

    def append(self, value: int):
        ok = _lib.MutableArraySequence_append(self.obj, value)
        if not ok:
            raise RuntimeError("Append failed")

    def prepend(self, value: int):
        ok = _lib.MutableArraySequence_prepend(self.obj, value)
        if not ok:
            raise RuntimeError("Prepend failed")

    def insert_at(self, index: int, value: int):
        ok = _lib.MutableArraySequence_insertAt(self.obj, index, value)
        if not ok:
            raise RuntimeError("InsertAt failed")

    def get(self, index: int) -> int:
        err = ctypes.c_int(0)
        val = _lib.MutableArraySequence_get(self.obj, index, ctypes.byref(err))
        if err.value:
            raise IndexError("Index out of range")
        return val

    def get_first(self) -> int:
        err = ctypes.c_int(0)
        val = _lib.MutableArraySequence_getFirst(self.obj, ctypes.byref(err))
        if err.value:
            raise IndexError("Sequence is empty")
        return val

    def get_last(self) -> int:
        err = ctypes.c_int(0)
        val = _lib.MutableArraySequence_getLast(self.obj, ctypes.byref(err))
        if err.value:
            raise IndexError("Sequence is empty")
        return val

    def get_length(self) -> int:
        err = ctypes.c_int(0)
        length = _lib.MutableArraySequence_length(self.obj, ctypes.byref(err))
        if err.value:
            raise RuntimeError("Failed to get length")
        return length

    def get_subsequence(self, start: int, end: int):
        err = ctypes.c_int(0)
        sub_obj = _lib.MutableArraySequence_getSubsequence(
            self.obj, start, end, ctypes.byref(err)
        )
        if err.value or not sub_obj:
            raise IndexError("Invalid indices")
        return MutableArraySequence(sub_obj)

    def concat(self, other):
        err = ctypes.c_int(0)
        res_obj = _lib.MutableArraySequence_concat(self.obj, other.obj, ctypes.byref(err))
        if err.value or not res_obj:
            raise RuntimeError("Concat failed")
        return MutableArraySequence(res_obj)

    def clear(self):
        if not self.obj:
            raise RuntimeError("Sequence is not initialized")
        ok = _lib.MutableArraySequence_clear(ctypes.byref(self.obj))
        if not ok:
            raise RuntimeError("Clear failed")

    def to_string(self) -> str:
        length = self.get_length()
        items = [str(self.get(i)) for i in range(length)]
        return "[" + ", ".join(items) + "]"


_lib.MutableArraySequence_new.argtypes = []
_lib.MutableArraySequence_new.restype = ctypes.c_void_p

_lib.MutableArraySequence_delete.argtypes = [ctypes.c_void_p]
_lib.MutableArraySequence_delete.restype = ctypes.c_int

_lib.MutableArraySequence_append.argtypes = [ctypes.c_void_p, ctypes.c_int]
_lib.MutableArraySequence_append.restype = ctypes.c_int

_lib.MutableArraySequence_prepend.argtypes = [ctypes.c_void_p, ctypes.c_int]
_lib.MutableArraySequence_prepend.restype = ctypes.c_int

_lib.MutableArraySequence_insertAt.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
_lib.MutableArraySequence_insertAt.restype = ctypes.c_int

_lib.MutableArraySequence_get.argtypes = [
    ctypes.c_void_p,
    ctypes.c_int,
    ctypes.POINTER(ctypes.c_int),
]
_lib.MutableArraySequence_get.restype = ctypes.c_int

_lib.MutableArraySequence_getFirst.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.MutableArraySequence_getFirst.restype = ctypes.c_int

_lib.MutableArraySequence_getLast.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.MutableArraySequence_getLast.restype = ctypes.c_int

_lib.MutableArraySequence_length.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.MutableArraySequence_length.restype = ctypes.c_int

_lib.MutableArraySequence_getSubsequence.argtypes = [
    ctypes.c_void_p,
    ctypes.c_int,
    ctypes.c_int,
    ctypes.POINTER(ctypes.c_int),
]
_lib.MutableArraySequence_getSubsequence.restype = ctypes.c_void_p

_lib.MutableArraySequence_concat.argtypes = [
    ctypes.c_void_p,
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_int),
]
_lib.MutableArraySequence_concat.restype = ctypes.c_void_p

_lib.MutableArraySequence_clear.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
_lib.MutableArraySequence_clear.restype = ctypes.c_int