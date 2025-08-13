#include "stringeditdialog.h"

#include <QVBoxLayout>

StringEditDialog::StringEditDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Edit Item");
    resize(400, 300);

    textEdit = new QPlainTextEdit(this);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    layout->addWidget(buttonBox);
}

void StringEditDialog::setText(const QString &text) {
    textEdit->setPlainText(text);
}

QString StringEditDialog::getText() const {
    return textEdit->toPlainText();
}
