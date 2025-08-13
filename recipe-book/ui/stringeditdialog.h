#ifndef STRINGEDITDIALOG_H
#define STRINGEDITDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QDialogButtonBox>

class StringEditDialog : public QDialog
{
    Q_OBJECT

    QPlainTextEdit *textEdit;
    QDialogButtonBox *buttonBox;

public:
    explicit StringEditDialog(QWidget *parent = nullptr);

    QString getText() const;
    void setText(const QString &text);

};

#endif // STRINGEDITDIALOG_H
