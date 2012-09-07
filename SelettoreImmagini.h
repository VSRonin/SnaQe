#ifndef SELETTOREIMMAGINI_H
#define SELETTOREIMMAGINI_H
#include <QWidget>
#include <QList>
#include <QBitmap>
class QPushButton;
class QFrame;
class QLabel;

class SelettoreImmagini: public QWidget{
	Q_OBJECT
private:
	int Orientamento;
	QPushButton* PulsanteAlto;
	QPushButton* PulsanteBasso;
	QPushButton* PulsanteDestra;
	QPushButton* PulsanteSinistra;
	QFrame* Displayer;
	QLabel* IconaCorrente;
	QLabel* IconaSuccessiva;
	QLabel* IconaPrecedente;
	QPixmap Freccia;
	QPixmap VoidImage;
	QList<QPixmap> Immagini;
	unsigned int IndiceCorrente;
	unsigned int DurataAnimazione;
public:
	enum{Verticale,Orizzontale};
	SelettoreImmagini(QWidget* parent=0, int Orient=Orizzontale);
	int GetOrientamento() const {return Orientamento;}
	void AggiungiImmagine(const QPixmap& fonte);
protected:
	void resizeEvent(QResizeEvent *event);
public slots:
	void SetIndex(int a);
private slots:
	void NextImage();
	void PrevImage();
	void Successiva();
	void Precedente();
};
#endif