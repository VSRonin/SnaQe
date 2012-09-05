#ifndef COORDINATECORPO_H
#define COORDINATECORPO_H
#include <QPoint>
class CoordinateCorpo{
private:
	unsigned int x;
	unsigned int y;
	unsigned int direzione;
public:
	unsigned int GetX() const {return x;}
	unsigned int GetY() const {return y;}
	unsigned int GetDirezione() const {return direzione;}
	void SetX(const unsigned int& a) {x=a;}
	void SetY(const unsigned int& a) {y=a;}
	void SetDirezione(const unsigned int& d) {if(d>=Nord && d<=Ovest) direzione=d;}
	void IncrementaX(const int &a) {if (x+a<0) x=0; else x+=a;}
	void IncrementaY(const int &a) {if (y+a<0) y=0; else y+=a;}
	enum {Nord,Est,Sud,Ovest};
	CoordinateCorpo() : x(0),y(0),direzione(Est){}
	CoordinateCorpo(unsigned int a, unsigned int b): x(a),y(b),direzione(Est){}
	CoordinateCorpo(unsigned int a, unsigned int b, unsigned int d): x(a),y(b){if(d<Nord || d>Ovest) direzione=Est; else direzione=d;}
	bool operator==(const CoordinateCorpo& a) const {return (x==a.x && y==a.y);}
	CoordinateCorpo& operator=(const CoordinateCorpo& a){x=a.x; y=a.y; direzione=a.direzione; return *this;}
};
#endif