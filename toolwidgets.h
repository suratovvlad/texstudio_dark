/*
	This file contains the dockwidgets at the left/bottom side of txs
*/
#ifndef TOOLWIDGETS_H
#define TOOLWIDGETS_H

#include "mostQtHeaders.h"

#include "titledpanel.h"
#include "logeditor.h"
#include "latexlog.h"
#include "latexlogwidget.h"
#include "searchresultwidget.h"

class PreviewWidget : public QScrollArea
{
	Q_OBJECT

public:
	explicit PreviewWidget(QWidget *parent = 0);

public slots:
	void previewLatex(const QPixmap &previewImage);
	void fitImage(bool fit);
	void centerImage(bool center);
	void scaleImage(double factor);
	void zoomOut();
	void zoomIn();
	void resetZoom();
	void contextMenu(QPoint point);

protected:
	void wheelEvent(QWheelEvent *event);

private:
	QLabel *preViewer;
	double pvscaleFactor;
	bool mCenter;
	bool mFit;
};

class OutputViewWidget: public TitledPanel
{
	Q_OBJECT

public:
	explicit OutputViewWidget(QWidget *parent = 0);

	const QString MESSAGES_PAGE;
	const QString LOG_PAGE;
	const QString PREVIEW_PAGE;
	const QString SEARCH_RESULT_PAGE;

	LatexLogWidget *getLogWidget() { return logWidget; }
	SearchResultWidget *getSearchResultWidget() { return searchResultWidget; }
	bool isPreviewPanelVisible();
	void setMessage(const QString &message); //set the message text (don't change page and no auto-show)
	bool childHasFocus();

	virtual void changeEvent(QEvent *event);

public slots:
	void copy();
	void resetMessages(bool noTabChange = false); //remove all messages and jumps to the message page (stays hidden if not visible)
	void resetMessagesAndLog(bool noTabChange = false);
	void selectLogEntry(int logEntryNumber, bool makeVisible = true);
	void previewLatex(const QPixmap &pixmap);

	void insertMessageLine(const QString &message); //inserts the message text (don't change page and no auto-show)

signals:

private:
	PreviewWidget *previewWidget;
	LatexLogWidget *logWidget;
	SearchResultWidget *searchResultWidget;
	LogEditor *OutputMessages;

	void retranslateUi();
};


class CustomWidgetList: public QDockWidget
{
	Q_OBJECT

public:
	CustomWidgetList(QWidget *p = 0);
	void addWidget(QWidget *widget, const QString &id, const QString &text, const QString &iconName);
	void setWidgetText(const QString &id, const QString &text);
	void setWidgetText(QWidget *widget, const QString &text);
	void setWidgetIcon(const QString &id, const QString &icon);
	void setWidgetIcon(QWidget *widget, const QString &icon);
	int widgetCount() const;
	void setHiddenWidgets(const QString &hidden);
	QString hiddenWidgets() const;
	QWidget *widget(int i) const;
	QWidget *widget(const QString &id) const;
	QList<QWidget *> getWidgets() const;
	void setCurrentWidget(QWidget *widget);
	QWidget *currentWidget() const;
	bool isNewLayoutStyleEnabled() const;

signals:
	void widgetContextMenuRequested(QWidget *widget, const QPoint &globalPosition);

public slots:
	void showWidgets(bool newLayoutStyle);
	void setToolbarIconSize(int sz);

private slots:
	void showPageFromAction();
	void currentWidgetChanged(int i);
	void toggleWidgetFromAction(bool on);
	void customContextMenuRequested(const QPoint &localPosition);

private:
	void showWidget(const QString &id);
	void hideWidget(const QString &id);
	//void addWidgetOld(QWidget* widget, const QString& id, const QString& text, const QString& iconName, const bool visible);
//	void addWidgetNew(QWidget* widget, const QString& id, const QString& text, const QString& iconName, const bool visible);
	QString widgetId(QWidget *widget) const;


	QStringList hiddenWidgetsIds;
	QList<QWidget *> widgets;
	bool newStyle;

	//old layout
	QToolBox *toolbox;

	//new layout
	QFrame *frame;
	QStackedWidget *stack;
	QToolBar *toolbar;

};

#endif