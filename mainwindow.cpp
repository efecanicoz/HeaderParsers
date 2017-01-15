#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    ui->asciiBrowser->setFont(fixedFont);
    ui->hexBrowser->setFont(fixedFont);

    ui->sectionContentBrowser->setReadOnly(true);
    ui->hexBrowser->setReadOnly(true);
    ui->asciiBrowser->setReadOnly(true);
    ui->sectionContentBrowser->setUndoRedoEnabled(false);
    ui->asciiBrowser->setUndoRedoEnabled(false);
    ui->hexBrowser->setUndoRedoEnabled(false);
    connect(ui->asciiBrowser->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->hexBrowser->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->hexBrowser->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->asciiBrowser->verticalScrollBar(), SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::format_for_hex_view(std::vector<uint8_t> byte_array)
{
    std::stringstream ss;
    uint64_t i;
    for(i = 0; i < byte_array.size(); i++)
    {
        if(i % 16 == 0 && i != 0)
        {
            ss << "\n";
        }
        ss << std::setfill('0') << std::setw(2) << std::hex << (uint32_t) byte_array[i] << " ";
    }
    return QString::fromStdString(ss.str());
}

QString MainWindow::format_for_ascii_view(std::vector<uint8_t> byte_array)
{
    std::stringstream ss;
    uint64_t i;
    for(i = 0; i < byte_array.size(); i++)
    {
        if(i % 16 == 0 && i != 0)
        {
            ss << "\n";
        }
        if(byte_array[i] > 0x1F && byte_array[i] < 0x80)
            ss << byte_array[i];
        else
            ss << ".";
    }
    return QString::fromStdString(ss.str());
}

void MainWindow::on_pushButton_clicked()
{
    QStringList *stringList;
    QStringListModel *listModel;
    std::vector<std::string> sectionList;
    std::vector<uint8_t> headerHexContent;
    exePath = QFileDialog::getOpenFileName(this, tr("Select executable file.."),tr("Files (*)"));
    ui->filePathBox->setText(exePath);
    /*Read file*/
    exeObj = readFile(exePath.toStdString());
    if(exeObj == NULL)
    {
        /*Invalid file*/
        return;
    }
    /*Fill sectionListView*/
    stringList = new QStringList();
    sectionList = exeObj->getSectionNames();
    for(std::string section : sectionList)
    {
        stringList->append(QString::fromStdString(section));
    }
    listModel = new QStringListModel(*stringList, NULL);
    ui->sectionListView->setModel(listModel);
    ui->sectionContentBrowser->setPlainText(QString::fromStdString(exeObj->getHeaderInfo()));
    headerHexContent = exeObj->getHexHeader();
    ui->asciiBrowser->setPlainText(format_for_ascii_view(headerHexContent));
    ui->hexBrowser->setPlainText(format_for_hex_view(headerHexContent));
}

void MainWindow::on_sectionListView_doubleClicked(const QModelIndex &index)
{
    std::vector<uint8_t> hexContent;
    std::string content;
    QString itemText = index.data(Qt::DisplayRole).toString();
    hexContent = exeObj->getHexSectionContent(itemText.toStdString());
    content = exeObj->getSectionContent(itemText.toStdString(), ui->linearSweepButton->isChecked());

    ui->sectionContentBrowser->setUpdatesEnabled(false);
    ui->asciiBrowser->setUpdatesEnabled(false);
    ui->hexBrowser->setUpdatesEnabled(false);
    ui->sectionContentBrowser->setPlainText(QString::fromStdString(content));
    ui->asciiBrowser->setPlainText(format_for_ascii_view(hexContent));
    ui->hexBrowser->setPlainText(format_for_hex_view(hexContent));
    ui->sectionContentBrowser->setUpdatesEnabled(true);
    ui->asciiBrowser->setUpdatesEnabled(true);
    ui->hexBrowser->setUpdatesEnabled(true);

}

void MainWindow::on_pushButton_2_clicked()
{
    QModelIndexList selected_section_list = ui->sectionListView->selectionModel()->selectedIndexes();
    std::string selected_section = selected_section_list.at(0).data(Qt::DisplayRole).toString().toStdString();
    exeObj->create_svg(selected_section);
}
