#pragma once

#include <MdiChild.hpp>
#include <ModbusCom.hpp>
#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Configuration;
class QStandardItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void closeEvent(QCloseEvent *event) override;

signals:
    void importFinished(QPrivateSignal);

private slots:
    void selectFile();
    void createConfigView();
    void customConfigViewContextMenu(const QPoint &point);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<Configuration> m_config;
    std::unique_ptr<QAction> m_serialConnect;
    std::unique_ptr<QAction> m_serialSettings;
    std::unique_ptr<QDockWidget> m_configViewDock;

    QString m_importFilePath;

    std::unique_ptr<ModbusCom> m_modbus;
    std::vector<MdiChild *> m_mdiChilds;

    struct Error
    {
        bool error{false};
        QString message{};
    };

    void createMenuBar();
    Error importConfig(const QString &filename);
    void createWidgetRequested(QStandardItem *item);
    void saveSettings();
    void loadSettings();
    bool setFocusIfAlreadyExists(const Block &block) const;

    friend class tst_MainWindow;
};
