#include "gui.h"
#include "./ui_gui.h"
#include <QInputDialog>

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);

}

gui::~gui()
{
    delete ui;
}


void gui::on_addBlock_clicked() //add a block
{

    QString senderId=QInputDialog::getText(this,"input","Ingresar el sender_ID: "); //sender_id
    QString receiverId=QInputDialog::getText(this,"input","Ingresar el Receiver_ID: "); //receiver_id
    QString amount=QInputDialog::getText(this,"input","Ingresar la cantidad: "); //amount
    QString date=QInputDialog::getText(this,"input","Ingresar la fecha (YYYY-MM-DD HH:MM:SS) : "); //date

}


//void gui::on_pushButton_2_clicked() //delete
//{
//    QString temp1=QInputDialog::getText(this,"input","Ingrese su nombre"); //inputbox
////    QString temp1=ui->lineEdit->text();

//    ui->textBrowser->setText("Deleted Block: " + temp1);
//}


void gui::on_deleteRecord_clicked() // To delete a record
{
    int blockIndex=QInputDialog::getInt(this, "input","Ingresar en Block Index: "); //receive block index
    int recordIndex=QInputDialog::getInt(this, "input","Ingresar en Record Index: "); //receive record index
}


void gui::on_editBlock_clicked() //To edit a block
{
    int blockIndex=QInputDialog::getInt(this, "input","Ingresar en Block Index: "); //receive block index
    int recordIndex=QInputDialog::getInt(this, "input","Ingresar en Record Index: "); //receive record index
    QString senderId=QInputDialog::getText(this,"input","Ingresar el sender_ID: "); //sender_id
    QString receiverId=QInputDialog::getText(this,"input","Ingresar el Receiver_ID: "); //receiver_id
    QString amount=QInputDialog::getText(this,"input","Ingresar la cantidad: "); //amount
    QString date=QInputDialog::getText(this,"input","Ingresar la fecha (YYYY-MM-DD HH:MM:SS) : "); //date

}


void gui::on_showBlockchain_clicked() //Imprimir los valores
{
    ui->textBrowser->setText("kaslf;sdjfkalsdfs");

    ui->textBrowser->append("appended value");
}

