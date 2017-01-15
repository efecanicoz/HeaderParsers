
/*******************************************************************************
 *  The "New BSD License" : http://www.opensource.org/licenses/bsd-license.php  *
 ********************************************************************************

 Copyright (c) 2010, Mark Turney
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of the <organization> nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************/

#include "Display.h"

namespace svg
{


    std::string elemStart(std::string const & element_name)
    {
        return "\t<" + element_name + " ";
    }

    std::string elemEnd(std::string const & element_name)
    {
        return "</" + element_name + ">\n";
    }

    std::string emptyElemEnd()
    {
        return "/>\n";
    }

    optional<Point> getMinPoint(std::vector<Point> const & points)
    {
        if (points.empty())
            return optional<Point>();

        Point min = points[0];
        for (unsigned i = 0; i < points.size(); ++i) {
            if (points[i].x < min.x)
                min.x = points[i].x;
            if (points[i].y < min.y)
                min.y = points[i].y;
        }
        return optional<Point>(min);
    }

    optional<Point> getMaxPoint(std::vector<Point> const & points)
    {
        if (points.empty())
            return optional<Point>();

        Point max = points[0];
        for (unsigned i = 0; i < points.size(); ++i) {
            if (points[i].x > max.x)
                max.x = points[i].x;
            if (points[i].y > max.y)
                max.y = points[i].y;
        }
        return optional<Point>(max);
    }

    // Convert coordinates in user space to SVG native space.
    double translateX(double x, Layout const & layout)
    {
        if (layout.origin == Layout::BottomRight || layout.origin == Layout::TopRight)
            return layout.dimensions.width - ((x + layout.origin_offset.x) * layout.scale);
        else
            return (layout.origin_offset.x + x) * layout.scale;
    }

    double translateY(double y, Layout const & layout)
    {
        if (layout.origin == Layout::BottomLeft || layout.origin == Layout::BottomRight)
            return layout.dimensions.height - ((y + layout.origin_offset.y) * layout.scale);
        else
            return (layout.origin_offset.y + y) * layout.scale;
    }

    double translateScale(double dimension, Layout const & layout)
    {
        return dimension * layout.scale;
    }

    template <typename T>
    std::string vectorToString(std::vector<T> collection, Layout const & layout)
    {
        std::string combination_str;
        for (unsigned i = 0; i < collection.size(); ++i)
            combination_str += collection[i].toString(layout);

        return combination_str;
    }

}
