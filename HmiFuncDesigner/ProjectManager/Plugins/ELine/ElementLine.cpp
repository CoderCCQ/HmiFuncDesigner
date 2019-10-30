﻿#include "ElementLine.h"
#include <QDebug>

int ElementLine::iLastIndex_ = 1;

ElementLine::ElementLine(const QString &szProjPath,
                         const QString &szProjName,
                         QtVariantPropertyManager *propertyMgr,
                         ProjectData *pProjDataObj)
    : Element(szProjPath, szProjName, propertyMgr, pProjDataObj)
{
    elementId = QString(tr("Line_%1").arg(iLastIndex_, 4, 10, QChar('0')));
    iLastIndex_++;
    internalElementType = tr("Line");
    elementIcon = QIcon(":/images/lineitem.png");
    borderWidth_ = 1;
    borderColor_ = Qt::black;
    init();
    createPropertyList();
    updatePropertyModel();
}

void ElementLine::regenerateElementId()
{
    elementId = QString(tr("Line_%1").arg(iLastIndex_ - 1, 4, 10, QChar('0')));
    this->updatePropertyModel();
}

/**
 * @brief ElementLine::release
 * @details 释放占用的资源
 */
void ElementLine::release()
{

}

QRectF ElementLine::boundingRect() const
{
    qreal extra = 5;
    const qreal x1 = elementLine.p1().x();
    const qreal x2 = elementLine.p2().x();
    const qreal y1 = elementLine.p1().y();
    const qreal y2 = elementLine.p2().y();
    qreal lx = qMin(x1,x2);
    qreal rx = qMax(x1,x2);
    qreal ty = qMin(y1,y2);
    qreal by = qMax(y1,y2);

    return QRectF(lx, ty, rx - lx, by - ty).normalized()
            .adjusted(-extra, -extra, extra, extra);;
}

void ElementLine::createPropertyList()
{
    propList.clear();
    clearProperties();

    QtVariantProperty *property = Q_NULLPTR;

    // ID
    property = variantPropertyManager_->addProperty(QVariant::String, tr("ID"));
    property->setAttribute(QLatin1String("readOnly"), true);
    addProperty(property, QLatin1String("id"));

    // 线条宽度
    property = variantPropertyManager_->addProperty(QVariant::Int, tr("线条宽度"));
    property->setAttribute(QLatin1String("minimum"), 0);
    property->setAttribute(QLatin1String("maximum"), 5000);
    addProperty(property, QLatin1String("borderWidth"));

    // 线条颜色
    property = variantPropertyManager_->addProperty(QVariant::Color, tr("线条颜色"));
    addProperty(property, QLatin1String("borderColor"));

    // 坐标 X
    property = variantPropertyManager_->addProperty(QVariant::Int, tr("坐标 X"));
    property->setAttribute(QLatin1String("minimum"), 0);
    property->setAttribute(QLatin1String("maximum"), 5000);
    addProperty(property, QLatin1String("xCoord"));

    // 坐标 Y
    property = variantPropertyManager_->addProperty(QVariant::Int, tr("坐标 Y"));
    property->setAttribute(QLatin1String("minimum"), 0);
    property->setAttribute(QLatin1String("maximum"), 5000);
    addProperty(property, QLatin1String("yCoord"));

    // Z 值
    property = variantPropertyManager_->addProperty(QVariant::Int, tr("Z 值"));
    property->setAttribute(QLatin1String("minimum"), -1000);
    property->setAttribute(QLatin1String("maximum"), 1000);
    addProperty(property, QLatin1String("zValue"));

    // 宽度
    property = variantPropertyManager_->addProperty(QVariant::Int, tr("宽度"));
    property->setAttribute(QLatin1String("minimum"), 0);
    property->setAttribute(QLatin1String("maximum"), 5000);
    addProperty(property, QLatin1String("width"));

    // 高度
    property = variantPropertyManager_->addProperty(QVariant::Int, tr("高度"));
    property->setAttribute(QLatin1String("minimum"), 0);
    property->setAttribute(QLatin1String("maximum"), 5000);
    addProperty(property, QLatin1String("height"));

    // 旋转角度
    property = variantPropertyManager_->addProperty(QVariant::Int, tr("角度"));
    property->setAttribute(QLatin1String("minimum"), -360);
    property->setAttribute(QLatin1String("maximum"), 360);
    addProperty(property, QLatin1String("angle"));
}

