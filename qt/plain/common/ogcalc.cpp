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
  // Initialise the interface
  setupUi();

  // Set interface to initial state.
  reset();
}

ogcalc::~ogcalc ()
{
}

void
ogcalc::setupUi ()
{
  // Widgets only referenced during interface initialisation.  Widgets
  // needed after initialisation are class members.
  QWidget     *toplevel_layout;
  QVBoxLayout *vertical_layout;
  QHBoxLayout *entry_layout;
  QHBoxLayout *pg_layout;
  QHBoxLayout *ri_layout;
  QHBoxLayout *cf_layout;
  QHBoxLayout *result_layout;
  QHBoxLayout *og_layout;
  QHBoxLayout *abv_layout;
  QFrame      *line;
  QHBoxLayout *button_layout;

  // Set initial window size and size policy.
  resize(407, 123);
  {
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHorizontalStretch(0);
    sp.setVerticalStretch(0);
    sp.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sp);
  }
  setMaximumSize(QSize(16777215, 16777215));

  // Load and set the window icon.
  QIcon icon;
  icon.addFile(QStringLiteral("ogcalc.svg"), QSize(), QIcon::Normal, QIcon::Off);
  setWindowIcon(icon);

  // Top level layout and size policy for all window content.
  toplevel_layout = new QWidget(this);
  {
    QSizePolicy sp(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sp.setHorizontalStretch(0);
    sp.setVerticalStretch(0);
    sp.setHeightForWidth(toplevel_layout->sizePolicy().hasHeightForWidth());
    toplevel_layout->setSizePolicy(sp);
  }

  // Vertical layout for containing widgets at the top level.
  vertical_layout = new QVBoxLayout(toplevel_layout);
  vertical_layout->setSpacing(6);
  vertical_layout->setContentsMargins(11, 11, 11, 11);

  // Size policy for labels (minimum size).
  QSizePolicy label_size_policy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  label_size_policy.setHorizontalStretch(0);
  label_size_policy.setVerticalStretch(0);
  label_size_policy.setHeightForWidth(false);

  // Size policy for entry boxes (expand horizontally, fixed vertically).
  QSizePolicy entry_size_policy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  entry_size_policy.setHorizontalStretch(0);
  entry_size_policy.setVerticalStretch(0);
  entry_size_policy.setHeightForWidth(false);

  // Size policy for result labels (expand horizontally, can be expanded
  // vertically if needed).
  QSizePolicy result_size_policy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  result_size_policy.setHorizontalStretch(0);
  result_size_policy.setVerticalStretch(0);
  result_size_policy.setHeightForWidth(false);

  // We'll start by creating the top row of entry widgets.

  // Horizontal layout to contain entry widgets.
  entry_layout = new QHBoxLayout();
  entry_layout->setSpacing(6);

  // Horizontal layout for PG.
  pg_layout = new QHBoxLayout();
  pg_layout->setSpacing(6);

  // Create label widget for PG and add to PG layout.
  pg_label = new QLabel(toplevel_layout);
  pg_label->setSizePolicy(label_size_policy);
  pg_label->setTextFormat(Qt::AutoText);
  pg_layout->addWidget(pg_label);

  // Create entry widget for PG and add to PG layout.
  pg_entry = new SpinBoxEntry(toplevel_layout);
  pg_entry->setSizePolicy(entry_size_policy);
  pg_layout->addWidget(pg_entry);

  // Add PG layout to entry layout.
  entry_layout->addLayout(pg_layout);

  // Repeat for RI layout.
  ri_layout = new QHBoxLayout();
  ri_layout->setSpacing(6);

  ri_label = new QLabel(toplevel_layout);
  ri_label->setSizePolicy(label_size_policy);
  ri_layout->addWidget(ri_label);

  ri_entry = new SpinBoxEntry(toplevel_layout);
  ri_entry->setSizePolicy(entry_size_policy);
  ri_layout->addWidget(ri_entry);

  entry_layout->addLayout(ri_layout);

  // Repeat for CF layout.
  cf_layout = new QHBoxLayout();
  cf_layout->setSpacing(6);

  cf_label = new QLabel(toplevel_layout);
  cf_label->setSizePolicy(label_size_policy);
  cf_layout->addWidget(cf_label);

  cf_entry = new SpinBoxEntry(toplevel_layout);
  cf_entry->setSizePolicy(entry_size_policy);
  cf_layout->addWidget(cf_entry);

  entry_layout->addLayout(cf_layout);

  // Add the entry layout to the vertical layout.
  vertical_layout->addLayout(entry_layout);

  // Next, we'll create a second row of result widgets.

  // A new horizontal layout to contain the widgets for this row.
  result_layout = new QHBoxLayout();
  result_layout->setSpacing(6);

  // Create a horizontal layout for the OG result.
  og_layout = new QHBoxLayout();
  og_layout->setSpacing(6);

  // Create a descriptive label for the OG result and add it to the OG
  // layout.
  og_label = new QLabel(toplevel_layout);
  og_label->setSizePolicy(label_size_policy);
  og_layout->addWidget(og_label);

  // Create a result label for the OG result and add it to the OG
  // layout.  This will additionally be displayed using a bold font,
  // centred, which is also selectable using the mouse or keyboard (so
  // the result value can be copied and pasted elsewhere).  Add to the
  // OG layout.
  og_result = new QLabel(toplevel_layout);
  og_result->setSizePolicy(result_size_policy);
  QFont font;
  font.setBold(true);
  font.setWeight(75);
  og_result->setFont(font);
  og_result->setAlignment(Qt::AlignCenter);
  og_result->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
  og_layout->addWidget(og_result);

  // Add the OG layout to the result layout.
  result_layout->addLayout(og_layout);

  // Repeat for the ABV result.
  abv_layout = new QHBoxLayout();
  abv_layout->setSpacing(6);

  abv_label = new QLabel(toplevel_layout);
  abv_label->setSizePolicy(label_size_policy);
  abv_layout->addWidget(abv_label);

  abv_result = new QLabel(toplevel_layout);
  abv_result->setSizePolicy(result_size_policy);
  abv_result->setFont(font);
  abv_result->setAlignment(Qt::AlignCenter);
  abv_result->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
  abv_layout->addWidget(abv_result);

  result_layout->addLayout(abv_layout);

  // Add the result layout as the second row in the vertical layout.
  vertical_layout->addLayout(result_layout);

  // Next, add a vertical line to separate the entry fields and
  // results from the bottom row of buttons.

  // Create the line setting to to a single pixel width, of type
  // horizontal line.  Add this as the third row of the vertical
  // layout.
  line = new QFrame(toplevel_layout);
  line->setFrameShadow(QFrame::Sunken);
  line->setLineWidth(1);
  line->setMidLineWidth(0);
  line->setFrameShape(QFrame::HLine);
  vertical_layout->addWidget(line);

  // Lastly, create a row of buttons.

  // As before, create a horizontal layout to contain the row.
  button_layout = new QHBoxLayout();
  button_layout->setSpacing(6);

  // Create a button and add to the horizontal layout.
  quit_button = new QPushButton(toplevel_layout);
  button_layout->addWidget(quit_button);

  // Repeat the button creation, but this button may become the
  // default.
  reset_button = new QPushButton(toplevel_layout);
  reset_button->setAutoDefault(true);
  button_layout->addWidget(reset_button);

  // Repeat the button creation, but this button may become the
  // default and additionally is the initial default.
  calculate_button = new QPushButton(toplevel_layout);
  calculate_button->setAutoDefault(true);
  calculate_button->setDefault(true);
  button_layout->addWidget(calculate_button);

  // Add the buttons to the vertical layout as the fourth row.
  vertical_layout->addLayout(button_layout);

  // Set the toplevel layout as the main window central widget.
  setCentralWidget(toplevel_layout);

  // Set the entry widgets as "buddies" of their corresponding labels.
  // This enables the use of keyboard shortcuts (alt-letter) to switch
  // focus to the entry widgets.  Mac users are forbidden to have this
  // feature; Windows users can enable them in the control panel.
  // Enabled by default on Linux.
#ifndef QT_NO_SHORTCUT
  pg_label->setBuddy(pg_entry);
  ri_label->setBuddy(ri_entry);
  cf_label->setBuddy(cf_entry);
#endif // QT_NO_SHORTCUT

  // The labels and buttons haven't yet been assigned any text; this
  // function adds the text in the user's native language.
  retranslateUi();

  // Connect signals to signal handlers (slots).  The parameters of
  // the connect function here are: (1) the object emitting the
  // signal, (2) the signal being emitted, (3) the object receiving
  // the signal and (4) the method to call on the receiving object.

  // When the Reset reset_button button is clicked, the "clicked"
  // signal is emitted, triggering a call of the reset() method on
  // ourselves (since the receiving object is this).
  QObject::connect(reset_button, SIGNAL(clicked()), this, SLOT(reset()));

  // Likewise, the Quit button calls close()
  QObject::connect(quit_button, SIGNAL(clicked()), this, SLOT(close()));

  // The calculate button calls two methods in the order defined.
  // Firstly the calculate() method, and then the setFocus() method of
  // the reset_button widget so that the reset button gets focus.
  QObject::connect(calculate_button, SIGNAL(clicked()), this, SLOT(calculate()));
  QObject::connect(calculate_button, SIGNAL(clicked()), reset_button, SLOT(setFocus()));

  // Pressing Enter when in the PG entry will cause the RI entry to
  // get the focus, and for its contents to be selected.
  QObject::connect(pg_entry, SIGNAL(enterPressed()), ri_entry, SLOT(setFocus()));
  QObject::connect(pg_entry, SIGNAL(enterPressed()), ri_entry, SLOT(selectAll()));

  // Likewise for Enter in the RI entry setting focus to the CF entry
  // and selecting its contents.
  QObject::connect(ri_entry, SIGNAL(enterPressed()), cf_entry, SLOT(setFocus()));
  QObject::connect(ri_entry, SIGNAL(enterPressed()), cf_entry, SLOT(selectAll()));

  // Pressing Enter in the CF entry will trigger the click() method of
  // the Calculate button (that is, it will perform the same action
  // that clicking the button by hand would do).
  QObject::connect(cf_entry, SIGNAL(enterPressed()), calculate_button, SLOT(click()));

  // Auto-connect signals to slots with the matching name.  Not
  // actually used in this example, but left here to inform.
  QMetaObject::connectSlotsByName(this);
}

