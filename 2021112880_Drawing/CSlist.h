#pragma once
struct Node
{
	int now_RGB = 0;//画笔颜色
	void* data;
	int now_type;//存储形状
	Node* next = nullptr;
};
class CSlist
{
public:
	CSlist();
	Node* head;
	//头插
	void InputFront(Node* Pelem);
	//尾插
	void InputTail(Node* Pelem);
	//获取链表长度
	int Length()const;
	//判断链表是否为空
	bool IsEmpty()const;
	//将链表清空
	void MakeEmpty();
	//将第i个数据取出
	Node* GetElement(int i);
	//在第几个数值之后插入新节点
	void Input_behind_pos(Node* Pelem, int pos);
	//在第几个数值之前插入新节点
	void Input_before_pos(Node* Pelem, int pos);

	void Delete(int pos);

};