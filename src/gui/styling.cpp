#include "styling.h"

#include <QApplication>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>

#include "oscillator.h"

namespace Styling {

namespace {

const char* personalStyle =
    "";

}

void apply(QApplication& app)
{
    app.setStyleSheet(QString());
}

QIcon makeWaveIcon(Oscillator::Waveforms w)
{
    QPixmap pm(32, 20);
    pm.fill(Qt::transparent);

    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::white, 1.5));

    Oscillator osc(32.0);            // one cycle across 32 samples
    osc.setFrequency(1.0);
    osc.setWaveform(w);

    QPainterPath path;
    for (int x = 0; x < 32; ++x) {
        const double y = 10.0 - osc.nextSample() * 8.0;
        if (x == 0) path.moveTo(x, y);
        else        path.lineTo(x, y);
    }
    p.drawPath(path);

    return QIcon(pm);
}

}  // namespace Styling