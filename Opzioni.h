#ifndef OPZIONI_H
#define OPZIONI_H
#include "SelettoreImmagini.h"
#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>

class WOpzioni: public QWidget{
	Q_OBJECT
private:
	QLabel* OpzioniLabel;
	QFrame* Sfondo;

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
protected:
	void resizeEvent(QResizeEvent *event);
private slots:
	void AggiornaTestoDifficolta(int a) {DifficoltaNum->setText(QString("%1").arg(a));}
	void AggiornaTestoVolMus(int a) {VolumeMusNum->setText(QString("%1").arg(a));}
	void AggiornaTestoVolEff(int a) {VolumeEffNum->setText(QString("%1").arg(a));}
	void SetDifficolta(int a) {if (a>0 && a<=9) difficolta=a;}
	void SetSmartMouse(bool a) {SmartMouse=a;}
	void SetVolMus(int a) {if (a>0 && a<=10) VolumeMus=a;}
	void SetVolEff(int a) {if (a>0 && a<=10) VolumeEff=a;}
	void SetMuteMus(bool a) {MuteMus=a;}
	void SetMuteEff(bool a) {MuteEff=a;}
	void SetSchema(int a) {if (a>=0 && a<SelettoreSchema->GetNumeroImmagini()) SchemaScelto=a;}
signals:
	void Confermato();
	void Annullato();
public:
	WOpzioni(QWidget* parent=0);
	unsigned int GetDifficolta() const{return difficolta;}
	void ImpostaDifficolta(const int& a){if (a<1 || a>9) return; DifficoltaSlide->setValue(a);}
	unsigned int GetVolumeMus() const {return VolumeMus;}
	void ImpostaVolumeMus(const int& a){if(a<1 || a>10) return; VolumeMusSlide->setValue(a);}
	unsigned int GetVolumeEff() const {return VolumeEff;}
	void ImpostaVolumeEff(const int& a){if(a<1 || a>10) return; VolumeEffSlide->setValue(a);}
	bool GetMuteMus() const {return MuteMus;}
	void ImpostaMuteMus(bool a){MuteMus=a; MutoMus->setChecked(a);}
	bool GetMuteEff() const {return MuteEff;}
	void ImpostaMuteEff(bool a){MuteEff=a; MutoEff->setChecked(a);}
	int GetSchemaScelto() const {return SchemaScelto;}
	void ImpostaSchemaScelto(int a){if (a<0 || a>=SelettoreSchema->GetNumeroImmagini()) return; SchemaScelto=a; SelettoreSchema->SetIndex(a);}
	bool GetSmartMouse() const {return SmartMouse;}
	void ImpostaSmartMouse(bool a){SmartMouse=a; TopoIntelligente->setChecked(a);}
	void SalvaRecord(int punti);
	void AggiornaTopScores();
	void AttivaSelettoreSchema(bool a) {SelettoreSchema->setEnabled(a);}

};
#endif