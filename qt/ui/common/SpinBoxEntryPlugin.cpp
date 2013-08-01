#include <QtCore/qplugin.h>

#include "SpinBoxEntry.h"
#include "SpinBoxEntryPlugin.h"

SpinBoxEntryPlugin::SpinBoxEntryPlugin()
{
}

SpinBoxEntryPlugin::~SpinBoxEntryPlugin()
{
}

QWidget *
SpinBoxEntryPlugin::createWidget ( QWidget * parent )
{
  return new SpinBoxEntry(parent);
}

QString
SpinBoxEntryPlugin::group () const
{
  return "ogcalc";
}

QIcon
SpinBoxEntryPlugin::icon () const
{
  QIcon icon;
  icon.addFile(QStringLiteral("ogcalc.svg"), QSize(), QIcon::Normal, QIcon::Off);
  return icon;
}

QString
SpinBoxEntryPlugin::includeFile () const
{
  return "SpinBoxEntry.h";
}

bool
SpinBoxEntryPlugin::isContainer () const
{
  return false;
}

QString SpinBoxEntryPlugin::name () const
{
  return "SpinBoxEntry";
}

QString
SpinBoxEntryPlugin::toolTip () const
{
  return "Enhanced double spin entry";
}

QString
SpinBoxEntryPlugin::whatsThis () const
{
  return "Enhanced double spin entry";
}
