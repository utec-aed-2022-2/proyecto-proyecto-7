#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);
    ~gui();

private slots:
    void on_addBlock_clicked();

    void on_deleteRecord_clicked();

    void on_editBlock_clicked();

    void on_showBlockchain_clicked();
private:
    Ui::gui *ui;


};
#endif // GUI_H
