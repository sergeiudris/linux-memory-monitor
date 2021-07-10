/****************************************************************************
**
** Copyright (C) 2015 sergeiudris
** Contact: sergei.udris@gmail.com
**
** This file is part of Linux Memory Monitor
** Program uses /proc interface to calculate precise RAM usage for a group of processes,
** e.g. browser,database etc., excluding shared and not present(swapped out) memory pages
**
**
** Linux Memory Monitor is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** Linux Memory Monitor is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with Linux Memory Monitor.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#ifndef PAGESET_H
#define PAGESET_H

#include <cstdint>


namespace iproc{

typedef struct Pageset{

    uint_least64_t address_from = 0;
    uint_least64_t address_to = 0;

    /* if we need we can utize other properties present in map/smaps files*/

    //    std::string Flags,
    //                Offset,
    //                Device,
    //                Inode,
    //                Path;
    //
    //    uint32_t    Size = 0,
    //                Rss = 0,
    //                Pss = 0,
    //                Shared_Clean = 0,
    //                Shared_Dirty = 0,
    //                Private_Clean = 0,
    //                Private_Dirty = 0,
    //                Referenced = 0,
    //                Anonymous = 0,
    //                AnonHugePages = 0,
    //                Swap = 0,
    //                KernelPageSize = 0,
    //                MMUPAgeSize = 0,
    //                Locked = 0;
    //

} pageset;

}
#endif // PAGESET_H
