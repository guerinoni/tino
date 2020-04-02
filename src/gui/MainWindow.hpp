#pragma once

#include "../gui/MdiChild.hpp"
#include "../serialcom/ModbusCom.hpp"

#include <QMainWindow>

#include <memory>

class Configuration;

class QStandardItem;

namespace Ui {
class MainWindow;
} // namespace Ui

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
    void connectClient();
    void disconnectClient();

private:
    Ui::MainWindow *ui;

    QToolBar *m_toolbar{nullptr};
    std::unique_ptr<Configuration> m_config;
    enum class Actions { Open, Connect, Disconnect, Settins, About, Quit };
    std::unordered_map<Actions, std::unique_ptr<QAction>> m_actions;
    std::unique_ptr<QDockWidget> m_configViewDock;

    QString m_importFilePath;

    std::unique_ptr<ModbusCom> m_modbus;
    std::vector<MdiChild *> m_mdiChilds;

    struct Error
    {
        bool error{false};
        QString message{};
    };

    void createActions();
    void createMenuBar();
    void createToolBar();
    Error importConfig(const QString &filename);
    void createWidgetRequested(QStandardItem *item);
    void saveSettings();
    void loadSettings();
    bool setFocusIfAlreadyExists(const Block &block) const;

    friend class tst_MainWindow;
};
