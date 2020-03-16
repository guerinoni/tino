#include <Bitset.hpp>
#include <ConfigViewFactory.hpp>
#include <QDir>
#include <QDockWidget>
#include <QStandardItemModel>
#include <QTreeView>
#include <QtTest>

class tst_ConfigView : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void checkEmptyProtocol();
    void checkSimpleProtocol();
    void avoidShowEmptyField();

private:
    Protocol m_protocol;

    bool forEach(QAbstractItemModel *model, QModelIndex parent = QModelIndex());
};

void tst_ConfigView::initTestCase()
{
    auto bitset = std::make_unique<Bitset>("bitset 1", "bitset 1 description", 0x10);
    for (size_t i = 0; i < 8; ++i) {
        bitset->setAt(i, false, {}, QStringLiteral("description_%1").arg(i));
    }

    Block bl;
    bl.description = "block";
    bl.elements.emplace_back(std::move(bitset));

    m_protocol.blocks.emplace_back(std::move(bl));
}

void tst_ConfigView::checkEmptyProtocol()
{
    auto dock = ConfigViewFactory().makeConfigView({});
    const auto view = qobject_cast<QTreeView *>(dock->widget());
    const auto model = qobject_cast<QStandardItemModel *>(view->model());
    QVERIFY(dock != Q_NULLPTR);
    QVERIFY(view != Q_NULLPTR);
    QVERIFY(model != Q_NULLPTR);
    QVERIFY(model->rowCount() == 0);
}

void tst_ConfigView::checkSimpleProtocol()
{
    auto dock = ConfigViewFactory().makeConfigView(m_protocol);
    const auto view = qobject_cast<QTreeView *>(dock->widget());
    const auto model = qobject_cast<QStandardItemModel *>(view->model());
    QVERIFY(dock != Q_NULLPTR);
    QVERIFY(view != Q_NULLPTR);
    QVERIFY(model != Q_NULLPTR);
    QVERIFY(model->rowCount() == 1);

    auto root = model->data(model->index(0, 0));
    QVERIFY(root.isValid());
    QCOMPARE(root.toString(), "block");
}

void tst_ConfigView::avoidShowEmptyField()
{
    auto dock = ConfigViewFactory().makeConfigView(m_protocol);
    const auto view = qobject_cast<QTreeView *>(dock->widget());
    const auto model = qobject_cast<QStandardItemModel *>(view->model());
    QVERIFY(forEach(model));
}

bool tst_ConfigView::forEach(QAbstractItemModel *model, QModelIndex parent)
{
    for (int r = 0; r < model->rowCount(parent); ++r) {
        QModelIndex index = model->index(r, 0, parent);
        QVariant name = model->data(index);
        if (name.toString().isEmpty()) {
            return false;
        }

        if (model->hasChildren(index)) {
            return forEach(model, index);
        }
    }

    return true;
}

QTEST_MAIN(tst_ConfigView)

#include "tst_ConfigView.moc"
