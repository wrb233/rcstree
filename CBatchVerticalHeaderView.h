#pragma once

/*
 * 这是为QTableView或者QTableWidget所写的一个批量操作控件。
 *
 * 它事实上就是View上的Vertical HeadView，只不错这里不再绘制行数，而是checkbox。
 *
 * 原理：在HeadView设置给View之后，通过HeadView返回的model，其实是View相关的Model，
 * 因此，我们将是否勾选的信息写入 model的第一列中的CheckedRole中，默认CheckedRole 为 Qt::UserRole+1
 * 如果和其他逻辑有冲突，可以修改CheckRole的实际值。然后重载paintSection，获取第一列的CheckRole的值，绘制
 * 相关图像即可。
 *
 * 由于View会在model变化时自动去重新绘制HeadView，因此剩下的交给Model/View固有逻辑即可。
 *
*/
#include <QHeaderView>
#include <QList>
#include <functional>
 
#define CheckedRole Qt::UserRole+1
 
class CBatchVerticalHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    CBatchVerticalHeaderView(QWidget *parent = 0);
 
    void SetAllSelected();
    void SetAllUnselected();
    void SetSelected(int section,bool selected);
    bool IsSelected(int section);
protected:
    //重载paint函数，改为绘制checkbox
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
 
private slots:
    void slotOnSectionClicked(int section);
};