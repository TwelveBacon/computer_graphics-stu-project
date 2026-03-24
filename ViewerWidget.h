#pragma once
#include <QtWidgets>
class ViewerWidget :public QWidget {
	Q_OBJECT

public:
	enum ObjectType
	{
		ObjectNone,
		ObjectLine,
		ObjectPolygon
	};
private:
	ObjectType currentObjectType = ObjectNone;

	QVector<QPoint> objectPoints;

	bool drawPolygonActvated = false;
	bool dragging = false;
	bool clippingEnabled = false;
	QPoint lastMousePos = QPoint(0, 0);

	QSize areaSize = QSize(0, 0);
	QImage* img = nullptr;
	uchar* data = nullptr;

	bool drawLineActivated = false;
	QPoint drawLineBegin = QPoint(0, 0);

	bool drawCircleActivated = false;
	QPoint drawCircleCenter = QPoint(0, 0);
public:
	ViewerWidget(QSize imgSize, QWidget* parent = Q_NULLPTR);
	~ViewerWidget();
	void resizeWidget(QSize size);

	//Image functions
	bool setImage(const QImage& inputImg);
	QImage* getImage() { return img; };
	bool isEmpty();
	bool changeSize(int width, int height);

	void setPixel(int x, int y, int r, int g, int b, int a = 255);
	void setPixel(int x, int y, double valR, double valG, double valB, double valA = 1.);
	void setPixel(int x, int y, const QColor& color);
	bool isInside(int x, int y);

	//Draw functions
	void drawLine(QPoint start, QPoint end, QColor color, int algType = 0);
	void setDrawLineBegin(QPoint begin) { drawLineBegin = begin; }
	QPoint getDrawLineBegin() { return drawLineBegin; }
	void setDrawLineActivated(bool state) { drawLineActivated = state; }
	bool getDrawLineActivated() { return drawLineActivated; }

	void drawCircle(QPoint center, int radius, QColor color);
	void drawCircleBresenham(QPoint center, int radius, QColor color);
	void setDrawCircleCenter(QPoint center) { drawCircleCenter = center; }
	QPoint getDrawCircleCenter() { return drawCircleCenter; }
	void setDrawCircleActivated(bool state) { drawCircleActivated = state; }
	bool getDrawCircleActivated() { return drawCircleActivated; }

	//Get/Set functions
	uchar* getData() { return data; }
	void setDataPtr() { data = img ? img->bits() : nullptr; }

	int getImgWidth() { return img ? img->width() : 0; };
	int getImgHeight() { return img ? img->height() : 0; };

	void clear();

	//Algorithms
	void drawLineDDA(QPoint start, QPoint end, QColor color);
	void drawLineBresenham(QPoint start, QPoint end, QColor color);
	//void scanLine();

	//----------Cvicenie 3----------
	void clearAll();
	void redrawScene(QColor color, int algType);
	void drawCurrentObject(QColor color, int algType);
	void drawPolygon(QVector<QPoint> pts, QColor color, int algType);

	void translateObject(int dx, int dy);
	void rotateObject(double angleDeg);
	void scaleObject(double kx, double ky);
	void shearX(double shx);
	void symmetry();

public slots:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
};