#include "SelettoreImmagini.h"
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QPainter>
#include <QGridLayout>
#include <QTransform>
#include <QPropertyAnimation>
SelettoreImmagini::SelettoreImmagini(QWidget* parent, int Orient)
:QWidget(parent)
,Freccia(256,256)
,IndiceCorrente(-1)
,DurataAnimazione(500)
,VoidImage(256,256)
{
	if (Orient==Verticale || Orient==Orizzontale) Orientamento=Orient;
	else Orientamento=Orizzontale;
	Freccia.fill(QColor(0,0,0,0));
	QPainter Disegnatore(&Freccia);
	Disegnatore.setBrush(QBrush(QColor(0,0,0,255)));
	Disegnatore.setPen(QColor(0,0,0,255));
	QVector<QPoint> Punti;
	Punti.append(QPoint(0,256));
	Punti.append(QPoint(128,0));
	Punti.append(QPoint(256,256));
	Disegnatore.drawPolygon(QPolygon(Punti));

	PulsanteAlto=new QPushButton(this);
	PulsanteAlto->setObjectName("PulsanteAlto");
	PulsanteAlto->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	PulsanteAlto->setMinimumHeight(10);
	PulsanteAlto->setEnabled(false);

	PulsanteBasso=new QPushButton(this);
	PulsanteBasso->setObjectName("PulsanteBasso");
	PulsanteBasso->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	PulsanteBasso->setMinimumHeight(10);
	PulsanteBasso->setEnabled(false);

	PulsanteDestra=new QPushButton(this);
	PulsanteDestra->setObjectName("PulsanteDestra");
	PulsanteDestra->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
	PulsanteDestra->setMinimumWidth(10);
	PulsanteDestra->setEnabled(false);

	PulsanteSinistra=new QPushButton(this);
	PulsanteSinistra->setObjectName("PulsanteAlto");
	PulsanteSinistra->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
	PulsanteSinistra->setMinimumWidth(10);
	PulsanteSinistra->setEnabled(false);

	Displayer=new QFrame(this);
	Displayer->setObjectName("Displayer");
	Displayer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	Displayer->setMinimumSize(50,50);


	VoidImage.fill(QColor(0,0,0,255));

	IconaCorrente=new QLabel(Displayer);
	IconaCorrente->setObjectName("IconaCorrente");
	IconaCorrente->setScaledContents(true);
	IconaCorrente->setPixmap(VoidImage);
	
	QGridLayout* LayoutVisulizzatore=new QGridLayout(this);
	LayoutVisulizzatore->addWidget(PulsanteAlto,0,1);
	LayoutVisulizzatore->addWidget(PulsanteSinistra,1,0);
	LayoutVisulizzatore->addWidget(Displayer,1,1);
	LayoutVisulizzatore->addWidget(PulsanteDestra,1,2);
	LayoutVisulizzatore->addWidget(PulsanteBasso,2,1);
	if (Orientamento==Orizzontale){PulsanteAlto->hide(); PulsanteBasso->hide();}
	else {PulsanteDestra->hide(); PulsanteSinistra->hide();}
}
void SelettoreImmagini::resizeEvent(QResizeEvent *event){
	QTransform Rotazione;
	Rotazione.reset();
	if (Orientamento==Verticale) PulsanteAlto->setMask(Freccia.scaled(Displayer->width(),PulsanteAlto->height()).mask());
	Rotazione.rotate(90);
	if (Orientamento==Orizzontale) PulsanteDestra->setMask(Freccia.transformed(Rotazione).scaled(PulsanteDestra->width(),Displayer->height()).mask());
	Rotazione.rotate(90);
	if (Orientamento==Verticale) PulsanteBasso->setMask(Freccia.transformed(Rotazione).scaled(Displayer->width(),PulsanteBasso->height()).mask());
	Rotazione.rotate(90);
	if (Orientamento==Orizzontale) PulsanteSinistra->setMask(Freccia.transformed(Rotazione).scaled(PulsanteSinistra->width(),Displayer->height()).mask());
	IconaCorrente->setGeometry(0,0,Displayer->width(),Displayer->height());
	QWidget::resizeEvent(event);
}
void SelettoreImmagini::AggiungiImmagine(const QPixmap& fonte){
	Immagini.append(fonte);
	if (IndiceCorrente<0){
		IconaCorrente->setPixmap(Immagini.first());
		IndiceCorrente=0;
	}
	else {PulsanteBasso->setEnabled(true); PulsanteDestra->setEnabled(true);}
}
void SelettoreImmagini::SetIndex(int a){
	if (a>0 && a<Immagini.size()) ;
}
void SelettoreImmagini::NextImage(){
	IconaSuccessiva->show();
	if (IndiceCorrente==Immagini.size()-1) return;
	QParallelAnimationGroup* Animazioni=new QParallelAnimationGroup;
	QPropertyAnimation* AnimCurrent=new QPropertyAnimation(IconaCorrente,"pos",Displayer);
	AnimCurrent->setDuration(DurataAnimazione);
	AnimCurrent->setEasingCurve(QEasingCurve::Linear);
	AnimCurrent->setKeyValueAt(0.0,QPoint(0,0));
	if (Orientamento=Orizzontale) AnimCurrent->setKeyValueAt(1.0,QPoint(-Displayer->width()-10,0));
	else AnimCurrent->setKeyValueAt(1.0,QPoint(0,-Displayer->height()-10));
	Animazioni->addAnimation(AnimCurrent);
	QPropertyAnimation* AnimNext=new QPropertyAnimation(IconaSuccessiva,"pos",Displayer);
	AnimNext->setDuration(DurataAnimazione);
	AnimNext->setEasingCurve(QEasingCurve::Linear);
	AnimNext->setKeyValueAt(1.0,QPoint(0,0));
	if (Orientamento=Orizzontale) AnimNext->setKeyValueAt(0.0,QPoint(Displayer->width()+10,0));
	else AnimNext->setKeyValueAt(0.0,QPoint(0,Displayer->height()+10));
	Animazioni->addAnimation(AnimNext);
	connect(Animazioni,SIGNAL(finished()),this,SLOT(Successiva()));
	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
}
void SelettoreImmagini::Successiva(){
	IconaCorrente->raise();
	IconaCorrente->move(0,0);
	IconaCorrente->setPixmap(Immagini.at(++IndiceCorrente));
	if (IndiceCorrente==Immagini.size()-1) IconaSuccessiva->setPixmap(VoidImage);
	else IconaSuccessiva->setPixmap(Immagini.at(IndiceCorrente+1));
	IconaSuccessiva->hide();
}