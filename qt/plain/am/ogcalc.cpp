#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "SpinBoxEntry.h"

#include <sstream>
#include <iomanip>

#include "ogcalc.h"

ogcalc::ogcalc (QWidget *parent):
  QMainWindow(parent)
{
  setupUi();
}

ogcalc::~ogcalc ()
{
}

void
ogcalc::setupUi ()
{
  QWidget *toplevel_layout;
  QVBoxLayout *vertical_layout;
  QHBoxLayout *entry_layout;
  QHBoxLayout *pg_layout;
  QHBoxLayout *ri_layout;
  QHBoxLayout *cf_layout;
  QHBoxLayout *result_layout;
  QHBoxLayout *og_layout;
  QHBoxLayout *abv_layout;
  QHBoxLayout *button_layout;

  if (objectName().isEmpty())
    setObjectName(QStringLiteral("ogcalc"));
  resize(407, 123);
  QSizePolicy sp1(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sp1.setHorizontalStretch(0);
  sp1.setVerticalStretch(0);
  sp1.setHeightForWidth(sizePolicy().hasHeightForWidth());
  setSizePolicy(sp1);
  setMaximumSize(QSize(16777215, 16777215));
  QIcon icon;
  icon.addFile(QStringLiteral("ogcalc.svg"), QSize(), QIcon::Normal, QIcon::Off);
  setWindowIcon(icon);
  toplevel_layout = new QWidget(this);
  toplevel_layout->setObjectName(QStringLiteral("toplevel_layout"));
  QSizePolicy sp2(QSizePolicy::Minimum, QSizePolicy::Minimum);
  sp2.setHorizontalStretch(0);
  sp2.setVerticalStretch(0);
  sp2.setHeightForWidth(toplevel_layout->sizePolicy().hasHeightForWidth());
  toplevel_layout->setSizePolicy(sp2);
  vertical_layout = new QVBoxLayout(toplevel_layout);
  vertical_layout->setSpacing(6);
  vertical_layout->setContentsMargins(11, 11, 11, 11);
  vertical_layout->setObjectName(QStringLiteral("vertical_layout"));
  entry_layout = new QHBoxLayout();
  entry_layout->setSpacing(6);
  entry_layout->setObjectName(QStringLiteral("entry_layout"));
  pg_layout = new QHBoxLayout();
  pg_layout->setSpacing(6);
  pg_layout->setObjectName(QStringLiteral("pg_layout"));
  pg_label = new QLabel(toplevel_layout);
  pg_label->setObjectName(QStringLiteral("pg_label"));
  QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
  sizePolicy2.setHorizontalStretch(0);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(pg_label->sizePolicy().hasHeightForWidth());
  pg_label->setSizePolicy(sizePolicy2);
  pg_label->setTextFormat(Qt::AutoText);

  pg_layout->addWidget(pg_label);

  pg_entry = new SpinBoxEntry(toplevel_layout);
  pg_entry->setObjectName(QStringLiteral("pg_entry"));
  QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(pg_entry->sizePolicy().hasHeightForWidth());
  pg_entry->setSizePolicy(sizePolicy3);

  pg_layout->addWidget(pg_entry);


  entry_layout->addLayout(pg_layout);

  ri_layout = new QHBoxLayout();
  ri_layout->setSpacing(6);
  ri_layout->setObjectName(QStringLiteral("ri_layout"));
  ri_label = new QLabel(toplevel_layout);
  ri_label->setObjectName(QStringLiteral("ri_label"));
  sizePolicy2.setHeightForWidth(ri_label->sizePolicy().hasHeightForWidth());
  ri_label->setSizePolicy(sizePolicy2);

  ri_layout->addWidget(ri_label);

  ri_entry = new SpinBoxEntry(toplevel_layout);
  ri_entry->setObjectName(QStringLiteral("ri_entry"));
  sizePolicy3.setHeightForWidth(ri_entry->sizePolicy().hasHeightForWidth());
  ri_entry->setSizePolicy(sizePolicy3);

  ri_layout->addWidget(ri_entry);


  entry_layout->addLayout(ri_layout);

  cf_layout = new QHBoxLayout();
  cf_layout->setSpacing(6);
  cf_layout->setObjectName(QStringLiteral("cf_layout"));
  cf_label = new QLabel(toplevel_layout);
  cf_label->setObjectName(QStringLiteral("cf_label"));
  sizePolicy2.setHeightForWidth(cf_label->sizePolicy().hasHeightForWidth());
  cf_label->setSizePolicy(sizePolicy2);

  cf_layout->addWidget(cf_label);

  cf_entry = new SpinBoxEntry(toplevel_layout);
  cf_entry->setObjectName(QStringLiteral("cf_entry"));
  sizePolicy3.setHeightForWidth(cf_entry->sizePolicy().hasHeightForWidth());
  cf_entry->setSizePolicy(sizePolicy3);

  cf_layout->addWidget(cf_entry);


  entry_layout->addLayout(cf_layout);


  vertical_layout->addLayout(entry_layout);

  result_layout = new QHBoxLayout();
  result_layout->setSpacing(6);
  result_layout->setObjectName(QStringLiteral("result_layout"));
  og_layout = new QHBoxLayout();
  og_layout->setSpacing(6);
  og_layout->setObjectName(QStringLiteral("og_layout"));
  og_label = new QLabel(toplevel_layout);
  og_label->setObjectName(QStringLiteral("og_label"));
  sizePolicy2.setHeightForWidth(og_label->sizePolicy().hasHeightForWidth());
  og_label->setSizePolicy(sizePolicy2);

  og_layout->addWidget(og_label);

  og_result = new QLabel(toplevel_layout);
  og_result->setObjectName(QStringLiteral("og_result"));
  QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
  sizePolicy4.setHorizontalStretch(0);
  sizePolicy4.setVerticalStretch(0);
  sizePolicy4.setHeightForWidth(og_result->sizePolicy().hasHeightForWidth());
  og_result->setSizePolicy(sizePolicy4);
  QFont font;
  font.setBold(true);
  font.setWeight(75);
  og_result->setFont(font);
  og_result->setAlignment(Qt::AlignCenter);
  og_result->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

  og_layout->addWidget(og_result);


  result_layout->addLayout(og_layout);

  abv_layout = new QHBoxLayout();
  abv_layout->setSpacing(6);
  abv_layout->setObjectName(QStringLiteral("abv_layout"));
  abv_entry = new QLabel(toplevel_layout);
  abv_entry->setObjectName(QStringLiteral("abv_entry"));
  sizePolicy2.setHeightForWidth(abv_entry->sizePolicy().hasHeightForWidth());
  abv_entry->setSizePolicy(sizePolicy2);

  abv_layout->addWidget(abv_entry);

  abv_result = new QLabel(toplevel_layout);
  abv_result->setObjectName(QStringLiteral("abv_result"));
  sizePolicy4.setHeightForWidth(abv_result->sizePolicy().hasHeightForWidth());
  abv_result->setSizePolicy(sizePolicy4);
  abv_result->setFont(font);
  abv_result->setAlignment(Qt::AlignCenter);
  abv_result->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

  abv_layout->addWidget(abv_result);


  result_layout->addLayout(abv_layout);


  vertical_layout->addLayout(result_layout);

  button_layout = new QHBoxLayout();
  button_layout->setSpacing(6);
  button_layout->setObjectName(QStringLiteral("button_layout"));
  quit_button = new QPushButton(toplevel_layout);
  quit_button->setObjectName(QStringLiteral("quit"));

  button_layout->addWidget(quit_button);

  reset_button = new QPushButton(toplevel_layout);
  reset_button->setObjectName(QStringLiteral("reset"));
  reset_button->setAutoDefault(true);

  button_layout->addWidget(reset_button);

  calculate_button = new QPushButton(toplevel_layout);
  calculate_button->setObjectName(QStringLiteral("calculate"));
  calculate_button->setAutoDefault(true);
  calculate_button->setDefault(true);

  button_layout->addWidget(calculate_button);


  vertical_layout->addLayout(button_layout);

  setCentralWidget(toplevel_layout);
#ifndef QT_NO_SHORTCUT
  pg_label->setBuddy(pg_entry);
  ri_label->setBuddy(ri_entry);
  cf_label->setBuddy(cf_entry);
#endif // QT_NO_SHORTCUT

  retranslateUi();
  QObject::connect(reset_button, SIGNAL(clicked()), this, SLOT(reset()));
  QObject::connect(quit_button, SIGNAL(clicked()), this, SLOT(close()));
  QObject::connect(calculate_button, SIGNAL(clicked()), this, SLOT(calculate()));
  QObject::connect(calculate_button, SIGNAL(clicked()), reset_button, SLOT(setFocus()));
  QObject::connect(pg_entry, SIGNAL(enterPressed()), ri_entry, SLOT(setFocus()));
  QObject::connect(ri_entry, SIGNAL(enterPressed()), cf_entry, SLOT(setFocus()));
  QObject::connect(cf_entry, SIGNAL(enterPressed()), calculate_button, SLOT(click()));
  QObject::connect(pg_entry, SIGNAL(enterPressed()), ri_entry, SLOT(selectAll()));
  QObject::connect(ri_entry, SIGNAL(enterPressed()), cf_entry, SLOT(selectAll()));

  QMetaObject::connectSlotsByName(this);
}

void
ogcalc::retranslateUi ()
{
  setWindowTitle(QApplication::translate("ogcalc", "OG & ABV calculator", 0));

  pg_label->setToolTip(QApplication::translate("ogcalc", "Present Gravity (density)", 0));
  pg_label->setText(QApplication::translate("ogcalc", "&PG:", 0));

  pg_entry->setSpecialValueText(QApplication::translate("ogcalc", "0.00", 0));
  pg_entry->setPrefix(QString());

  ri_label->setToolTip(QApplication::translate("ogcalc", "Refractive Index", 0));
  ri_label->setText(QApplication::translate("ogcalc", "R&I:", 0));

  cf_label->setToolTip(QApplication::translate("ogcalc", "Correction Factor", 0));
  cf_label->setText(QApplication::translate("ogcalc", "C&F:", 0));

  og_label->setToolTip(QApplication::translate("ogcalc", "Original Gravity (density)", 0));
  og_label->setText(QApplication::translate("ogcalc", "OG:", 0));
  og_result->setText(QApplication::translate("ogcalc", "OGVAL", 0));

  abv_entry->setToolTip(QApplication::translate("ogcalc", "Percent Alcohol By Volume", 0));
  abv_entry->setText(QApplication::translate("ogcalc", "ABV %:", 0));
  abv_result->setText(QApplication::translate("ogcalc", "ABVVAL", 0));

  quit_button->setText(QApplication::translate("ogcalc", "&Quit", 0));
  reset_button->setText(QApplication::translate("ogcalc", "&Reset", 0));
  calculate_button->setText(QApplication::translate("ogcalc", "&Calculate", 0));
}

void
ogcalc::calculate ()
{
  // PG, RI, and CF values.
  double pg = pg_entry->value();
  double ri = ri_entry->value();
  double cf = cf_entry->value();

  // Calculate OG.
  double og = (ri * 2.597) - (pg * 1.644) - 34.4165 + cf;

  // Calculate ABV.
  double abv;
  if (og < 60)
    abv = (og - pg) * 0.130;
  else
    abv = (og - pg) * 0.134;

  std::ostringstream output;
  // Use the user's locale for this stream.
  output.imbue(std::locale(""));
  output << std::fixed << std::setprecision(2) << og;
  og_result->setText(QString::fromStdString(output.str()));
  output.str("");
  output << std::fixed << std::setprecision(2) << abv;
  abv_result->setText(QString::fromStdString(output.str()));

  reset_button->setDefault(true);
  calculate_button->setDefault(false);
}

void
ogcalc::reset ()
{
  pg_entry->setValue(0.0);
  ri_entry->setValue(0.0);
  cf_entry->setValue(0.0);
  og_result->setText("");
  abv_result->setText("");

  pg_entry->setFocus();
  pg_entry->selectAll();
  reset_button->setDefault(false);
  calculate_button->setDefault(true);
}
