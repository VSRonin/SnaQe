#include "snake.h"
#include "StyleSheet.h"

Snake::Snake(QWidget *parent)
: QWidget(parent)
,punti(0)
,difficolta(3)
,WhatToDo(Boh)
,ImmagineTesta(":/Snake/Head.png")
,ImmagineCoda(":/Snake/Tail.png")
,ImmagineCorpo(":/Snake/Body.png")
,ImmagineTopo(":/Snake/Mouse.png")
,Giocando(false)
,Salvataggio("Save.snk")
,Records("TopScores.snk")
{
	qsrand(QTime::currentTime().msec());
	installEventFilter(this);

	Sfondo=new QFrame(this);
	Sfondo->setObjectName("Sfondo");
	Sfondo->setMinimumSize(400,400);

	DifficoltaSpin=new QSpinBox(this);
	DifficoltaSpin->setRange(1,9);
	DifficoltaSpin->setObjectName("DifficoltaSpin");
	DifficoltaSpin->setValue(difficolta);
	DifficoltaSlide=new QSlider(Qt::Horizontal,this);
	DifficoltaSlide->setRange(1,9);
	DifficoltaSlide->setObjectName("DifficoltaSlide");
	DifficoltaSlide->setValue(difficolta);
	connect(DifficoltaSlide,SIGNAL(valueChanged(int)),this,SLOT(ImpostaDifficolta(int)));
	connect(DifficoltaSpin,SIGNAL(valueChanged(int)),this,SLOT(ImpostaDifficolta(int)));
	connect(DifficoltaSlide,SIGNAL(valueChanged(int)),DifficoltaSpin, SLOT(setValue(int)));
	connect(DifficoltaSpin,SIGNAL(valueChanged(int)),DifficoltaSlide, SLOT(setValue(int)));
	DifficoltaSlide->hide();
	DifficoltaSpin->hide();
	DifficoltaSlide->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	DifficoltaSpin->setMinimumSize(AltezzaPulsante,AltezzaPulsante);
	OpzioniLabel=new QLabel(this);
	OpzioniLabel->setObjectName("OpzioniLabel");
	OpzioniLabel->setText(tr("Opzioni"));
	OpzioniLabel->setScaledContents(true);
	OpzioniLabel->hide();
	DifficoltaLabel=new QLabel(this);
	DifficoltaLabel->setObjectName("DifficoltaLabel");
	DifficoltaLabel->setText(tr("Difficoltà"));
	DifficoltaLabel->setScaledContents(true);
	DifficoltaLabel->hide();
	ChiudiOpzioni=new QPushButton(this);
	ChiudiOpzioni->setObjectName("ChiudiOpzioni");
	ChiudiOpzioni->setText(tr("Indietro"));
	ChiudiOpzioni->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	connect(ChiudiOpzioni,SIGNAL(clicked()),this,SLOT(NascondiOpzioni()));
	ChiudiOpzioni->hide();


	TopScores=new QLabel(this);
	TopScores->setObjectName("TopScores");
	TopScores->setScaledContents(true);


	Punteggio=new QLabel(this);
	Punteggio->setObjectName("Punteggio");
	Punteggio->setText("<b>"+tr("Punteggio")+QString(": 0</b>"));
	Punteggio->hide();
	Punteggio->setScaledContents(true);

	Mela=new QLabel(this);
	Mela->setObjectName("Mela");
	Mela->setScaledContents(true);
	Mela->setPixmap(QPixmap(":/Snake/Mela.png"));
	Mela->hide();
	Topo=new QLabel(this);
	Topo->setObjectName("Topo");
	Topo->setScaledContents(true);
	Topo->setPixmap(ImmagineTopo);
	Topo->hide();
	AusiliariaSerpente=new QLabel(this);
	AusiliariaSerpente->setObjectName("AusiliariaSerpente");
	AusiliariaSerpente->setScaledContents(true);
	AusiliariaSerpente->hide();
	AusiliariaTopo=new QLabel(this);
	AusiliariaTopo->setObjectName("AusiliariaTopo");
	AusiliariaTopo->setScaledContents(true);
	AusiliariaTopo->hide();

	NuovoGioco=new QPushButton(this);
	NuovoGioco->setObjectName("NuovoGioco");
	NuovoGioco->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	NuovoGioco->setText(tr("Nuova Partita"));
	connect(NuovoGioco,SIGNAL(clicked()),this,SLOT(NascondiMenu()));
	connect(NuovoGioco,SIGNAL(clicked()),this,SLOT(SetNuova()));
	CaricaGioco=new QPushButton(this);
	CaricaGioco->setObjectName("CaricaGioco");
	CaricaGioco->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	CaricaGioco->setText(tr("Carica Partita"));
	CaricaGioco->setDefault(true);
	connect(CaricaGioco,SIGNAL(clicked()),this,SLOT(NascondiMenu()));
	connect(CaricaGioco,SIGNAL(clicked()),this,SLOT(SetCarica()));
	Opzioni=new QPushButton(this);
	Opzioni->setObjectName("Opzioni");
	Opzioni->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	Opzioni->setText(tr("Opzioni"));
	connect(Opzioni,SIGNAL(clicked()),this,SLOT(NascondiMenu()));
	connect(Opzioni,SIGNAL(clicked()),this,SLOT(SetOpzioni()));
	Esci=new QPushButton(this);
	Esci->setObjectName("Esci");
	Esci->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	Esci->setText(tr("Esci"));
	connect(Esci,SIGNAL(clicked()),this,SLOT(close()));
	CaricaGioco->setEnabled(Salvataggio.size()>0);

	Conferma=new QPushButton(this);
	Conferma->setObjectName("Conferma");
	Conferma->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	Conferma->setGeometry((width()-Conferma->width()/2),3*height()/4,LargezzaPulsante,AltezzaPulsante);
	Conferma->setText(tr("Ok"));
	Conferma->hide();
	connect(Conferma,SIGNAL(clicked()),this,SLOT(MostraMenu()));


	
	TestaSerpente=new QLabel(this);
	TestaSerpente->setObjectName("TestaSerpente");
	TestaSerpente->setScaledContents(true);
	TestaSerpente->setPixmap(ImmagineTesta);
	TestaSerpente->hide();
	CoordinateSerpente.append(CoordinateCorpo(0,0));

	CodaSerpente=new QLabel(this);
	CodaSerpente->setObjectName("CodaSerpente");
	CodaSerpente->setScaledContents(true);
	CodaSerpente->setPixmap(ImmagineCoda);
	CodaSerpente->hide();
	CoordinateSerpente.append(CoordinateCorpo(0,0));

	QHBoxLayout* LayoutSfondo=new QHBoxLayout(this);
	LayoutSfondo->setMargin(0);
	LayoutSfondo->setSpacing(0);
	LayoutSfondo->addWidget(Sfondo);

	CorpoSerpente.clear();

	setStyleSheet(CSS::Principale);
}
void Snake::MostraMenu(){
	CaricaGioco->setEnabled(Salvataggio.size()>0);
	int temp=(height()-(AltezzaPulsante*4)-(DistanzaPulsanti*3))/2;
	NuovoGioco->show();
	CaricaGioco->show();
	CaricaGioco->setText(tr("Carica Partita"));
	Opzioni->show();
	Esci->show();
	Mela->hide();
	Topo->hide();
	AusiliariaSerpente->hide();
	AusiliariaTopo->hide();
	EliminaCorpo();
	TestaSerpente->hide();
	CodaSerpente->hide();
	Punteggio->hide();
	Conferma->hide();
	QPropertyAnimation* animNuovoGioco= new QPropertyAnimation(NuovoGioco,"pos",this);
	animNuovoGioco->setDuration(DurataAnimazioni);
	animNuovoGioco->setEasingCurve(QEasingCurve::OutBack);
	animNuovoGioco->setKeyValueAt(0.0,QPoint(NuovoGioco->pos().x(),temp-width()-40));
	animNuovoGioco->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp));

	QPropertyAnimation* animCaricaGioco= new QPropertyAnimation(CaricaGioco,"pos",this);
	animCaricaGioco->setDuration(DurataAnimazioni);
	animCaricaGioco->setEasingCurve(QEasingCurve::OutBack);
	animCaricaGioco->setKeyValueAt(0.0,QPoint(CaricaGioco->pos().x(),temp+AltezzaPulsante+DistanzaPulsanti-width()-40));
	animCaricaGioco->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp+AltezzaPulsante+DistanzaPulsanti));

	QPropertyAnimation* animOpzioni= new QPropertyAnimation(Opzioni,"pos",this);
	animOpzioni->setDuration(DurataAnimazioni);
	animOpzioni->setEasingCurve(QEasingCurve::OutBack);
	animOpzioni->setKeyValueAt(0.0,QPoint(Opzioni->pos().x(),temp+2*AltezzaPulsante+2*DistanzaPulsanti-width()-40));
	animOpzioni->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp+2*AltezzaPulsante+2*DistanzaPulsanti));


	QPropertyAnimation* animEsci= new QPropertyAnimation(Esci,"pos",this);
	animEsci->setDuration(DurataAnimazioni);
	animEsci->setEasingCurve(QEasingCurve::OutBack);
	animEsci->setKeyValueAt(0.0,QPoint(Esci->pos().x(),temp+3*AltezzaPulsante+3*DistanzaPulsanti-width()-40));
	animEsci->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp+3*AltezzaPulsante+3*DistanzaPulsanti));


	QParallelAnimationGroup *Animazioni=new QParallelAnimationGroup;
	Animazioni->addAnimation(animNuovoGioco);
	Animazioni->addAnimation(animCaricaGioco);
	Animazioni->addAnimation(animOpzioni);
	Animazioni->addAnimation(animEsci);

	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
	this->setFocus();
}

