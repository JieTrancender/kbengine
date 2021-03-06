// Copyright 2008-2018 Yolo Technogies, Inc. All Rights Reserved. https://www.comblockengine.com

#include "space.h"	
#include "spaces.h"	
#include "loadnavmesh_threadtasks.h"
#include "server/serverconfig.h"
#include "common/deadline.h"
#include "navigation/navigation.h"

namespace KBEngine{

//-------------------------------------------------------------------------------------
bool LoadNavmeshTask::process()
{
	Navigation::getSingleton().loadNavigation(resPath_, params_);
	return false;
}

//-------------------------------------------------------------------------------------
thread::TPTask::TPTaskState LoadNavmeshTask::presentMainThread()
{
	NavigationHandlePtr pNavigationHandle = Navigation::getSingleton().findNavigation(resPath_);
	
	Space* pSpace = Spaces::findSpace(spaceID_);
	if(pSpace == NULL || !pSpace->isGood())
	{
		ERROR_MSG(fmt::format("LoadNavmeshTask::presentMainThread(): not found space({})\n",
			spaceID_));
	}
	else
	{
		pSpace->onLoadedSpaceGeometryMapping(pNavigationHandle);
	}
	
	return thread::TPTask::TPTASK_STATE_COMPLETED; 
}

//-------------------------------------------------------------------------------------
}
