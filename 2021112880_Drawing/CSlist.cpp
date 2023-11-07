#include "pch.h"
#include "CSlist.h"

#include<iostream>
#include<stdlib.h>
using namespace std;

CSlist::CSlist()
{
	head = nullptr;
}

void CSlist::InputTail(Node* Pelem)
{
	if (Pelem == nullptr)  return;
	if (head == nullptr)
	{
		head = Pelem;
		return;
	}

	Node* temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = Pelem;
}


void CSlist::InputFront(struct Node* Pelem)
{
	if (Pelem == nullptr)  return;
	Pelem->next = head;
	head = Pelem;
}

int CSlist::Length()const
{
	if (head == nullptr)  
		return 0;

	struct Node* n = head;
	int length = 1;
	while (n->next)
	{
		++length;
		n = n->next;
	}
	return length;
}

bool CSlist::IsEmpty()const
{
	return head == nullptr ? true : false;
}

void CSlist::MakeEmpty()
{
	struct Node* d;
	while (head)
	{
		d = head;
		head = head->next;
		delete d;
	}
}

struct Node* CSlist::GetElement(int i)
{
	int pos = 0;
	struct Node* cur = head;
	if (i <= 0 || i > Length()) cout << "error" << endl;

	while (cur)
	{
		++pos;
		if (pos == i)
		{
			return cur;
		}
		else  cur = cur->next;
	}
}

void CSlist::Input_behind_pos(struct Node* Pelem, int pos)
{

	struct Node* after = GetElement(pos + 1);
	Pelem->next = after;//新节点的next指向原来的下一个节点
	struct Node* before = GetElement(pos);
	before->next = Pelem;//上一个节点的next指向新节点
}

void CSlist::Input_before_pos(struct Node* Pelem, int pos)
{

	struct Node* before = GetElement(pos - 1);
	before->next = Pelem;//上一个节点的next指向新节点
	struct Node* after = GetElement(pos);
	Pelem->next = after;//新节点的next指向原来的下一个节点
}

void CSlist::Delete(int pos)
{
	struct Node* before = GetElement(pos - 1);
	struct Node* cur = GetElement(pos);
	struct Node* after = GetElement(pos + 1);
	before->next = after;
	delete cur;
}
