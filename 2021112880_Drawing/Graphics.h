#pragma once
class Graphics 
{
public:
	Graphics() = default;
	~Graphics() = default;
	//��ͼ����
	virtual void Draw(CDC* pDC) = 0;
	//ѡ����
	int Selected(CPoint p);
};
