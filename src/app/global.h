/*
 *	Dualword-wiki is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Dualword-wiki is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Dualword-wiki. If not, see <http://www.gnu.org/licenses/>.
 *
*/

#ifndef SRC_APP_GLOBAL_H_
#define SRC_APP_GLOBAL_H_

#include "app/DualwordWikiApp.h"
#include "gui/MainWindow.h"

#if defined(mainApp)
#undef mainApp
#endif
#define mainApp (DualwordWikiApp::instance())

#if defined(mainWin)
#undef mainWin
#endif
#define mainWin (DualwordWikiApp::instance()->window())



#endif /* SRC_APP_GLOBAL_H_ */
