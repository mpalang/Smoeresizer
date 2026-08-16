#include "widgets.h"

MySpinBox::MySpinBox(QWidget* parent)
    : QSpinBox(parent)
{
    setFixedWidth(60);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setStyleSheet(
        "QSpinBox::up-button {"
        "  subcontrol-origin: border;"
        "  subcontrol-position: top right;"
        "  width: 20px;"
        "  height: 12px;"
        "}"
        "QSpinBox::down-button {"
        "  subcontrol-origin: border;"
        "  subcontrol-position: bottom right;"
        "  width: 20px;"
        "  height: 12px;"
        "}"
    );
}