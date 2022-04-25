
#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H

#include <memory>
#include <QQuickItem>

class SevenSegmentDisplayPrivate;

/** QQuick widget that implements a seven-segment display. */
class SevenSegmentDisplay : public QQuickItem
{
    Q_OBJECT

	/** Property that controls the count of digits. */
	Q_PROPERTY(int digitCount READ getDigitCount WRITE setDigitCount NOTIFY digitCountChanged)

	/** Property that controls the current value shown by the widget. */
	Q_PROPERTY(double value READ getValue WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(QString string READ getString WRITE setString NOTIFY stringChanged)

	Q_PROPERTY(int precision READ getPrecision WRITE setPrecision NOTIFY precisionChanged)
    /** Property that controls the digit height. */
	Q_PROPERTY(int digitSize READ getDigitSize WRITE setDigitSize NOTIFY digitSizeChanged)

	Q_ENUMS(Alignment)
	/** Property that controls the vertical alignment. */
	Q_PROPERTY(Alignment verticalAlignment READ getVerticalAlignment WRITE setVerticalAlignment NOTIFY verticalAlignmentChanged)
	/** Property that controls the horizontal alignment. */
	Q_PROPERTY(Alignment horizontalAlignment READ getHorizontalAlignment WRITE setHorizontalAlignment NOTIFY horizontalAlignmentChanged)

	/** Property that controls the background color. */
	Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor NOTIFY bgColorChanged)
	/** Property that controls the color of enabled segments. */
	Q_PROPERTY(QColor onColor READ getOnColor WRITE setOnColor NOTIFY onColorChanged)
	/** Property that controls the color of disabled segments. */
	Q_PROPERTY(QColor offColor READ getOffColor WRITE setOffColor NOTIFY offColorChanged)

public:
	/** Alignment options. */
	enum Alignment
	{
		AlignLeft,  //!< AlignLeft
		AlignTop,   //!< AlignTop
		AlignCenter,//!< AlignCenter
	};

  SevenSegmentDisplay(QQuickItem* parent = nullptr);
  virtual ~SevenSegmentDisplay();

  int getDigitCount() const;
  void setDigitCount(int count);

  double getValue() const;
  void setValue(double value);

  QString getString() const;
  void setString(QString string);

  int getPrecision() const;
  void setPrecision(int precision);

  int getDigitSize() const;
  void setDigitSize(int size);

  Alignment getVerticalAlignment() const;
  void setVerticalAlignment(Alignment alignment);

  Alignment getHorizontalAlignment() const;
  void setHorizontalAlignment(Alignment alignment);

  QColor getBgColor() const;
  void setBgColor(const QColor& color);

  QColor getOnColor() const;
  void setOnColor(const QColor& color);

  QColor getOffColor() const;
  void setOffColor(const QColor& color);

signals:
	void digitCountChanged();
	void valueChanged();
	void stringChanged();
	void precisionChanged();
	void digitSizeChanged();
	void verticalAlignmentChanged();
	void horizontalAlignmentChanged();
	void bgColorChanged();
	void onColorChanged();
	void offColorChanged();

	/** Emitted on value overflow or when passed string need more literals than configured in digitCount. */
	void overflow();

protected:
    QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*);

private:
	QScopedPointer<SevenSegmentDisplayPrivate> d_ptr;
  Q_DECLARE_PRIVATE(SevenSegmentDisplay)
  Q_DISABLE_COPY(SevenSegmentDisplay)
};

#endif // SEVENSEGMENTDISPLAY_H
