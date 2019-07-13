#pragma once
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <stdlib.h>

#include <QPropertyAnimation>

/* GAME BOARD - COORDINATES (DEFAULT)

(0,0)					(width(),0)



(0,height()),			(width(),height())
*/



/*
	All the walls have to do is *exist*
	We need an array of Wall-s so that we can decide who collides with who

		-TODO-
	make it possible to define walls more easily
	(don't know how)
*/
class Wall :public QGraphicsRectItem {
	QGraphicsDropShadowEffect * effect;
public:
	/*
	constructor that uses width, height and the colour of the rectangle.
	This contructor defines the specific parameters of the rectangle, but not the place on the board
	*/
	Wall(int w, int h,QColor color) {
		setRect(0, 0, w, h);// the rectangle is defined as (STARTING_X, STARTING_Y, LENGHTH_X, LENGHTH_Y)

		setBrush(QBrush(color));

		QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect();

	}

	/*
	diffenret constructor that uses more parameters
	it directy defines the place of the rectangle on the board and its parameters
	*/
	Wall(int x, int y, int w, int h, QColor color) {
		setRect(x, y, w, h);

		setBrush(QBrush(color));

		QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect();

	}

};