void Snake::NascondiMenu(){
	QPropertyAnimation* animNuovoGioco= new QPropertyAnimation(NuovoGioco,"pos",this);
	animNuovoGioco->setDuration(DurataAnimazioni);
	animNuovoGioco->setEasingCurve(QEasingCurve::InBack);
	animNuovoGioco->setKeyValueAt(1.0,QPoint(NuovoGioco->pos().x(),NuovoGioco->pos().y()-width()-40));
	animNuovoGioco->setKeyValueAt(0.0,NuovoGioco->pos());

	QPropertyAnimation* animCaricaGioco= new QPropertyAnimation(CaricaGioco,"pos",this);
	animCaricaGioco->setDuration(DurataAnimazioni);
	animCaricaGioco->setEasingCurve(QEasingCurve::InBack);
	animCaricaGioco->setKeyValueAt(1.0,QPoint(CaricaGioco->pos().x(),CaricaGioco->pos().y()-width()-40));
	animCaricaGioco->setKeyValueAt(0.0,CaricaGioco->pos());

	QPropertyAnimation* animOpzioni= new QPropertyAnimation(Opzioni,"pos",this);
	animOpzioni->setDuration(DurataAnimazioni);
	animOpzioni->setEasingCurve(QEasingCurve::InBack);
	animOpzioni->setKeyValueAt(1.0,QPoint(Opzioni->pos().x(),Opzioni->pos().y()-width()-40));
	animOpzioni->setKeyValueAt(0.0,Opzioni->pos());

	QPropertyAnimation* animEsci= new QPropertyAnimation(Esci,"pos",this);
	animEsci->setDuration(DurataAnimazioni);
	animEsci->setEasingCurve(QEasingCurve::InBack);
	animEsci->setKeyValueAt(1.0,QPoint(Esci->pos().x(),Esci->pos().y()-width()-40));
	animEsci->setKeyValueAt(0.0,Esci->pos());


	QParallelAnimationGroup *Animazioni=new QParallelAnimationGroup;
	Animazioni->addAnimation(animNuovoGioco);
	Animazioni->addAnimation(animCaricaGioco);
	Animazioni->addAnimation(animOpzioni);
	Animazioni->addAnimation(animEsci);
	connect(Animazioni,SIGNAL(finished()),this,SLOT(HideMenuItems()));
	connect(Animazioni,SIGNAL(finished()),this,SLOT(EseguiAzione()));


	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
}
void Snake::HideMenuItems(){
	NuovoGioco->hide();
	CaricaGioco->hide();
	Opzioni->hide();
	Esci->hide();
}
void Snake::MostraOpzioni(){
	ChiudiOpzioni->show();
	OpzioniLabel->show();
	DifficoltaSlide->show();
	DifficoltaSpin->show();
	TopScores->show();
	DifficoltaLabel->show();
	ChiudiOpzioni->raise();
	OpzioniLabel->raise();
	DifficoltaSlide->raise();
	DifficoltaSpin->raise();
	TopScores->raise();
	DifficoltaLabel->raise();
	quint16 punteggi[3];
	if (Records.size()==0) {punteggi[0]=punteggi[1]=punteggi[2]=0;}
	else{
		Records.open(QIODevice::ReadOnly);
		QDataStream dati(&Records);
		dati.setVersion(QDataStream::Qt_4_7);
		dati >> *punteggi;
		if (*punteggi!=NumeroMagico) {punteggi[0]=punteggi[1]=punteggi[2]=0;}
		else{
			dati >> punteggi[0];
			dati >> punteggi[1];
			dati >> punteggi[2];
		}
		Records.close();
	}
	TopScores->setText("<b>"+tr("Punteggi Migliori:")+QString("</b><br>1) %1<br>2) %2<br>3) %3").arg(punteggi[0]).arg(punteggi[1]).arg(punteggi[2]));
	TopScores->resize(TopScores->sizeHint());
	QParallelAnimationGroup *Animazioni=new QParallelAnimationGroup;
	QPropertyAnimation* temp=new QPropertyAnimation(TopScores,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::OutBack);
	temp->setKeyValueAt(0.0,QPoint((width()-TopScores->width())/2,-40));
	temp->setKeyValueAt(1.0,QPoint((width()-TopScores->width())/2,height()/2+10));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(DifficoltaSpin,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::OutBack);
	temp->setKeyValueAt(0.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,-40));
	temp->setKeyValueAt(1.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,height()/4+10));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(DifficoltaSlide,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::OutBack);
	temp->setKeyValueAt(0.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2+15+DifficoltaSpin->width(),-40));
	temp->setKeyValueAt(1.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2+15+DifficoltaSpin->width(),height()/4+10));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(DifficoltaLabel,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::OutBack);
	temp->setKeyValueAt(0.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,-40));
	temp->setKeyValueAt(1.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,height()/4-DifficoltaLabel->height()));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(OpzioniLabel,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::OutBack);
	temp->setKeyValueAt(0.0,QPoint((width()-OpzioniLabel->width())/2,-40));
	temp->setKeyValueAt(1.0,QPoint((width()-OpzioniLabel->width())/2,15));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(ChiudiOpzioni,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::OutBack);
	temp->setKeyValueAt(0.0,QPoint((width()-ChiudiOpzioni->width())/2,-40));
	temp->setKeyValueAt(1.0,QPoint((width()-ChiudiOpzioni->width())/2,3*height()/4));
	Animazioni->addAnimation(temp);
	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
}
void Snake::NascondiOpzioni(){
	QParallelAnimationGroup *Animazioni=new QParallelAnimationGroup;
	QPropertyAnimation* temp=new QPropertyAnimation(TopScores,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::InBack);
	temp->setKeyValueAt(1.0,QPoint((width()-TopScores->width())/2,-40));
	temp->setKeyValueAt(0.0,QPoint((width()-TopScores->width())/2,height()/2+10));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(DifficoltaSpin,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::InBack);
	temp->setKeyValueAt(1.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,-40));
	temp->setKeyValueAt(0.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,height()/4+10));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(DifficoltaSlide,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::InBack);
	temp->setKeyValueAt(1.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2+15+DifficoltaSpin->width(),-40));
	temp->setKeyValueAt(0.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2+15+DifficoltaSpin->width(),height()/4+10));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(DifficoltaLabel,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::InBack);
	temp->setKeyValueAt(1.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,-40));
	temp->setKeyValueAt(0.0,QPoint((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,height()/4-DifficoltaLabel->height()));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(OpzioniLabel,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::InBack);
	temp->setKeyValueAt(1.0,QPoint((width()-OpzioniLabel->width())/2,-40));
	temp->setKeyValueAt(0.0,QPoint((width()-OpzioniLabel->width())/2,15));
	Animazioni->addAnimation(temp);
	temp=NULL;
	temp=new QPropertyAnimation(ChiudiOpzioni,"pos",this);
	temp->setDuration(DurataAnimazioni);
	temp->setEasingCurve(QEasingCurve::InBack);
	temp->setKeyValueAt(1.0,QPoint((width()-ChiudiOpzioni->width())/2,-40));
	temp->setKeyValueAt(0.0,QPoint((width()-ChiudiOpzioni->width())/2,3*height()/4));
	Animazioni->addAnimation(temp);
	connect(Animazioni,SIGNAL(finished()),this,SLOT(HideOpzioni()));
	if (!Punteggio->isVisible()) connect(Animazioni,SIGNAL(finished()),this,SLOT(MostraMenu()));
	else{
		Giocando=true;
		Mela->setEnabled(true);
		Topo->setEnabled(true);
		for(QList<QLabel*>::iterator i=CorpoSerpente.begin();i!=CorpoSerpente.end();i++) (*i)->setEnabled(true);
		TestaSerpente->setEnabled(true);
		CodaSerpente->setEnabled(true);
		Punteggio->setEnabled(true);
		AusiliariaSerpente->setEnabled(true);
		AusiliariaTopo->setEnabled(true);
		connect(Animazioni,SIGNAL(finished()),this,SLOT(Partita()));
	}
	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
}
void Snake::HideOpzioni(){
	ChiudiOpzioni->hide();
	OpzioniLabel->hide();
	DifficoltaSlide->hide();
	DifficoltaSpin->hide();
	TopScores->hide();
	DifficoltaLabel->hide();
}
void Snake::NuovaPartita(){
	Salvataggio.resize(0);
	CoordinateSerpente.clear();
	EliminaCorpo();
	punti=0;
	AggiornaPunti();
	for (int j=12;j>7;j--){
		CoordinateSerpente.append(CoordinateCorpo(j,10,CoordinateCorpo::Est));
		if (j!=12 && j!=8){
			CorpoSerpente.append(new QLabel(this));
			CorpoSerpente.last()->setScaledContents(true);
			CorpoSerpente.last()->show();
		}
	}
	QTransform Rotazione;
	for (int i=0;i<CoordinateSerpente.size();i++){
		Rotazione.reset();
		Rotazione.rotate(90*CoordinateSerpente.at(i).GetDirezione());
		if (i==0){
			TestaSerpente->setPixmap(ImmagineTesta.transformed(Rotazione));
			TestaSerpente->setGeometry(CoordinateSerpente.at(i).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(i).GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
		}
		else if(i==CoordinateSerpente.size()-1){
			CodaSerpente->setPixmap(ImmagineCoda.transformed(Rotazione));
			CodaSerpente->setGeometry(CoordinateSerpente.at(i).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(i).GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
		}
		else{
			CorpoSerpente.at(i-1)->setPixmap(ImmagineCorpo.transformed(Rotazione));
			CorpoSerpente.at(i-1)->setGeometry(CoordinateSerpente.at(i).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(i).GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
		}
	}
	TestaSerpente->show();
	CodaSerpente->show();
	ProssimaDirezione=Destra;

	do{
		CoordinateMela.SetX(qrand()%NumeroCaselle);
		CoordinateMela.SetY(qrand()%NumeroCaselle);
	}while(CoordinateMela.GetY()==10 && CoordinateMela.GetX()<13 && CoordinateMela.GetX()>7);
	Mela->setGeometry(CoordinateMela.GetX()*width()/NumeroCaselle,CoordinateMela.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
	do{
		CoordinateTopo.SetX(qrand()%NumeroCaselle);
		CoordinateTopo.SetY(qrand()%NumeroCaselle);
	}while((CoordinateTopo.GetY()==10 && CoordinateTopo.GetX()<13 && CoordinateTopo.GetX()>7) || CoordinateTopo==CoordinateMela);
	Topo->setGeometry(CoordinateTopo.GetX()*width()/NumeroCaselle,CoordinateTopo.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);

	Mela->show();
	Topo->show();
	Punteggio->show();
	Giocando=true;
	Partita();

}
void Snake::AggiornaPunti(){
	Punteggio->setText("<b>"+tr("Punteggio")+QString(": %1").arg(punti)+"</b>");
}
void Snake::CaricaPartita(){
	CoordinateSerpente.clear();
	EliminaCorpo();
	Salvataggio.open(QIODevice::ReadOnly);
	QDataStream in(&Salvataggio);
	in.setVersion(QDataStream::Qt_4_7);
	qint16 temp,num;
	in >> temp;
	if (temp!=NumeroMagico){
		QMessageBox::critical(this, tr("Impossibile caricare la partita"),tr("Il file di salvataggio potrebbe essere danneggiato o illeggibile"));
		MostraMenu();
		return;
	}
	in >> temp;
	punti=temp;
	in >> temp;
	CoordinateMela.SetX(temp);
	in >> temp;
	CoordinateMela.SetY(temp);
	in >> temp;
	CoordinateTopo.SetY(temp);
	in >> temp;
	CoordinateTopo.SetY(temp);
	in >> temp;
	CoordinateTopo.SetDirezione(temp);
	in >> num;
	for (int i=0;i<num;i++){
		CoordinateSerpente.append(CoordinateCorpo());
		in >> temp;
		CoordinateSerpente.last().SetX(temp);
		in >> temp;
		CoordinateSerpente.last().SetY(temp);
		in >> temp;
		CoordinateSerpente.last().SetDirezione(temp);
		if(i!=0 && i!=num-1){
			CorpoSerpente.append(new QLabel(this));
			CorpoSerpente.last()->setScaledContents(true);
			CorpoSerpente.last()->show();
		}
	}
	Salvataggio.close();
	QTransform Rotazione;
	for (int i=0;i<CoordinateSerpente.size();i++){
		Rotazione.reset();
		Rotazione.rotate(90*CoordinateSerpente.at(i).GetDirezione());
		if (i==0){
			TestaSerpente->setPixmap(ImmagineTesta.transformed(Rotazione));
			TestaSerpente->setGeometry(CoordinateSerpente.at(i).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(i).GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
		}
		else if(i==CoordinateSerpente.size()-1){
			CodaSerpente->setPixmap(ImmagineCoda.transformed(Rotazione));
			CodaSerpente->setGeometry(CoordinateSerpente.at(i).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(i).GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
		}
		else{
			CorpoSerpente.at(i-1)->setPixmap(ImmagineCorpo.transformed(Rotazione));
			CorpoSerpente.at(i-1)->setGeometry(CoordinateSerpente.at(i).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(i).GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
		}
	}
	TestaSerpente->show();
	CodaSerpente->show();
	ProssimaDirezione=CoordinateSerpente.first().GetDirezione();
	Mela->setGeometry(CoordinateMela.GetX()*width()/NumeroCaselle,CoordinateMela.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
	Topo->setGeometry(CoordinateTopo.GetX()*width()/NumeroCaselle,CoordinateTopo.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);

	Mela->show();
	Topo->show();
	Punteggio->show();
	AggiornaPunti();
	Giocando=true;
	QTimer::singleShot(1000,this,SLOT(Partita()));
}
void Snake::resizeEvent(QResizeEvent *event){
	
	int temp=(height()-(AltezzaPulsante*4)-(DistanzaPulsanti*3))/2;
	if(Giocando)
		Punteggio->setGeometry(width()-Punteggio->sizeHint().width()-60,10,Punteggio->sizeHint().width()+50,Punteggio->sizeHint().height());
	else
		Punteggio->setGeometry((width()-Punteggio->width())/2,(height()-Punteggio->height())/2,Punteggio->sizeHint().width(),Punteggio->sizeHint().height());
	NuovoGioco->setGeometry((width()-LargezzaPulsante)/2,temp,LargezzaPulsante,AltezzaPulsante);
	CaricaGioco->setGeometry((width()-LargezzaPulsante)/2,temp+AltezzaPulsante+DistanzaPulsanti,LargezzaPulsante,AltezzaPulsante);
	Opzioni->setGeometry((width()-LargezzaPulsante)/2,temp+2*AltezzaPulsante+2*DistanzaPulsanti,LargezzaPulsante,AltezzaPulsante);
	Esci->setGeometry((width()-LargezzaPulsante)/2,temp+3*AltezzaPulsante+3*DistanzaPulsanti,LargezzaPulsante,AltezzaPulsante);
	Mela->setGeometry(CoordinateMela.GetX()*width()/NumeroCaselle,CoordinateMela.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
	Topo->setGeometry(CoordinateTopo.GetX()*width()/NumeroCaselle,CoordinateTopo.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
	TestaSerpente->setGeometry(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
	CodaSerpente->setGeometry(CoordinateSerpente.last().GetX()*width()/NumeroCaselle,CoordinateSerpente.last().GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
	AusiliariaSerpente->resize(width()/NumeroCaselle,height()/NumeroCaselle);
	AusiliariaTopo->resize(width()/NumeroCaselle,height()/NumeroCaselle);
	for (int i=0;i<CorpoSerpente.size();i++)
		CorpoSerpente.at(i)->setGeometry(CoordinateSerpente.at(i+1).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(i+1).GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
	TopScores->resize(width()*TopScores->sizeHint().width()/400,height()*TopScores->sizeHint().height()/400);
	TopScores->move((width()-TopScores->width())/2,height()/2+10);
	DifficoltaSpin->resize(width()*DifficoltaSpin->sizeHint().width()/400,height()*DifficoltaSpin->sizeHint().height()/400);
	DifficoltaSlide->resize(width()*DifficoltaSlide->sizeHint().width()/400,height()*DifficoltaSlide->sizeHint().height()/400);
	DifficoltaSpin->move((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,height()/4+10);
	DifficoltaSlide->move((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2+15+DifficoltaSpin->width(),height()/4+10);
	DifficoltaLabel->resize(width()*DifficoltaLabel->sizeHint().width()/400,height()*DifficoltaLabel->sizeHint().height()/400);
	DifficoltaLabel->move((width()-DifficoltaSpin->width()-DifficoltaSlide->width()-15)/2,height()/4-DifficoltaLabel->height());
	OpzioniLabel->resize(width()*OpzioniLabel->sizeHint().width()/400,height()*OpzioniLabel->sizeHint().height()/400);
	OpzioniLabel->move((width()-OpzioniLabel->width())/2,15);
	ChiudiOpzioni->resize(width()*ChiudiOpzioni->sizeHint().width()/400,height()*ChiudiOpzioni->sizeHint().height()/400);
	ChiudiOpzioni->move((width()-ChiudiOpzioni->width())/2,3*height()/4);
	Conferma->setGeometry((width()-Conferma->width())/2,3*height()/4,LargezzaPulsante,AltezzaPulsante);
}
void Snake::EseguiAzione(){
	switch(WhatToDo){
		case IniziaNuova:
			NuovaPartita(); break;
		case IniziaCaricata:
			if (TestaSerpente->isVisible()) NascondiPausa();
			else CaricaPartita();
			break;
		case Settings:
			MostraOpzioni();
			break;
		default:
			MostraMenu();
			break;
	}
}
void Snake::EliminaCorpo(){
	if (CorpoSerpente.isEmpty()) return;
	for (QList<QLabel*>::iterator i=CorpoSerpente.begin();i!=CorpoSerpente.end();i++)
		(*i)->deleteLater();
	CorpoSerpente.clear();
}

void Snake::Partita(){
	if (!Giocando) return;
	Punteggio->setGeometry(width()-Punteggio->sizeHint().width()-60,10,Punteggio->sizeHint().width()+50,Punteggio->sizeHint().height());
	this->setFocus();
	Punteggio->raise();
	QTransform Rotazione;
	bool mangiato=false;
	QParallelAnimationGroup *Animazioni=new QParallelAnimationGroup;
	connect(Animazioni,SIGNAL(finished()),this,SLOT(Partita()));
	//Controllo i conflitti

	
	
	
	if(
		CoordinateSerpente.first()==CoordinateMela
		|| (CoordinateSerpente.first().GetX()==CoordinateMela.GetX() && CoordinateMela.GetY()==0 && CoordinateSerpente.first().GetY()>=NumeroCaselle)
		|| (CoordinateSerpente.first().GetX()==CoordinateMela.GetX() && CoordinateMela.GetY()==NumeroCaselle-1 && CoordinateSerpente.first().GetY()<0)
		|| (CoordinateSerpente.first().GetY()==CoordinateMela.GetY() && CoordinateMela.GetX()==0 && CoordinateSerpente.first().GetX()>=NumeroCaselle)
		|| (CoordinateSerpente.first().GetY()==CoordinateMela.GetY() && CoordinateMela.GetX()==NumeroCaselle-1 && CoordinateSerpente.first().GetX()<0)

		|| CoordinateTopo==CoordinateMela
		|| (CoordinateTopo.GetX()==CoordinateMela.GetX() && CoordinateMela.GetY()==0 && CoordinateTopo.GetY()>=NumeroCaselle)
		|| (CoordinateTopo.GetX()==CoordinateMela.GetX() && CoordinateMela.GetY()==NumeroCaselle-1 && CoordinateSerpente.first().GetY()<0)
		|| (CoordinateTopo.GetY()==CoordinateMela.GetY() && CoordinateMela.GetX()==0 && CoordinateTopo.GetX()>=NumeroCaselle)
		|| (CoordinateTopo.GetY()==CoordinateMela.GetY() && CoordinateMela.GetX()==NumeroCaselle-1 && CoordinateTopo.GetX()<0)
	){ //la mela è stata mangiata
		if (
			CoordinateSerpente.first()==CoordinateMela
			|| (CoordinateSerpente.first().GetX()==CoordinateMela.GetX() && CoordinateMela.GetY()==0 && CoordinateSerpente.first().GetY()>=NumeroCaselle)
			|| (CoordinateSerpente.first().GetX()==CoordinateMela.GetX() && CoordinateMela.GetY()==NumeroCaselle-1 && CoordinateSerpente.first().GetY()<0)
			|| (CoordinateSerpente.first().GetY()==CoordinateMela.GetY() && CoordinateMela.GetX()==0 && CoordinateSerpente.first().GetX()>=NumeroCaselle)
			|| (CoordinateSerpente.first().GetY()==CoordinateMela.GetY() && CoordinateMela.GetX()==NumeroCaselle-1 && CoordinateSerpente.first().GetX()<0)
		) {punti+=difficolta; mangiato=true;} //l'ha mangiata il serpente
		else punti-=5*difficolta;  //l'ha mangiata il topo
		AggiornaPunti();
		bool buono;
		do{
			buono=true;
			CoordinateMela.SetX(qrand()%NumeroCaselle);
			CoordinateMela.SetY(qrand()%NumeroCaselle);
			if(CoordinateMela==CoordinateTopo) buono=false;
			for (QList<CoordinateCorpo>::iterator i=CoordinateSerpente.begin();i!=CoordinateSerpente.end() && buono;i++){
				if(CoordinateMela==*i) buono=false;
			}
		}while(!buono);
		Mela->setGeometry(CoordinateMela.GetX()*width()/NumeroCaselle,CoordinateMela.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);	
	}
	if(
		CoordinateSerpente.first()==CoordinateTopo
		|| (CoordinateSerpente.first().GetX()==CoordinateTopo.GetX() && CoordinateTopo.GetY()==0 && CoordinateSerpente.first().GetY()>=NumeroCaselle)
		|| (CoordinateSerpente.first().GetX()==CoordinateTopo.GetX() && CoordinateTopo.GetY()==NumeroCaselle-1 && CoordinateSerpente.first().GetY()<0)
		|| (CoordinateSerpente.first().GetY()==CoordinateTopo.GetY() && CoordinateTopo.GetX()==0 && CoordinateSerpente.first().GetX()>=NumeroCaselle)
		|| (CoordinateSerpente.first().GetY()==CoordinateTopo.GetY() && CoordinateTopo.GetX()==NumeroCaselle-1 && CoordinateSerpente.first().GetX()<0)
	){ //Ho mangiato il topo
		punti+=10*difficolta;
		AggiornaPunti();
		mangiato=true;
		bool buono;
		do{
			buono=true;
			CoordinateTopo.SetX(qrand()%NumeroCaselle);
			CoordinateTopo.SetY(qrand()%NumeroCaselle);
			if(CoordinateMela==CoordinateTopo) buono=false;
			for (QList<CoordinateCorpo>::iterator i=CoordinateSerpente.begin();i!=CoordinateSerpente.end() && buono;i++){
				if(CoordinateTopo==*i) buono=false;
			}
		}while(!buono);
		Topo->setGeometry(CoordinateTopo.GetX()*width()/NumeroCaselle,CoordinateTopo.GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);	
	}

	bool vivo=true;
	for (QList<CoordinateCorpo>::iterator i=CoordinateSerpente.begin()+1;i!=CoordinateSerpente.end() && vivo;i++){
		if(CoordinateSerpente.first()==*i)
			vivo=false;
	}
	Salvataggio.resize(0);
	if (!vivo){
		qint16 temp[3];
		bool salta=false,fine=false;
		Records.open(QIODevice::ReadOnly);
		QDataStream dati(&Records);
		dati.setVersion(QDataStream::Qt_4_7);
		if (Records.size()==0) salta=true;
		if (!salta){
			dati >> *temp;
			if (*temp!=NumeroMagico) salta=true;
		}
		if (!salta){
			dati >> *temp;
			dati >> temp[1];
			dati >> temp[2];
			if (*temp<punti){temp[2]=temp[1]; temp[1]=*temp; *temp=punti;}
			else if (temp[1]<punti) {temp[2]=temp[1]; temp[1]=punti;}
			else if (temp[2]<punti) {temp[2]=punti;}
			else fine=true;
		}
		if (salta){
			*temp=punti;
			temp[1]=0;
			temp[2]=0;
		}
		Records.close();
		if (!fine){
			Records.resize(0);
			Records.open(QIODevice::WriteOnly);
			QDataStream Output(&Records);
			Output.setVersion(QDataStream::Qt_4_7);
			Output << qint16(NumeroMagico) << *temp << temp[1] << temp[2];
			Records.close();
		}


		Conferma->show();
		Conferma->raise();
		//disconnect(Animazioni,SIGNAL(finished()),this,SLOT(Partita()));
		Giocando=false;
		Punteggio->setText("<b>"+tr("Partita Terminata</b><br><b>Punteggio")+QString(": %1").arg(punti)+"</b>");
		Punteggio->resize(Punteggio->sizeHint());
		QPropertyAnimation* animPunteggio= new QPropertyAnimation(Punteggio,"pos",this);
		animPunteggio->setDuration(DurataAnimazioni);
		animPunteggio->setEasingCurve(QEasingCurve::Linear);
		animPunteggio->setKeyValueAt(0.0,Punteggio->pos());
		animPunteggio->setKeyValueAt(1.0,QPoint((width()-Punteggio->width())/2,(height()-Punteggio->height())/2));
		Animazioni->addAnimation(animPunteggio);
		animPunteggio=NULL;
		animPunteggio= new QPropertyAnimation(Conferma,"pos",this);
		animPunteggio->setDuration(DurataAnimazioni);
		animPunteggio->setEasingCurve(QEasingCurve::Linear);
		animPunteggio->setKeyValueAt(0.0,QPoint((width()-LargezzaPulsante)/2,height()+40));
		animPunteggio->setKeyValueAt(1.0,QPoint((width()-Conferma->width())/2,3*height()/4));
		Animazioni->addAnimation(animPunteggio);
		Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
		return;

	}
	
	AusiliariaSerpente->hide();
	AusiliariaTopo->hide();

	//Salvo la Partita
	Salvataggio.open(QIODevice::WriteOnly);
	QDataStream dati(&Salvataggio);
	dati.setVersion(QDataStream::Qt_4_7);
	dati << qint16(NumeroMagico)
		<< qint16(punti)
		<< qint16(CoordinateMela.GetX())
		<< qint16(CoordinateMela.GetY())
		<< qint16(CoordinateTopo.GetX())
		<< qint16(CoordinateTopo.GetY())
		<< qint16(CoordinateTopo.GetDirezione())
		<< qint16(CoordinateSerpente.size());
	for (QList<CoordinateCorpo>::iterator i=CoordinateSerpente.begin();i!=CoordinateSerpente.end();i++){
		dati << qint16(i->GetX())
			<< qint16(i->GetY())
			<< qint16(i->GetDirezione());
	}
	Salvataggio.close();


	QPropertyAnimation* animTesta= new QPropertyAnimation(TestaSerpente,"pos",this);
	animTesta->setDuration(VelocitaGioco/difficolta);
	animTesta->setEasingCurve(QEasingCurve::Linear);
	//animTesta->setKeyValueAt(0.0,TestaSerpente->pos());
	if(CoordinateSerpente.first().IsInside(QRect(0,0,NumeroCaselle,NumeroCaselle)))
		animTesta->setKeyValueAt(0.0,QPoint(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle));
	else{
		QPoint Partenza(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle);
		if (CoordinateSerpente.first().GetX()<0) Partenza.setX((NumeroCaselle-1)*width()/NumeroCaselle);
		if (CoordinateSerpente.first().GetX()>=NumeroCaselle) Partenza.setX(0);
		if (CoordinateSerpente.first().GetY()<0) Partenza.setY((NumeroCaselle-1)*height()/NumeroCaselle);
		if (CoordinateSerpente.first().GetY()>=NumeroCaselle) Partenza.setY(0);
		animTesta->setKeyValueAt(0.0,Partenza);
	}

	if (mangiato){
		CorpoSerpente.prepend(new QLabel(this));
		CorpoSerpente.first()->setScaledContents(true);
		CorpoSerpente.first()->show();
		if(CoordinateSerpente.first().IsInside(QRect(0,0,NumeroCaselle,NumeroCaselle)))
			CorpoSerpente.first()->setGeometry(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle,width()/NumeroCaselle,height()/NumeroCaselle);
		else{
			QPoint Partenza(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle);
			if (CoordinateSerpente.first().GetX()<0) Partenza.setX((NumeroCaselle-1)*width()/NumeroCaselle);
			if (CoordinateSerpente.first().GetX()>=NumeroCaselle) Partenza.setX(0);
			if (CoordinateSerpente.first().GetY()<0) Partenza.setY((NumeroCaselle-1)*height()/NumeroCaselle);
			if (CoordinateSerpente.first().GetY()>=NumeroCaselle) Partenza.setY(0);
			CorpoSerpente.first()->setGeometry(Partenza.x(),Partenza.y(),width()/NumeroCaselle,height()/NumeroCaselle);
		}
		QPropertyAnimation* animNuovo= new QPropertyAnimation(CorpoSerpente.first(),"size",this);
		animNuovo->setDuration(VelocitaGioco/difficolta);
		animNuovo->setEasingCurve(QEasingCurve::Linear);
		if (CoordinateSerpente.first().GetX()-CoordinateSerpente.at(1).GetX()==0){
			animNuovo->setKeyValueAt(0.0,QSize(width()/NumeroCaselle,0));
		}
		else {
			animNuovo->setKeyValueAt(0.0,QSize(0,height()/NumeroCaselle));
		}
		animNuovo->setKeyValueAt(1.0,QSize(width()/NumeroCaselle,height()/NumeroCaselle));
		Animazioni->addAnimation(animNuovo);
		CoordinateSerpente.insert(1,CoordinateSerpente.first());
	}
	else{
		QPropertyAnimation* temp;
		for(int j=CorpoSerpente.size();j>0;j--){
			temp=NULL;
			temp=new QPropertyAnimation(CorpoSerpente.at(j-1),"pos",this);
			temp->setDuration(VelocitaGioco/difficolta);
			temp->setEasingCurve(QEasingCurve::Linear);
			if(CoordinateSerpente.at(j).IsInside(QRect(0,0,NumeroCaselle,NumeroCaselle)))
				temp->setKeyValueAt(0.0,QPoint(CoordinateSerpente.at(j).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(j).GetY()*height()/NumeroCaselle));
			else{
				QPoint Partenza(CoordinateSerpente.at(j).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(j).GetY()*height()/NumeroCaselle);
				if (CoordinateSerpente.at(j).GetX()<0) Partenza.setX((NumeroCaselle-1)*width()/NumeroCaselle);
				if (CoordinateSerpente.at(j).GetX()>=NumeroCaselle) Partenza.setX(0);
				if (CoordinateSerpente.at(j).GetY()<0) Partenza.setY((NumeroCaselle-1)*height()/NumeroCaselle);
				if (CoordinateSerpente.at(j).GetY()>=NumeroCaselle) Partenza.setY(0);
				temp->setKeyValueAt(0.0,Partenza);
			}
			temp->setKeyValueAt(1.0,QPoint(CoordinateSerpente.at(j-1).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(j-1).GetY()*height()/NumeroCaselle));
			Animazioni->addAnimation(temp);
			if (!CoordinateSerpente.at(j-1).IsInside(QRect(0,0,NumeroCaselle,NumeroCaselle))){
				Rotazione.reset();
				Rotazione.rotate(90*CoordinateSerpente.at(j-1).GetDirezione());
				AusiliariaSerpente->setPixmap(ImmagineCorpo.transformed(Rotazione));
				AusiliariaSerpente->show();
				QPropertyAnimation* AuxAnim=new QPropertyAnimation(AusiliariaSerpente,"pos",this);
				AuxAnim->setDuration(VelocitaGioco/difficolta);
				AuxAnim->setEasingCurve(QEasingCurve::Linear);
				if (CoordinateSerpente.at(j-1).GetX()<0){
					AuxAnim->setKeyValueAt(0.0,QPoint(width(),CoordinateSerpente.at(j-1).GetY()*height()/NumeroCaselle));
					AuxAnim->setKeyValueAt(1.0,QPoint((NumeroCaselle-1)*width()/NumeroCaselle,CoordinateSerpente.at(j-1).GetY()*height()/NumeroCaselle));
				}
				else if (CoordinateSerpente.at(j-1).GetX()>=NumeroCaselle){
					AuxAnim->setKeyValueAt(0.0,QPoint(-width()/NumeroCaselle,CoordinateSerpente.at(j-1).GetY()*height()/NumeroCaselle));
					AuxAnim->setKeyValueAt(1.0,QPoint(0,CoordinateSerpente.at(j-1).GetY()*height()/NumeroCaselle));
				}
				else if (CoordinateSerpente.at(j-1).GetY()>=NumeroCaselle){
					AuxAnim->setKeyValueAt(0.0,QPoint(CoordinateSerpente.at(j-1).GetX()*width()/NumeroCaselle,-height()/NumeroCaselle));
					AuxAnim->setKeyValueAt(1.0,QPoint(CoordinateSerpente.at(j-1).GetX()*width()/NumeroCaselle,0));
				}
				else if (CoordinateSerpente.at(j-1).GetY()<0){
					AuxAnim->setKeyValueAt(0.0,QPoint(CoordinateSerpente.at(j-1).GetX()*width()/NumeroCaselle,height()));
					AuxAnim->setKeyValueAt(1.0,QPoint(CoordinateSerpente.at(j-1).GetX()*width()/NumeroCaselle,(NumeroCaselle-1)*height()/NumeroCaselle));
				}
				Animazioni->addAnimation(AuxAnim);
			}
		}
		temp=NULL;
		temp=new QPropertyAnimation(CodaSerpente,"pos",this);
		temp->setDuration(VelocitaGioco/difficolta);
		temp->setEasingCurve(QEasingCurve::Linear);
		if(CoordinateSerpente.last().IsInside(QRect(0,0,NumeroCaselle,NumeroCaselle)))
			temp->setKeyValueAt(0.0,QPoint(CoordinateSerpente.last().GetX()*width()/NumeroCaselle,CoordinateSerpente.last().GetY()*height()/NumeroCaselle));
		else{
			QPoint Partenza(CoordinateSerpente.last().GetX()*width()/NumeroCaselle,CoordinateSerpente.last().GetY()*height()/NumeroCaselle);
			if (CoordinateSerpente.last().GetX()<0) Partenza.setX((NumeroCaselle-1)*width()/NumeroCaselle);
			if (CoordinateSerpente.last().GetX()>=NumeroCaselle) Partenza.setX(0);
			if (CoordinateSerpente.last().GetY()<0) Partenza.setY((NumeroCaselle-1)*height()/NumeroCaselle);
			if (CoordinateSerpente.last().GetY()>=NumeroCaselle) Partenza.setY(0);
			temp->setKeyValueAt(0.0,Partenza);
		}
		temp->setKeyValueAt(1.0,QPoint(CoordinateSerpente.at(CoordinateSerpente.size()-2).GetX()*width()/NumeroCaselle,CoordinateSerpente.at(CoordinateSerpente.size()-2).GetY()*height()/NumeroCaselle));
		Animazioni->addAnimation(temp);

		if (!CoordinateSerpente.at(CoordinateSerpente.size()-2).IsInside(QRect(0,0,NumeroCaselle,NumeroCaselle))){
			Rotazione.reset();
			Rotazione.rotate(90*CoordinateSerpente.at(CoordinateSerpente.size()-2).GetDirezione());
			AusiliariaSerpente->setPixmap(ImmagineCoda.transformed(Rotazione));
			AusiliariaSerpente->show();
			QPropertyAnimation* AuxAnim=new QPropertyAnimation(AusiliariaSerpente,"pos",this);
			AuxAnim->setDuration(VelocitaGioco/difficolta);
			AuxAnim->setEasingCurve(QEasingCurve::Linear);
			if (CoordinateSerpente.at(CoordinateSerpente.size()-2).GetX()<0){
				AuxAnim->setKeyValueAt(0.0,QPoint(width(),CoordinateSerpente.at(CoordinateSerpente.size()-2).GetY()*height()/NumeroCaselle));
				AuxAnim->setKeyValueAt(1.0,QPoint((NumeroCaselle-1)*width()/NumeroCaselle,CoordinateSerpente.at(CoordinateSerpente.size()-2).GetY()*height()/NumeroCaselle));
			}
			else if (CoordinateSerpente.at(CoordinateSerpente.size()-2).GetX()>=NumeroCaselle){
				AuxAnim->setKeyValueAt(0.0,QPoint(-width()/NumeroCaselle,CoordinateSerpente.at(CoordinateSerpente.size()-2).GetY()*height()/NumeroCaselle));
				AuxAnim->setKeyValueAt(1.0,QPoint(0,CoordinateSerpente.at(CoordinateSerpente.size()-2).GetY()*height()/NumeroCaselle));
			}
			else if (CoordinateSerpente.at(CoordinateSerpente.size()-2).GetY()>=NumeroCaselle){
				AuxAnim->setKeyValueAt(0.0,QPoint(CoordinateSerpente.at(CoordinateSerpente.size()-2).GetX()*width()/NumeroCaselle,-height()/NumeroCaselle));
				AuxAnim->setKeyValueAt(1.0,QPoint(CoordinateSerpente.at(CoordinateSerpente.size()-2).GetX()*width()/NumeroCaselle,0));
			}
			else if (CoordinateSerpente.at(CoordinateSerpente.size()-2).GetY()<0){
				AuxAnim->setKeyValueAt(0.0,QPoint(CoordinateSerpente.at(CoordinateSerpente.size()-2).GetX()*width()/NumeroCaselle,height()));
				AuxAnim->setKeyValueAt(1.0,QPoint(CoordinateSerpente.at(CoordinateSerpente.size()-2).GetX()*width()/NumeroCaselle,(NumeroCaselle-1)*height()/NumeroCaselle));
			}
			Animazioni->addAnimation(AuxAnim);
		}

		for (QList<CoordinateCorpo>::iterator i=CoordinateSerpente.end()-1;i!=CoordinateSerpente.begin();i--) *i=*(i-1);
	}	

	//Normalizzo le Coordinate
	{
		bool trovato=false;
		for (QList<CoordinateCorpo>::iterator i=CoordinateSerpente.begin();i!=CoordinateSerpente.end() && !trovato;i++){
			if (i->GetY()<0) i->SetY(NumeroCaselle-1);
			if (i->GetY()>=NumeroCaselle) i->SetY(0);
			if (i->GetX()>=NumeroCaselle) i->SetX(0);
			if (i->GetX()<0) i->SetX(NumeroCaselle-1);
			trovato=true;
		}
	}

	switch (ProssimaDirezione){
		case Su:
			CoordinateSerpente.first().IncrementaY(-1);
			break;
		case Giu:
			CoordinateSerpente.first().IncrementaY(1);
			break;
		case Destra:
			CoordinateSerpente.first().IncrementaX(1);
			break;
		case Sinistra:
			CoordinateSerpente.first().IncrementaX(-1);
			break;
		default:
			animTesta->setKeyValueAt(1.0,QPoint(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle));
	}
	animTesta->setKeyValueAt(1.0,QPoint(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle));
	Animazioni->addAnimation(animTesta);
	if(!CoordinateSerpente.first().IsInside(QRect(0,0,NumeroCaselle,NumeroCaselle))){
		Rotazione.reset();
		Rotazione.rotate(90*CoordinateSerpente.first().GetDirezione());
		AusiliariaSerpente->setPixmap(ImmagineTesta.transformed(Rotazione));
		AusiliariaSerpente->show();
		QPropertyAnimation* AuxAnim=new QPropertyAnimation(AusiliariaSerpente,"pos",this);
		AuxAnim->setDuration(VelocitaGioco/difficolta);
		AuxAnim->setEasingCurve(QEasingCurve::Linear);
		if (CoordinateSerpente.first().GetX()<0){
			AuxAnim->setKeyValueAt(0.0,QPoint(width(),CoordinateSerpente.first().GetY()*height()/NumeroCaselle));
			AuxAnim->setKeyValueAt(1.0,QPoint((NumeroCaselle-1)*width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle));
		}
		else if (CoordinateSerpente.first().GetX()>=NumeroCaselle){
			AuxAnim->setKeyValueAt(0.0,QPoint(-width()/NumeroCaselle,CoordinateSerpente.first().GetY()*height()/NumeroCaselle));
			AuxAnim->setKeyValueAt(1.0,QPoint(0,CoordinateSerpente.first().GetY()*height()/NumeroCaselle));
		}
		else if (CoordinateSerpente.first().GetY()>=NumeroCaselle){
			AuxAnim->setKeyValueAt(0.0,QPoint(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,-height()/NumeroCaselle));
			AuxAnim->setKeyValueAt(1.0,QPoint(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,0));
		}
		else if (CoordinateSerpente.first().GetY()<0){
			AuxAnim->setKeyValueAt(0.0,QPoint(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,height()));
			AuxAnim->setKeyValueAt(1.0,QPoint(CoordinateSerpente.first().GetX()*width()/NumeroCaselle,(NumeroCaselle-1)*height()/NumeroCaselle));
		}
		Animazioni->addAnimation(AuxAnim);
	}

	CoordinateSerpente.first().SetDirezione(ProssimaDirezione);
	for (int i=0;i<CoordinateSerpente.size();i++){
		Rotazione.reset();
		Rotazione.rotate(90*CoordinateSerpente.at(i).GetDirezione());
		if (i==0){
			TestaSerpente->setPixmap(ImmagineTesta.transformed(Rotazione));
		}
		else if(i==CoordinateSerpente.size()-1){
			CodaSerpente->setPixmap(ImmagineCoda.transformed(Rotazione));
		}
		else{
			CorpoSerpente.at(i-1)->setPixmap(ImmagineCorpo.transformed(Rotazione));
		}
	}
	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
}
void Snake::NascondiPausa(){
	Giocando=true;
	Mela->setEnabled(true);
	Topo->setEnabled(true);
	for(QList<QLabel*>::iterator i=CorpoSerpente.begin();i!=CorpoSerpente.end();i++) (*i)->setEnabled(true);
	TestaSerpente->setEnabled(true);
	CodaSerpente->setEnabled(true);
	Punteggio->setEnabled(true);
	QPropertyAnimation* animNuovoGioco= new QPropertyAnimation(NuovoGioco,"pos",this);
	animNuovoGioco->setDuration(DurataAnimazioni);
	animNuovoGioco->setEasingCurve(QEasingCurve::InBack);
	animNuovoGioco->setKeyValueAt(1.0,QPoint(NuovoGioco->pos().x(),NuovoGioco->pos().y()-width()-40));
	animNuovoGioco->setKeyValueAt(0.0,NuovoGioco->pos());

	QPropertyAnimation* animCaricaGioco= new QPropertyAnimation(CaricaGioco,"pos",this);
	animCaricaGioco->setDuration(DurataAnimazioni);
	animCaricaGioco->setEasingCurve(QEasingCurve::InBack);
	animCaricaGioco->setKeyValueAt(1.0,QPoint(CaricaGioco->pos().x(),CaricaGioco->pos().y()-width()-40));
	animCaricaGioco->setKeyValueAt(0.0,CaricaGioco->pos());

	QPropertyAnimation* animOpzioni= new QPropertyAnimation(Opzioni,"pos",this);
	animOpzioni->setDuration(DurataAnimazioni);
	animOpzioni->setEasingCurve(QEasingCurve::InBack);
	animOpzioni->setKeyValueAt(1.0,QPoint(Opzioni->pos().x(),Opzioni->pos().y()-width()-40));
	animOpzioni->setKeyValueAt(0.0,Opzioni->pos());

	QPropertyAnimation* animEsci= new QPropertyAnimation(Esci,"pos",this);
	animEsci->setDuration(DurataAnimazioni);
	animEsci->setEasingCurve(QEasingCurve::InBack);
	animEsci->setKeyValueAt(1.0,QPoint(Esci->pos().x(),Esci->pos().y()-width()-40));
	animEsci->setKeyValueAt(0.0,Esci->pos());


	QParallelAnimationGroup *Animazioni=new QParallelAnimationGroup;
	Animazioni->addAnimation(animNuovoGioco);
	Animazioni->addAnimation(animCaricaGioco);
	Animazioni->addAnimation(animOpzioni);
	Animazioni->addAnimation(animEsci);
	connect(Animazioni,SIGNAL(finished()),this,SLOT(HideMenuItems()));
	connect(Animazioni,SIGNAL(finished()),this,SLOT(Partita()));


	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
}
void Snake::MostraPausa(){
	Giocando=false;
	int temp=(height()-(AltezzaPulsante*4)-(DistanzaPulsanti*3))/2;
	NuovoGioco->show();
	NuovoGioco->raise();
	CaricaGioco->show();
	CaricaGioco->setText(tr("Continua"));
	CaricaGioco->raise();
	Opzioni->show();
	Opzioni->raise();
	Esci->show();
	Esci->raise();
	Mela->setEnabled(false);
	Topo->setEnabled(false);
	for(QList<QLabel*>::iterator i=CorpoSerpente.begin();i!=CorpoSerpente.end();i++) (*i)->setEnabled(false);
	TestaSerpente->setEnabled(false);
	CodaSerpente->setEnabled(false);
	Punteggio->setEnabled(false);
	AusiliariaSerpente->setEnabled(false);
	AusiliariaTopo->setEnabled(false);
	QPropertyAnimation* animNuovoGioco= new QPropertyAnimation(NuovoGioco,"pos",this);
	animNuovoGioco->setDuration(DurataAnimazioni);
	animNuovoGioco->setEasingCurve(QEasingCurve::OutBack);
	animNuovoGioco->setKeyValueAt(0.0,QPoint(NuovoGioco->pos().x(),temp-width()-40));
	animNuovoGioco->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp));

	QPropertyAnimation* animCaricaGioco= new QPropertyAnimation(CaricaGioco,"pos",this);
	animCaricaGioco->setDuration(DurataAnimazioni);
	animCaricaGioco->setEasingCurve(QEasingCurve::OutBack);
	animCaricaGioco->setKeyValueAt(0.0,QPoint(CaricaGioco->pos().x(),temp+AltezzaPulsante+DistanzaPulsanti-width()-40));
	animCaricaGioco->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp+AltezzaPulsante+DistanzaPulsanti));

	QPropertyAnimation* animOpzioni= new QPropertyAnimation(Opzioni,"pos",this);
	animOpzioni->setDuration(DurataAnimazioni);
	animOpzioni->setEasingCurve(QEasingCurve::OutBack);
	animOpzioni->setKeyValueAt(0.0,QPoint(Opzioni->pos().x(),temp+2*AltezzaPulsante+2*DistanzaPulsanti-width()-40));
	animOpzioni->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp+2*AltezzaPulsante+2*DistanzaPulsanti));


	QPropertyAnimation* animEsci= new QPropertyAnimation(Esci,"pos",this);
	animEsci->setDuration(DurataAnimazioni);
	animEsci->setEasingCurve(QEasingCurve::OutBack);
	animEsci->setKeyValueAt(0.0,QPoint(Esci->pos().x(),temp+3*AltezzaPulsante+3*DistanzaPulsanti-width()-40));
	animEsci->setKeyValueAt(1.0,QPoint((width()-LargezzaPulsante)/2,temp+3*AltezzaPulsante+3*DistanzaPulsanti));


	QParallelAnimationGroup *Animazioni=new QParallelAnimationGroup;
	Animazioni->addAnimation(animNuovoGioco);
	Animazioni->addAnimation(animCaricaGioco);
	Animazioni->addAnimation(animOpzioni);
	Animazioni->addAnimation(animEsci);

	Animazioni->start(QAbstractAnimation::DeleteWhenStopped);
}
bool Snake::eventFilter(QObject *target, QEvent *event){
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if ((keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_W) && CoordinateSerpente.first().GetDirezione()!=Giu) {
			ProssimaDirezione=Su;
		}
		else if ((keyEvent->key() == Qt::Key_Down || keyEvent->key() == Qt::Key_S) && CoordinateSerpente.first().GetDirezione()!=Su) {
			ProssimaDirezione=Giu;
		}
		else if ((keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_A) && CoordinateSerpente.first().GetDirezione()!=Destra) {
			ProssimaDirezione=Sinistra;
		}
		else if ((keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_D) && CoordinateSerpente.first().GetDirezione()!=Sinistra) {
			ProssimaDirezione=Destra;
		}
		else if (keyEvent->key() == Qt::Key_Escape || keyEvent->key() == Qt::Key_Pause) {
			if (Giocando){
				MostraPausa();
			}
			else if(NuovoGioco->isVisible() && TestaSerpente->isVisible()){
				NascondiPausa();
			}
			else if(OpzioniLabel->isVisible()){
				NascondiOpzioni();
			}
		}
	}
	return QWidget::eventFilter(target, event);
}