#include <QDesignerCustomWidgetInterface>

class SpinBoxEntryPlugin : public QObject,
                     public QDesignerCustomWidgetInterface
{
  Q_OBJECT;
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "SpinBoxEntryPlugin.json");
  Q_INTERFACES(QDesignerCustomWidgetInterface);

public:
  SpinBoxEntryPlugin();
  virtual ~SpinBoxEntryPlugin();

  QWidget * 	createWidget ( QWidget * parent );

  QString 	group () const;
  QIcon 	icon () const;
  QString 	includeFile () const;

  bool 	isContainer () const;

  QString 	name () const;
  QString 	toolTip () const;
  QString 	whatsThis () const;
};

/*
 * Local Variables:
 * mode:C++
 * fill-column:60
 * End:
 */
