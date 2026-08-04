# type: ignore
import ctypes
import os
from typing import Optional, Any

_lib_path = os.path.join(os.path.dirname(__file__), "..", "build", "libsequence_lib.so")
_lib = ctypes.CDLL(_lib_path)


class _BaseSequence:
    def __init__(self, new_func, delete_func, obj: Optional[Any] = None):
        self._new_func = new_func
        self._delete_func = delete_func
        if obj is None:
            self.obj = new_func()
        else:
            self.obj = obj
        if not self.obj:
            raise RuntimeError("Failed to create sequence")

    def __del__(self):
        if hasattr(self, 'obj') and self.obj:
            self._delete_func(self.obj)
            self.obj = None

    def _call_void(self, method: str, *args) -> None:
        func = getattr(_lib, f"{self._prefix}_{method}")
        ok = func(self.obj, *args)
        if not ok:
            raise RuntimeError(f"{method} failed")

    def _call_with_error(self, method: str, *args) -> Any:
        err = ctypes.c_int(0)
        func = getattr(_lib, f"{self._prefix}_{method}")
        result = func(self.obj, *args, ctypes.byref(err))
        if err.value:
            raise IndexError("Operation failed")
        return result

    def _call_with_error_return_cls(self, method: str, *args):
        err = ctypes.c_int(0)
        func = getattr(_lib, f"{self._prefix}_{method}")
        result = func(self.obj, *args, ctypes.byref(err))
        if err.value or not result:
            raise RuntimeError("Operation failed")
        return self.__class__(result)

    def _call_clear(self) -> None:
        func = getattr(_lib, f"{self._prefix}_clear")
        ok = func(ctypes.byref(self.obj))
        if not ok:
            raise RuntimeError("Clear failed")

    def append(self, value: int) -> None:
        self._call_void("append", value)

    def prepend(self, value: int) -> None:
        self._call_void("prepend", value)

    def insert_at(self, index: int, value: int) -> None:
        self._call_void("insertAt", index, value)

    def get(self, index: int) -> int:
        return self._call_with_error("get", index)

    def get_first(self) -> int:
        return self._call_with_error("getFirst")

    def get_last(self) -> int:
        return self._call_with_error("getLast")

    def get_length(self) -> int:
        return self._call_with_error("length")

    def get_subsequence(self, start: int, end: int):
        return self._call_with_error_return_cls("getSubsequence", start, end)

    def concat(self, other):
        return self._call_with_error_return_cls("concat", other.obj)

    def clear(self) -> None:
        self._call_clear()

    def to_string(self) -> str:
        length = self.get_length()
        return "[" + ", ".join(str(self.get(i)) for i in range(length)) + "]"


def _config(cls_name: str, methods: list) -> None:
    for method, argtypes, restype in methods:
        func = getattr(_lib, f"{cls_name}_{method}")
        func.argtypes = argtypes
        func.restype = restype


