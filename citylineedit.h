#ifndef CITYLINEEDIT_H
#define CITYLINEEDIT_H

#include <QKeyEvent>
#include <QLineEdit>



class CityLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit CityLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) {}

signals:
    void enterKeyPressed();

protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            if (hasFocus())
            {
                emit enterKeyPressed();
            }
        }
        else
        {
            QLineEdit::keyPressEvent(event);
        }

    }
};

#endif // CITYLINEEDIT_H
