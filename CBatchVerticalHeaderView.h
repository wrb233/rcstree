#pragma once

/*
 * ����ΪQTableView����QTableWidget��д��һ�����������ؼ���
 *
 * ����ʵ�Ͼ���View�ϵ�Vertical HeadView��ֻ�������ﲻ�ٻ�������������checkbox��
 *
 * ԭ����HeadView���ø�View֮��ͨ��HeadView���ص�model����ʵ��View��ص�Model��
 * ��ˣ����ǽ��Ƿ�ѡ����Ϣд�� model�ĵ�һ���е�CheckedRole�У�Ĭ��CheckedRole Ϊ Qt::UserRole+1
 * ����������߼��г�ͻ�������޸�CheckRole��ʵ��ֵ��Ȼ������paintSection����ȡ��һ�е�CheckRole��ֵ������
 * ���ͼ�񼴿ɡ�
 *
 * ����View����model�仯ʱ�Զ�ȥ���»���HeadView�����ʣ�µĽ���Model/View�����߼����ɡ�
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
    //����paint��������Ϊ����checkbox
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
 
private slots:
    void slotOnSectionClicked(int section);
};