void ElementLine::updateElementProperty(QtProperty *property, const QVariant &value)
{
    QString id = propertyToId_[property];
    if (id == QLatin1String("id")) {
        elementId = value.toString();
    } else if (id == QLatin1String("borderWidth")) {
        borderWidth_ = value.toInt();
    } else if (id == QLatin1String("borderColor")) {
        borderColor_ = value.value<QColor>();
    } else if (id == QLatin1String("xCoord")) {
        elementXPos = value.toInt();
        setElementXPos(elementXPos);
    } else if (id == QLatin1String("yCoord")) {
        elementYPos = value.toInt();
        setElementYPos(elementYPos);
    } else if (id == QLatin1String("zValue")) {
        elementZValue = value.toInt();
        setZValue(elementZValue);
    } else if (id == QLatin1String("width")) {
        elementWidth = value.toInt();
        updateBoundingElement();
    } else if (id == QLatin1String("height")) {
        elementHeight = value.toInt();
        updateBoundingElement();
    } else if (id == QLatin1String("angle")) {
        elemAngle = value.toInt();
        setAngle(elemAngle);
    }

    scene()->update();
    update();
}

void ElementLine::updatePropertyModel()
{
    QtVariantProperty *property = Q_NULLPTR;

    property = idToProperty_[QLatin1String("id")];
    if(property != Q_NULLPTR) {
        property->setValue(elementId);
    }

    property = idToProperty_[QLatin1String("borderWidth")];
    if(property != Q_NULLPTR) {
        property->setValue(borderWidth_);
    }

    property = idToProperty_[QLatin1String("borderColor")];
    if(property != Q_NULLPTR) {
        property->setValue(borderColor_);
    }

    property = idToProperty_[QLatin1String("xCoord")];
    if(property != Q_NULLPTR) {
        property->setValue(elementXPos);
    }

    property = idToProperty_[QLatin1String("yCoord")];
    if(property != Q_NULLPTR) {
        property->setValue(elementYPos);
    }

    property = idToProperty_[QLatin1String("zValue")];
    if(property != Q_NULLPTR) {
        property->setValue(elementZValue);
    }

    property = idToProperty_[QLatin1String("width")];
    if(property != Q_NULLPTR) {
        property->setValue(elementWidth);
    }

    property = idToProperty_[QLatin1String("height")];
    if(property != Q_NULLPTR) {
        property->setValue(elementHeight);
    }

    property = idToProperty_[QLatin1String("angle")];
    if(property != Q_NULLPTR) {
        property->setValue(elemAngle);
    }
}

void ElementLine::setClickPosition(QPointF position)
{
    prepareGeometryChange();
    setElementXPos(static_cast<int>(position.x()));
    setElementYPos(static_cast<int>(position.y()));
    elementLine.setLine(0, 0, elementWidth, elementHeight);
    updatePropertyModel();
}

void ElementLine::updateBoundingElement()
{
    elementLine.setLine(0, 0, elementWidth, elementHeight);
}

void ElementLine::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
    painter->setPen(QPen(borderColor_, borderWidth_));
    painter->drawLine(elementLine);

    if (isSelected()) {
        setCursor(Qt::SizeAllCursor);
        painter->setBrush(Qt::red);
        painter->setPen(Qt::red);
        painter->drawRect(QRectF(elementLine.p1() - QPointF(3,3),elementLine.p1() + QPointF(3,3)));
        painter->drawRect(QRectF(elementLine.p2() - QPointF(3,3),elementLine.p2() + QPointF(3,3)));
    }
}

void ElementLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (resizing) {
        setCursor(Qt::SizeFDiagCursor);
        QPointF mousePoint = event->pos();
        switch (rd) {
        case RdBottomRight:
            elementLine.setP2(mousePoint);
            elementWidth = static_cast<int>(qAbs(elementLine.p1().x() - elementLine.p2().x()));
            elementHeight = static_cast<int>(qAbs(elementLine.p1().y() - elementLine.p2().y()));
            break;
        case RdTopLeft:
            elementLine.setP1(mousePoint);
            setElementXPos(static_cast<int>(mapToScene(elementLine.p1()).x()));
            setElementYPos(static_cast<int>(mapToScene(elementLine.p1()).y()));
            setElementWidth(static_cast<int>(qAbs(mapToScene(elementLine.p1()).x() - mapToScene(elementLine.p2()).x())));
            setElementHeight(static_cast<int>(qAbs(mapToScene(elementLine.p1()).y() - mapToScene(elementLine.p2()).y())));
            updateBoundingElement();
            break;
        case RdNone:
            QGraphicsObject::mouseMoveEvent(event);
            break;
        }

        scene()->update();
        return;
    } else {
        QGraphicsObject::mouseMoveEvent(event);
        // 限制矩形区域
        RestrictedRectangularRegion();
    }
}

void ElementLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePoint = event->pos();
    QPointF mouseHandler = QPointF(3,3);
    QPointF pp1 = elementLine.p1();
    QPointF pp2 = elementLine.p2();

    if (mousePoint.x() <= (pp1.x() + mouseHandler.x()) &&
        mousePoint.x() >= (pp1.x() - mouseHandler.x()) &&
        mousePoint.y() <= (pp1.y() + mouseHandler.y()) &&
        mousePoint.y() >= (pp1.y() - mouseHandler.y())) {
        rd = RdTopLeft;
        resizing = true;
        setCursor(Qt::SizeFDiagCursor);
    } else if (mousePoint.x() <= (pp2.x() + mouseHandler.x()) &&
             mousePoint.x() >= (pp2.x() - mouseHandler.x()) &&
             mousePoint.y() <= (pp2.y() + mouseHandler.y()) &&
             mousePoint.y() >= (pp2.y() - mouseHandler.y())) {
        rd = RdBottomRight;
        resizing = true;
        setCursor(Qt::SizeFDiagCursor);
    } else {
        resizing = false;
        rd = RdNone;
    }

    oldPos = pos();
    oldWidth = elementWidth;
    oldHeight = elementHeight;

    QGraphicsObject::mousePressEvent(event);
}

void ElementLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    elementXPos = static_cast<int>(pos().x());
    elementYPos = static_cast<int>(pos().y());
    updatePropertyModel();

    if (oldPos != pos()) {
        emit elementMoved(oldPos);
    }

    if (resizing) {
        emit elementResized(oldWidth,oldHeight,oldPos);
    }

    QGraphicsObject::mouseReleaseEvent(event);
}

void ElementLine::writeAsXml(QXmlStreamWriter &writer)
{
    writer.writeStartElement("element");
    writer.writeAttribute("internalType",internalElementType);
    writer.writeAttribute("elementId",elementId);
    writer.writeAttribute("x",QString::number(x()));
    writer.writeAttribute("y",QString::number(y()));
    writer.writeAttribute("z",QString::number(zValue()));
    writer.writeAttribute("width",QString::number(elementWidth));
    writer.writeAttribute("height",QString::number(elementHeight));
    writer.writeAttribute("borderWidth", QString::number(borderWidth_));
    writer.writeAttribute("borderColor", borderColor_.name());
    writer.writeAttribute("elemAngle", QString::number(elemAngle));
    writer.writeEndElement();
}

