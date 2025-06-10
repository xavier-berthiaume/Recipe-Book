#ifndef PROFILEROOTVIEW_H
#define PROFILEROOTVIEW_H

#include <QWidget>

namespace Ui {
class ProfileRootView;
}

class ProfileRootView : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileRootView(QWidget *parent = nullptr);
    ~ProfileRootView();

private:
    Ui::ProfileRootView *ui;
};

#endif // PROFILEROOTVIEW_H
