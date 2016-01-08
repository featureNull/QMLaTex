#include "ImageProvider.h"

#include <QDebug>
#include <QPainter>
#include <QElapsedTimer>

static ImageProvider* inst = nullptr;

#define PDF_PAGE_SPACE	50

ImageProvider::ImageProvider() 
	: QQuickImageProvider(QQuickImageProvider::Pixmap), logger("ImageProvider")
{
	inst = this;
	_pageLoadingPixmap = QPixmap(":/res/png/pageloading.png");
}

ImageProvider* ImageProvider::instance()
{
	Q_ASSERT_X(inst != nullptr, Q_FUNC_INFO, "ImageProvider is singletone and you should"
		"cretae one instance in main.cpp");
	return inst;
}


QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
	QPixmap result;
	qDebug() << "requestPixmap: id=" << id;

	if (id.startsWith("pdfdoc")) {
		QString numstr = id;
		numstr = numstr.remove("pdfdoc");
		int num = numstr.toInt();
		result =  requestPdfPreview(num, size, requestedSize);
	}
	else {
		result = QPixmap(1, 1);
	}

	return result;
}

QPixmap ImageProvider::requestPdfPreview(int pageNum, QSize *size, const QSize &requestedSize)
{
	QPixmap pixi;

	if (_pdfPreview.contains(pageNum)) {
		pixi = _pdfPreview[pageNum];
	}
	else {
		pixi = _pageLoadingPixmap;
	}

	if (size)
		*size = QSize(pixi.width(), pixi.height());

	return pixi;
}

void ImageProvider::setPdfPreview(int page, const QPixmap& pixi)
{
	qCDebug(logger) << "setPdfPreview: page=" << page;
	_pdfPreview[page] = pixi;
}

void ImageProvider::clearPdfPreview()
{
	_pdfPreview.clear();
}
