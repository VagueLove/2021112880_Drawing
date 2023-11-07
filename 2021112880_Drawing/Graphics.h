#pragma once
class Graphics 
{
public:
	Graphics() = default;
	~Graphics() = default;
	//»æÍ¼º¯Êý
	virtual void Draw(CDC* pDC) = 0;
	//Ñ¡Ôñº¯Êý
	int Selected(CPoint p);
};
