// Copyright (C) 2007, 2008, 2009 Marc Betoule

// This file is part of SkOP.

// SkOP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
  
// SkOP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with SkOP.  If not, see <http://www.gnu.org/licenses/>.


/**
 * \file main.cpp
 * \brief Application launcher
 */

#include <QApplication>

#include "skop.h"

int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     //Q_INIT_RESOURCE(ressources);
     Skop mainWin;
     mainWin.show();
     return app.exec();
 }
