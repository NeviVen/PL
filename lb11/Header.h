#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	shared_ptr<Node> next;
	T data;
};

template <typename T>
class LinkedList
{
private:
	shared_ptr<Node<T>> head;
	shared_ptr<Node<T>> tail;

public:
	LinkedList() : head(NULL), tail(NULL)
	{
		/*this->head = nullptr;
		this->tail = nullptr;*/
	}

	void push_back(T data)
	{
		shared_ptr<Node<T>> tmp(new Node<T>);
		tmp->data = data;
		tmp->next = head;

		if (head == NULL)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tail = tail->next;
		}
	}

	shared_ptr<Node<T>> find(T data)
	{
		shared_ptr<Node<T>> tmp(head);
		if (head == NULL)
		{
			cerr << "Linked list is empty\n";
			exit(1);
		}
		if (head->data == data)
			return head;

		tmp = tmp->next;
		while (tmp != head && tmp != NULL)
		{
			if (tmp->data == data)
				return tmp;

			tmp = tmp->next;
		}

		return NULL;
	}

	void insert(shared_ptr<Node<T>> prev, T data)
	{
		if (prev == NULL)
		{
			cerr << "Insert error. Element not found.\n";
			exit(1);
		}

		shared_ptr<Node<T>> tmp(new Node<T>);
		tmp->data = data;

		if (prev == tail)
		{
			tmp = tail->next;
			tmp->next = head;
			tail = tmp;
			return;
		}

		tmp->next = prev->next;
		prev->next = tmp;
	}

	void pop(shared_ptr<Node<T>> del)
	{
		shared_ptr<Node<T>> tmp(head);
		while (tmp->next != del)
		{
			tmp = tmp->next;
		}

		tmp->next = del->next;
		if (del == tail)
		{
			tail = tmp;
		}
		if (del == head)
		{
			head = head->next;
		}

	}

	void print()
	{
		if (head == NULL)
		{
			cout << "Linked list is empty\n";
			return;
		}

		shared_ptr<Node<T>> tmp(head);
		if (tail == head)
		{
			cout << tmp->data << endl;
			return;
		}

		do
		{
			cout << tmp->data << " ";
			tmp = tmp->next;
		} while (tmp != head);

		cout << endl;
	}
};