#pragma once
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <stdlib.h>

#include <QPropertyAnimation>
class Wall :public QGraphicsRectItem {
	QGraphicsDropShadowEffect * effect;
public:
	Wall(int w, int h,QColor color) {
		setRect(0, 0, w, h);

		setBrush(QBrush(color));

		QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect();

	}

	void hit() {
		QPropertyAnimation *animation = new QPropertyAnimation(effect, "color");
		animation->setDuration(5000);
		animation->setStartValue(QColor(Qt::red));
		animation->setEndValue(QColor(Qt::black));
		animation->start();
	}
};