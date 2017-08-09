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

#include "DualwordWikiApp.h"

#include <iostream>

int main(int argc, char *argv[]) {
	DualwordWikiApp app(argc, argv);
	try {
		app.start();
		return app.exec();
	} catch (std::exception& e) {
		std::cerr << "Dualword-wiki:" << e.what() << std::endl;
	}catch (...) {
		std::cerr << "Dualword-wiki:Uncaught exception" << std::endl;
	}
}
