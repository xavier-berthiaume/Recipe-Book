#ifndef PROFILEROOTVIEW_H
#define PROFILEROOTVIEW_H

#include <QWidget>
#include <QStackedWidget>

#include "profilelistmodel.h"
#include "profilefactory.h"
#include "datacache.h"

namespace Ui {
class ProfileRootView;
}

class ProfileRootView : public QWidget
{
    Q_OBJECT

    Ui::ProfileRootView *ui;

    DataCache *m_cache;

    QStackedWidget *m_stackedWidget;
    ProfileListModel *m_model;
    ProfileFactory *m_factory;

    QModelIndex m_editProfile = QModelIndex();
    bool m_editMode = false;

public:
    explicit ProfileRootView(DataCache *cache = nullptr, QWidget *parent = nullptr);
    ~ProfileRootView();

private slots:
    void on_createButton_clicked();
    void on_cancelButton_clicked();
    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_confirmButton_clicked();

    void deleteProfile(const QModelIndex &index);
    void selectProfile(const QModelIndex &index);

    void profileCreated(QProfile *profile); // Set the cache as the parent to the QProfile object

signals:
    void selectedProfileChanged(QProfile *profile);
};

#endif // PROFILEROOTVIEW_H
