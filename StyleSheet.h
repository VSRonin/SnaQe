#ifndef STYLESHEET_H
#define STYLESHEET_H
namespace CSS{
const QString Principale(
	"#Sfondo {"
		"background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2198c0, stop: 1 #0d5ca6);"
	"}"
	"QPushButton {"
		"color: #222;"
		"font: 14px bold;"
		"border: 2px solid #555;"
		"border-radius: 11px;"
		"padding: 5px;"
		"background: qradialgradient(cx: 0.3, cy: -0.4,"
		"fx: 0.3, fy: -0.4,"
		"radius: 1.35, stop: 0 #fff, stop: 1 #888);"
	"}"
	"QPushButton:hover {"
		"background: qradialgradient(cx: 0.3, cy: -0.4,"
		"fx: 0.3, fy: -0.4,"
		"radius: 1.35, stop: 0 #fff, stop: 1 #bbb);"
	"}"

	"QPushButton:pressed {"
		"background:"
		" qradialgradient(cx: 0.4, cy: -0.1,"
		"fx: 0.4, fy: -0.1,"
		"radius: 1.35, stop: 0 #fff, stop: 1 #ddd);"
	"}"
	
	"#Punteggio {"
		"color: red;"
		"font: 14px bold;"
	"}"
	"#Punteggio:disabled {"
		"color: #555;"
		"font: 14px bold;"
	"}"
);
}
#endif