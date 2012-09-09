#ifndef SNAKE_H
#define SNAKE_H

#include <QtGui>
#include "CoordinateCorpo.h"
#include "Opzioni.h"

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
	QLabel* Punteggio;
	QLabel* Mela;
	QLabel* Topo;
	QList<QLabel*> AusiliariaSerpente;
	QLabel* AusiliariaTopo;
	QPixmap ImmagineTesta;
	QPixmap ImmagineCoda;
	QPixmap ImmagineCorpo;
	QPixmap ImmagineTopo;
	QPixmap ImmagineSasso;
	QLabel* TestaSerpente;
	QLabel* CodaSerpente;
	WOpzioni* OpzioniWid;
	QSound Score;
	QSound Fail;
	QSound GameOver;
	bool MuteMus;
	bool MuteEff;
	bool SmartMouse;
	QList<QLabel*> CorpoSerpente;
	void EliminaCorpo();
	void EliminaAusiliari();
	int punti;
	int SchemaCorrente;
	unsigned int difficolta;
	unsigned short WhatToDo;
	unsigned short ProssimaDirezione;
	CoordinateCorpo CoordinateMela;
	CoordinateCorpo CoordinateTopo;
	QList<CoordinateCorpo> CoordinateSerpente;
	QList<CoordinateCorpo> CoordinateOstacoli;
	QList<QLabel*> Ostacoli;
	bool Giocando;
	QFile Salvataggio;
	enum {Boh, IniziaNuova, IniziaCaricata, Settings};
	enum{LargezzaPulsante=160, AltezzaPulsante=40, DistanzaPulsanti=10
		,DurataAnimazioni=1000
		,NumeroCaselle=20};
	enum{Su,Destra,Giu,Sinistra};
	enum {VelocitaGioco=1000};
	enum {NumeroMagico=8889};
	enum {SchemaLibero,SchemaGabbia};
protected:
	void resizeEvent(QResizeEvent *event);
	bool eventFilter(QObject *target, QEvent *event);
private slots:
	void SetNuova(){WhatToDo=IniziaNuova;}
	void SetCarica(){WhatToDo=IniziaCaricata;}
	void SetOpzioni(){WhatToDo=Settings;}
	void MostraOpzioni();
	void NascondiOpzioni();
	void AggiornaOpzioni();
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
	void ImpostaSchema(int a);

public:
	Snake(QWidget *parent = 0);


};

#endif // SNAKE_H
