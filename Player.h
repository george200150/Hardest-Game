#pragma once
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QKeyEvent>
#include <qdebug.h>
#include <stdio.h>
#include <QTimer>

class Player : public QGraphicsRectItem {
private:
	QGraphicsDropShadowEffect * effect;
public:
	/*
	define the shape of the player block
	*/
	Player() {
		setBrush(QBrush(Qt::red));
	}
	/*
	define the movement on the X axis (left and right)
	*/
	void moveX(int dx) {
		setPos(x() + dx, y());
	}

	/*
	define the movement on the Y axis (up and down)
	*/
	void moveY(int dy) {
		setPos(x(), y() + dy);
	}

	/*
	define the collision event effect on the player
	*/
	void hit() {
		QPropertyAnimation *animation = new QPropertyAnimation(effect, "color");
		animation->setDuration(5000);
		animation->setStartValue(QColor(Qt::red));
		animation->setEndValue(QColor(Qt::black));
		animation->start();
	}
};