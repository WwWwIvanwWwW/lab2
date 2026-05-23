#pragma once

#include <memory>
#include <stdexcept>
#include <utility>

template <class T> class LinkedList
{
  private:
	struct Node {
		T data;
		std::unique_ptr<Node> next;
		Node(const T &value);
	};

	std::unique_ptr<Node> m_head;
	Node *m_tail;
	int m_length;

	void validateIndex(int index) const;
	Node *getNode(int index) const;

  public:
	LinkedList();
	LinkedList(T *items, int count);
	LinkedList(const LinkedList<T> &other);
	LinkedList<T> &operator=(const LinkedList<T> &other);
	LinkedList(LinkedList<T> &&other) noexcept;
	LinkedList<T> &operator=(LinkedList<T> &&other) noexcept;
	~LinkedList() = default;

	T &operator[](int index);
	void swap(LinkedList<T> &other) noexcept;
	T GetFirst() const;
	T GetLast() const;
	T Get(int index) const;
	LinkedList<T> GetSubList(int startIndex, int endIndex) const;
	int GetLength() const;

	void Append(T item);
	void Prepend(T item);
	void InsertAt(T item, int index);
	LinkedList<T> Concat(const LinkedList<T> &list) const;
};

#include "LinkedList.tpp"