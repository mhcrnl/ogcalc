from PyQt5.QtCore import (Qt, pyqtSignal)
from PyQt5.QtWidgets import (QDoubleSpinBox)

class SpinBoxEntry(QDoubleSpinBox):
    def __init__(self, parent = None):
        super(SpinBoxEntry, self).__init__(parent)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Enter or event.key() == Qt.Key_Return:
            self.enterPressed.emit()
        else:
            super(SpinBoxEntry, self).keyPressEvent(event)

    enterPressed = pyqtSignal()
