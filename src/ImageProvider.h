#pragma once

#include<QQuickImageProvider>
#include<QString>
#include<QPixmap>
#include<QSize>
#include<QList>
#include <QLoggingCategory>


/**
 * @brief provide pdf preview for QML
 * @details this is singelton for the whole application
 */
class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();
	static ImageProvider* instance();
	
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
	
	/** pdf preview [page, pixmap] */
	void setPdfPreview(int page, const QPixmap& pixi);
	void clearPdfPreview();
	
	/** kunstwerk von plot prog */
	// ....

private:
	QPixmap requestPdfPreview(QSize *size, const QSize &requestedSize);

	/// @todo here the name could be set
	QPixmap requestPdfPreview(int pageNum, QSize *size, const QSize &requestedSize);

	QLoggingCategory logger;
	QMap<int, QPixmap> _pdfPreview;

	QPixmap _pageLoadingPixmap;
};

