#include "BitSequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "ImmutableListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include <stdexcept>

extern "C" {

#define DEFINE_SEQUENCE(name, type)                                            \
	void *name##_new()                                                         \
	{                                                                          \
		try {                                                                  \
			return new type();                                                 \
		} catch (...) {                                                        \
			return nullptr;                                                    \
		}                                                                      \
	}                                                                          \
	int name##_delete(void *ptr)                                               \
	{                                                                          \
		if (ptr)                                                               \
			delete static_cast<type *>(ptr);                                   \
		return 1;                                                              \
	}                                                                          \
	int name##_append(void *ptr, int value)                                    \
	{                                                                          \
		try {                                                                  \
			static_cast<type *>(ptr)->Append(value);                           \
			return 1;                                                          \
		} catch (...) {                                                        \
			return 0;                                                          \
		}                                                                      \
	}                                                                          \
	int name##_prepend(void *ptr, int value)                                   \
	{                                                                          \
		try {                                                                  \
			static_cast<type *>(ptr)->Prepend(value);                          \
			return 1;                                                          \
		} catch (...) {                                                        \
			return 0;                                                          \
		}                                                                      \
	}                                                                          \
	int name##_insertAt(void *ptr, int index, int value)                       \
	{                                                                          \
		try {                                                                  \
			static_cast<type *>(ptr)->InsertAt(value, index);                  \
			return 1;                                                          \
		} catch (...) {                                                        \
			return 0;                                                          \
		}                                                                      \
	}                                                                          \
	int name##_get(void *ptr, int index, int *error)                           \
	{                                                                          \
		try {                                                                  \
			if (error)                                                         \
				*error = 0;                                                    \
			return static_cast<type *>(ptr)->Get(index);                       \
		} catch (...) {                                                        \
			if (error)                                                         \
				*error = 1;                                                    \
			return 0;                                                          \
		}                                                                      \
	}                                                                          \
	int name##_getFirst(void *ptr, int *error)                                 \
	{                                                                          \
		try {                                                                  \
			if (error)                                                         \
				*error = 0;                                                    \
			return static_cast<type *>(ptr)->GetFirst();                       \
		} catch (...) {                                                        \
			if (error)                                                         \
				*error = 1;                                                    \
			return 0;                                                          \
		}                                                                      \
	}                                                                          \
	int name##_getLast(void *ptr, int *error)                                  \
	{                                                                          \
		try {                                                                  \
			if (error)                                                         \
				*error = 0;                                                    \
			return static_cast<type *>(ptr)->GetLast();                        \
		} catch (...) {                                                        \
			if (error)                                                         \
				*error = 1;                                                    \
			return 0;                                                          \
		}                                                                      \
	}                                                                          \
	int name##_length(void *ptr, int *error)                                   \
	{                                                                          \
		try {                                                                  \
			if (error)                                                         \
				*error = 0;                                                    \
			return static_cast<type *>(ptr)->GetLength();                      \
		} catch (...) {                                                        \
			if (error)                                                         \
				*error = 1;                                                    \
			return 0;                                                          \
		}                                                                      \
	}                                                                          \
	void *name##_getSubsequence(void *ptr, int start, int end, int *error)     \
	{                                                                          \
		try {                                                                  \
			if (error)                                                         \
				*error = 0;                                                    \
			auto sub = static_cast<type *>(ptr)->GetSubsequence(start, end);   \
			return static_cast<type *>(sub.release());                         \
		} catch (...) {                                                        \
			if (error)                                                         \
				*error = 1;                                                    \
			return nullptr;                                                    \
		}                                                                      \
	}                                                                          \
	void *name##_concat(void *ptr, void *other, int *error)                    \
	{                                                                          \
		try {                                                                  \
			if (error)                                                         \
				*error = 0;                                                    \
			auto res =                                                         \
				static_cast<type *>(ptr)->Concat(static_cast<type *>(other));  \
			return static_cast<type *>(res.release());                         \
		} catch (...) {                                                        \
			if (error)                                                         \
				*error = 1;                                                    \
			return nullptr;                                                    \
		}                                                                      \
	}                                                                          \
	int name##_clear(void **ptr)                                               \
	{                                                                          \
		try {                                                                  \
			auto *old = static_cast<type *>(*ptr);                             \
			*ptr = new type();                                                 \
			delete old;                                                        \
			return 1;                                                          \
		} catch (...) {                                                        \
			return 0;                                                          \
		}                                                                      \
	}

DEFINE_SEQUENCE(MutableArraySequence, MutableArraySequence<int>)
DEFINE_SEQUENCE(ImmutableArraySequence, ImmutableArraySequence<int>)
DEFINE_SEQUENCE(MutableListSequence, MutableListSequence<int>)
DEFINE_SEQUENCE(ImmutableListSequence, ImmutableListSequence<int>)

void *BitSequence_new()
{
	try {
		return new BitSequence();
	} catch (...) {
		return nullptr;
	}
}
int BitSequence_delete(void *ptr)
{
	if (ptr)
		delete static_cast<BitSequence *>(ptr);
	return 1;
}

int BitSequence_append(void *ptr, int value)
{
	try {
		static_cast<BitSequence *>(ptr)->Append(Bit(value != 0));
		return 1;
	} catch (...) {
		return 0;
	}
}
int BitSequence_prepend(void *ptr, int value)
{
	try {
		static_cast<BitSequence *>(ptr)->Prepend(Bit(value != 0));
		return 1;
	} catch (...) {
		return 0;
	}
}
int BitSequence_insertAt(void *ptr, int index, int value)
{
	try {
		static_cast<BitSequence *>(ptr)->InsertAt(Bit(value != 0), index);
		return 1;
	} catch (...) {
		return 0;
	}
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
int BitSequence_getFirst(void *ptr, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<BitSequence *>(ptr)->GetFirst().GetValue() ? 1 : 0;
	} catch (...) {
		if (error)
			*error = 1;
		return 0;
	}
}
int BitSequence_getLast(void *ptr, int *error)
{
	try {
		if (error)
			*error = 0;
		return static_cast<BitSequence *>(ptr)->GetLast().GetValue() ? 1 : 0;
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

int BitSequence_clear(void **ptr)
{
	try {
		auto *old = static_cast<BitSequence *>(*ptr);
		*ptr = new BitSequence();
		delete old;
		return 1;
	} catch (...) {
		return 0;
	}
}
}