_common = [
    ("new", [], ctypes.c_void_p),
    ("delete", [ctypes.c_void_p], ctypes.c_int),
    ("append", [ctypes.c_void_p, ctypes.c_int], ctypes.c_int),
    ("prepend", [ctypes.c_void_p, ctypes.c_int], ctypes.c_int),
    ("insertAt", [ctypes.c_void_p, ctypes.c_int, ctypes.c_int], ctypes.c_int),
    ("get", [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)], ctypes.c_int),
    ("getFirst", [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_int),
    ("getLast", [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_int),
    ("length", [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_int),
    ("getSubsequence", [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int)], ctypes.c_void_p),
    ("concat", [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_void_p),
    ("clear", [ctypes.POINTER(ctypes.c_void_p)], ctypes.c_int),
]

_bitwise = [
    ("and", [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_void_p),
    ("or", [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_void_p),
    ("xor", [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_void_p),
    ("not", [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)], ctypes.c_void_p),
]


def _make_sequence_class(cls_name: str):
    class DynamicSequence(_BaseSequence):
        _prefix = cls_name

        def __init__(self, obj=None):
            new_func = getattr(_lib, f"{cls_name}_new")
            del_func = getattr(_lib, f"{cls_name}_delete")
            super().__init__(new_func, del_func, obj)

    DynamicSequence.__name__ = cls_name
    return DynamicSequence


MutableArraySequence = _make_sequence_class("MutableArraySequence")
ImmutableArraySequence = _make_sequence_class("ImmutableArraySequence")
MutableListSequence = _make_sequence_class("MutableListSequence")
ImmutableListSequence = _make_sequence_class("ImmutableListSequence")


class BitSequence(_BaseSequence):
    _prefix = "BitSequence"

    def __init__(self, obj=None):
        super().__init__(_lib.BitSequence_new, _lib.BitSequence_delete, obj)

    def append(self, value: int) -> None:
        if value not in (0, 1):
            raise ValueError("BitSequence accepts only 0 or 1")
        super().append(value)

    def prepend(self, value: int) -> None:
        if value not in (0, 1):
            raise ValueError("BitSequence accepts only 0 or 1")
        super().prepend(value)

    def insert_at(self, index: int, value: int) -> None:
        if value not in (0, 1):
            raise ValueError("BitSequence accepts only 0 or 1")
        super().insert_at(index, value)

    def get(self, index: int) -> int:
        return self._call_with_error("get", index)

    def get_first(self) -> int:
        return self._call_with_error("getFirst")

    def get_last(self) -> int:
        return self._call_with_error("getLast")

    def get_length(self) -> int:
        return self._call_with_error("length")

    def get_subsequence(self, start: int, end: int):
        return self._call_with_error_return_cls("getSubsequence", start, end)

    def concat(self, other):
        return self._call_with_error_return_cls("concat", other.obj)

    def bitwise_and(self, other):
        return self._call_bitwise("and", other)

    def bitwise_or(self, other):
        return self._call_bitwise("or", other)

    def bitwise_xor(self, other):
        return self._call_bitwise("xor", other)

    def bitwise_not(self):
        return self._call_bitwise("not")

    def _call_bitwise(self, method: str, other=None):
        err = ctypes.c_int(0)
        func = getattr(_lib, f"BitSequence_{method}")
        if other is None:
            result = func(self.obj, ctypes.byref(err))
        else:
            result = func(self.obj, other.obj, ctypes.byref(err))
        if err.value or not result:
            raise RuntimeError(f"{method.upper()} operation failed")
        return BitSequence(result)

    def clear(self) -> None:
        self._call_clear()


for cls in ["MutableArraySequence", "ImmutableArraySequence", "MutableListSequence", "ImmutableListSequence"]:
    _config(cls, _common)

_config("BitSequence", _common + _bitwise)

for cls in ["MutableArraySequence", "ImmutableArraySequence", "MutableListSequence", "ImmutableListSequence", "BitSequence"]:
    func = getattr(_lib, f"{cls}_clear")
    func.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
    func.restype = ctypes.c_int
    

_lib.VectorInt_new.argtypes = []
_lib.VectorInt_new.restype = ctypes.c_void_p
_lib.VectorInt_delete.argtypes = [ctypes.c_void_p]
_lib.VectorInt_delete.restype = ctypes.c_int
_lib.VectorInt_getSize.argtypes = [ctypes.c_void_p]
_lib.VectorInt_getSize.restype = ctypes.c_int
_lib.VectorInt_get.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
_lib.VectorInt_get.restype = ctypes.c_int
_lib.VectorInt_set.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
_lib.VectorInt_set.restype = ctypes.c_int
_lib.VectorInt_add.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.VectorInt_add.restype = ctypes.c_void_p
_lib.VectorInt_sub.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.VectorInt_sub.restype = ctypes.c_void_p
_lib.VectorInt_mul.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
_lib.VectorInt_mul.restype = ctypes.c_void_p
_lib.VectorInt_norm.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_double)]
_lib.VectorInt_norm.restype = ctypes.c_int
_lib.VectorInt_dot.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
_lib.VectorInt_dot.restype = ctypes.c_int
_lib.VectorInt_toString.argtypes = [ctypes.c_void_p]
_lib.VectorInt_toString.restype = ctypes.c_char_p
_lib.VectorInt_clear.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
_lib.VectorInt_clear.restype = ctypes.c_int
_lib.VectorInt_new_with_size.argtypes = [ctypes.c_int]
_lib.VectorInt_new_with_size.restype = ctypes.c_void_p

class VectorInt:
    def __init__(self, size=None):
        if size is None:
            self.obj = _lib.VectorInt_new()
        else:
            self.obj = _lib.VectorInt_new_with_size(size)
        if not self.obj:
            raise RuntimeError("Failed to create VectorInt")
    
    def __del__(self):
        if hasattr(self, 'obj') and self.obj:
            _lib.VectorInt_delete(self.obj)
            self.obj = None
    
    def _check_ok(self, ok, msg):
        if not ok:
            raise RuntimeError(msg)
    
    def get_size(self) -> int:
        return _lib.VectorInt_getSize(self.obj)
    
    def get(self, index: int) -> int:
        err = ctypes.c_int(0)
        val = _lib.VectorInt_get(self.obj, index, ctypes.byref(err))
        if err.value:
            raise IndexError("Index out of range")
        return val
    
    def set(self, index: int, value: int) -> None:
        ok = _lib.VectorInt_set(self.obj, index, value)
        self._check_ok(ok, "Set failed")
    
    def add(self, other):
        err = ctypes.c_int(0)
        obj = _lib.VectorInt_add(self.obj, other.obj, ctypes.byref(err))
        if err.value or not obj:
            raise RuntimeError("Addition failed")
        return VectorInt(obj)
    
    def sub(self, other):
        err = ctypes.c_int(0)
        obj = _lib.VectorInt_sub(self.obj, other.obj, ctypes.byref(err))
        if err.value or not obj:
            raise RuntimeError("Subtraction failed")
        return VectorInt(obj)
    
    def mul(self, scalar: int):
        err = ctypes.c_int(0)
        obj = _lib.VectorInt_mul(self.obj, scalar, ctypes.byref(err))
        if err.value or not obj:
            raise RuntimeError("Multiplication failed")
        return VectorInt(obj)
    
    def norm(self) -> float:
        err = ctypes.c_double(0.0)
        ok = _lib.VectorInt_norm(self.obj, ctypes.byref(err))
        if not ok:
            raise RuntimeError("Norm calculation failed")
        return err.value
    
    def dot(self, other) -> int:
        err = ctypes.c_int(0)
        val = _lib.VectorInt_dot(self.obj, other.obj, ctypes.byref(err))
        if err.value:
            raise RuntimeError("Dot product failed")
        return val
    
    def to_string(self) -> str:
        result = _lib.VectorInt_toString(self.obj)
        if result:
            return result.decode('utf-8')
        return "[]"
    
    def clear(self) -> None:
        ok = _lib.VectorInt_clear(ctypes.byref(self.obj))
        self._check_ok(ok, "Clear failed")