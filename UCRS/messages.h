#ifndef MESSAGES_H
#define MESSAGES_H
#include <QMessageBox>
#include <QWidget>

inline void showError(QWidget* parent, const QString& message) {
    QMessageBox::critical(parent, "Error", message);
}

inline void showSuccess(QWidget* parent, const QString& message) {
    QMessageBox::information(parent, "Success", message);
}

inline bool confirmAction(QWidget* parent, const QString& action) {
    return QMessageBox::question(parent, "Confirm Action", action, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}



#endif // MESSAGES_H
