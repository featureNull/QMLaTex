import QtQuick 2.3
import qmlatex.reports 1.0

LatexCodeBlock {
	packages: [	"{pgfplots}" ]
	
	code:'	\\begin{tikzpicture}' + '\r\n' +
		'		\\begin{axis}[' + '\r\n' +
		'			height=9cm,' + '\r\n' +
		'			width=9cm,' + '\r\n' +
		'			grid=major,' + '\r\n' +
		'		]' + '\r\n' +
		'\r\n' +
		'		\\addplot {-x^5 - 242};' + '\r\n' +
		'		\\addlegendentry{model}' + '\r\n' +
		'\r\n' +
		'		\\addplot coordinates {' + '\r\n' +
		'			(-4.77778,2027.60977)' + '\r\n' +
		'			(-3.55556,347.84069)' + '\r\n' +
		'			(-2.33333,22.58953)' + '\r\n' +
		'			(-1.11111,-493.50066)' + '\r\n' +
		'			(0.11111,46.66082)' + '\r\n' +
		'			(1.33333,-205.56286)' + '\r\n' +
		'			(2.55556,-341.40638)' + '\r\n' +
		'			(3.77778,-1169.24780)' + '\r\n' +
		'			(5.00000,-3269.56775)' + '\r\n' +
		'		};' + '\r\n' +
		'		\\addlegendentry{estimate}' + '\r\n' +
		'		\\end{axis}' + '\r\n' +
		'	\\end{tikzpicture}'
}
