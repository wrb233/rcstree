######################################################################
# Automatically generated by qmake (2.01a) Fri Dec 8 16:21:21 2017
######################################################################

TEMPLATE = app
TARGET   = rcstree
RESOURCES     = rcstree.qrc
TRANSLATIONS    = rcstree_zh_CN.ts								 
QMAKE_ORIG_TARGET = $(TARGET)

QT       += core gui
CONFIG   += plugin

DEPENDPATH += . GeneratedFiles

#commin pri
include($(CPS_ROOT)/CPS/compile/cps_common.pri)
               
unix {
    CONFIG(debug, debug|release) {
        LIBS += -lACEd -lquazipd
        LIBS += -ldatabased -lormd -lORMDatabased -lapplicationd -lUserMSd -lModelTranslated -ldbbackupd -lormdbcommitd -lormdbbackupd -lDeviceExplorer -lCpsWindowd -lxlsreader -lOperationLog -llog4cplus
    } else {       
        LIBS += -lACE -lquazip -lormdbpermit
        LIBS += -ldatabase -lorm -lORMDatabase -lapplication -lUserMS -lModelTranslate -ldbbackup -lormdbcommit -lormdbbackup -lDeviceExplorer -lCpsWindow -lxlsreader -lOperationLog -llog4cplus
    }
    VERSION=0.1.0
}

win32 {  
    RC_FILE                 = rcstree.rc

    CONFIG(debug, debug|release) {
        QMAKE_POST_LINK = $$QMAKE_COPY debug\\*.exe $(CPS_ENV)\\bin
        
        LIBS += ACEd.lib quazipd.lib
        LIBS += libdatabased.lib libormd.lib libORMDatabased.lib libapplicationd.lib UserMSd.lib ModelTranslated.lib libdbbackupd.lib ormdbcommitd.lib ormdbbackupd.lib DeviceExplorerd.lib CpsWindowd.lib libxlsd.lib OperationLogd.lib log4cplus.lib

    }
    else{
        QMAKE_POST_LINK = $$QMAKE_COPY release\\*.exe $(CPS_ENV)\\bin
        
        LIBS += ACE.lib quazip.lib libormdbpermit.lib
        LIBS += libdatabase.lib liborm.lib libORMDatabase.lib libapplication.lib UserMS.lib ModelTranslate.lib libdbbackup.lib ormdbcommit.lib ormdbbackup.lib DeviceExplorer.lib CpsWindow.lib libxls.lib OperationLog.lib log4cplus.lib
    }   
}

#install
{
      target.path = $$(CPS_ENV)/bin
      INSTALLS += target
}

# Input






HEADERS += AddFolderDialog.h\
           BatchComboxDialog.h\
           BatchLineEditDialog.h\
		   CBatchVerticalHeaderView.h\
		   CellDelegateWidget.h\
		   CenterTableView.h\
		   CheckSessionThread.h\
           common.h\
		   DataModel.h\
           DBUtil.h\
		   DPSPointImportDialog.h\
		   GlobalInfo.h\
		   logger_wrapper.h\
		   MVPointImportDialog.h\
		   MyEnum.h\
		   MyQProgressDialog.h\
		   PickPointDialog.h\
		   PickTreeDialog.h\
		   PluginInterface.h\
		   RCSCfgTreeView.h\
           RCSTreeApp.h\
		   RCSTreeMW.h\
		   resource.h\
		   TableDelegate.h\
		   ToolUtil.h\
		   TreeUtil.h\
		   version.h

           
		   
SOURCES += AddFolderDialog.cpp\
           BatchComboxDialog.cpp\
           BatchLineEditDialog.cpp\
		   CBatchVerticalHeaderView.cpp\
           CellDelegateWidget.cpp\
		   CenterTableView.cpp\
		   CheckSessionThread.cpp\
           DBUtil.cpp\
		   DPSPointImportDialog.cpp\
		   GlobalInfo.cpp\
		   main.cpp\
		   MVPointImportDialog.cpp\
		   MyQProgressDialog.cpp\
		   PickPointDialog.cpp\
		   PickTreeDialog.cpp\
		   RCSCfgTreeView.cpp\
           RCSTreeApp.cpp\
		   RCSTreeMW.cpp\
		   TableDelegate.cpp\
		   ToolUtil.cpp\
		   TreeUtil.cpp\
		   version.cpp

FORMS   += addfolder.ui\
		   batchcombox.ui\
		   batchlineedit.ui\
		   celldelegate.ui\
		   centertable.ui\
		   dpspointimport.ui\
		   mvpointimport.ui\
		   pickpoint.ui\
		   picktree.ui\
		   rcsconfigtree.ui\
		   rcstree.ui