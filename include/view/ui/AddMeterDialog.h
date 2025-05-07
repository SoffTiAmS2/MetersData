#ifndef ADDMETERDIALOG_H
#define ADDMETERDIALOG_H

#include <QDialog>
#include <memory>

class AbstractMeter;

namespace Ui {
class AddMeterDialog;
}

class AddMeterDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddMeterDialog(QWidget* parent = nullptr);
    ~AddMeterDialog();

    std::unique_ptr<AbstractMeter> getMeter() const;

private slots:
    void onTypeChanged(const QString& type);

private:
    void hideAllExtraFields();
    Ui::AddMeterDialog* ui;
};

#endif // ADDMETERDIALOG_H