void
ogcalc::retranslateUi ()
{
  // Set the main window title.
  setWindowTitle(QApplication::translate("ogcalc", "OG & ABV calculator", 0));

  // Set tooltips for all descriptive labels.
#ifndef QT_NO_TOOLTIP
  pg_label->setToolTip(QApplication::translate("ogcalc", "Present Gravity (density)", 0));
  ri_label->setToolTip(QApplication::translate("ogcalc", "Refractive Index", 0));
  cf_label->setToolTip(QApplication::translate("ogcalc", "Correction Factor", 0));
  og_label->setToolTip(QApplication::translate("ogcalc", "Original Gravity (density)", 0));
  abv_label->setToolTip(QApplication::translate("ogcalc", "Percent Alcohol By Volume", 0));
#endif // QT_NO_TOOLTIP

  // Set descriptive label text.  Note the '&'s.  "&P" will cause the
  // 'P' to be underlined, and Alt-P will switch focus to the "buddy"
  // of the label.
  pg_label->setText(QApplication::translate("ogcalc", "&PG:", 0));
  ri_label->setText(QApplication::translate("ogcalc", "R&I:", 0));
  cf_label->setText(QApplication::translate("ogcalc", "C&F:", 0));
  og_label->setText(QApplication::translate("ogcalc", "OG:", 0));
  abv_label->setText(QApplication::translate("ogcalc", "ABV %:", 0));

  // Set button text.  Note again the use of '&' which will also allow
  // the use of Alt-letter to click the button using the keyboard.
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

  // Display the results.
  std::ostringstream output;
  // Use the user's locale for this stream.
  output.imbue(std::locale(""));
  output << std::fixed << std::setprecision(2) << og;
  og_result->setText(QString::fromStdString(output.str()));
  output.str("");
  output << std::fixed << std::setprecision(2) << abv;
  abv_result->setText(QString::fromStdString(output.str()));

  // Reset is the default action after calculation
  reset_button->setDefault(true);
  calculate_button->setDefault(false);
}

void
ogcalc::reset ()
{
  // Reset entry widgets to default state.
  pg_entry->setValue(0.0);
  ri_entry->setValue(0.0);

  // Clear results.
  cf_entry->setValue(0.0);
  og_result->setText("");
  abv_result->setText("");

  // Move focus back to the PG entry.
  pg_entry->setFocus();
  pg_entry->selectAll();

  // Calculate is the default action during entry.
  reset_button->setDefault(false);
  calculate_button->setDefault(true);
}
