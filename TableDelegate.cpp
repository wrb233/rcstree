#include "TableDelegate.h"

TableDelegate::TableDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

TableDelegate::~TableDelegate()
{
}
void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QItemDelegate::paint(painter, option, index);
}

QSize TableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return QItemDelegate::sizeHint(option, index);
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
	const QModelIndex &index) const
{
	if (index.isValid())
	{
		QString displayValue =  index.model()->data(index,Qt::DisplayRole).toString();
		ObId obId = index.model()->data(index,Qt::UserRole).toULongLong();
		AType atype = index.model()->data(index,Qt::UserRole+1).toUInt();
		ObId parentId = index.model()->data(index,Qt::UserRole+3).toULongLong();
		OType otype = index.model()->data(index,Qt::UserRole+4).toUInt();
		DataType db = GlobalInfo::g_Database->getObjectType(otype)->getObjectAttribute(atype)->getDataType();
		switch(db)
		{
		case STRING_DATA:
			{
				if (atype==GlobalInfo::AT_IPAddrA||atype==GlobalInfo::AT_IPAddrB||atype==GlobalInfo::AT_IPAddress||atype==GlobalInfo::AT_McastAddrA||atype==GlobalInfo::AT_McastAddrB)
				{
					QLineEdit *editor = new QLineEdit(parent);
					editor->setValidator(new QRegExpValidator(QRegExp("(\\d{1,3})(\\.)(\\d{1,3})(\\.)(\\d{1,3})(\\.)(\\d{1,3})")));
					editor->installEventFilter(const_cast<TableDelegate*>(this));
					return editor;
				}else{
					QLineEdit *editor = new QLineEdit(parent);
					editor->setValidator(new QRegExpValidator(QRegExp("^(\\w|\\.){1,80}$")));
					editor->installEventFilter(const_cast<TableDelegate*>(this));
					return editor;
				}	
			}
		case LINK_DATA:
		case LONGLONG_DATA:
		case CONTAINER_DATA:
			{
				if (atype==GlobalInfo::AT_AlarmStateContainerLink||atype==GlobalInfo::AT_StateContainerLink)
				{
					QComboBox *editor = new QComboBox(parent);
					//editor->setEditable(true);
					ToolUtil::setComboxCustomData(editor, displayValue, atype, obId);
					editor->installEventFilter(const_cast<TableDelegate*>(this));			
					return editor;
				}else{
					CellDelegateWidget* editor = new CellDelegateWidget(displayValue, atype, otype,parentId, parent);					
					editor->installEventFilter(const_cast<TableDelegate*>(this));

					if (atype==GlobalInfo::AT_PartitionList)
					{
						QMessageBox::StandardButton reply;
						reply = QMessageBox::information(NULL, tr("save"), tr("You need to clear clone!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
						if (reply == QMessageBox::No)
						{
							return NULL;
						}else{
							//LOG_INFO(PROCESSLOG, "Need to clear clone");
						}
					}

					return editor;
				}
			}
		case MULTIPLE_CHOICE_DATA:
		case BOOLEAN_DATA:
			{
				QComboBox *editor = new QComboBox(parent);
				//editor->setEditable(true);
				ToolUtil::setComboxCustomData(editor, displayValue, atype, obId);
				editor->installEventFilter(const_cast<TableDelegate*>(this));			
				return editor;
			}
		case INTEGER_DATA:
			{
				QLineEdit *editor = new QLineEdit(parent);
				editor->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,10}$")));
				editor->installEventFilter(const_cast<TableDelegate*>(this));
				return editor;
			}
		case SHORT_DATA:
			{
				QLineEdit *editor = new QLineEdit(parent);
				editor->setValidator(new QRegExpValidator(QRegExp("^(\\d{1,5})$")));
				editor->installEventFilter(const_cast<TableDelegate*>(this));
				return editor;
			}
		case FLOAT_DATA:
			{
				QLineEdit *editor = new QLineEdit(parent);
				editor->setValidator(new QRegExpValidator(QRegExp("^(-?\\d{1,12})(\\.\\d{1,6})?$")));
				editor->installEventFilter(const_cast<TableDelegate*>(this));
				return editor;
			}
		}
	}
	return QItemDelegate::createEditor(parent, option, index);
}

void TableDelegate::test()
{
	
	
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QItemDelegate::setEditorData(editor, index);
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	if (index.isValid())
	{
		QString displayValue = index.model()->data(index, Qt::DisplayRole).toString();
		AType atype = index.model()->data(index,Qt::UserRole+1).toInt();
		OType otype = index.model()->data(index,Qt::UserRole+4).toUInt();
		DataType db = GlobalInfo::g_Database->getObjectType(otype)->getObjectAttribute(atype)->getDataType();
		switch(db)
		{
		case STRING_DATA:
			{
				QLineEdit *lineEditor = static_cast<QLineEdit *>(editor);
				model->setData(index, lineEditor->text(), Qt::DisplayRole);  
				break;
			}
		case LINK_DATA:
		case LONGLONG_DATA:
			{
				if (atype==GlobalInfo::AT_AlarmStateContainerLink||atype==GlobalInfo::AT_StateContainerLink)
				{
					QComboBox *comboBox = static_cast<QComboBox*>(editor);  
					QString text = comboBox->currentText();  
					model->setData(index, text, Qt::DisplayRole);
					model->setData(index, comboBox->itemData(comboBox->currentIndex(),Qt::UserRole), Qt::UserRole+2);
				}else{
					CellDelegateWidget *widget = static_cast<CellDelegateWidget *>(editor);
					QString text = widget->ui.lineEdit->text();
					model->setData(index, text, Qt::DisplayRole); 
					model->setData(index, widget->obId, Qt::UserRole+2);  
				}				
				break;
			}
		case CONTAINER_DATA:
			{
				CellDelegateWidget *widget = static_cast<CellDelegateWidget *>(editor);
				QString text = widget->ui.lineEdit->text();
				model->setData(index, text, Qt::DisplayRole); 
				model->setData(index, widget->obIds, Qt::UserRole+2);  
				break;
			}
		case MULTIPLE_CHOICE_DATA:
		case BOOLEAN_DATA:
			{
				QComboBox *comboBox = static_cast<QComboBox*>(editor);  
				QString text = comboBox->currentText();  
				model->setData(index, text, Qt::DisplayRole);
				model->setData(index, comboBox->currentIndex(), Qt::UserRole+2);
				break;
			}
		case INTEGER_DATA:
		case SHORT_DATA:
			{
				QLineEdit *lineEditor = static_cast<QLineEdit *>(editor);
				model->setData(index, QString::number(lineEditor->text().toInt()), Qt::DisplayRole);  
				break;
			}
		case FLOAT_DATA:
			{
				QLineEdit *lineEditor = static_cast<QLineEdit *>(editor);
				model->setData(index, QString::number(lineEditor->text().toFloat(),'f',6), Qt::DisplayRole);  
				break;
			}
		default:
			{
				QItemDelegate::setModelData(editor, model, index);				
				break;
			}
		}
		if (displayValue!=index.data(Qt::DisplayRole))
		{
			model->setData(index, QBrush(QColor(255, 0, 0)), Qt::TextColorRole);
			QStandardItemModel* tableModel = (QStandardItemModel*)model;
			qlonglong isNewInsert = index.data(Qt::UserRole).toLongLong();
			if (isNewInsert>0)
			{
				GlobalInfo::g_WriteDatas.append(tableModel->itemFromIndex(index));
				GlobalInfo::g_SaveButton->show();
			}
			//comcfgMW->centerWidget->getUi().saveButton->setVisible(true);
		}
		
		
	}else{
		QItemDelegate::setModelData(editor, model, index);
	}
}