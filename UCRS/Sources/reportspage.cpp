#include "../Headers/reportspage.h"
#include "Headers/dashboard.h"
#include "ui_reportspage.h"
#include "../Headers/user.h"
#include "../Headers/student.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include "../Headers/instructor.h"
#include "../Headers/student.h"
#include<QMessageBox>
#include <QFileDialog>

ReportsPage::ReportsPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReportsPage)
{
    ui->setupUi(this);
    ui->comboBoxReportType->addItem("Student Schedule");
    ui->comboBoxReportType->addItem("Course Enrollment");
    ui->comboBoxReportType->addItem("Instructor Workload");

}

ReportsPage::~ReportsPage()
{
    delete ui;
}

void ReportsPage::setBanner(Banner *b)
{
    banner = b;
}



void ReportsPage::on_generatePushButton_clicked()
{
    User* user = banner->getCurrentUser();
    auto Courses = banner->listCourses();
    QString selectedReport = ui->comboBoxReportType->currentText();
    ui->reportWidget->clearContents();
    ui->reportWidget->setRowCount(0);
        if(selectedReport == "Student Schedule" )
        {
            Student* student= dynamic_cast<Student*>(user);
            if(!student)
            {
             QMessageBox::warning(this, "Error", "Only students can view their schedule.");
                return;
            }
            auto registeredCourses=student->getCourses();
            const QStringList headers={"Course ID","Course Name","Instructor","Schedule"};
            ui->reportWidget->setColumnCount(headers.size());
            ui->reportWidget->setHorizontalHeaderLabels(headers);
            ui->reportWidget->setRowCount(registeredCourses.size());
            int row = 0;
            for (Course* course : registeredCourses) {
                ui->reportWidget->setItem(row, 0, new QTableWidgetItem(course->getCourseID()));
                ui->reportWidget->setItem(row, 1, new QTableWidgetItem(course->getCourseName()));
                Instructor* instructor = course->getInstructor();
                ui->reportWidget->setItem(row, 2, new QTableWidgetItem(instructor ? (instructor->getName()) : "N/A"));
                ui->reportWidget->setItem(row, 3, new QTableWidgetItem(course->getScheduleTime()));
                row++;
            }
            ui->reportWidget->resizeColumnsToContents();
        }
        else if(selectedReport == "Course Enrollment")
        {
            const QStringList headers={"Course ID", "Course Name", "Instructor", "Credit Hours", "Schedule", "Enrolled", "Capacity"};
            ui->reportWidget->setColumnCount(headers.size());
            ui->reportWidget->setHorizontalHeaderLabels(headers);
            ui->reportWidget->setRowCount(Courses.size());
            int row=0;
            for(const auto &c: Courses)
            {
                Course*course = c.second;
                ui->reportWidget->setItem(row, 0, new QTableWidgetItem(course->getCourseID()));
                ui->reportWidget->setItem(row, 1, new QTableWidgetItem(course->getCourseName()));
                Instructor* instructor = course->getInstructor();
                ui->reportWidget->setItem(row, 2, new QTableWidgetItem(instructor ? (instructor->getName()) : "N/A"));
                ui->reportWidget->setItem(row, 3, new QTableWidgetItem(QString::number(course->getCreditHours())));
                ui->reportWidget->setItem(row, 4, new QTableWidgetItem(course->getScheduleTime()));
                ui->reportWidget->setItem(row, 5, new QTableWidgetItem(QString::number(course->getEnrolledStudentsNumber())));
                ui->reportWidget->setItem(row, 6, new QTableWidgetItem(QString::number(course->getCapacity())));
                row++;
            }
            ui->reportWidget->resizeColumnsToContents();

        }
       else if(selectedReport == "Instructor Workload")
        {
            Instructor* instructor= dynamic_cast<Instructor*>(user);
            if(!instructor)
            {
                QMessageBox::warning(this, "Error", "Only Insructors can access this");
                return;
            }
            auto registerdCourses = instructor->getCourses();
            const QStringList headers={"Instructor","CourseID","Course Name","CreditHours","Schedule","Enrolled"};
            ui->reportWidget->setColumnCount(headers.size());
            ui->reportWidget->setHorizontalHeaderLabels(headers);
            ui->reportWidget->setRowCount(registerdCourses.size());
            int row=0;
                for(Course* course:registerdCourses)
                {
                    ui->reportWidget->setItem(row, 0, new QTableWidgetItem(instructor->getName()));
                    ui->reportWidget->setItem(row, 1, new QTableWidgetItem(course->getCourseID()));
                    ui->reportWidget->setItem(row, 2, new QTableWidgetItem(course->getCourseName()));
                    ui->reportWidget->setItem(row, 3, new QTableWidgetItem(QString::number(course->getCreditHours())));
                    ui->reportWidget->setItem(row, 4, new QTableWidgetItem(course->getScheduleTime()));
                    ui->reportWidget->setItem(row, 5, new QTableWidgetItem(QString::number(course->getEnrolledStudentsNumber())));
                    row++;
                }
            ui->reportWidget->resizeColumnsToContents();
        }
}
void ReportsPage::on_exportPushButton_clicked()
{
    if (ui->reportWidget->rowCount() == 0 && ui->reportWidget->columnCount() == 0) {
        QMessageBox::warning(this, "Export Error", "Please generate a report to export");
        return;
    }

    QString selectedFilter;
    QString extension;
    QString separator;
    if(ui->txtRadioButton->isChecked())
        {
            selectedFilter= "Text Files (*.txt)";
            extension = ".txt";
            separator = "\t";
        }
        else if(ui->csvRadioButton->isChecked())
        {
            selectedFilter= "CSV files (*.csv)";
            extension=".csv";
            separator=",";
        }
        else
        {
        QMessageBox::warning(this, "Export Error", "Please select a file format to export ((.txt) or (.csv))");
            return;
        }

    QString generatedReport = QFileDialog::getSaveFileName(this, "Export Report","", selectedFilter);
    if(generatedReport.isEmpty())
    {
        return;
    }
    if(!generatedReport.endsWith(extension, Qt::CaseSensitive))
    {
        generatedReport+=extension;
    }
    QFile file(generatedReport);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::warning(this, "Export Error", "Cannot open this file for writing");
    }
    QTextStream stream(&file);
    QStringList headers;
    for(int col=0;col< ui->reportWidget->columnCount();++col)
    {
        QTableWidgetItem* headerItem= ui->reportWidget->horizontalHeaderItem(col);
        headers<<(headerItem ? headerItem->text(): "");
    }
    stream<<headers.join(separator)<<"\n";
    for (int row=0; row<ui->reportWidget->rowCount();row++)
    {
        QStringList rowData;
        for(int col=0;col<ui->reportWidget->columnCount(); ++col)
        {
            QTableWidgetItem* item= ui->reportWidget->item(row,col);
            QString cell= item ? item->text(): "";
            if((separator == "," && (cell.contains(',')))|| cell.contains("\""))
            {
                cell.replace("\"","\"\\");
                cell = "\"" + cell+ "\"";
            }
            rowData<<cell;
        }
        stream<< rowData.join(separator)<<"\n";
    }
    file.close();
    QMessageBox::information(this, "Export", "Report exported successfully to:\n"+generatedReport);
}

void ReportsPage::on_pushButton_clicked()
{
    Dashboard* d = new Dashboard(NULL);
    d->setBanner(banner);
    this->close();
    d->show();
}
