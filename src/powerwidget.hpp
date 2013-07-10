#ifndef POWERWIDGET_HPP
#define POWERWIDGET_HPP

#include <QWidget>

#include <inttypes.h>

/**
* \brief A basic widget representing power and maximum power available.
*
* Can be read-only or set the value.
*/
class PowerWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
    Q_PROPERTY(uint8_t value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(uint8_t max READ max WRITE setMax)

public:
    explicit PowerWidget(QWidget *parent = 0);

    uint8_t value() const;
    uint8_t max() const;

    bool isReadOnly() const;

    void setReadOnly(bool readOnly);
    
signals:
    void valueChanged(uint8_t);

public slots:
    void setValue(uint8_t);
    void setMax(uint8_t);

protected:
    virtual void paintEvent(QPaintEvent* evt);
    virtual void mousePressEvent(QMouseEvent* evt);

private:
    bool m_readOnly;
    uint8_t m_value;
    uint8_t m_max;
};

#endif // POWERWIDGET_HPP
