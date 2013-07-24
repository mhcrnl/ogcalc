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

#include "ogcalc.h"

#include <sstream>
#include <iomanip>

ogcalc::ogcalc(QWidget *parent) :
    QMainWindow(parent)
{
}

void
ogcalc::setupUi()
{
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;

        if (objectName().isEmpty())
            setObjectName(QStringLiteral("ogcalc"));
        resize(407, 123);
        QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sp.setHorizontalStretch(0);
        sp.setVerticalStretch(0);
        sp.setHeightForWidth(sizePolicy().hasHeightForWidth());
        setSizePolicy(sp);
        setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral("ogcalc.svg"), QSize(), QIcon::Normal, QIcon::Off);
        setWindowIcon(icon);
        centralWidget = new QWidget(this);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pg_label = new QLabel(centralWidget);
        pg_label->setObjectName(QStringLiteral("pg_label"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pg_label->sizePolicy().hasHeightForWidth());
        pg_label->setSizePolicy(sizePolicy2);
        pg_label->setTextFormat(Qt::AutoText);

        horizontalLayout_7->addWidget(pg_label);

        pg_entry = new SpinBoxEntry(centralWidget);
        pg_entry->setObjectName(QStringLiteral("pg_entry"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pg_entry->sizePolicy().hasHeightForWidth());
        pg_entry->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(pg_entry);


        horizontalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        ri_label = new QLabel(centralWidget);
        ri_label->setObjectName(QStringLiteral("ri_label"));
        sizePolicy2.setHeightForWidth(ri_label->sizePolicy().hasHeightForWidth());
        ri_label->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(ri_label);

        ri_entry = new SpinBoxEntry(centralWidget);
        ri_entry->setObjectName(QStringLiteral("ri_entry"));
        sizePolicy3.setHeightForWidth(ri_entry->sizePolicy().hasHeightForWidth());
        ri_entry->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(ri_entry);


        horizontalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        cf_label = new QLabel(centralWidget);
        cf_label->setObjectName(QStringLiteral("cf_label"));
        sizePolicy2.setHeightForWidth(cf_label->sizePolicy().hasHeightForWidth());
        cf_label->setSizePolicy(sizePolicy2);

        horizontalLayout_9->addWidget(cf_label);

        cf_entry = new SpinBoxEntry(centralWidget);
        cf_entry->setObjectName(QStringLiteral("cf_entry"));
        sizePolicy3.setHeightForWidth(cf_entry->sizePolicy().hasHeightForWidth());
        cf_entry->setSizePolicy(sizePolicy3);

        horizontalLayout_9->addWidget(cf_entry);


        horizontalLayout->addLayout(horizontalLayout_9);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        og_label = new QLabel(centralWidget);
        og_label->setObjectName(QStringLiteral("og_label"));
        sizePolicy2.setHeightForWidth(og_label->sizePolicy().hasHeightForWidth());
        og_label->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(og_label);

        og_result = new QLabel(centralWidget);
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

        horizontalLayout_4->addWidget(og_result);


        horizontalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        abv_entry = new QLabel(centralWidget);
        abv_entry->setObjectName(QStringLiteral("abv_entry"));
        sizePolicy2.setHeightForWidth(abv_entry->sizePolicy().hasHeightForWidth());
        abv_entry->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(abv_entry);

        abv_result = new QLabel(centralWidget);
        abv_result->setObjectName(QStringLiteral("abv_result"));
        sizePolicy4.setHeightForWidth(abv_result->sizePolicy().hasHeightForWidth());
        abv_result->setSizePolicy(sizePolicy4);
        abv_result->setFont(font);
        abv_result->setAlignment(Qt::AlignCenter);
        abv_result->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout_5->addWidget(abv_result);


        horizontalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        quit_button = new QPushButton(centralWidget);
        quit_button->setObjectName(QStringLiteral("quit"));

        horizontalLayout_3->addWidget(quit_button);

        reset_button = new QPushButton(centralWidget);
        reset_button->setObjectName(QStringLiteral("reset"));
        reset_button->setAutoDefault(true);

        horizontalLayout_3->addWidget(reset_button);

        calculate_button = new QPushButton(centralWidget);
        calculate_button->setObjectName(QStringLiteral("calculate"));
        calculate_button->setAutoDefault(true);
        calculate_button->setDefault(true);

        horizontalLayout_3->addWidget(calculate_button);


        verticalLayout->addLayout(horizontalLayout_3);

        setCentralWidget(centralWidget);
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
    ogcalc::retranslateUi()
    {
        setWindowTitle(QApplication::translate("ogcalc", "OG & ABV calculator", 0));
#ifndef QT_NO_TOOLTIP
        pg_label->setToolTip(QApplication::translate("ogcalc", "Present Gravity (density)", 0));
#endif // QT_NO_TOOLTIP
        pg_label->setText(QApplication::translate("ogcalc", "&PG:", 0));
        pg_entry->setSpecialValueText(QApplication::translate("ogcalc", "0.00", 0));
        pg_entry->setPrefix(QString());
#ifndef QT_NO_TOOLTIP
        ri_label->setToolTip(QApplication::translate("ogcalc", "Refractive Index", 0));
#endif // QT_NO_TOOLTIP
        ri_label->setText(QApplication::translate("ogcalc", "R&I:", 0));
#ifndef QT_NO_TOOLTIP
        cf_label->setToolTip(QApplication::translate("ogcalc", "Correction Factor", 0));
#endif // QT_NO_TOOLTIP
        cf_label->setText(QApplication::translate("ogcalc", "C&F:", 0));
#ifndef QT_NO_TOOLTIP
        og_label->setToolTip(QApplication::translate("ogcalc", "Original Gravity (density)", 0));
#endif // QT_NO_TOOLTIP
        og_label->setText(QApplication::translate("ogcalc", "OG:", 0));
        og_result->setText(QApplication::translate("ogcalc", "OGVAL", 0));
#ifndef QT_NO_TOOLTIP
        abv_entry->setToolTip(QApplication::translate("ogcalc", "Percent Alcohol By Volume", 0));
#endif // QT_NO_TOOLTIP
        abv_entry->setText(QApplication::translate("ogcalc", "ABV %:", 0));
        abv_result->setText(QApplication::translate("ogcalc", "ABVVAL", 0));
        quit_button->setText(QApplication::translate("ogcalc", "&Quit", 0));
        reset_button->setText(QApplication::translate("ogcalc", "&Reset", 0));
        calculate_button->setText(QApplication::translate("ogcalc", "&Calculate", 0));
    }

ogcalc::~ogcalc()
{
}

void
ogcalc::calculate()
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
ogcalc::reset()
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
