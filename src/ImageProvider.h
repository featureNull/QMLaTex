#pragma once

#include<QQuickImageProvider>
#include<QString>
#include<QPixmap>
#include<QSize>
#include<QList>
#include <QLoggingCategory>


/**
 * @brief provided old style qpixmap dinger in qml
 * @details ist singletone fuer die ganze anwednung
 */
class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();
	static ImageProvider* instance();
	
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
	
	/** pdf Vorschau [page, pixmap] */
	void setPdfPreview(int page, const QPixmap& pixi);
	void clearPdfPreview();
	
	/** kunstwerk von plot prog */
	// ....

private:
	QPixmap requestPdfPreview(QSize *size, const QSize &requestedSize);

	/// @todo hier koennt man document name eingeben
	QPixmap requestPdfPreview(int pageNum, QSize *size, const QSize &requestedSize);

	QLoggingCategory logger;
	QMap<int, QPixmap> _pdfPreview;

	QPixmap _pageLoadingPixmap;
};

