#ifndef SNAKE_H
#define SNAKE_H

#include <QtGui>
#include "CoordinateCorpo.h"

class Snake : public QWidget
{
	Q_OBJECT
private:
	QFrame* Sfondo;
	QPushButton* NuovoGioco;
	QPushButton* CaricaGioco;
	QPushButton* Opzioni;
	QPushButton* Esci;
	QPushButton* Conferma;
	QSpinBox* DifficoltaSpin;
	QSlider* DifficoltaSlide;
	QLabel* DifficoltaLabel;
	QLabel* Punteggio;
	QLabel* Mela;
	QLabel* Topo;
	QLabel* TopScores;
	QLabel* OpzioniLabel;
	QLabel* AusiliariaSerpente;
	QLabel* AusiliariaTopo;
	QPushButton* ChiudiOpzioni;
	QPixmap ImmagineTesta;
	QPixmap ImmagineCoda;
	QPixmap ImmagineCorpo;
	QPixmap ImmagineTopo;
	QLabel* TestaSerpente;
	QLabel* CodaSerpente;
	QList<QLabel*> CorpoSerpente;
	void EliminaCorpo();
	int punti;
	unsigned int difficolta;
	unsigned short WhatToDo;
	unsigned short ProssimaDirezione;
	CoordinateCorpo CoordinateMela;
	CoordinateCorpo CoordinateTopo;
	QList<CoordinateCorpo> CoordinateSerpente;
	bool Giocando;
	QFile Salvataggio;
	QFile Records;
	enum {Boh, IniziaNuova, IniziaCaricata, Settings};
	enum{LargezzaPulsante=160, AltezzaPulsante=40, DistanzaPulsanti=10
		,DurataAnimazioni=1000
		,NumeroCaselle=20};
	enum{Su,Destra,Giu,Sinistra};
	enum {VelocitaGioco=1000};
	enum {NumeroMagico=8889};
protected:
	void resizeEvent(QResizeEvent *event);
	bool eventFilter(QObject *target, QEvent *event);
private slots:
	void SetNuova(){WhatToDo=IniziaNuova;}
	void SetCarica(){WhatToDo=IniziaCaricata;}
	void SetOpzioni(){WhatToDo=Settings;}
	void MostraOpzioni();
	void NascondiOpzioni();
	void HideOpzioni();
	void EseguiAzione();
	void NascondiMenu();
	void NascondiPausa();
	void MostraMenu();
	void MostraPausa();
	void HideMenuItems();
	void NuovaPartita();
	void CaricaPartita();
	void AggiornaPunti();
	void Partita();
	void ImpostaDifficolta(int a){difficolta=a;}

public:
	Snake(QWidget *parent = 0);


};

#endif // SNAKE_H
