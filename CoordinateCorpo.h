#ifndef COORDINATECORPO_H
#define COORDINATECORPO_H
#include <QPoint>
#include <QRect>
class CoordinateCorpo{
private:
	int x;
	int y;
	unsigned int direzione;
public:
	int GetX() const {return x;}
	int GetY() const {return y;}
	int GetDirezione() const {return direzione;}
	void SetX(const int& a) {x=a;}
	void SetY(const int& a) {y=a;}
	void SetDirezione(const unsigned int& d) {if(d>=Nord && d<=Ovest) direzione=d;}
	void IncrementaX(const int &a) {x+=a;}
	void IncrementaY(const int &a) {y+=a;}
	bool IsInside(const QRect& a) const {return a.contains(x,y,false);}
	bool IsInside(int a,int b,int c, int d) const {return IsInside(QRect(a,b,c-a,d-b));}
	enum {Nord,Est,Sud,Ovest};
	CoordinateCorpo() : x(0),y(0),direzione(Est){}
	CoordinateCorpo( int a,  int b): x(a),y(b),direzione(Est){}
	CoordinateCorpo( int a,  int b, unsigned int d): x(a),y(b){if(d<Nord || d>Ovest) direzione=Est; else direzione=d;}
	bool operator==(const CoordinateCorpo& a) const {return (x==a.x && y==a.y);}
	CoordinateCorpo& operator=(const CoordinateCorpo& a){x=a.x; y=a.y; direzione=a.direzione; return *this;}
};
#endif