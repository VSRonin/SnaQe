#ifndef OPZIONI_H
#define OPZIONI_H
#include "SelettoreImmagini.h"
#include <QWidget>
#include <QFile>
#include <QLabel>
class QSlider;
class QPushButton;
class QCheckBox;
class WOpzioni: public QWidget{
	Q_OBJECT
private:
	QLabel* OpzioniLabel;

	QLabel* DifficoltaLabel;
	QLabel* DifficoltaNum;
	QSlider* DifficoltaSlide;
	QCheckBox* TopoIntelligente;
	
	QLabel* VolumeMusLabel;
	QLabel* VolumeMusNum;
	QSlider* VolumeMusSlide;
	QCheckBox* MutoMus;

	QLabel* VolumeEffLabel;
	QLabel* VolumeEffNum;
	QSlider* VolumeEffSlide;
	QCheckBox* MutoEff;
	
	QFile Records;
	QLabel* TopScores;

	int SchemaScelto;
	QLabel* SchemaLabel;
	SelettoreImmagini* SelettoreSchema;
	
	QPushButton* Conferma;
	QPushButton* Annulla;


	int difficolta;
	int VolumeMus;
	int VolumeEff;
	bool MuteMus;
	bool MuteEff;
	bool SmartMouse;

	enum {NumeroMagico=8889};
private slots:
	void ImpostaDifficolta(const int& a){difficolta=a;}
	void ImpostaVolMus(const int& a){VolumeMus=a;}
	void ImpostaVolEff(const int& a){VolumeEff=a;}
	void ImpostaMuteMus(bool a){MuteMus=a;}
	void ImpostaMuteEff(bool a){MuteEff=a;}
	void ImpostaIntelligenza(bool a){SmartMouse=a;}
	void ImpostaSchema(int a){SchemaScelto=a;}
	void AggiornaTestoDifficolta(int a) {DifficoltaNum->setText(QString("%1").arg(a));}
	void AggiornaTestoVolMus(int a) {VolumeMusNum->setText(QString("%1").arg(a));}
	void AggiornaTestoVolEff(int a) {VolumeEffNum->setText(QString("%1").arg(a));}
signals:
	void Confermato();
	void Annullato();
public:
	WOpzioni(QWidget* parent=0);
	unsigned int GetDifficolta() const{return difficolta;}
	unsigned int GetVolumeMus() const {return VolumeMus;}
	unsigned int GetVolumeEff() const {return VolumeEff;}
	bool GetMuteMus() const {return MuteMus;}
	bool GetMuteEff() const {return MuteEff;}
	int GetSchemaScelto() const {return SchemaScelto;}
	bool GetSmartMouse() const {return SmartMouse;}
	void SalvaRecord(int punti);
	void AggiornaTopScores();
	void AttivaSelettoreSchema(bool a) {SelettoreSchema->setEnabled(a);}

};
#endif