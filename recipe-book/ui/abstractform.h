#ifndef ABSTRACTFORM_H
#define ABSTRACTFORM_H

#include "../models.h"
#include "../objecttypes.h"

#include <QDialog>
#include <QObject>

class AbstractForm : public QDialog {
  Q_OBJECT

protected:
  virtual bool validateForm() = 0;
  virtual void extractFormData() = 0;
  virtual void populateForm(const QVariantMap &data) = 0;
  virtual void clearForm() = 0;

  template <typename T> T *castObject(Storable *object) {
    T *casted = dynamic_cast<T *>(object);
    if (!casted) {
      throw std::runtime_error("Invalid object type for this form");
    }
    return casted;
  }

  ObjectTypes m_objectType;
  bool m_editMode = false;
  QVariantMap m_data;
  Storable *m_currentObject = nullptr;

public:
  explicit AbstractForm(ObjectTypes type, QWidget *parent = nullptr)
      : QDialog(parent), m_objectType(type), m_editMode(false) {}

  explicit AbstractForm(ObjectTypes type, Storable *object,
                        QWidget *parent = nullptr)
      : QDialog(parent), m_objectType(type), m_editMode(true),
        m_currentObject(object) {}

  bool isEditMode() const { return m_editMode; }
  ObjectTypes objectType() const { return m_objectType; }

signals:
  void createRequested(ObjectTypes type, QVariantMap &data);
  void updateRequested(ObjectTypes type, Storable *object,
                       const QVariantMap &data);
  void requestObject(ObjectTypes type, const QUuid &id);
  void requestObjects(ObjectTypes type, int offset = 0, int limit = 10);
  void requestObjectsCount(ObjectTypes type);
};

#endif // ABSTRACTFORM_H
