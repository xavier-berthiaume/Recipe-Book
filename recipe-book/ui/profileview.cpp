#include "profileview.h"
#include "ui_profileview.h"

#include "profileform.h"

ProfileView::ProfileView(QWidget *parent)
    : AbstractView(parent), ui(new Ui::ProfileView) {
  ui->setupUi(this);
}

ProfileView::~ProfileView() { delete ui; }

void ProfileView::handleObjectCreated(ObjectTypes type, Storable *object) {}

void ProfileView::handleObjectLoaded(ObjectTypes type, Storable *object) {}

void ProfileView::on_createButton_clicked() {
  ProfileForm *form = ProfileForm::createForm(this);

  connect(form, &ProfileForm::createRequested, this,
          &ProfileView::createObjectRequested);

  form->exec();
}
