#ifndef RECIPEROOTVIEW_H
#define RECIPEROOTVIEW_H

#include <QWidget>

#include "datacache.h"

namespace Ui {
class RecipeRootView;
}

class RecipeRootView : public QWidget
{
    Q_OBJECT

    DataCache *m_cache;

public:
    explicit RecipeRootView(DataCache *cache = nullptr, QWidget *parent = nullptr);
    ~RecipeRootView();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RecipeRootView *ui;
};

#endif // RECIPEROOTVIEW_H
