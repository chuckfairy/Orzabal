/**
 *
 */
#include <QHBoxLayout>
#include "MainWindow.h"

//  note that we call the superclass constructor here and pass on the arguments
MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {

    UI.setupUi(this);

    dropdown = new InstrumentDropdown();

    UI.horizontalLayout_3->addWidget( dropdown );

}
