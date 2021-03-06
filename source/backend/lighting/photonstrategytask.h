/*******************************************************************************
 * photonstrategytask.h
 *
 * ---------------------------------------------------------------------------
 * Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
 * Copyright 1991-2013 Persistence of Vision Raytracer Pty. Ltd.
 *
 * POV-Ray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * POV-Ray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------
 * POV-Ray is based on the popular DKB raytracer version 2.12.
 * DKBTrace was originally written by David K. Buck.
 * DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
 * ---------------------------------------------------------------------------
 * $File: //depot/public/povray/3.x/source/backend/lighting/photonstrategytask.h $
 * $Revision: #1 $
 * $Change: 6069 $
 * $DateTime: 2013/11/06 11:59:40 $
 * $Author: chrisc $
 *******************************************************************************/

#ifndef PHOTONSTRATEGYTASK_H
#define PHOTONSTRATEGYTASK_H

#include "base/povms.h"
#include "backend/frame.h"
#include "backend/render/trace.h"
#include "backend/control/messagefactory.h"
#include "backend/colour/colutils.h"
#include "backend/render/rendertask.h"
#include "backend/parser/parse.h"
#include "backend/lighting/photonshootingstrategy.h"

namespace pov
{

using namespace pov_base;

class PhotonStrategyTask : public RenderTask
{
	public:
		MessageFactory messageFactory;
		Timer timer;

		PhotonShootingStrategy* strategy;

		PhotonStrategyTask(ViewData *vd, PhotonShootingStrategy* strategy);
		~PhotonStrategyTask();

		void Run();
		void Stopped();
		void Finish();

		void SendProgress();

		void SearchThroughObjectsCreateUnits(vector<ObjectPtr>& Objects, LightSource *Light);
	private:
		class CooperateFunction : public Trace::CooperateFunctor
		{
			public:
				CooperateFunction(Task& t) : task(t) { }
				virtual void operator()() { task.Cooperate(); }
			private:
				Task& task;
		};

		CooperateFunction cooperate;
};

}
#endif
