#ifndef PROFILEROOTVIEW_H
#define PROFILEROOTVIEW_H

#include <QWidget>
#include <QStackedWidget>

#include "profilelistmodel.h"
#include "profilefactory.h"

namespace Ui {
class ProfileRootView;
}

class ProfileRootView : public QWidget
{
    Q_OBJECT

    Ui::ProfileRootView *ui;

    QStackedWidget *m_stackedWidget;
    ProfileListModel *m_model;
    ProfileFactory *m_factory;

    QModelIndex m_editProfile = QModelIndex();
    bool m_editMode = false;

public:
    explicit ProfileRootView(QWidget *parent = nullptr);
    ~ProfileRootView();

private slots:
    void on_createButton_clicked();
    void on_cancelButton_clicked();
    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_confirmButton_clicked();
};

#endif // PROFILEROOTVIEW_H