void ElementLine::readFromXml(const QXmlStreamAttributes &attributes)
{
    if (attributes.hasAttribute("elementId")) {
        QString szID = attributes.value("elementId").toString();
        setElementId(szID);
        int index = getIndexFromIDString(szID);
        if(iLastIndex_ < index) {
            iLastIndex_ = index;
        }
    }

    if (attributes.hasAttribute("x")) {
        setElementXPos(attributes.value("x").toString().toInt());
    }

    if (attributes.hasAttribute("y")) {
        setElementYPos(attributes.value("y").toString().toInt());
    }

    if (attributes.hasAttribute("z")) {
        setZValue(attributes.value("z").toString().toInt());
    }

    if (attributes.hasAttribute("width")) {
        setElementWidth(attributes.value("width").toString().toInt());
    }

    if (attributes.hasAttribute("height")) {
        setElementHeight(attributes.value("height").toString().toInt());
    }

    if (attributes.hasAttribute("borderWidth")) {
        borderWidth_ = attributes.value("borderWidth").toInt();
    }

    if (attributes.hasAttribute("borderColor")) {
        borderColor_ = QColor(attributes.value("borderColor").toString());
    }

    if (attributes.hasAttribute("elemAngle")) {
        setAngle(attributes.value("elemAngle").toString().toInt());
    }

    updateBoundingElement();
    updatePropertyModel();
}

void ElementLine::writeData(QDataStream &out)
{
    out << this->elementId
        << this->x()
        << this->y()
        << this->zValue()
        << this->elementWidth
        << this->elementHeight
        << this->borderWidth_
        << this->borderColor_
        << this->elemAngle;
}

void ElementLine::readData(QDataStream &in)
{
    QString id;
    qreal xpos;
    qreal ypos;
    qreal zvalue;
    int width;
    int height;
    int borderWidth;
    QColor borderColor;
    qreal angle;

    in >> id
       >> xpos
       >> ypos
       >> zvalue
       >> width
       >> height
       >> borderWidth
       >> borderColor
       >> angle;

    this->setElementId(id);
    int index = getIndexFromIDString(id);
    if(iLastIndex_ < index) {
        iLastIndex_ = index;
    }
    this->setElementXPos(static_cast<int>(xpos));
    this->setElementYPos(static_cast<int>(ypos));
    this->setElementZValue(static_cast<int>(zvalue));
    this->setElementWidth(width);
    this->setElementHeight(height);
    this->borderWidth_ = borderWidth;
    this->borderColor_ = borderColor;
    this->setAngle(angle);
    this->updateBoundingElement();
    this->updatePropertyModel();
}

QDataStream &operator<<(QDataStream &out,const ElementLine &line)
{
    out << line.elementId
        << line.x()
        << line.y()
        << line.zValue()
        << line.elementWidth
        << line.elementHeight
        << line.borderWidth_
        << line.borderColor_
        << line.elemAngle;

    return out;
}

QDataStream &operator>>(QDataStream &in,ElementLine &line)
{
    QString id;
    qreal xpos;
    qreal ypos;
    qreal zvalue;
    int width;
    int height;
    int borderWidth;
    QColor borderColor;
    qreal angle;

    in >> id
       >> xpos
       >> ypos
       >> zvalue
       >> width
       >> height
       >> borderWidth
       >> borderColor
       >> angle;

    line.setElementId(id);
    int index = line.getIndexFromIDString(id);
    if(line.iLastIndex_ < index) {
        line.iLastIndex_ = index;
    }
    line.setElementXPos(static_cast<int>(xpos));
    line.setElementYPos(static_cast<int>(ypos));
    line.setElementZValue(static_cast<int>(zvalue));
    line.setElementWidth(width);
    line.setElementHeight(height);
    line.borderWidth_ = borderWidth;
    line.borderColor_ = borderColor;
    line.setAngle(angle);
    line.updateBoundingElement();
    line.updatePropertyModel();

    return in;
}
