#include "display_box.h"
#include <qtypes.h>

DisplayBox::DisplayBox(QWidget *parent) : DisplayBox(0, 0, 0, parent) {}

DisplayBox::DisplayBox(quint32 width, quint32 height, quint16 radius,
                       QWidget *parent)
    : QWidget(parent), width(width), height(height), radius(radius) {}

quint32 DisplayBox::getWidth() const { return width; }

quint32 DisplayBox::getHeight() const { return height; }

quint16 DisplayBox::getRadius() const { return radius; }

void DisplayBox::setWidth(quint32 width) { width = width; }

void DisplayBox::setHeight(quint32 height) { height = height; }

void DisplayBox::setRadius(quint16 radius) { radius = radius; }
