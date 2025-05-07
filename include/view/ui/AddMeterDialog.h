#pragma once

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
    bool validateInput() const;
    Ui::AddMeterDialog* ui;
};