#include "BitSequence.hpp"
#include "MutableArraySequence.hpp"
#include <stdexcept>

extern "C" {

#define CATCH_INT try {
#define CATCH_INT_END                                                          \
	}                                                                          \
	catch (...) { return 0; }

#define CATCH_PTR try {
#define CATCH_PTR_END                                                          \
	}                                                                          \
	catch (...) { return nullptr; }

void *BitSequence_new()
{
	CATCH_PTR
	return new BitSequence();
	CATCH_PTR_END
}

int BitSequence_delete(void *ptr)
{
	if (ptr)
		delete static_cast<BitSequence *>(ptr);
	return 1;
}

int BitSequence_append(void *ptr, int value)
{
	CATCH_INT
	static_cast<BitSequence *>(ptr)->Append(Bit(value != 0));
	return 1;
	CATCH_INT_END
}

int BitSequence_prepend(void *ptr, int value)
{
	CATCH_INT
	static_cast<BitSequence *>(ptr)->Prepend(Bit(value != 0));
	return 1;
	CATCH_INT_END
}

int BitSequence_insertAt(void *ptr, int index, int value)
{
	CATCH_INT
	static_cast<BitSequence *>(ptr)->InsertAt(Bit(value != 0), index);
	return 1;
	CATCH_INT_END
}

int BitSequence_get(void *ptr, int index, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<BitSequence *>(ptr)->Get(index).GetValue() ? 1 : 0;
	} catch (...) {
		if (error)
			*error = 1;
		return 0;
	}
}

int BitSequence_length(void *ptr, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<BitSequence *>(ptr)->GetLength();
	} catch (...) {
		if (error)
			*error = 1;
		return 0;
	}
}

void *BitSequence_getSubsequence(void *ptr, int start, int end, int *error)
{
	try {
		if (error)
			*error = 0;
		auto sub = static_cast<BitSequence *>(ptr)->GetSubsequence(start, end);
		return static_cast<BitSequence *>(sub.release());
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

void *BitSequence_concat(void *ptr, void *other, int *error)
{
	try {
		if (error)
			*error = 0;
		auto res = static_cast<BitSequence *>(ptr)->Concat(
			static_cast<BitSequence *>(other));
		return static_cast<BitSequence *>(res.release());
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

void *BitSequence_and(void *ptr, void *other, int *error)
{
	try {
		if (error)
			*error = 0;
		BitSequence res = (*static_cast<BitSequence *>(ptr)) &
						  (*static_cast<BitSequence *>(other));
		return new BitSequence(res);
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

void *BitSequence_or(void *ptr, void *other, int *error)
{
	try {
		if (error)
			*error = 0;
		BitSequence res = (*static_cast<BitSequence *>(ptr)) |
						  (*static_cast<BitSequence *>(other));
		return new BitSequence(res);
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

void *BitSequence_xor(void *ptr, void *other, int *error)
{
	try {
		if (error)
			*error = 0;
		BitSequence res = (*static_cast<BitSequence *>(ptr)) ^
						  (*static_cast<BitSequence *>(other));
		return new BitSequence(res);
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

void *BitSequence_not(void *ptr, int *error)
{
	try {
		if (error)
			*error = 0;
		BitSequence res = ~(*static_cast<BitSequence *>(ptr));
		return new BitSequence(res);
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

void *MutableArraySequence_new()
{
	CATCH_PTR
	return new MutableArraySequence<int>();
	CATCH_PTR_END
}

int MutableArraySequence_delete(void *ptr)
{
	if (ptr)
		delete static_cast<MutableArraySequence<int> *>(ptr);
	return 1;
}

int MutableArraySequence_append(void *ptr, int value)
{
	CATCH_INT
	static_cast<MutableArraySequence<int> *>(ptr)->Append(value);
	return 1;
	CATCH_INT_END
}

int MutableArraySequence_prepend(void *ptr, int value)
{
	CATCH_INT
	static_cast<MutableArraySequence<int> *>(ptr)->Prepend(value);
	return 1;
	CATCH_INT_END
}

int MutableArraySequence_insertAt(void *ptr, int index, int value)
{
	CATCH_INT
	static_cast<MutableArraySequence<int> *>(ptr)->InsertAt(value, index);
	return 1;
	CATCH_INT_END
}

int MutableArraySequence_get(void *ptr, int index, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<MutableArraySequence<int> *>(ptr)->Get(index);
	} catch (...) {
		if (error)
			*error = 1;
		return 0;
	}
}

int MutableArraySequence_getFirst(void *ptr, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<MutableArraySequence<int> *>(ptr)->GetFirst();
	} catch (...) {
		if (error)
			*error = 1;
		return 0;
	}
}

int MutableArraySequence_getLast(void *ptr, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<MutableArraySequence<int> *>(ptr)->GetLast();
	} catch (...) {
		if (error)
			*error = 1;
		return 0;
	}
}

int MutableArraySequence_length(void *ptr, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<MutableArraySequence<int> *>(ptr)->GetLength();
	} catch (...) {
		if (error)
			*error = 1;
		return 0;
	}
}

void *MutableArraySequence_getSubsequence(void *ptr, int start, int end,
										  int *error)
{
	try {
		if (error)
			*error = 0;
		auto sub =
			static_cast<MutableArraySequence<int> *>(ptr)->GetSubsequence(start,
																		  end);
		return static_cast<MutableArraySequence<int> *>(sub.release());
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

void *MutableArraySequence_concat(void *ptr, void *other, int *error)
{
	try {
		if (error)
			*error = 0;
		auto res = static_cast<MutableArraySequence<int> *>(ptr)->Concat(
			static_cast<MutableArraySequence<int> *>(other));
		return static_cast<MutableArraySequence<int> *>(res.release());
	} catch (...) {
		if (error)
			*error = 1;
		return nullptr;
	}
}

int MutableArraySequence_clear(void **ptr)
{
	try {
		auto *old = static_cast<MutableArraySequence<int> *>(*ptr);
		auto *newSeq = new MutableArraySequence<int>();
		*ptr = newSeq;
		delete old;
		return 1;
	} catch (...) {
		return 0;
	}
}
}