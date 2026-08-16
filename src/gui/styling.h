#pragma once

#include "oscillator.h"

class QApplication;
class QIcon;

namespace Styling {

void apply(QApplication& app);
QIcon makeWaveIcon(Oscillator::Waveforms w);

}