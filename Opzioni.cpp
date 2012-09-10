#include "Opzioni.h"
#include <QtGui>
WOpzioni::WOpzioni(QWidget* parent/* =0 */)
: QWidget(parent)
,difficolta(1)
,SmartMouse(false)
,MuteEff(false)
,MuteMus(false)
,Records("TopScores.snq")
,VolumeMus(5)
,VolumeEff(5)
,SchemaScelto(0)
{
	OpzioniLabel=new QLabel(this);
	OpzioniLabel->setObjectName("OpzioniLabel");
	OpzioniLabel->setText(tr("Opzioni"));
	OpzioniLabel->setScaledContents(true);

	DifficoltaLabel=new QLabel(this);
	DifficoltaLabel->setObjectName("DifficoltaLabel");
	DifficoltaLabel->setText(tr("Difficoltà"));
	DifficoltaLabel->setScaledContents(true);
	DifficoltaNum=new QLabel(this);
	DifficoltaNum->setObjectName("DifficoltaNum");
	DifficoltaNum->setScaledContents(true);
	DifficoltaNum->setText(QString("%1").arg(difficolta));
	DifficoltaSlide=new QSlider(Qt::Horizontal,this);
	DifficoltaSlide->setRange(1,9);
	DifficoltaSlide->setObjectName("DifficoltaSlide");
	DifficoltaSlide->setValue(difficolta);
	connect(DifficoltaSlide,SIGNAL(valueChanged(int)),this, SLOT(AggiornaTestoDifficolta(int)));
	connect(DifficoltaSlide,SIGNAL(valueChanged(int)),this,SLOT(ImpostaDifficolta(int)));
	TopoIntelligente=new QCheckBox(this);
	TopoIntelligente->setObjectName("TopoIntelligente");
	TopoIntelligente->setText(tr("Topo Intelligente"));
	connect(TopoIntelligente,SIGNAL(clicked(bool)),this,SLOT(ImpostaIntelligenza(bool)));
	QGridLayout* LayoutDifficolta=new QGridLayout;
	LayoutDifficolta->addWidget(DifficoltaLabel,0,0,1,2);
	LayoutDifficolta->addWidget(DifficoltaNum,1,0,1,1);
	LayoutDifficolta->addWidget(DifficoltaSlide,1,1,1,1);
	LayoutDifficolta->addWidget(TopoIntelligente,2,0,1,2);

	VolumeMusLabel=new QLabel(this);
	VolumeMusLabel->setObjectName("VolumeMusLabel");
	VolumeMusLabel->setText(tr("Volume Musica"));
	VolumeMusLabel->setScaledContents(true);
	VolumeMusNum=new QLabel(this);
	VolumeMusNum->setObjectName("VolumeMusNum");
	VolumeMusNum->setScaledContents(true);
	VolumeMusNum->setText(QString("%1").arg(VolumeMus));
	VolumeMusSlide=new QSlider(Qt::Horizontal,this);
	VolumeMusSlide->setRange(1,10);
	VolumeMusSlide->setObjectName("VolumeMusSlide");
	VolumeMusSlide->setValue(VolumeMus);
	connect(VolumeMusSlide,SIGNAL(valueChanged(int)),this, SLOT(AggiornaTestoVolMus(int)));
	connect(VolumeMusSlide,SIGNAL(valueChanged(int)),this,SLOT(ImpostaVolMus(int)));
	MutoMus=new QCheckBox(this);
	MutoMus->setObjectName("MutoMus");
	MutoMus->setText(tr("Disattiva Musica"));
	connect(MutoMus,SIGNAL(clicked(bool)),VolumeMusSlide,SLOT(setDisabled(bool)));
	connect(MutoMus,SIGNAL(clicked(bool)),VolumeMusNum,SLOT(setDisabled(bool)));
	connect(MutoMus,SIGNAL(clicked(bool)),this,SLOT(ImpostaMuteMus(bool)));
	QGridLayout* LayoutMusica=new QGridLayout;
	LayoutMusica->addWidget(VolumeMusLabel,0,0,1,2);
	LayoutMusica->addWidget(VolumeMusNum,1,0,1,1);
	LayoutMusica->addWidget(VolumeMusSlide,1,1,1,1);
	LayoutMusica->addWidget(MutoMus,2,0,1,2);

	VolumeEffLabel=new QLabel(this);
	VolumeEffLabel->setObjectName("VolumeMusLabel");
	VolumeEffLabel->setText(tr("Volume Effetti"));
	VolumeEffLabel->setScaledContents(true);
	VolumeEffNum=new QLabel(this);
	VolumeEffNum->setObjectName("VolumeMusNum");
	VolumeEffNum->setScaledContents(true);
	VolumeEffNum->setText(QString("%1").arg(VolumeEff));
	VolumeEffSlide=new QSlider(Qt::Horizontal,this);
	VolumeEffSlide->setRange(1,10);
	VolumeEffSlide->setObjectName("VolumeMusSlide");
	VolumeEffSlide->setValue(VolumeEff);
	connect(VolumeEffSlide,SIGNAL(valueChanged(int)),this, SLOT(AggiornaTestoVolEff(int)));
	connect(VolumeEffSlide,SIGNAL(valueChanged(int)),this,SLOT(ImpostaVolEff(int)));
	MutoEff=new QCheckBox(this);
	MutoEff->setObjectName("MutoEff");
	MutoEff->setText(tr("Disattiva Effetti"));
	connect(MutoEff,SIGNAL(clicked(bool)),VolumeEffSlide,SLOT(setDisabled(bool)));
	connect(MutoEff,SIGNAL(clicked(bool)),VolumeEffNum,SLOT(setDisabled(bool)));
	connect(MutoEff,SIGNAL(clicked(bool)),this,SLOT(ImpostaMuteEff(bool)));
	QGridLayout* LayoutEffetti=new QGridLayout;
	LayoutEffetti->addWidget(VolumeEffLabel,0,0,1,2);
	LayoutEffetti->addWidget(VolumeEffNum,1,0,1,1);
	LayoutEffetti->addWidget(VolumeEffSlide,1,1,1,1);
	LayoutEffetti->addWidget(MutoEff,2,0,1,2);

	TopScores=new QLabel(this);
	TopScores->setObjectName("TopScores");
	TopScores->setScaledContents(true);
	TopScores->setText("<b>"+tr("Punteggi Migliori:")+"</b><br>1) 0<br>2) 0<br>3) 0");

	SelettoreSchema=new SelettoreImmagini(this);
	SelettoreSchema->setObjectName("SelettoreSchema");
	SelettoreSchema->ImpostaPosDidascalia(SelettoreImmagini::Sopra);
	SelettoreSchema->AggiungiImmagine(QPixmap(":/Schemi/Libero.png"),tr("Libero"));
	SelettoreSchema->AggiungiImmagine(QPixmap(":/Schemi/Gabbia.png"),tr("Gabbia"));
	SelettoreSchema->AggiungiImmagine(QPixmap(":/Schemi/Angoli.png"),tr("Angoli"));
	SelettoreSchema->AggiungiImmagine(QPixmap(":/Schemi/Labirinto.png"),tr("Labirinto"));
	SelettoreSchema->AggiungiImmagine(QPixmap(":/Schemi/Gabbia.png"),tr("Casuale"));
	connect(SelettoreSchema,SIGNAL(IndexChanged(int)),this,SLOT(ImpostaSchema(int)));
	SchemaLabel=new QLabel(this);
	SchemaLabel->setObjectName("SchemaLabel");
	SchemaLabel->setText(tr("Schema"));
	QVBoxLayout *LayoutSchemi=new QVBoxLayout;
	LayoutSchemi->addWidget(SchemaLabel);
	LayoutSchemi->addWidget(SelettoreSchema);
	
	Annulla=new QPushButton(this);
	Annulla->setObjectName("Annulla");
	Annulla->setText(tr("Annulla"));
	Annulla->setMinimumSize(60,40);
	//Annulla->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	connect(Annulla,SIGNAL(clicked()),this,SIGNAL(Annullato()));
	Conferma=new QPushButton(this);
	Conferma->setObjectName("Conferma");
	Conferma->setText(tr("Ok"));
	Conferma->setDefault(true);
	Conferma->setMinimumSize(60,40);
	//Conferma->setMinimumSize(LargezzaPulsante,AltezzaPulsante);
	connect(Conferma,SIGNAL(clicked()),this,SIGNAL(Confermato()));
	QHBoxLayout* LayoutPulsanti=new QHBoxLayout;
	QSpacerItem* SpaziatorePulsanti=new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
	LayoutPulsanti->addWidget(Conferma);
	LayoutPulsanti->addItem(SpaziatorePulsanti);
	LayoutPulsanti->addWidget(Annulla);

	QGridLayout* LayoutOpzioni=new QGridLayout(this);
	LayoutOpzioni->addWidget(OpzioniLabel,0,0,1,2);
	LayoutOpzioni->addLayout(LayoutDifficolta,1,0,1,1);
	LayoutOpzioni->addLayout(LayoutMusica,1,1,1,1);
	LayoutOpzioni->addLayout(LayoutEffetti,2,1,1,1);
	LayoutOpzioni->addWidget(TopScores,3,1,1,1);
	LayoutOpzioni->addLayout(LayoutSchemi,2,0,2,1);
	LayoutOpzioni->addLayout(LayoutPulsanti,4,0,1,2);	
}
void WOpzioni::AggiornaTopScores(){
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
}
void WOpzioni::SalvaRecord(int punti){
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
}